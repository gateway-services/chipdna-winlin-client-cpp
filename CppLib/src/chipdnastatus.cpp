#include "chipdnastatus.h"
#include <sstream>
#include <cstdlib>
#include <cstring>
#include "pugixml.hpp"
#include "parameterkeys.h"

namespace ChipDnaClientLib {

	static bool StringToBool(std::string & str) {
		if (str.length() > 1) {
			if (str == "True")
				return true;
			if (str == "true")
				return true;
		}
		return str == "Y";
	}

#pragma region ChipDNA Status Methods

	ChipDnaStatus::ChipDnaStatus() {
		versionInfoList = std::vector<AvailabilityErrorStruct>();
		paymentDeviceList = std::vector<PaymentDeviceStruct>();
		status = std::map<std::string, std::string>();
	}

	ChipDnaStatus::~ChipDnaStatus() = default;

	ChipDnaStatus * ChipDnaStatus::ParseFromResponse(ParameterSet & statusResponse) {
		auto ptr_status = new ChipDnaStatus();
		const std::string versionXML = statusResponse.GetValue(ParameterKeys::VersionInformation);
		char* buffer;
		{
			buffer = new char[versionXML.size()];
			std::memcpy(buffer, versionXML.c_str(), versionXML.size());
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, versionXML.size());

			if (result) {				
				auto arrayNode = doc.child("ArrayOfParameter");
				auto paramNode = arrayNode.child("Parameter");
				
				while (paramNode != nullptr) {
					std::map<std::string, std::string> versionItem;
					ptr_status->status[paramNode.child(VERSION_KEY.c_str()).text().get()] = paramNode.child(VERSION_VALUE.c_str()).text().get();
					paramNode = paramNode.next_sibling("Parameter");
				}

				ptr_status->versionInfo = VersionInfo(ptr_status->status);
			}

			delete[] buffer;
			buffer = nullptr;
		}
		const std::string deviceXML = statusResponse.GetValue(ParameterKeys::PaymentDeviceStatus);
		{
			buffer = new char[deviceXML.size()];
			std::memcpy(buffer, deviceXML.c_str(), deviceXML.size());
			pugi::xml_document doc;
			auto result = doc.load_buffer_inplace(buffer, deviceXML.size());

			if (result) {
				auto arrayNode = doc.child("ArrayOfPaymentDeviceStatus");
				auto paymentDeviceNode = arrayNode.child("PaymentDeviceStatus");

				while (paymentDeviceNode != nullptr) {
					PaymentDeviceStruct deviceItem;
					deviceItem.DeviceId = paymentDeviceNode.child(DEVICE_ID.c_str()).text().get();
					deviceItem.DeviceModel = paymentDeviceNode.child(DEVICE_MODEL.c_str()).text().get();
					deviceItem.IsAvailable = paymentDeviceNode.child(IS_AVAILABLE.c_str()).text().get();
					deviceItem.ConfigurationState = paymentDeviceNode.child(DEVICE_STATE.c_str()).text().get();
					deviceItem.IsProcessingTransaction = paymentDeviceNode.child(PROCESSING_TRANSACTION.c_str()).text().get();
					deviceItem.AvailabilityError = paymentDeviceNode.child(AVAILABILITY_ERROR.c_str()).text().get();
					deviceItem.BatteryPercentage = paymentDeviceNode.child(BATTERY_PERCENTAGE.c_str()).text().get();
					deviceItem.BatteryChargingStatus = paymentDeviceNode.child(BATTERY_CHARGING_STATUS.c_str()).text().get();
					deviceItem.BatteryStatusUpdateDateTime = paymentDeviceNode.child(BATTERY_STATUS_UPDATE_DATETIME.c_str()).text().get();
					deviceItem.BatteryStatusUpdateDateTimeFormat = paymentDeviceNode.child(BATTERY_STATUS_UPDATE_DATETIME_FORMAT.c_str()).text().get();

					auto outerErrorListNode = paymentDeviceNode.child(AVAILABILITY_ERROR_TAG.c_str());
					auto paramNode = outerErrorListNode.child("PaymentDeviceAvailabilityErrorInformation");

					while (paramNode != nullptr) {
						AvailabilityErrorStruct error;
						error.key = paramNode.child("Name").text().get();
						error.value = paramNode.child("Value").text().get();
						deviceItem.AvailabilityErrorList.push_back(error);
						paramNode = paramNode.next_sibling("PaymentDeviceAvailabilityErrorInformation");
					}

					ptr_status->paymentDeviceStatus.push_back(PaymentDeviceStatus(deviceItem));
					paymentDeviceNode = paymentDeviceNode.next_sibling("PaymentDeviceStatus");
				}
			}
			delete[] buffer;
			buffer = nullptr;
		}
		const std::string platformXML = statusResponse.GetValue(ParameterKeys::PaymentPlatformStatus);
		{
			buffer = new char[platformXML.size()];
			std::memcpy(buffer, platformXML.c_str(), platformXML.size());
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, platformXML.size());
			if (result) {
				// adding PAYMENT_PLATFORM_STATUS
				pugi::xml_node paymentPlatformNode = doc.child("PaymentPlatformStatus");
				ptr_status->status[MACHINE_LOCAL_DATE_TIME] = paymentPlatformNode.child(MACHINE_LOCAL_DATE_TIME.c_str()).text().get();
				ptr_status->status[PAYMENT_PLATFORM_LOCAL_DATE_TIME] = paymentPlatformNode.child(PAYMENT_PLATFORM_LOCAL_DATE_TIME.c_str()).text().get();
				ptr_status->status[PAYMENT_PLATFORM_FORM_LOCAL_DATE_TIME_FORMAT] = paymentPlatformNode.child(PAYMENT_PLATFORM_FORM_LOCAL_DATE_TIME_FORMAT.c_str()).text().get();
				ptr_status->status[STATE] = paymentPlatformNode.child(STATE.c_str()).text().get();
				ptr_status->paymentPlatformStatus = PaymentPlatformStatus(ptr_status->status);
			}

