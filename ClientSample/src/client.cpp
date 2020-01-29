#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "client.h"
#include <fstream>
#include <time.h>
#include <map>
#include <string>


#include "parameterkeys.h"
#include "parameterset.h"
#include "chipdnastatus.h"
#include "merchantdata.h"
#include "cardhash.h"
#include "cardstatus.h"
#include "clienthelper.h"

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#include <sys/stat.h>
#define GetCurrentDir getcwd
#endif

#if (_MSC_VER >= 1900)
#include "VS2015.h"
#endif

namespace ChipDNA {

	using namespace ChipDnaClientLib;
	using namespace ParameterTokens;

//default messages for voice referral
const std::string AuthCodeInput = "\r\nAuth Code (Default=12345)";
const std::string AuthCodeDefault = "12345";
const std::string VoiceReferralContinue = "\r\nVoice Referral Approved [True,False] (Default=True)";
const std::string VoiceReferralDefault = "true";
const std::string VoiceReferralError = "ContinueVoiceReferral Errors ->";
const std::string VoiceReferralStart = "*Waiting for Continue Voice Referral command -> Press F to continue *";
const std::string VoiceReferralEventParameters = "Voice Referral Event Parameters: ";
const std::string VoiceReferralTelNumber = "VOICE_REFERRAL_TELEPHONE_NUMBER ";
const std::string VoiceReferralSource = "VOICE_REFERRAL_VERIFICATION_SOURCE ";

//default messages for deferred authorization
const std::string DeferredAuthorizationDefault = "true";
const std::string DeferredAuthorizationStart = "*Waiting for Continue Deferred Authorization command -> Press D to continue *";
const std::string DeferredAuthorizationError = "ContinueDeferredAuthorization Errors ->";
const std::string DeferredAuthorizationContinue = "\rDeferred Authorization Approved [True,False] (Default=True)";
const std::string DeferredAuthorizationEventParameters = "Deferred Authorization Event Parameters: ";
const std::string PinBlockPresent = "PIN_BLOCK_PRESENT ";
const std::string DeferredAuthReason = "DEFERRED_AUTHORIZATION_REASON ";

static std::string printParameters(const KeyValue & parameters)
{
	std::stringstream stringStream;
	stringStream << "Parameters: ";
	for (KeyValue::const_iterator it = parameters.begin(); it != parameters.end(); it++)
	{
		stringStream << " [" << it->first << ", " << it->second << "] ";
	}
	return stringStream.str();
}

static std::string getCurrentPath(){
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return "";
	}

	cCurrentPath[sizeof(cCurrentPath)-1] = '\0';
	return cCurrentPath;
}


static std::string getUserInput(const std::string promt){
	std::cout << std::endl << promt << ": ";
	std::string input;
	std::getline(std::cin, input);
	return input;
}

static std::string getDate()
{
	std::stringstream stringStream;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	stringStream << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday << "-"
		<< now->tm_hour
		<< now->tm_min
		<< now->tm_sec;
	return stringStream.str().c_str();
}

static std::string getParameterValue(std::string key, KeyValue& parameter){
	std::map<std::string, std::string>::iterator value;
	value = parameter.find(key);
	if (value == parameter.end())
		return "";
	return value->second;
}

static bool shouldUpdateReference(){
	std::string answer = getUserInput("Update Batch Reference [Y,N]. (Default = N)");
	if (answer.empty())
		return false;
	return std::toupper(answer[0]) == 'Y';
}

static std::string getCommandMenu( ){

	std::stringstream stringStream;
	stringStream << std::endl;
	stringStream << "S \t Current Status\r\n";
	stringStream << "N \t Get Card Status\r\n";
	stringStream << "W \t Get Merchant Data\r\n";
	stringStream << "M \t Set Idle Message on Supported PED\r\n";
	stringStream << "R \t Process Refund By Reference\r\n";
	stringStream << "P \t Start Transaction\r\n";
	stringStream << "C \t Confirm Transaction\r\n";
	stringStream << "V \t Void Transaction\r\n";
	stringStream << "T \t Terminate Transaction (Only works after 'P' command otherwise ignored)\r\n";
	stringStream << "U \t Update Transaction\r\n";
	stringStream << "K \t Release Card\r\n";
	stringStream << "L \t Continue Transaction\r\n";
	stringStream << "F \t Continue Voice Referral\r\n";
	stringStream << "D \t Continue Deferred Authorization\r\n";
	stringStream << "J \t Continue Signature Verification\r\n";
	stringStream << "I \t Transaction Information\r\n";
	stringStream << "+ \t Toggle Client Verbose Debug\r\n";
	stringStream << "x \t Request TMS Update\r\n";
	stringStream << "G \t Get Card Details\r\n";
	stringStream << "Q \t Quit Client Application\r\n";
	stringStream << "B \t Open Pass Thru Session\r\n";
	stringStream << "E \t Close Pass Thru Session\r\n";
	stringStream << "H \t Send Pass Thru Command\r\n";
	stringStream << "O \t Connect And Configure\r\n";
	stringStream << "A \t Custom Command\r\n";
	stringStream << "Press a key\r\n" << std::endl;
	return stringStream.str();
}

