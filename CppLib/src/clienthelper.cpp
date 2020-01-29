#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "xmlrequest.h"
#include "tcpipclient.h"
#include "clienthelper.h"
#include "parameterset.h"
#include "parameterkeys.h"
#include "responsecontainer.h"
#include "libraryversion.h"

namespace ChipDnaClientLib {

	struct EventThreadArgs {

		std::string* eventType;
		Response * response;

		EventThreadArgs() {
			eventType = nullptr;
			response = nullptr;
		}

		EventThreadArgs(std::string * eventName, Response * eventData) : eventType(eventName), response(eventData) {}

		~EventThreadArgs() {
			if (eventType) {
				delete eventType;
				eventType = nullptr;
			}

			if (response) {
				delete response;
				response = nullptr;
			}
		}
	};

	TcpIpClient tcpIpClient;
	pthread_mutex_t event_mutex;
	pthread_cond_t event_cond;
	std::vector<EventThreadArgs *> incomingEvents;
	bool isExiting = false;

	static std::string getOsName()
	{
#ifdef _WIN32
		return "Windows 32-bit";
#elif _WIN64
		return "Windows 64-bit";
#elif __unix || __unix__
		return "Unix";
#elif __APPLE__ || __MACH__
		return "Mac OSX";
#elif __linux__
		return "Linux";
#elif __FreeBSD__
		return "FreeBSD";
#else
		return "Other";
#endif
	}

	static bool areThereWaitingEvents() {
		pthread_mutex_lock(&event_mutex);
		bool areThereWaitingEvents = !incomingEvents.empty();
		pthread_mutex_unlock(&event_mutex);

		return areThereWaitingEvents;
	}

#pragma region Constructors

	ClientHelper::ClientHelper(const std::string terminalId, const std::string address, const int port) {
		this->init(terminalId, address, port, false);
	}

	ClientHelper::ClientHelper(const std::string terminalId, const std::string address, const int port, const bool enableSSL) {
		this->init(terminalId, address, port, enableSSL);
	}

	ClientHelper::ClientHelper(const std::string posId, const std::string address, const int port, const bool enableSSL, std::string apiKey) {
		this->apiKey = apiKey;
		this->init(posId, address, port, enableSSL);
	}

	ClientHelper::ClientHelper(const std::string posId, const std::string address, const int port, std::string apiKey) {
		this->apiKey = apiKey;
		this->init(posId, address, port, false);
	}

	ClientHelper::ClientHelper(const std::string address, const int port, std::string apiKey) : ClientHelper("default", address, port, apiKey)
	{
	}

	ClientHelper::ClientHelper(const std::string address, const int port, const bool enableSSL, std::string apiKey) : ClientHelper("default", address, port, enableSSL, apiKey)
	{
	}

	void ClientHelper::init(const std::string identifier, const std::string address, const int port, const bool enableSSL) {
		pthread_mutex_init(&connectMutex, nullptr);
		pthread_mutex_init(&event_mutex, nullptr);
		pthread_cond_init(&event_cond, nullptr);
		isExiting = false;
		this->identifier = identifier;
		this->address = address;
		this->port = port;
		this->isSslEnabled = enableSSL;
		tcpIpClient = TcpIpClient();
		incomingEvents = std::vector<EventThreadArgs*>();

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		pthread_create(&reconnectionThread, &attr, &ClientHelper::reconnect, static_cast<void *>(this));

		pthread_attr_destroy(&attr);
		
#ifdef  _WIN32
		Sleep(3000);
#else
		usleep(3000 * 1000);
#endif
	}

	ClientHelper::~ClientHelper() {
		isExiting = true;

		pthread_join(reconnectionThread, nullptr);

		tcpIpClient.Disconnect();

		pthread_mutex_unlock(&connectMutex);
		pthread_mutex_destroy(&connectMutex);

		pthread_cond_broadcast(&event_cond);
		pthread_cond_destroy(&event_cond);

		pthread_mutex_unlock(&event_mutex);
		pthread_mutex_destroy(&event_mutex);
		
#ifdef  _WIN32
		Sleep(500);
#else
		usleep(500 * 1000);
#endif
	}

#pragma endregion

#pragma region Connection Methods