			delete[] buffer;
			buffer = nullptr;
		}

		std::string allowedParameters(ParameterSet[1]);
		if (statusResponse.ContainsKey("REQUEST_QUEUE_STATUS")) {
			const std::string queueXML = statusResponse.GetValue(ParameterKeys::RequestQueueStatus);
			{
				buffer = new char[queueXML.size()];
				std::memcpy(buffer, queueXML.c_str(), queueXML.size());
				pugi::xml_document doc;
				pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, queueXML.size());
				if (result) {
					// adding REQUEST_QUEUE_STATUS
					pugi::xml_node requestQueueNode = doc.child("RequestQueueStatus");
					ptr_status->status[CREDIT_REQUEST_COUNT] = requestQueueNode.child(CREDIT_REQUEST_COUNT.c_str()).value();
					ptr_status->status[CREDIT_CONFIRM_REQUEST_COUNT] = requestQueueNode.child(CREDIT_CONFIRM_REQUEST_COUNT.c_str()).text().get();
					ptr_status->status[CREDIT_VOID_REQUEST_COUNT] = requestQueueNode.child(CREDIT_VOID_REQUEST_COUNT.c_str()).text().get();
					ptr_status->status[DEBIT_REQUEST_COUNT] = requestQueueNode.child(DEBIT_REQUEST_COUNT.c_str()).text().get();
					ptr_status->status[DEBIT_CONFIRM_REQUEST_COUNT] = requestQueueNode.child(DEBIT_CONFIRM_REQUEST_COUNT.c_str()).text().get();
					ptr_status->status[DEBIT_VOID_REQUEST_COUNT] = requestQueueNode.child(DEBIT_VOID_REQUEST_COUNT.c_str()).text().get();
				}

				ptr_status->requestQueueStatus = RequestQueueStatus(ptr_status->status);
				delete[] buffer;
				buffer = nullptr;
			}
		}
		const std::string statusXML = statusResponse.GetValue(ParameterKeys::ChipDnaStatus);
		{
			buffer = new char[statusXML.size()];
			std::memcpy(buffer, statusXML.c_str(), statusXML.size());
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, statusXML.size());
			if (result) {
				// adding STATUS
				pugi::xml_node chipDnaServerNode = doc.child("ServerStatus");
				ptr_status->status[IS_PROCESSING_TRANSACTION] = chipDnaServerNode.child(IS_PROCESSING_TRANSACTION.c_str()).text().get();
				ptr_status->status[CHIPDNA_SERVER_ISSUE] = chipDnaServerNode.child(CHIPDNA_SERVER_ISSUE.c_str()).text().get();
			}
			ptr_status->serverStatus = ServerStatus(ptr_status->status);
			delete[] buffer;
			buffer = nullptr;
		}
		const std::string tmsXML = statusResponse.GetValue(ParameterKeys::TmsStatus);
		{
			buffer = new char[tmsXML.size()];
			std::memcpy(buffer, tmsXML.c_str(), tmsXML.size());
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, tmsXML.size());
			if (result) {
				// adding STATUS
				pugi::xml_node chipDnaServerNode = doc.child("TmsStatus");
				ptr_status->status[DAYS_UNTIL_UPDATE_IS_REQUIRED] = chipDnaServerNode.child(DAYS_UNTIL_UPDATE_IS_REQUIRED.c_str()).text().get();
				ptr_status->status[LAST_CONFIG_UPDATE_DATE_TIME] = chipDnaServerNode.child(LAST_CONFIG_UPDATE_DATE_TIME.c_str()).text().get();
				ptr_status->status[REQUIRED_CONFIG_UPDATE_DATE_TIME] = chipDnaServerNode.child(REQUIRED_CONFIG_UPDATE_DATE_TIME.c_str()).text().get();
			}
			ptr_status->tmsStatus = TmsStatus(ptr_status->status);
			delete[] buffer;
			buffer = nullptr;
		}
		const std::string virtualTerminalStatusXML = statusResponse.GetValue(ParameterKeys::VirtualTerminalStatus);
		{
			buffer = new char[virtualTerminalStatusXML.size()];
			std::memcpy(buffer, virtualTerminalStatusXML.c_str(), virtualTerminalStatusXML.size());
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, virtualTerminalStatusXML.size());
			if (result) {
				
				auto arrayNode = doc.child("ArrayOfVirtualTerminalStatus");
				auto virtualTerminalStatusNode = arrayNode.child(VIRTUAL_TERMINAL_STATUS_TAG.c_str());
				while (virtualTerminalStatusNode != nullptr) {
					ptr_status->virtualTerminalStatus.emplace_back(
						virtualTerminalStatusNode.child(VIRTUAL_TERMINAL_ID.c_str()).text().get(),
						virtualTerminalStatusNode.child(VIRTUAL_TERMINAL_ENABLED.c_str()).text().get());
					virtualTerminalStatusNode = virtualTerminalStatusNode.next_sibling("VirtualTerminalStatus");
				}
			}

			delete[] buffer;
			buffer = nullptr;
		}

		return ptr_status;
	}

	std::vector<ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation> ChipDnaStatus::ParseFromAvailabilityErrorInformation(const std::string xml) {
		std::vector<PaymentDeviceAvailabilityErrorInformation> errorList;
		if (xml.empty()) {
			return errorList;
		}

		{
			auto buffer = new char[xml.size()];
			std::memcpy(buffer, xml.c_str(), xml.size());
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, xml.size());
			if (result) {
				
				auto ArrayNode = doc.child("ArrayOfPaymentDeviceAvailabilityErrorInformation");
				auto ParamNode = ArrayNode.child("PaymentDeviceAvailabilityErrorInformation");
				
				while (ParamNode != nullptr) {
					std::string name = ParamNode.child("Name").text().get();
					std::string value = ParamNode.child("Value").text().get();
					errorList.emplace_back(name, value);
					ParamNode = ParamNode.next_sibling("PaymentDeviceAvailabilityErrorInformation");
				}
			}

			delete[] buffer;
			buffer = nullptr;
		}

		return errorList;
	}



	ChipDnaStatus::PaymentPlatformStatus ChipDnaStatus::GetPaymentPlatformStatus() {
		return paymentPlatformStatus;
	}

	std::vector<ChipDnaStatus::PaymentDeviceStatus> ChipDnaStatus::GetPaymentDeviceStatus() {
		return paymentDeviceStatus;
	}

	ChipDnaStatus::ServerStatus ChipDnaStatus::GetServerStatus() {
		return serverStatus;
	}

	ChipDnaStatus::RequestQueueStatus ChipDnaStatus::GetRequestQueueStatus() {
		return requestQueueStatus;
	}

	ChipDnaStatus::VersionInfo ChipDnaStatus::GetVersionInfo() {
		return versionInfo;
	}

	ChipDnaStatus::TmsStatus ChipDnaStatus::GetTmsStatus() {
		return tmsStatus;
	}
	
	std::string ChipDnaStatus::ToString() {
		std::stringstream paymentDeviceStatusString;
		for (int i = 0; i < paymentDeviceStatus.size(); i++) {
			paymentDeviceStatusString << paymentDeviceStatus[i].ToString();
		}

		std::stringstream virtualTerminalStatusString;
		for (int i = 0; i < virtualTerminalStatus.size(); i++) {
			virtualTerminalStatusString << " \t" << virtualTerminalStatus[i].ToString() << std::endl;
		}

		std::string statusObjects[] = {
			versionInfo.ToString(),
			serverStatus.ToString(),
			paymentDeviceStatusString.str(),
			paymentPlatformStatus.ToString(),
			requestQueueStatus.ToString(),
			tmsStatus.ToString()
		};

		std::stringstream ss;
		ss << "----------\n  ChipDNA status:\n";

		int statusObjectsSize = sizeof statusObjects / sizeof*statusObjects;

		for (int i = 0; i < statusObjectsSize; i++) {
			if (!statusObjects[i].empty()) {
				ss << statusObjects[i] << std::endl;
			}
		}

		if (!virtualTerminalStatus.empty()) {
			ss << " Virtual Terminals:" << std::endl;
			ss << virtualTerminalStatusString.str();
		}

		ss << "\n----------\n";
		return ss.str();
	}