std::string getPrintableCardHash(std::vector<CardHash> & cardHashes){
	std::stringstream ss;
	for (int i = 0; i < cardHashes.size(); i++){
			ss << cardHashes.at(i).ToString() << " ";
	}
	return ss.str();

}

	std::string static GetStringOfReceiptItemType(ReceiptItemType item) {
	switch (item){
		case Debug:
		return "Debug";
		case Mandatory:
		return "Mandatory";
		case MandatoryCardHolder:
		return "MandatoryCardHolder";
		case Optional:
		return "Optional";
	default:
		return "";
	}
}


	Client::Client(const std::string identifier, const std::string ipAddress, const int port, bool enableSSL, bool saveReceipt, Configparser& settings) : settings_(settings)
{
	errorOccured = false;
	m_clientHelper = NULL;
	this->saveReceipt = saveReceipt;
	verboseLogEnabled = false;
	voiceReferralRequired = false;
	voiceReferralDone = false;
	deferredAuthorizationRequired = false;
	getCardDetailsInProgress = false;
	deferredAuthorizationDone = false;
	transactionInProgress = false;
	
	if (settings.apiKey() != "") {
		if (identifier != "") {
			m_clientHelper = new ClientHelper(identifier, ipAddress, port, enableSSL, settings.apiKey());
		}
		else {
			m_clientHelper = new ClientHelper(ipAddress, port, enableSSL, settings.apiKey());
		}
		
	}
	else {
		m_clientHelper = new ClientHelper(identifier, ipAddress, port, enableSSL);
	}
	
		m_clientHelper->CardDetailsEvent(bind(&Client::cardDetailsEvent, this, std::placeholders::_1));
		m_clientHelper->CardNotificationEvent(bind(&Client::cardNotificationEvent, this, std::placeholders::_1));
		m_clientHelper->TransactionFinishedEvent(bind(&Client::transactionFinishedEvent, this, std::placeholders::_1));
		m_clientHelper->TransactionPauseEvent(bind(&Client::transactionPauseEvent, this, std::placeholders::_1));
		m_clientHelper->TransactionUpdateEvent(bind(&Client::transactionUpdateEvent, this, std::placeholders::_1));
		m_clientHelper->VoiceReferralEvent(bind(&Client::voiceReferralEvent, this, std::placeholders::_1));
		m_clientHelper->SignatureVerificationRequestedEvent(bind(&Client::signatureVerificationRequestedEvent, this, std::placeholders::_1));
		m_clientHelper->DeferredAuthorizationEvent(bind(&Client::deferredAuthorizationEvent, this, std::placeholders::_1));
		m_clientHelper->ErrorEvent(bind(&Client::errorEvent, this, std::placeholders::_1));
		m_clientHelper->PaymentDeviceAvailabilityChangeEvent(bind(&Client::paymentDeviceAvailabilityChangeEvent, this, std::placeholders::_1));
		m_clientHelper->TmsUpdateEvent(bind(&Client::tmsUpdateEvent, this, std::placeholders::_1));
		m_clientHelper->UpdateTransactionParametersFinishedEvent(bind(&Client::updateTransactionParametersFinishedEvent, this, std::placeholders::_1));
		m_clientHelper->OpenPassThruSessionResponseEvent(bind(&Client::openPassThruSessionResponseEvent, this, std::placeholders::_1));
		m_clientHelper->SendPassThruCommandResponseEvent(bind(&Client::sendPassThruCommandResponseEvent, this, std::placeholders::_1));
		m_clientHelper->ConnectAndConfigureEvent(bind(&Client::connectAndConfigureEvent, this, std::placeholders::_1));
		m_clientHelper->ConfigurationUpdateEvent(bind(&Client::configurationUpdateEvent, this, std::placeholders::_1));
		m_clientHelper->DccRateInformationEvent(bind(&Client::dccRateInformationEvent, this, std::placeholders::_1));	run();
}

void Client::run(){
	std::string command = "";
	
	while (true){
		printConsoleCommands();
		command = "";
		std::cin.clear();
		std::cout.clear();
		std::getline(std::cin, command);
		if (command.empty())
			continue;
		char commandKey = std::toupper(command[0]);
		if (commandKey == 'Q'){
			delete m_clientHelper;
			break;
		}
		computeInput(commandKey);
	}
}

void Client::printConsoleCommands() {
	if (transactionInProgress || getCardDetailsInProgress || deferredAuthorizationDone || voiceReferralDone) return;

	std::string menu = getCommandMenu();
	std::cout << getCommandMenu();
}

void Client::resetTransaction() {
	transactionInProgress = false;
	getCardDetailsInProgress = false;

	voiceReferralRequired = false;
	voiceReferralDone = false;
	deferredAuthorizationRequired = false;
	deferredAuthorizationDone = false;
}

void Client::computeInput(char command){
	switch (command){
	case 'M':
		setIdleMessage();
		break;
	case 'R':
		performRefundTransactionByReference();
		break;
	case 'C':
		performConfirmTransaction();
		break;
	case 'V':
		performVoidTransaction();
		break;
	case 'I':
		performGetTransactionInformation();
		break;
	case 'P':
		performStartTransaction();
		break;
	case 'K':
		performReleaseCard();
		break;
	case 'L':
		performContinueTransaction();
		break;
	case 'J':
		performContinueSignatureVerification();
		break;
	case 'U':
		doUpdateTransaction();
		break;
	case 'T':
		performTerminateTransaction();
		break;
	case '+':
		verboseLogEnabled = !verboseLogEnabled;
		std::cout << "VerboseLogEnabled: " << ((verboseLogEnabled) ? "True" : "False") << std::endl;
		break;
	case 'S':
		getStatus();
		break;
	case 'W':
		getMerchantData();
		break;
	case 'N':
		getCardStatus();
		break;
	case 'X':
		requestTmsUpdate();
		break;
	case 'G':
		performGetCardDetails();
		break;
	case 'Y':
	case 'F':
		performVoiceReferral();	
		break;
	case 'D':
		performDeferredAuthorization();
		break;
	case 'B':
		performOpenPassThruSession();
		break;
	case 'E':
		performClosePassthroughSession();
		break;
	case 'H':
		performSendPassThruCommand();
		break;
	case 'O':
		performConnectAndConfigure();
		break;
	case 'A':
		performCustomCommand();
		break;
	default:
		return;
	}
}