	bool ClientHelper::connect() {
		pthread_mutex_lock(&connectMutex);

		if (tcpIpClient.IsConnected()) {
			pthread_mutex_unlock(&connectMutex);
			return true;
		}

		//register disconnection event before connect so that connection failure is detected
		auto disconnectionEvent = std::bind(&ClientHelper::onClientDisconnection, this, std::placeholders::_1);
		
		tcpIpClient.ClientDisconnectionEvent(disconnectionEvent);

		if (tcpIpClient.Connect(address, std::to_string(port), isSslEnabled)) {
			if (registerForEvents()) {
				pthread_mutex_unlock(&connectMutex);
				return true;
			}
		}

		//deregister disconnection event
		tcpIpClient.RemoveClientDisconnection();
		pthread_mutex_unlock(&connectMutex);

		return false;
	}

	void ClientHelper::onClientDisconnection(std::string& message) {
		tcpIpClient.RemoveClientDisconnection();
		tcpIpClient.RemoveClientEventListener();

		if (errorEventMethod != nullptr) {
			errorEventMethod(message);
		}

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		pthread_create(&reconnectionThread, &attr, &ClientHelper::reconnect, static_cast<void *>(this));

		pthread_attr_destroy(&attr);
	}

	void * ClientHelper::reconnect(void * o) {
		auto * clientHelper = static_cast<ClientHelper *>(o);

		while (!isExiting && clientHelper != nullptr && !clientHelper->connect()) {
#ifdef  _WIN32
			Sleep(500);
#else
			usleep(500 * 1000);
#endif
		}

		pthread_exit(nullptr);
		return nullptr;
	}

#pragma endregion

#pragma region ChipDNA API

	bool ClientHelper::GetVersion(ParameterSet & response) {
		ParameterSet Param;
		return tcpIpClient.StartCommand(Param, response, identifier, GET_VERSION);
	}

	bool ClientHelper::RequestTmsUpdate(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, TMS_UPDATE);
	}

	bool ClientHelper::GetStatus(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, GET_STATUS);
	}

	bool ClientHelper::GetMerchantData(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, GET_MERCHANT_DATA);
	}

	bool ClientHelper::ContinueVoiceReferral(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, CONTINUE_VOICE_REFERRAL);
	}

	bool ClientHelper::ContinueDeferredAuthorization(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, CONTINUE_DEFERRED_AUTHORIZATION);
	}

	bool ClientHelper::ContinueSignatureVerification(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, CONTINUE_SIGNATURE_VERIFICATION);
	}

	bool ClientHelper::StartTransaction(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, START_TRANSACTION);
	}

	bool ClientHelper::GetCardDetails(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, GET_CARD_DETAILS);
	}

	bool ClientHelper::UpdateTransactionParameters(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, UPDATE_TRANSACTION_PARAMETERS);
	}

	bool ClientHelper::ContinueTransaction(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, CONTINUE_TRANSACTION);
	}

	bool ClientHelper::LinkedRefundTransaction(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, LINKED_REFUND_TRANSACTION);
	}

	bool ClientHelper::TerminateTransaction(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, TERMINATE_TRANSACTION);
	}

	bool ClientHelper::ConfirmTransaction(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, CONFIRM_TRANSACTION);
	}

	bool ClientHelper::VoidTransaction(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, VOID_TRANSACTION);
	}
	
	bool ClientHelper::SetIdleMessage(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, SET_IDLE_MESSAGE);
	}

	bool ClientHelper::CustomCommand(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, CUSTOM_COMMAND);
	}

	bool ClientHelper::ReleaseCard(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, RELEASE_CARD);
	}

	bool ClientHelper::GetTransactionInformation(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, GET_TRANSACTION_INFORMATION);
	}

	bool ClientHelper::GetCardStatus(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, GET_CARD_STATUS);
	}

	bool ClientHelper::OpenPassThruSession(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, OPEN_PASS_THRU_SESSION);
	}

	bool ClientHelper::ClosePassThruSession(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, CLOSE_PASS_THRU_SESSION);
	}

	bool ClientHelper::SendPassThruCommand(ParameterSet & parameter, ParameterSet & response) {
		return tcpIpClient.StartCommand(parameter, response, identifier, SEND_PASS_THRU_COMMAND);
	}

	bool ClientHelper::ConnectAndConfigure(ParameterSet & parameter, ParameterSet & response) {
		if (!apiKey.empty()) {
			parameter.Add(ParameterKeys::ApiKey, this->apiKey);
		}

		ParameterSet registerParams = getRegisterParameters();
		KeyValue map = registerParams.GetMap();

		for (auto it = map.begin(); it != map.end(); it++) {
			parameter.Add(it->first, it->second);
		}

		return tcpIpClient.StartCommand(parameter, response, identifier, CONNECT_AND_CONFIGURE);
	}