#pragma endregion

#pragma region Payment Device Availability Error Information Methods

	std::string ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation::GetName() {
		return name;
	}

	std::string ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation::GetValue() {
		return value;
	}

	std::string ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation::ToString() {
		std::stringstream ss;
		ss << "Name: " << name;
		ss << ", Value: " << value;
		return ss.str();
	}

	ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation::PaymentDeviceAvailabilityErrorInformation(std::string errorName, std::string errorValue) {
		name = errorName;
		value = errorValue;
	}

	ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation::PaymentDeviceAvailabilityErrorInformation() {
		name = "";
		value = "";
	}

#pragma endregion 

#pragma region Version Info Methods

	ChipDnaStatus::VersionInfo::VersionInfo(std::map<std::string, std::string> & status) {
		appHostName = status[ParameterKeys::ChipDnaApplicationName];
		version = status[ParameterKeys::ChipDnaVersion];
		releaseName = status[ParameterKeys::ChipDnaReleaseName];
	}

	ChipDnaStatus::VersionInfo::VersionInfo() {
		appHostName = "";
		version = "";
		releaseName = "";
	}

	std::string ChipDnaStatus::VersionInfo::GetAppHostName() {
		return appHostName;
	}

	std::string ChipDnaStatus::VersionInfo::GetVersion() {
		return version;
	}

	std::string ChipDnaStatus::VersionInfo::GetReleaseName() {
		return releaseName;
	}

	std::string ChipDnaStatus::VersionInfo::ToString() {
		std::stringstream ss;
		ss << ParameterKeys::VersionInformation + ": AppHostName: " << appHostName;
		ss << ", ReleaseName: " << releaseName;
		ss << ", Version: " << version;

		if (appHostName.empty()) {
			return "";
		}
		return ss.str();
	}