void Client::getStatus() {

	std::cout << ParameterKeys::VersionInformation + "\n" + ParameterKeys::ChipDnaStatus + "\n" + ParameterKeys::PaymentDeviceStatus + "\n" + ParameterKeys::RequestQueueStatus + "\n" + ParameterKeys::TmsStatus + "\n" + ParameterKeys::PaymentPlatformStatus;

	ParameterSet parameter; 
	ParameterSet response; 
	
	parameter += getExtraParams("GetStatus"); 
	ParameterSet parameters = getRequestedParameterSet(parameter);
	if (m_clientHelper->GetStatus(parameters, response)) {
		auto statusData = ChipDnaStatus::ParseFromResponse(response);
		
		if (!response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << statusData->ToString() << std::endl;
			delete statusData;
		}
		else {
			std::cout << response.ToString() << std::endl;
			delete statusData;
		}
	}
}

void Client::getMerchantData() {

	ParameterSet parameter;
	ParameterSet response;

	ParameterSet parameters;
	if (m_clientHelper->GetMerchantData(parameters, response)) {
		auto merchantData = MerchantData::ParseFromResponse(response);
		
		if (response.ContainsKey(ParameterKeys::Errors)) { 
			std::cout << response.ToString() << std::endl;
		}
		else {
			std::cout << merchantData->ToString() << std::endl;
		}
		delete merchantData;
	}
}

void Client::getCardStatus() {
	ParameterSet parameters;
	ParameterSet response;

	std::string cardNotificationEvents = getUserInput("Enter CardNotificationEvents [Transactions,Always] (Optional)");

	// Optional.
	if (!cardNotificationEvents.empty())
			parameters.Add(ParameterKeys::CardNotificationEvents, cardNotificationEvents);

		parameters += getExtraParams("GetCardStatus");
	if (m_clientHelper->GetCardStatus(parameters, response)){
		auto cardStatusData = CardStatus::ParseFromResponse(response);
		
		if (!response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << cardStatusData->ToString() << std::endl;
			delete cardStatusData;
		}
		else {
			std::cout << response.ToString() << std::endl;
		}
	}
}

void Client::requestTmsUpdate(){
	ParameterSet parameter;
	ParameterSet response;
	std::string requestType = getUserInput("\r\nTMS Request Type. Default =[TmsConfiguration]");
	if (!requestType.empty()){
			parameter.Add(ParameterKeys::TmsRequestType, requestType);
	}
	std::string updateType = getUserInput("\r\nConfiguration Update Type. Default=[PARTIAL]");
	if (!updateType.empty()) {
			parameter.Add(ParameterKeys::TmsUpdateType, updateType);
	}

	std::string configUpdateSchedule = getUserInput("\r\nConfiguration Update Schedule. Default=[IMMEDIATE]");
	if (!configUpdateSchedule.empty()) {
			parameter.Add(ParameterKeys::ConfigurationUpdateSchedule, configUpdateSchedule);
	}

		parameter += getExtraParams("RequestTmsUpdate");
	if (m_clientHelper->RequestTmsUpdate(parameter, response)){
		if (response.ContainsKey(ParameterKeys::Errors))
		{
			std::cout << "requestTmsUpdate Errors:\t" << response.GetValue(ParameterKeys::Errors);
		}
		else {
			std::cout << response.ToString() << std::endl;
		}
	}
	else {
		std::cout << "requestTmsUpdate failed" << std::endl;
	}
}