#pragma endregion

#pragma region Event Handling

	bool ClientHelper::registerForEvents() {
		ParameterSet registerParams = getRegisterParameters();

		if (tcpIpClient.StartCommand(registerParams, registerParams, identifier, REGISTER, this->apiKey)) {			
			tcpIpClient.ClientEventListener(onChipDnaClientEvent);
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

			pthread_create(&eventThread, &attr, &ClientHelper::handleEvent, static_cast<void *>(this));

			pthread_attr_destroy(&attr);
			return true;
		}

		return false;
	}

	ParameterSet ClientHelper::getRegisterParameters() {
		ParameterSet registerParams;
		registerParams.Add(LibraryVersion::ClientReleaseNameTag, LibraryVersion::ClientLibraryReleaseName);
		registerParams.Add(LibraryVersion::ClientVersionTag, LibraryVersion::ClientLibraryVersion);
		registerParams.Add(LibraryVersion::ClientTypeTag, LibraryVersion::ClientLibraryType);;
		registerParams.Add(LibraryVersion::ClientOsTag, getOsName());

		return registerParams;
	}

	void ClientHelper::onChipDnaClientEvent(std::string* eventType, Response * response) {
		pthread_mutex_lock(&event_mutex);
		incomingEvents.push_back(new EventThreadArgs(eventType, response));
		pthread_cond_broadcast(&event_cond);
		pthread_mutex_unlock(&event_mutex);
	}

	void * ClientHelper::handleEvent(void * o) {
		static_cast<ClientHelper *>(o)->processTransactionEvents();
		pthread_exit(nullptr);

		return nullptr;
	}

	void ClientHelper::processTransactionEvents() {
		std::vector<EventThreadArgs*> events(0);

		while (isConnected() || areThereWaitingEvents()) {
			for (auto& event : events)
			{
				KeyValue params = event->response->GetMap();

				if (*event->eventType == "CardDetails" && cardDetails) {
					if (cardDetails != nullptr) cardDetails(params);
				}
				else if (*event->eventType == "CardNotification" && cardNotification) {
					if (cardNotification != nullptr) cardNotification(params);
				}
				else if (*event->eventType == "TransactionFinished" && transactionFinished) {
					if (transactionFinished != nullptr) transactionFinished(params);
				}
				else if (*event->eventType == "TransactionPause" && transactionPause) {
					if (transactionPause != nullptr) transactionPause(params);
				}
				else if (*event->eventType == "TransactionUpdate" && transactionUpdate) {
					if (transactionUpdate != nullptr) transactionUpdate(params);
				}
				else if (*event->eventType == "VoiceReferral" && voiceReferral) {
					if (voiceReferral != nullptr) voiceReferral(params);
				}
				else if (*event->eventType == "DeferredAuthorization" && deferredAuthorization) {
					if (deferredAuthorization != nullptr) deferredAuthorization(params);
				}
				else if (*event->eventType == "SignatureVerificationRequested" && signatureVerificationRequested) {
					if (signatureVerificationRequested != nullptr) signatureVerificationRequested(params);
				}
				else if (*event->eventType == "PaymentDeviceAvailabilityChange" && paymentDeviceAvailabilityChange) {
					if (paymentDeviceAvailabilityChange != nullptr) paymentDeviceAvailabilityChange(params);
				}
				else if (*event->eventType == "TmsUpdate" && tmsUpdate) {
					if (tmsUpdate != nullptr) tmsUpdate(params);
				}
				else if (*event->eventType == "UpdateTransactionParametersFinished" && updateTransactionParametersFinished) {
					if (updateTransactionParametersFinished != nullptr) updateTransactionParametersFinished(params);
				}
				else if (*event->eventType == "SendPassThruCommandResponse" && sendPassThruCommandResponse) {
					if (sendPassThruCommandResponse != nullptr) sendPassThruCommandResponse(params);
				}
				else if (*event->eventType == "OpenPassThruSessionResponse" && openPassThruSessionResponse) {
					if (openPassThruSessionResponse != nullptr) openPassThruSessionResponse(params);
				}
				else if (*event->eventType == "ConnectAndConfigure" && connectAndConfigureResponse) {
					if (connectAndConfigureResponse != nullptr) connectAndConfigureResponse(params);
				}
				else if (*event->eventType == "ConfigurationUpdate" && configurationUpdate) {
					if (configurationUpdate != nullptr) configurationUpdate(params);
				}
				else if (*event->eventType == "DccRateInformation" && dccRateInformation) {
					if (dccRateInformation != nullptr) dccRateInformation(params);
				}
				else if (*event->eventType == "ErrorEvent" && errorEventMethod) {
					std::string error = event->response->ToString();
					if (errorEventMethod != nullptr) errorEventMethod(error);
				}

				delete event;
				event = nullptr;
			}

			pthread_mutex_lock(&event_mutex);

			if (incomingEvents.empty()) {
				pthread_cond_wait(&event_cond, &event_mutex);
			}

			events = incomingEvents;
			incomingEvents.clear();
			pthread_mutex_unlock(&event_mutex);
		}
	}