#pragma endregion 

#pragma region Payment Platform Status Methods

	ParameterTokens::PaymentPlatformState ChipDnaStatus::PaymentPlatformStatus::GetState() {
		return ParameterTokens::StringToPaymentPlatformState.at(state);
	}

	std::string ChipDnaStatus::PaymentPlatformStatus::GetMachineLocalDateTimeFormat() {
		return machineLocalDateTimeFormat;
	}

	std::string ChipDnaStatus::PaymentPlatformStatus::GetMachineLocalDateTime() {
		return machineLocalDateTime;
	}

	std::string ChipDnaStatus::PaymentPlatformStatus::GetPaymentPlatformLocalDateTime() {
		return paymentPlatformLocalDateTime;
	}

	std::string ChipDnaStatus::PaymentPlatformStatus::GetPaymentPlatformLocalDateTimeFormat() {
		return paymentPlatformLocalDateTimeFormat;
	}

	ChipDnaStatus::PaymentPlatformStatus::PaymentPlatformStatus(std::map<std::string, std::string> & status) {
		state = status[STATE];
		machineLocalDateTimeFormat = "yyyyMMddHHmmss";
		machineLocalDateTime = status[MACHINE_LOCAL_DATE_TIME];
		paymentPlatformLocalDateTime = status[PAYMENT_PLATFORM_LOCAL_DATE_TIME];
		paymentPlatformLocalDateTimeFormat = status[PAYMENT_PLATFORM_FORM_LOCAL_DATE_TIME_FORMAT];
	}

	ChipDnaStatus::PaymentPlatformStatus::PaymentPlatformStatus() {
		state = "";
		machineLocalDateTimeFormat = "yyyyMMddHHmmss";
		machineLocalDateTime = "";
		paymentPlatformLocalDateTime = "";
		paymentPlatformLocalDateTimeFormat = "";
	}

	std::string ChipDnaStatus::PaymentPlatformStatus::ToString() {
		std::stringstream ss;
		ss << ParameterKeys::PaymentPlatformStatus + ": MachineLocalDateTime: " << machineLocalDateTime;
		ss << ", State: " << state;
		ss << ", PaymentPlatformLocalDateTime: " << machineLocalDateTime;

		if (machineLocalDateTime.empty()) {
			return "";
		}
		return ss.str();
	}