void Client::performStartTransaction()
{
	resetTransaction();
	transactionInProgress = true;

	errorOccured = false;
	if (m_clientHelper == NULL)
	{
		std::cout << "Connection is closed, cannot perform a transaction" << std::endl;
		return;
	}
	ParameterSet startTransParams;
	std::string amount = getAmount(true);
	if (!amount.empty())
			startTransParams.Add(ParameterKeys::Amount, amount);

	std::string amountType = getAmountType(true);
	if (!amountType.empty())
			startTransParams.Add(ParameterKeys::AmountType, amountType);

	std::string  type = getType(true, "SALE");
	if (!type.empty())
			startTransParams.Add(ParameterKeys::TransactionType, type);

	std::string reference = getReference(true, "ChipDNA-" + type + "-" + getDate());
	if (!reference.empty())
			startTransParams.Add(ParameterKeys::Reference, reference);

	std::string batchReference = getBatchReference();
	if (!batchReference.empty())
			startTransParams.Add(ParameterKeys::BatchReference, batchReference);

	std::string panKeyEntry = getUserInput("Perform Pan Key Entry? [True,False] (False - Optional)");	
	if (!panKeyEntry.empty() && strToUpper(panKeyEntry).compare("FALSE") != 0){
			startTransParams.Add(ParameterKeys::PanKeyEntry, panKeyEntry);

		std::string address = getUserInput("Please enter address information (Optional)");
		if (!address.empty()){
				startTransParams.Add(ParameterKeys::CardholderAddress, address);
		}

		std::string zipcode = getUserInput("Please enter Postcode/Zipcode (Optional)");
		if (!zipcode.empty()){
				startTransParams.Add(ParameterKeys::CardholderZipcode, zipcode);
		}
	}
	
	std::string tipping = getTippingMethod(false, "DEFAULT");
	if (!tipping.empty())
			startTransParams.Add(ParameterKeys::TippingSupport, tipping);

	ParameterSet response;
		startTransParams += getExtraParams("StartTransaction");
		if (m_clientHelper->StartTransaction(startTransParams, response)) {

			if (!response.ContainsKey(ParameterKeys::Errors)) {
				std::cout << response.ToString() << std::endl;
			}
			else {
				std::cout << "performStartTransaction Errors:\t" << response.GetValue(ParameterKeys::Errors);
			}
		}
	else
		std::cout << "performStartTransaction failed" << std::endl;
}

	ParameterSet Client::getExtraParams(const std::string& commandName)
	{
		const std::vector<ExtraParameter> extraParams = settings_.getExtraParameters(commandName);
		ParameterSet theSet;
		for (int i = 0; i < extraParams.size(); i++) {
			ExtraParameter p = extraParams.at(i);
			if (p.isInput()) {
				addUserInputToParams(p.getKey(), p.getDescription(), p.getDefaultValue(), theSet);
			}
			else if (p.getDefaultValue().compare(":EMPTY:") == 0) {
				theSet.Add(p.getKey(), "");
			}
			else {
				theSet.Add(p.getKey(), p.getDefaultValue());
			}
		}
		return theSet;
	}

	void Client::addUserInputToParams(const std::string& key, const std::string& description, const std::string& defaultVal, ParameterSet& params)
	{
		std::string inputMessage = "Please enter ";
		inputMessage += description;
		inputMessage += " (";
		if (!defaultVal.empty()) {
			inputMessage += "default= ";
			inputMessage += defaultVal;
		}
		else {
			inputMessage += "Optional";
		}

		inputMessage += ")";
		std::string input = getUserInput(inputMessage);
		input = input.empty() && defaultVal.compare(":EMPTY:") != 0? defaultVal : input;

		if (!input.empty() || defaultVal.compare(":EMPTY:") == 0) {
			params.Add(key, input);
		}
	}

