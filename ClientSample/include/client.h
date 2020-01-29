#ifndef CLIENT_H
#define CLIENT_H

#include "configparser.h"
#include "clienthelper.h"
#include "receiptdata.h"
#include "receiptitemtype.h"
#include "ExtraParameter.h"

namespace ChipDNA {
	
	using namespace ChipDnaClientLib;

	class Client
	{
	public:
		Client(const std::string identifier, const std::string ipAddress, const int port, bool enableSSL, bool saveReceipt, Configparser& settings);
		void run();
		static bool isNumber(const std::string& num);

	private:
		ParameterSet getExtraParams(const std::string& commandName);
		void addUserInputToParams(const std::string& key, const std::string& description, const std::string& defaultVal, ParameterSet& params);

		std::string getReference(const bool isRequired, const std::string def);
		std::string getAmount(const bool isRequired);
		ParameterSet getRequestedParameterSet(ParameterSet parameter);
		std::string getGratuity(const bool isRequired);
		std::string getAmountType(const bool isRequired);
		std::string getType(const bool isRequired, const std::string def);
		std::string getTippingMethod(const bool isRequired, const std::string def);
		std::string getBatchReference();
		bool errorOccured;
		bool voiceReferralRequired;
		bool voiceReferralDone;
		bool deferredAuthorizationRequired;
		bool deferredAuthorizationDone;
		bool transactionInProgress;
		bool getCardDetailsInProgress;
		bool saveReceipt;
		bool verboseLogEnabled;
		ClientHelper*  m_clientHelper;
		void performTransaction();
		void computeInput(char commandKey);
		void printConsoleCommands();
		void resetTransaction();
		KeyValue& getTransactionParameters(KeyValue& transactionParms, const bool amountIsRequired, const bool typeIsRequired, const bool refRequired, const std::string& referencePrefix);
		void setIdleMessage();
		void requestTmsUpdate();
		void performRefundTransactionByReference();
		void performConfirmTransaction();
		void performVoidTransaction();
		void performGetTransactionInformation();
		void performStartTransaction();
		void performGetCardDetails();
		void performContinueTransaction();
		void doUpdateTransaction();
		void performTerminateTransaction();
		void getStatus();
		void getMerchantData();
		void getCardStatus();
		void printReceipt(ReceiptData* receipt);
		void performReleaseCard();
		void performVoiceReferral();
		void performContinueSignatureVerification();
		void performDeferredAuthorization();
		void performOpenPassThruSession();
		void performClosePassthroughSession();
		void performSendPassThruCommand();
		void performConnectAndConfigure();
		void performCustomCommand();
		void cardDetailsEvent(KeyValue & list);
		void signatureVerificationRequestedEvent(KeyValue & list);
		void cardNotificationEvent(KeyValue & list);
		void transactionFinishedEvent(KeyValue & list);
		void transactionPauseEvent(KeyValue & list);
		void transactionUpdateEvent(KeyValue & list);
		void voiceReferralEvent(KeyValue & list);
		void deferredAuthorizationEvent(KeyValue & list);
		void paymentDeviceAvailabilityChangeEvent(KeyValue & list);
		void tmsUpdateEvent(KeyValue & list);
		void updateTransactionParametersFinishedEvent(KeyValue & list);
		void openPassThruSessionResponseEvent(KeyValue & list);
		void sendPassThruCommandResponseEvent(KeyValue & list);
		void connectAndConfigureEvent(KeyValue & parameters);
		void configurationUpdateEvent(KeyValue & parameters);
		void dccRateInformationEvent(KeyValue & list);	void errorEvent(std::string & details);
		std::string strToUpper(std::string upperme);

	private:
		Configparser& settings_;
	};
}
#endif