#pragma endregion

#pragma region Request Queue Status Methods

	ChipDnaStatus::RequestQueueStatus::RequestQueueStatus(std::map<std::string, std::string> & status) {
		creditRequestCount = atoi(status[CREDIT_CONFIRM_REQUEST_COUNT].c_str());
		creditVoidRequestCount = atoi(status[CREDIT_VOID_REQUEST_COUNT].c_str());
		creditConfirmRequestCount = atoi(status[CREDIT_REQUEST_COUNT].c_str());
		debitRequestCount = atoi(status[DEBIT_REQUEST_COUNT].c_str());
		debitConfirmRequestCount = atoi(status[DEBIT_CONFIRM_REQUEST_COUNT].c_str());
		debitVoidRequestCount = atoi(status[DEBIT_VOID_REQUEST_COUNT].c_str());
	}

	ChipDnaStatus::RequestQueueStatus::RequestQueueStatus() {
		creditRequestCount = -1;
		creditVoidRequestCount = -1;
		creditConfirmRequestCount = -1;
		debitRequestCount = -1;
		debitConfirmRequestCount = -1;
		debitVoidRequestCount = -1;
	}

	int ChipDnaStatus::RequestQueueStatus::GetCreditRequestCount() {
		return creditRequestCount;
	}

	int ChipDnaStatus::RequestQueueStatus::GetCreditVoidRequestCount() {
		return creditVoidRequestCount;
	}

	int ChipDnaStatus::RequestQueueStatus::GetCreditConfirmRequestCount() {
		return creditConfirmRequestCount;
	}

	int ChipDnaStatus::RequestQueueStatus::GetDebitRequestCount() {
		return debitRequestCount;
	}

	int ChipDnaStatus::RequestQueueStatus::GetDebitConfirmRequestCount() {
		return debitConfirmRequestCount;
	}

	int ChipDnaStatus::RequestQueueStatus::GetTotalRequestCount() {
		return creditRequestCount + creditVoidRequestCount + creditConfirmRequestCount + debitRequestCount + debitConfirmRequestCount;
	}

	int ChipDnaStatus::RequestQueueStatus::GetDebitVoidRequestCount() {
		return debitVoidRequestCount;
	}

	std::string ChipDnaStatus::RequestQueueStatus::ToString() {
		std::stringstream ss;
		ss << ParameterKeys::RequestQueueStatus + ": TotalRequestCount: " << GetTotalRequestCount();
		ss << ", CreditRequestCount: " << creditRequestCount;
		ss << ", CreditConfirmRequestCount: " << creditConfirmRequestCount;
		ss << ", CreditVoidRequestCount: " << creditVoidRequestCount;
		ss << ", DebitRequestCount: " << debitRequestCount;
		ss << ", DebitConfirmRequestCount: " << debitConfirmRequestCount;
		ss << ", DebitVoidRequestCount: " << debitVoidRequestCount;

		if (creditRequestCount == -1) {
			return "";
		}
		return ss.str();
	}

#pragma endregion