void Client::performGetCardDetails(){
	resetTransaction();
	getCardDetailsInProgress = true;

	ParameterSet transactionValues;
	ParameterSet response;
		transactionValues += getExtraParams("GetCardDetails");
	if (!m_clientHelper->GetCardDetails(transactionValues, response)){		
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performGetCardDetails Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
}

std::string Client::strToUpper(std::string upperme){
	std::string result;
	int i = 0;
	while (upperme[i]){
		const char c = toupper(upperme[i]);
		result = result.append(1u, c);
		i++;
	}
	return result;
}

void Client::setIdleMessage(){
	std::string message = getUserInput("Please enter a message for Idle Screen");
	ParameterSet transactionParms;
		transactionParms.Add(ParameterKeys::IdleDisplayMessage, message);
	ParameterSet  response;
		transactionParms += getExtraParams("SetIdleMessage");
	if (m_clientHelper->SetIdleMessage(transactionParms, response)){
			if (response.ContainsKey(ParameterKeys::Errors))
				std::cout << "setIdleMessage Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
	else 
			std::cout << "setIdleMessage failed" << std::endl;
}

void Client::performCustomCommand(){
	ParameterSet transactionParms;
		transactionParms += getExtraParams("CustomCommand");
	ParameterSet  response;		
	if (m_clientHelper->CustomCommand(transactionParms, response)){
			if (response.ContainsKey(ParameterKeys::Errors))
				std::cout << "customCommand Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
	else 
			std::cout << "customCommand failed" << std::endl;
}

void Client::performRefundTransactionByReference(){
	ParameterSet transactionValues;
	ParameterSet response;
	std::string amount = getAmount(true);
	std::string reference = getReference(true, "refundbyref-" + getDate());
	std::string saleReference = getUserInput("Please Enter Sale Reference(Required)");
	std::string dateTime = getUserInput("Please Enter Sale Date and Time (Optional)");
		transactionValues.Add(ParameterKeys::Amount, amount);
		transactionValues.Add(ParameterKeys::Reference, reference);
		transactionValues.Add(ParameterKeys::SaleReference, saleReference);
	if (!dateTime.empty())
			transactionValues.Add(ParameterKeys::SaleDateTime, dateTime);
		transactionValues += getExtraParams("LinkedRefundTransaction");
	if (m_clientHelper->LinkedRefundTransaction(transactionValues, response)){
			if (response.ContainsKey(ParameterKeys::Errors)) {
				std::cout << "performRefundTransactionByReference Errors:\t" << response.GetValue(ParameterKeys::Errors) << "\n\r" << std::endl;
		}
			if (response.ContainsKey(ParameterKeys::ErrorDescription)) {
				std::cout << "Error Description: " << response.GetValue(ParameterKeys::ErrorDescription) << "\n\r" << std::endl;
		}
			if (response.ContainsKey(ParameterKeys::TransactionId)) {
				std::cout << "Transaction ID: " << response.GetValue(ParameterKeys::TransactionId) << std::endl;
		}
			if (response.ContainsKey(ParameterKeys::ReceiptData)) {
				ReceiptData * data = ReceiptData::GetReceiptDataFromXml(response.GetValue(ParameterKeys::ReceiptData));
			printReceipt(data);
			delete data;
		}
	}
	else 
		std::cout << "performRefundTransactionByReference failed" << std::endl;
}

void Client::performConfirmTransaction(){
	ParameterSet transactionValues;
	ParameterSet response;
		transactionValues.Add(ParameterKeys::Reference, getReference(true, ""));
	std::string amount = getAmount(false);
	if (!amount.empty()){
			transactionValues.Add(ParameterKeys::Amount, amount);
	}
	std::string gratuity = getGratuity(false);
	if (!gratuity.empty()){
			transactionValues.Add(ParameterKeys::Gratuity, gratuity);
	}
	std::string closeTransaction = getUserInput("Close Transaction [True,False] (Optional - End Of Day tipping) True");
	if (!closeTransaction.empty()){
			transactionValues.Add(ParameterKeys::CloseTransaction, closeTransaction);
	}
		transactionValues += getExtraParams("ConfirmTransaction");
	if (!m_clientHelper->ConfirmTransaction(transactionValues, response)){
		std::cout << "performRefundTransactionByReference failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::TransactionResult)) {
			std::cout << "Confirm Transaction Result: " << response.GetValue(ParameterKeys::TransactionResult) << std::endl;
	}
		if (!response.ContainsKey(ParameterKeys::Errors)) {
			ReceiptData * data = ReceiptData::GetReceiptDataFromXml(response.GetValue(ParameterKeys::ReceiptData));
		if (data != NULL){
			printReceipt(data);
			delete data;
		}
	}
	else {
			std::cout << "performConfirmTransaction Errors:\t" << response.GetValue(ParameterKeys::Errors) << "\n\r" << std::endl;
	}
	if (response.ContainsKey(ParameterKeys::ErrorDescription)) {
		std::cout << "Error Description: " << response.GetValue(ParameterKeys::ErrorDescription) << "\n\r" << std::endl;
	}
}

void Client::performVoidTransaction(){
	ParameterSet transactionValues;
	ParameterSet response;
		transactionValues.Add(ParameterKeys::Reference, getReference(true, ""));
	std::string voidReason = getUserInput("Please Enter Void Reason (Optional)");
	if (!voidReason.empty()){
			transactionValues.Add(ParameterKeys::VoidReason, voidReason);
	}
		transactionValues += getExtraParams("VoidTransaction");
	if (!m_clientHelper->VoidTransaction(transactionValues, response)){
		std::cout << "performVoidTransaction failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::TransactionResult)) {
			std::cout << "Void Transaction Result: " << response.GetValue(ParameterKeys::TransactionResult) << std::endl;
	}
		if (!response.ContainsKey(ParameterKeys::Errors)) {
			ReceiptData * data = ReceiptData::GetReceiptDataFromXml(response.GetValue(ParameterKeys::ReceiptData));
		if (data != NULL){
			printReceipt(data);
			delete data;
		}
	}
	else {
			std::cout << "performVoidTransaction Errors:\t" << response.GetValue(ParameterKeys::Errors) << "\n\r" << std::endl;
	}
	if (response.ContainsKey(ParameterKeys::ErrorDescription)) {
		std::cout << "Error Description: " << response.GetValue(ParameterKeys::ErrorDescription) << "\n\r" << std::endl;
	}
}

void Client::performTerminateTransaction(){
	std::string reason = getUserInput("Please Enter Terminate Reason (Optional)");
	std::string message = getUserInput("Please Enter Display Message (Optional)");
	ParameterSet transactionParms;
	if (!message.empty())
			transactionParms.Add(ParameterKeys::TerminateDisplayMessage, message);
	if (!reason.empty())
			transactionParms.Add(ParameterKeys::TerminateReason, reason);
	ParameterSet response;
		transactionParms += getExtraParams("TerminateTransaction");
	if (!m_clientHelper->TerminateTransaction(transactionParms, response)) {
		std::cout << "performTerminateTransaction failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performTerminateTransaction Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
}

void Client::performGetTransactionInformation(){
	ParameterSet transactionValues;
	ParameterSet response;
		transactionValues.Add(ParameterKeys::Reference, getReference(true, ""));
		transactionValues += getExtraParams("GetTransactionInformation");
	if (!m_clientHelper->GetTransactionInformation(transactionValues, response)){
		std::cout << "performGetTransactionInformation failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "Perform Get Transaction Information" << response.GetValue(ParameterKeys::Errors);
	}
	else
			std::cout << response.ToString() << std::endl;
}

void Client::printReceipt(ReceiptData * receipt){
		if (receipt == NULL || receipt->GetItems().size() == 0)
		return;
	std::stringstream stringStream;
	std::string headerFooter = "";
	headerFooter.insert(0, 80, '=');
	stringStream << headerFooter << "\n\r";
		std::vector<ReceiptItem>& items = receipt->GetItems();
	for (size_t i = 0; i < items.size(); i++){
			std::string itemId = items[i].ReceiptEntryId;
			std::string itemType = GetStringOfReceiptItemType(items[i].ReceiptItemType);
		itemId.insert(itemId.size(), 40 - (itemId.size() + itemType.size()), '-');
		stringStream << itemId << itemType << " => ";
			if (!items[i].Label.empty())
				stringStream << items[i].Label << " : ";
			stringStream << items[i].Value << "\n\r";
	}
	stringStream << "\n\r" << headerFooter;
	std::cout << stringStream.str();
	if (saveReceipt){
		const std::string currentPath = getCurrentPath();
		if (currentPath.empty()){
			std::cout << "Unable to save receipt --> currentPath not found" << std::endl;
			return;
		}
		const std::string path = currentPath + "/ReceiptData";
#ifdef WIN32
		_mkdir(path.c_str());
#else
		mkdir(path.c_str(), 0777);
#endif
		const std::string filePath = path + "/ReceiptData" + getDate() + ".txt";
		std::ofstream file(filePath.c_str());
		file << stringStream.str();
		//file.close();
	}

}

void Client::performConnectAndConfigure() {
	ParameterSet connectAndConfigureParams;
	ParameterSet response;
	if (!m_clientHelper->ConnectAndConfigure(connectAndConfigureParams, response)) {
		std::cout << "performConnectAndConfigure failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "Perform Connect And Configure" << response.GetValue(ParameterKeys::Errors);
	}
	else
			std::cout << response.ToString() << std::endl;
}

void Client::performReleaseCard(){
	ParameterSet transactionValues;
	ParameterSet response;
		transactionValues += getExtraParams("ReleaseCard");
	if (!m_clientHelper->ReleaseCard(transactionValues, response)){
		std::cout << "performReleaseCard failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performReleaseCard" << response.GetValue(ParameterKeys::Errors);
	}
}

std::string Client::getAmount(const bool isRequired){
	std::string msg = (isRequired) ? "(Required)" : "(Optional)";
	std::string amount = "";
	std::stringstream stringStream;
	stringStream << "Please Enter Amount eg 250 --> " << "2.50 ";
	stringStream << msg;
	amount = getUserInput(stringStream.str());
	return amount;
}

ParameterSet Client::getRequestedParameterSet(ParameterSet parameter) {
	std::string key = "";
	std::stringstream stringStream;
	stringStream << "\r\nPlease Enter Requested Parameters (Comma Separated) [eg CHIPDNA_STATUS,TMS_STATUS]: (Default = Returns all parameters)";

	std::string input =  getUserInput(stringStream.str());
	std::stringstream ss(input);
	while (ss.good()) {
		std::string key;
		getline(ss, key, ',');
			if (!parameter.ContainsKey(key)) {
				parameter.Add(key, key);
		}
	}
	return parameter;
}

std::string Client::getGratuity(const bool isRequired){
	std::string msg = (isRequired) ? "(Required - End Of Day tipping)" : "(Optional - End Of Day tipping)";
	std::string amount = "";
	std::stringstream stringStream;
	stringStream << "Please Enter Gratuity eg 250 --> " << "2.50 ";
	stringStream << msg;
	amount = getUserInput(stringStream.str());
	return amount;
}

std::string Client::getReference(const bool isRequired, const std::string def){
	std::string msg = (isRequired) ? "(Required)" : "(Optional)";
	std::stringstream stringStream;
	stringStream << "Please Enter Reference ";
	stringStream << msg;
	if (!def.empty())
		stringStream << " " << def;
	std::string reference = getUserInput(stringStream.str());
	if (reference.empty() && !def.empty())
		return def;
	else
		return reference;
}

std::string Client::getType(const bool isRequired, const std::string def){
	std::stringstream stringStream;
	std::string msg = (isRequired) ? "(Required) " : "(Optional) ";
	stringStream << "Please Enter Transaction Type ";
	stringStream << msg << " ";
	stringStream << def;
	std::string type = getUserInput(stringStream.str());
	if (type.empty() && !def.empty())
		return def;
	else
		return type;
}

std::string Client::getTippingMethod(const bool isRequired, const std::string def){
	std::stringstream stringStream;
	std::string msg = (isRequired) ? "(Required) " : "(Optional) ";
	stringStream << "Please Enter Tipping Method ";
	stringStream << msg << " ";
	stringStream << def;
	std::string type = getUserInput(stringStream.str());
	if (type.empty() && !def.empty())
		return def;
	else
		return type;
}

std::string Client::getAmountType(const bool isRequired) {
	std::stringstream stringStream;
	std::string msg = isRequired ? "(Required)" : "(Optional)";
	stringStream << "Actual or Estimated Amount ";
	stringStream << msg << " ";
	stringStream << "[Actual]";
	std::string type = getUserInput(stringStream.str());
	return type;
}

std::string Client::getBatchReference(){
	return getUserInput("Please Enter Batch Reference(Optional)");
}


void Client::performContinueTransaction(){
	ParameterSet transactionParms;
	ParameterSet response;

	std::string declineReply = getUserInput("Force Decline[True, False](Default = False)");
	if (!declineReply.empty()){
			transactionParms.Add(ParameterKeys::ForceDecline, declineReply);
	}
	std::string amount = getAmount(false);
	std::string reference = getReference(false, "");

	if (!amount.empty())
			transactionParms.Add(ParameterKeys::Amount, amount);
	if (!reference.empty())
			transactionParms.Add(ParameterKeys::Reference, reference);
	if (shouldUpdateReference()){
		std::string batchReference = getBatchReference();
			transactionParms.Add(ParameterKeys::BatchReference, batchReference);
	}
	transactionParms += getExtraParams("ContinueTransaction");
	if (!m_clientHelper->ContinueTransaction(transactionParms, response)){
		std::cout << "performContinueTransaction failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
		std::cout << "performContinueTransaction Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
}


void Client::performContinueSignatureVerification(){
	ParameterSet transactionParms;
	ParameterSet response;
	
	std::string verifySignature = getUserInput("Verify Signature [True, False]");
	if (!verifySignature.empty()) {
		transactionParms.Add(ParameterKeys::SignatureVerificationResult, verifySignature);
	}
	
	transactionParms += getExtraParams("ContinueSignatureVerification");
	if (!m_clientHelper->ContinueSignatureVerification(transactionParms, response)) {
		std::cout << "performContinueSignatureVerification failed" << std::endl;
		return;
	}

	if (response.ContainsKey(ParameterKeys::Errors)) {
		std::cout << "performContinueSignatureVerification Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
}

void Client::doUpdateTransaction(){
	ParameterSet transactionValues;
	ParameterSet response;
	std::string reference = getReference(false, "");
	std::string amount = getAmount(true);
	if (!reference.empty())
			transactionValues.Add(ParameterKeys::Reference, reference);
	if (!amount.empty())
			transactionValues.Add(ParameterKeys::Amount, amount);
	if (shouldUpdateReference()){
		std::string batchReference = getBatchReference();
			transactionValues.Add(ParameterKeys::BatchReference, batchReference);
	}	
		transactionValues += getExtraParams("UpdateTransactionParameters");
	if (!m_clientHelper->UpdateTransactionParameters(transactionValues, response)){
		std::cout << "doUpdateTransaction failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "doUpdateTransaction Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
}

void Client::performVoiceReferral(){
	
	bool approved = false;	
	ParameterSet param;
	
	std::string input = getUserInput(VoiceReferralContinue);
	if (input.empty())
		input = VoiceReferralDefault;
		param.Add(ParameterKeys::VoiceReferralApproved, input);
	
	std::string authcode = getUserInput(AuthCodeInput);
	
	if (authcode.empty())
		authcode = AuthCodeDefault;

		param.Add(ParameterKeys::AuthCode, authcode);
	
	ParameterSet response;
		param += getExtraParams("ContinueVoiceReferral");
	m_clientHelper->ContinueVoiceReferral(param, response);
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performVoiceReferral Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
	
	voiceReferralRequired = false;
	voiceReferralDone = true;
}

void Client::performDeferredAuthorization() {
	bool approved = false;
	ParameterSet param;

	std::string input = getUserInput(DeferredAuthorizationContinue);
	if (input.empty())
		input = DeferredAuthorizationDefault;
		param.Add(ParameterKeys::DeferredAuthorizationApproved, input);

	ParameterSet response;
		param += getExtraParams("ContinueDeferredAuthorization");
	m_clientHelper->ContinueDeferredAuthorization(param, response);
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performDeferredAuthorization Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
	
	deferredAuthorizationRequired = false;
	deferredAuthorizationDone = true;
}

void Client::performOpenPassThruSession(){
	ParameterSet param;

	std::string input = getUserInput("\r\nEnter payment device ID");
	if (!input.empty())
			param.Add(ParameterKeys::PaymentDeviceIdentifier, input);
	
	ParameterSet response;
	if (!m_clientHelper->OpenPassThruSession(param, response)){
		std::cout << "performOpenPassThruSession failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performOpenPassThruSession Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
}

void Client::performClosePassthroughSession(){
	ParameterSet param;

	std::string input = getUserInput("\r\nEnter payment device ID");
	if (!input.empty())
			param.Add(ParameterKeys::PaymentDeviceIdentifier, input);

	ParameterSet response;
	if (!m_clientHelper->ClosePassThruSession(param, response)){
		std::cout << "performClosePassthroughSession failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performClosePassthroughSession " << response.GetValue(ParameterKeys::Errors);
	}
}

void Client::performSendPassThruCommand(){
	ParameterSet param;

	std::string input = getUserInput("\r\nEnter payment device ID");
	if (!input.empty())
			param.Add(ParameterKeys::PaymentDeviceIdentifier, input);

	input = getUserInput("\r\nEnter command (hex string)");
	if (!input.empty())
			param.Add(ParameterKeys::Data, input);

	ParameterSet response;
	if (!m_clientHelper->SendPassThruCommand(param, response)){
		std::cout << "performSendPassThruCommand failed" << std::endl;
		return;
	}
		if (response.ContainsKey(ParameterKeys::Errors)) {
			std::cout << "performSendPassThruCommand Errors:\t" << response.GetValue(ParameterKeys::Errors);
	}
}

void Client::cardDetailsEvent(KeyValue & parameters)
{
	std::stringstream stringStream;
	stringStream << "Parameters: ";
	for (KeyValue::const_iterator it = parameters.begin(); it != parameters.end(); it++)
	{
		std::string value = it->second;
		if (it->first.compare(ParameterKeys::CardHashCollection) == 0){
				std::vector<CardHash> cardHashes = CardHash::ParseCardHashFromXml(it->second);
			value = getPrintableCardHash(cardHashes);
		}
		stringStream << " [" << it->first << ", " << value << "] ";

		
	}
	std::cout << "CardDetailsEvent: " << stringStream.str() << "\n\r" << std::endl;

	getCardDetailsInProgress = false;
	printConsoleCommands();
}

void Client::cardNotificationEvent(KeyValue & parameters)
{
	std::cout << "CardNotificationEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::transactionFinishedEvent(KeyValue & parameters)
{
	std::stringstream stringStream;
	stringStream << "TransactonFinished: ";
	std::string xml = getParameterValue(ParameterKeys::ReceiptData, parameters);
		ReceiptData * ptr_receiptData = ReceiptData::GetReceiptDataFromXml(xml);
	std::string errorDescription = "";
	for (KeyValue::const_iterator it = parameters.begin(); it != parameters.end(); it++)
	{
		if (it->first.compare(ParameterKeys::ReceiptData) == 0)
			continue;
		std::string value = it->second;
		if (it->first.compare(ParameterKeys::CardHashCollection) == 0){
				std::vector<CardHash> cardHashes = CardHash::ParseCardHashFromXml(it->second);
			value = getPrintableCardHash(cardHashes);
		}
		
		if (it->first.compare(ParameterKeys::ErrorDescription) == 0){
			errorDescription = it->second;
		}

		stringStream << " [" << it->first << ", " << value << "] ";
		
	}
	std::cout << stringStream.str() << "\n\r" << std::endl;
	
	if(!errorDescription.empty()){
		std::cout << "Error Description: " << errorDescription << "\n\r" << std::endl;
	}

	if (ptr_receiptData != NULL){
		printReceipt(ptr_receiptData);
		delete ptr_receiptData;
	}

	resetTransaction();
	printConsoleCommands();
}

void Client::signatureVerificationRequestedEvent(KeyValue & parameters)
{
	std::stringstream stringStream;
	stringStream << "SignatureVerificationRequested: ";
	std::string xml = getParameterValue(ParameterKeys::ReceiptData, parameters);
	ReceiptData * ptr_receiptData = ReceiptData::GetReceiptDataFromXml(xml);
	std::string errorDescription = "";
	for (KeyValue::const_iterator it = parameters.begin(); it != parameters.end(); it++)
	{
		if (it->first.compare(ParameterKeys::ReceiptData) == 0)
			continue;
		std::string value = it->second;
		if (it->first.compare(ParameterKeys::CardHashCollection) == 0){
			std::vector<CardHash> cardHashes = CardHash::ParseCardHashFromXml(it->second);
			value = getPrintableCardHash(cardHashes);
		}

		if (it->first.compare(ParameterKeys::ErrorDescription) == 0){
			errorDescription = it->second;
		}
		stringStream << " [" << it->first << ", " << value << "] ";
	}
	std::cout << stringStream.str() << "\n\r" << std::endl;
	
	if(!errorDescription.empty()){
		std::cout << "Error Description: " << errorDescription << "\n\r" << std::endl;
	}

	if (ptr_receiptData != NULL){
		printReceipt(ptr_receiptData);
		delete ptr_receiptData;
	}
}

void Client::transactionPauseEvent(KeyValue & parameters)
{
	std::cout << "TransactionPauseEvent: " << printParameters(parameters) << "\n\r" << std::endl;
	std::cout << "Press l to continue transaction" << std::endl;
}

void Client::transactionUpdateEvent(KeyValue & parameters)
{
	std::cout << "TransactionUpdateEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::voiceReferralEvent(KeyValue & parameters)
{
	voiceReferralDone = false;
	std::string processSource = parameters[ParameterKeys::VoiceReferralVerificationSource];
	std::string telephone = parameters[ParameterKeys::VoiceReferralTelephoneNumber];
	if (processSource.compare("Pos") == 0){	

		std::cout << VoiceReferralEventParameters << std::endl;
		std::cout << "[" << VoiceReferralSource << processSource << "]" << std::endl;
		std::cout << "[" << VoiceReferralTelNumber << telephone << "]" << std::endl;
		std::cout << VoiceReferralStart << std::endl;
		voiceReferralRequired = true;
	}
}

void Client::deferredAuthorizationEvent(KeyValue & parameters)
{
	deferredAuthorizationDone = false;
	std::string blockPresent = parameters[ParameterKeys::PinBlockPresent];
	std::string deferredAuthReason = parameters[ParameterKeys::DeferredAuthorizationReason];
	std::cout << "Deferred Authorization Event Parameters: ";
	std::cout << "[" << PinBlockPresent << blockPresent << "]" << std::endl;
	std::cout << "[" << DeferredAuthReason << deferredAuthReason << "]" << std::endl;
	std::cout << DeferredAuthorizationStart << std::endl;
	deferredAuthorizationRequired = true;
}

void Client::paymentDeviceAvailabilityChangeEvent(KeyValue & parameters)
{
	std::stringstream stringStream;
	std::map<std::string, std::string>::iterator it;
	for (it = parameters.begin(); it != parameters.end(); ++it){
		if (it->first.compare(ParameterKeys::AvailabilityErrorInformation) == 0){
				std::vector<ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation> errorList = ChipDnaStatus::ParseFromAvailabilityErrorInformation(it->second);
			stringStream << " [" << it->first << ", ";
			for (int i = 0; i < errorList.size(); i++){
					stringStream << errorList.at(i).GetName() << ", " << errorList.at(i).GetValue();
			}
			stringStream << "] ";
			}
			else {
			stringStream << " [ " << it->first << ", " << it->second << " ] ";
		}
	}
	std::cout << stringStream.str() << std::endl;
}

void Client::tmsUpdateEvent(KeyValue & parameters)
{
	std::cout << "tmsUpdateEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::updateTransactionParametersFinishedEvent(KeyValue & parameters)
{
	std::cout << "updateTransactionParametersFinishedEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::openPassThruSessionResponseEvent(KeyValue & parameters)
{
	std::cout << "openPassThruSessionResponseEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::sendPassThruCommandResponseEvent(KeyValue & parameters)
{
	std::cout << "sendPassThruCommandResponseEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::connectAndConfigureEvent(KeyValue & parameters) {
	std::cout << "connectAndConfigureEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::configurationUpdateEvent(KeyValue & parameters) {
	std::cout << "configurationUpdateEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}

void Client::dccRateInformationEvent(KeyValue & parameters)
{
	std::cout << "DccRateInformationEvent: " << printParameters(parameters) << "\n\r" << std::endl;
}
void Client::errorEvent(std::string & details)
{
		std::cout << "Error: Connection has been closed, Details: " << details << std::endl;
}

bool Client::isNumber(const std::string& num) {
	std::string::const_iterator iterator = num.begin();
	while (iterator != num.end() && std::isdigit(*iterator))
		++iterator;
	return !num.empty() && iterator == num.end();
}
}