#pragma endregion 

#pragma region ChipDNA Events

	void ClientHelper::CardDetailsEvent(OnEventReceived onEventReceived) {
		cardDetails = onEventReceived;
	}

	void ClientHelper::TransactionPauseEvent(OnEventReceived onEventReceived) {
		transactionPause = onEventReceived;
	}

	void ClientHelper::TransactionFinishedEvent(OnEventReceived onEventReceived) {
		transactionFinished = onEventReceived;
	}

	void ClientHelper::TransactionUpdateEvent(OnEventReceived onEventReceived) {
		transactionUpdate = onEventReceived;
	}

	void ClientHelper::VoiceReferralEvent(OnEventReceived onEventReceived) {
		voiceReferral = onEventReceived;
	}

	void ClientHelper::DeferredAuthorizationEvent(OnEventReceived onEventReceived) {
		deferredAuthorization = onEventReceived;
	}

	void ClientHelper::SignatureVerificationRequestedEvent(OnEventReceived onEventReceived) {
		signatureVerificationRequested = onEventReceived;
	}

	void ClientHelper::CardNotificationEvent(OnEventReceived onEventReceived) {
		cardNotification = onEventReceived;
	}

	void ClientHelper::PaymentDeviceAvailabilityChangeEvent(OnEventReceived onEventReceived) {
		paymentDeviceAvailabilityChange = onEventReceived;
	}

	void ClientHelper::TmsUpdateEvent(OnEventReceived onEventReceived) {
		tmsUpdate = onEventReceived;
	}

	void ClientHelper::ErrorEvent(OnDisconnection onDisconnection) {
		errorEventMethod = onDisconnection;
	}

	void ClientHelper::UpdateTransactionParametersFinishedEvent(OnEventReceived onEventReceived) {
		updateTransactionParametersFinished = onEventReceived;
	}

	void ClientHelper::SendPassThruCommandResponseEvent(OnEventReceived onEventReceived) {
		sendPassThruCommandResponse = onEventReceived;
	}

	void ClientHelper::OpenPassThruSessionResponseEvent(OnEventReceived onEventReceived) {
		openPassThruSessionResponse = onEventReceived;
	}

	void ClientHelper::ConnectAndConfigureEvent(OnEventReceived onEventReceived) {
		connectAndConfigureResponse = onEventReceived;
	}

	void ClientHelper::ConfigurationUpdateEvent(OnEventReceived onEventReceived) {
		configurationUpdate = onEventReceived;
	}

	void ClientHelper::DccRateInformationEvent(OnEventReceived onEventReceived) {
		dccRateInformation = onEventReceived;
	}

	bool ClientHelper::isConnected() {
		return !isExiting && tcpIpClient.IsConnected();
	}