#pragma region Server Status Methods
	
	ChipDnaStatus::ServerStatus::ServerStatus(std::map<std::string, std::string> & status) {
		processingTransaction = StringToBool(status[IS_PROCESSING_TRANSACTION]);
		processingTransactionAsString = status[IS_PROCESSING_TRANSACTION];
		chipDnaServerIssue = status[CHIPDNA_SERVER_ISSUE];
	}

	ChipDnaStatus::ServerStatus::ServerStatus() {
		processingTransaction = false;
		processingTransactionAsString = "";
		chipDnaServerIssue = "";
	}

	bool ChipDnaStatus::ServerStatus::IsProcessingTransaction() {
		return processingTransaction;
	}

	ParameterTokens::ChipDnaServerIssue ChipDnaStatus::ServerStatus::GetChipDnaServerIssue() {
		return ParameterTokens::StringToChipDnaServerIssue.at(chipDnaServerIssue);
	}

	std::string ChipDnaStatus::ServerStatus::ToString() {
		std::stringstream ss;
		ss << ParameterKeys::ChipDnaStatus + ": IsProcessingTransaction: " << processingTransactionAsString;
		ss << ", ChipDnaServerIssue: " << chipDnaServerIssue;

		if (processingTransactionAsString.empty()) {
			return "";
		}
		return ss.str();
	}

#pragma endregion 
	
#pragma region Payment Device Status Methods

	ChipDnaStatus::PaymentDeviceStatus::PaymentDeviceStatus(PaymentDeviceStruct & device) {
		configuredDeviceId = device.DeviceId;
		configurationState = device.ConfigurationState;
		processingTransaction = StringToBool(device.IsProcessingTransaction);
		processingTransactionAsString = device.IsProcessingTransaction;
		availabilityError = device.AvailabilityError;
		for (auto& i : device.AvailabilityErrorList) {
			availabilityErrorInformation.emplace_back(i.key, i.value);
		}
		configuredDeviceModel = device.DeviceModel;
		available = StringToBool(device.IsAvailable);
		availableAsString = device.IsAvailable;
		batteryPercentage = device.BatteryPercentage;
		batteryChargingStatus = device.BatteryChargingStatus;
		batteryStatusUpdateDateTime = device.BatteryStatusUpdateDateTime;
		batteryStatusUpdateDateTimeFormat = device.BatteryStatusUpdateDateTimeFormat;
	}

	ChipDnaStatus::PaymentDeviceStatus::PaymentDeviceStatus() {
		configuredDeviceId = "";
		configurationState = "";
		processingTransaction = false;
		processingTransactionAsString = "";
		configuredDeviceModel = "";
		available = false;
		availableAsString = "";
		batteryPercentage = "";
		batteryChargingStatus = "";
		batteryStatusUpdateDateTime = "";
		batteryStatusUpdateDateTimeFormat = "";
	}

	std::string ChipDnaStatus::PaymentDeviceStatus::GetConfiguredDeviceId() {
		return configuredDeviceId;
	}

	ParameterTokens::PaymentDeviceConfigurationState ChipDnaStatus::PaymentDeviceStatus::GetConfigurationState() {
		return ParameterTokens::StringToPaymentDeviceConfigurationState.at(configurationState);
	}

	bool ChipDnaStatus::PaymentDeviceStatus::IsProcessingTransaction() {
		return processingTransaction;
	}

	bool ChipDnaStatus::PaymentDeviceStatus::IsAvailable() {
		return available;
	}

	ParameterTokens::PaymentDeviceAvailabilityError ChipDnaStatus::PaymentDeviceStatus::GetAvailabilityError() {
		return ParameterTokens::StringToPaymentDeviceAvailabilityError.at(availabilityError);
	}

	std::vector<ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation> ChipDnaStatus::PaymentDeviceStatus::GetAvailabilityErrorInformation() {
		return availabilityErrorInformation;
	}

	std::string ChipDnaStatus::PaymentDeviceStatus::GetConfiguredDeviceModel() {
		return configuredDeviceModel;
	}

	std::string ChipDnaStatus::PaymentDeviceStatus::GetBatteryPercentage() {
		return batteryPercentage;
	}

	std::string ChipDnaStatus::PaymentDeviceStatus::GetBatteryChargingStatus() {
		return batteryChargingStatus;
	}

	std::string ChipDnaStatus::PaymentDeviceStatus::GetBatteryStatusUpdateDateTime() {
		return batteryStatusUpdateDateTime;
	}

	std::string ChipDnaStatus::PaymentDeviceStatus::GetBatteryStatusUpdateDateTimeFormat() {
		return batteryStatusUpdateDateTimeFormat;
	}

	std::string ChipDnaStatus::PaymentDeviceStatus::ToString() {
		std::stringstream ss;
		ss << ParameterKeys::PaymentDeviceStatus + ": ConfiguredDeviceModel: " << configuredDeviceModel;
		ss << ", ConfiguredDeviceId: " << configuredDeviceId;
		ss << ", IsAvailable: " << availableAsString;
		ss << ", AvailabilityError: " << availabilityError;
		ss << ", AvailabilityErrorInformation: ";
		for (auto& i : availabilityErrorInformation) {
			ss << i.ToString();
		}
		ss << ", ConfigurationState: " << configurationState;
		ss << ", ProcessingTransaction: " << processingTransactionAsString;

		if (configuredDeviceModel.empty()) {
			return "";
		}

		if (!batteryPercentage.empty()) {
			ss << ", BatteryPercentage: " << batteryPercentage;
			ss << ", BatteryChargingStatus: " << batteryChargingStatus;
			ss << ", BatteryStatusUpdateDateTime: " << batteryStatusUpdateDateTime;
			ss << ", BatteryStatusUpdateDateTimeFormat: " << batteryStatusUpdateDateTimeFormat;
		}

		return ss.str();
	}

#pragma endregion 

#pragma region TMS Status Methods

	ChipDnaStatus::TmsStatus::TmsStatus() {
		lastConfigUpdateDateTime = "";
		daysUntilConfigUpdateIsRequired = "-1";
		requiredConfigUpdateDateTime = "";
	}

	ChipDnaStatus::TmsStatus::TmsStatus(std::map<std::string, std::string> & status) {
		lastConfigUpdateDateTime = status[LAST_CONFIG_UPDATE_DATE_TIME];
		daysUntilConfigUpdateIsRequired = status[DAYS_UNTIL_UPDATE_IS_REQUIRED];
		requiredConfigUpdateDateTime = status[REQUIRED_CONFIG_UPDATE_DATE_TIME];
	}

	std::string ChipDnaStatus::TmsStatus::GetDateTimeFormat() {
		return "yyyyMMddHHmmss";
	}

	std::string ChipDnaStatus::TmsStatus::GetLastConfigUpdateDateTime() {
		return lastConfigUpdateDateTime;
	}

	int ChipDnaStatus::TmsStatus::GetDaysUntilConfigUpdateIsRequired() {
		return atoi(daysUntilConfigUpdateIsRequired.c_str());
	}

	std::string ChipDnaStatus::TmsStatus::GetRequiredConfigUpdateDateTime() {
		return requiredConfigUpdateDateTime;
	}

	std::string ChipDnaStatus::TmsStatus::ToString() {
		std::stringstream ss;
		ss << ParameterKeys::TmsStatus + ": " << LAST_CONFIG_UPDATE_DATE_TIME << ": " << lastConfigUpdateDateTime << ", ";
		ss << DAYS_UNTIL_UPDATE_IS_REQUIRED << ": " << daysUntilConfigUpdateIsRequired << ", ";
		ss << REQUIRED_CONFIG_UPDATE_DATE_TIME << ": " << requiredConfigUpdateDateTime;
		if (daysUntilConfigUpdateIsRequired.empty()) {
			return "";
		}
		return ss.str();
	}

#pragma endregion 

#pragma region Virtual Terminal Status Methods

	ChipDnaStatus::VirtualTerminalStatus::VirtualTerminalStatus(std::string theVirtualTerminalId, std::string isVirtualTerminalEnabled) {
		virtualTerminalId = theVirtualTerminalId;
		virtualTerminalEnabled = StringToBool(isVirtualTerminalEnabled);
	}

	ChipDnaStatus::VirtualTerminalStatus::VirtualTerminalStatus() {
		virtualTerminalId = "";
		virtualTerminalEnabled = false;
	}

	std::string ChipDnaStatus::VirtualTerminalStatus::GetVirtualTerminalId() {
		return virtualTerminalId;
	}

	bool ChipDnaStatus::VirtualTerminalStatus::IsVirtualTerminalEnabled() {
		return virtualTerminalEnabled;
	}
	std::string ChipDnaStatus::VirtualTerminalStatus::ToString() {
		std::stringstream ss;
		ss << "VirtualTerminalId: " << virtualTerminalId;
		ss << ", VirtualTerminalEnabled: " << (virtualTerminalEnabled ? "true" : "false");
		return ss.str();
	}

#pragma endregion

}