#pragma endregion

#pragma region std::stringConstants

	const std::string ClientHelper::REGISTER = "Register";
	const std::string ClientHelper::GET_VERSION = "GetVersion";
	const std::string ClientHelper::SET_IDLE_MESSAGE = "SetIdleMessage";
	const std::string ClientHelper::GET_STATUS = "GetStatus";
	const std::string ClientHelper::GET_MERCHANT_DATA = "GetMerchantData";
	const std::string ClientHelper::GET_TRANSACTION_INFORMATION = "GetTransactionInformation";
	const std::string ClientHelper::TERMINATE_TRANSACTION = "TerminateTransaction";
	const std::string ClientHelper::CONFIRM_TRANSACTION = "ConfirmTransaction";
	const std::string ClientHelper::VOID_TRANSACTION = "VoidTransaction";
	const std::string ClientHelper::START_TRANSACTION = "StartTransaction";
	const std::string ClientHelper::GET_CARD_DETAILS = "GetCardDetails";
	const std::string ClientHelper::UPDATE_TRANSACTION_PARAMETERS = "UpdateTransactionParameters";
	const std::string ClientHelper::CONTINUE_TRANSACTION = "ContinueTransaction";
	const std::string ClientHelper::LINKED_REFUND_TRANSACTION = "LinkedRefundTransaction";
	const std::string ClientHelper::CONTINUE_VOICE_REFERRAL = "ContinueVoiceReferral";
	const std::string ClientHelper::CONTINUE_SIGNATURE_VERIFICATION = "ContinueSignatureVerification";
	const std::string ClientHelper::CONTINUE_DEFERRED_AUTHORIZATION = "ContinueDeferredAuthorization";
	const std::string ClientHelper::RELEASE_CARD = "ReleaseCard";
	const std::string ClientHelper::TMS_UPDATE = "TmsUpdate";
	const std::string ClientHelper::UPDATE_TRANSACTION_PARAMETERS_FINISHED = "UpdateTransactionParametersFinished";
	const std::string ClientHelper::GET_CARD_STATUS = "GetCardStatus";
	const std::string ClientHelper::OPEN_PASS_THRU_SESSION = "OpenPassThruSession";
	const std::string ClientHelper::CLOSE_PASS_THRU_SESSION = "ClosePassThruSession";
	const std::string ClientHelper::SEND_PASS_THRU_COMMAND = "SendPassThruCommand";
	const std::string ClientHelper::CONNECT_AND_CONFIGURE = "ConnectAndConfigure";
	const std::string ClientHelper::CUSTOM_COMMAND = "CustomCommand";

#pragma endregion 

}