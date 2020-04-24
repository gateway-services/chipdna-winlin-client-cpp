#ifndef CLIENTHELPER_H
#define CLIENTHELPER_H

#include <list>
#include <map>
#include <string>
#include <pthread.h>
#include <functional>
#include "parameterset.h"
#include "response.h"
#include <time.h>


#ifndef CHIPDNAREFERENCE_H


typedef std::map<std::string, std::string> KeyValue;
typedef std::function<void(KeyValue & parameters)> OnEventReceived;
typedef std::function<void(std::string & message)> OnDisconnection;

#endif

/**
 * \brief Namespace for the ChipDNA Client Library
 */
namespace ChipDnaClientLib {

	/**
	* \brief This contains the main API methods for integrating with ChipDNA.
	* This class is used to configure and initialize an instance of ChipDNA. The ChipDNA instance can then be used to process sale
	* and refund transactions, void and confirm approved authorizations and process linked refunds.
	*/
	class ClientHelper
	{
	public:
		/**
		* \brief
		*	Destructor for ClientHelper and disconnects the client from the Server.
		*/
		~ClientHelper();

		/**
		* \brief
		*	Initializes ClientHelper and automatically attempts to connect to server using the
		*  	server address and server port to connect to a server at a different address or disconnect the client from the server {@link ClientHelper.~ClientHelper} must be called.
		* \param terminalId The terminal ID.
		* \param address An IP address or host name of the server.
		* \param port The port of the server.
		*/
		ClientHelper(std::string terminalId, std::string address, int port);

		/**
		* \brief
		*	Initializes ClientHelper and automatically attempts to connect to server using the
		*  	server address and server port to connect to a server at a different address or disconnect the client from the server {@link ClientHelper.~ClientHelper} must be called.
		* \param terminalId The terminal ID.
		* \param address An IP address or host name of the server.
		* \param port The port of the server.
		* \param enableSsl Indicates if SSL should be enabled.
		*/
		ClientHelper(std::string terminalId, std::string address, int port, bool enableSSL);

		/**
		* \brief
		*	Initializes ClientHelper and automatically attempts to connect to server using the
		*  	server address and server port to connect to a server at a different address or disconnect the client from the server {@link ClientHelper.~ClientHelper} must be called.
		* \param posId The POS ID.
		* \param address An IP address or host name of the server.
		* \param serverPort The port of the server.
		* \param apiKey The API key.
		*/
		ClientHelper(std::string posId, std::string address, int port, std::string apiKey);

		/**
		* \brief
		*	Initializes ClientHelper and automatically attempts to connect to server using the
		*  	server address and server port to connect to a server at a different address or disconnect the client from the server {@link ClientHelper.~ClientHelper} must be called.
		* \param posId The POS ID.
		* \param address An IP address or host name of the server.
		* \param port The port of the server.
		* \param enableSSL Indicates if SSL should be enabled.
		* \param apiKey The API key.
		*/
		ClientHelper(std::string posId, std::string address, int port, bool enableSSL, std::string apiKey);

		/**
		* \brief
		*	Initializes ClientHelper and automatically attempts to connect to server using the
		*  	server address and server port to connect to a server at a different address or disconnect the client from the server {@link ClientHelper.~ClientHelper} must be called.
		* \param address An IP address or host name of the server.
		* \param port The port of the server.
		* \param apiKey The API key.
		*/
		ClientHelper(std::string address, int port, std::string apiKey);

		/**
		* \brief
		*	Initializes ClientHelper and automatically attempts to connect to server using the
		*  	server address and server port to connect to a server at a different address or disconnect the client from the server {@link ClientHelper.~ClientHelper} must be called.
		* \param address An IP address or host name of the server.
		* \param port The port of the server.
		* \param enableSSL Indicates if SSL should be enabled.
		* \param apiKey The API key.
		*/
		ClientHelper(std::string address, int port, bool enableSSL, std::string apiKey);

		/**
		* \brief
		*	Gets the ChipDNA server version information.
		* \param response {@link ParameterSet} with parameter collection:<BR>
		* {@link ParameterKeys.ChipDnaVersion} Always present.<BR>
		* {@link ParameterKeys.ChipDnaReleaseName} Always present.<BR>
		* {@link ParameterKeys.ChipDnaApplicationName} Always present.<BR>
		* \return True if the command has been processed correctly by the server
		*/
		bool GetVersion(ParameterSet& response);

		/**
		* \brief
		*	Get the current status of the different components of ChipDNA server in a single call.
		* \param parameter {@link ParameterSet} Container to use as request container
		* \param response  {@link ParameterSet} The parameter collection does not currently take any values.
		* 	Parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.VersionInformation} Present on no error. <BR>
		* 	{@link ParameterKeys.PaymentPlatformStatus}Present on no error. <BR>
		* 	{@link ParameterKeys.RequestQueueStatus} Present on no error. <BR>
		* 	{@link ParameterKeys.PaymentDeviceStatus} Present on no error. <BR>
		* 	{@link ParameterKeys.ChipDnaStatus} Present on no error. <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ChipDnaErrorCode}.
		* \return True if the command has been processed correctly by the server
		*/
		bool GetStatus(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Get all Merchant data in a single call.
		* \param parameter {@link ParameterSet} Container to use as request container
		* \param response  {@link ParameterSet} The parameter collection does not currently take any values.
		* 	Parameter collection containing the following name-value pairs: <BR>
		*   {@link ParameterKeys.MerchantData} Present on no error. <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ChipDnaErrorCode}.
		* \return True if the command has been processed correctly by the server
		*/
		bool GetMerchantData(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Call ContinueVoiceReferral when the merchant has completed the voice referral process if the voice referral result is not entered on the payment device..
		*
		* Set the result of a voice referral. If ChipDNA is configured to support voice referrals this method should be called to continue the transaction after a {@link voiceReferralEvent} is received and the POS is responsible for supplying the result (Some payment device manage this process internally, with no extra input from the POS).
		* \param parameter {@link ParameterSet}
		* 	Parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.VoiceReferralApproved} Required. <BR>
		* 	{@link ParameterKeys.AuthCode}  Required if {@link ParameterKeys.VoiceReferralApproved} is true <BR>
		* \param response {@link ParameterSet} <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool ContinueVoiceReferral(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Call ContinueDeferredAuthorization when the merchant has completed the deferred authorization process.
		*
		* Set the result of a deferred authorization. If ChipDNA is configured to support deferred authorizations this method should be called to continue the transaction after a {@link deferredAuthorizationEvent} is received.
		* \param parameter {@link ParameterSet}
		* 	Parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.DeferredAuthorizationApproved} Required. <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool ContinueDeferredAuthorization(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Call ContinueSignatureVerification when the merchant has completed the signature verification process.
		*
		* Continues an auto-confirm transaction if signature verification is required and a {@link signatureVerificationRequestedEvent} is fired the client must call this method for transaction processing to resume. 
		* \param parameter {@link ParameterSet}
		* 	Parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.SignatureVerificationResult} Required. <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool ContinueSignatureVerification(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Request the ChipDNA server to perform a TMS update.
		* \param parameter {@link ParameterSet}
		* 	Parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParamenterKeys.TmsRequestType} (Optional) - Default is {@link TmsRequestType.TmsConfiguration} <BR>
		* 	{@link ParameterKeys.TmsUpdateType} (Optional) - Default is {@link TmsUpdateType.Partial} <BR>
		* 	{@link ParameterKeys.ConfigurationUpdateSchedule} (Optional) - Default is {@link TmsUpdateSchedule.Immediate} <BR>
		* \param response - {@link ParameterSet} with a parameter collection containing the following name-value pairs:
		* 	{@link ParameterKeys.Errors } Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link TmsErrorCode}
		* \return True if the command has been processed correctly		
		*/
		bool RequestTmsUpdate(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Start a transaction.
		* A sale with an amount of zero should be used to obtain the details of an ICC card (as a transaction must be started with the card to retrieve these details). If the transaction type is {@link TransactionType.AccountVerification} the amount should not be supplied.
		* \param parameter {@link ParameterSet}
		* 	Parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.Amount} Required, unless {@link ParamenterKeys.TransactionType} is {@link ParameterTokens::TransactionType.AccountVerification} then the amount should not be supplied. <BR>
		* 	{@link ParameterKeys.Reference} Required.<BR>
		* 	{@link ParameterKeys.TransactionType} Required.<BR>
		* 	{@link ParameterKeys.TerminalLanguage} Optional.<BR>
		* 	{@link ParameterKeys.BatchReference} Optional.<BR>
		* \param response {@link ParameterSet} <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool StartTransaction(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Starts a Card Details transaction.
		* \param parameter {@link ParameterSet} The parameter collection does not currently take any value. <BR>
		* \param response {@link ParameterSet} <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool GetCardDetails(ParameterSet & parameter, ParameterSet & response);

		/**
		* \brief
		*	When {@link startTransaction} has been called but a card has not been provided to initiate the transaction then {@link UpdateTransactionParameters} may be called to change the amount or supplied reference. If required this method may be called multiple times and can be called until a {@link CardNotificationEvent} is raised.
		*
		* This method may only be called after {@link ClientHelper.StartTransaction} but may be called multiple times until the first {@link TransactionPauseEvent} or {@link DardNotificationEvent} is triggered When the payment device has successfully updated its transaction parameters the {@link UpdateTransactionParametersFinishedEvent} will be fired. No other calls to {@link UpdateTransactionParameters} can be called until {@link UpdateTransactionParametersFinishedEvent} is returned.
		* \param parameter {@link ParameterSet} collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.Amount} Optional.<BR>
		* 	{@link ParameterKeys.Reference} Optional.<BR>
		* 	{@link ParameterKeys.BatchReference} Optional.<BR>
		* \param response {@link ParameterSet} with a parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool UpdateTransactionParameters(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Continues a paused transaction if ChipDNA is set up to pause during a transaction and a {@link TransactionPauseEvent} is fired the client must call this method for transaction processing to resume.
		* \param parameter {@link ParameterSet} collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.Amount} Optional. <BR>
		* 	{@link ParameterKeys.Reference} Optional.<BR>
		* 	{@link ParameterKeys.ForceDecline} Optional.<BR>
		* 	{@link ParameterKeys.BatchReference} Optional.<BR>
		* \param response {@link ParameterSet} with parameter collection <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool ContinueTransaction(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Start a linked refund transaction to refund all or part of a previously approved and confirmed transaction.
		* \param parameter {@link ParameterSet} collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.Amount} Required.<BR>
		* 	{@link ParameterKeys.Reference} Required.<BR>
		* 	{@link ParameterKeys.SaleReference} Required. This is the reference of the sale that was previously performed.<BR>
		* 	{@link ParameterKeys.SaleDateTime} Optional.<BR>
		* \param response {@link ParameterSet} with a parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.TransactionResult} Always present.<BR>
		* 	{@link ParameterKeys.ReceiptData} Present on completed transaction, except when terminated.<BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link PaymentEngineErrorCode}
		* 	{@link ParameterKeys.ErrorDescription} Present only when error condition encountered and a description message is available.
		* \return True if the command has been processed correctly by the server
		*/
		bool LinkedRefundTransaction(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Terminate a transaction in progress. If the transaction has finished before this is called and the transaction result is approved then {@link VoidTransaction} can be used to cancel the transaction.
		*
		* This command is accepted only when transaction is currently being processed.
		* \param parameter {@link ParameterSet} collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.TerminateReason} Optional.<BR>
		* 	{@link ParameterKeys.TerminateDisplayMessage} Optional.<BR>
		* \param response {@link ParameterSet} with a parameter collection containing the following name-value pairs:  <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool TerminateTransaction(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Finalizes a transaction after it has been approved so that the transaction will be settled. If the data in {@link TransactionFinishedEvent} indicated that signature was required, calling {@link ConfirmTransaction} is also a confirmation that signature passed verification.
		*
		* ChipDNA does not auto-confirm transactions. This method should be called to confirm an approved transaction ready for settlement. An account verification transaction cannot be confirmed. This method allows the transaction to be committed using a different amount to the authorized amount.
		* \param parameter {@link ParameterSet} collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.Reference} Required used in {@link ClientHelper.StartTransaction}<BR>
		* 	{@link ParameterKeys.Amount} Optional, if different from authorized amount. Can only be used for sale transactions that were approved online, not for refunds or transactions approved offline and voice referrals.<BR>
		* \param response {@link ParameterSet} with a parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.TransactionResult} Always present.<BR>
		* 	{@link ParameterKeys.ReceiptData} Present on approved.<BR>
		* 	{@link ParameterKeys.Errors} Only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link PaymentEngineErrorCode}
		* 	{@link ParameterKeys.ErrorDescription} Present only when error condition encountered and a description message is available.
		* \return True if the command has been processed correctly by the server.
		*/
		bool ConfirmTransaction(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Voids a transaction after it has been approved. If the data in {@link ClientHelper.TransactionFinishedEvent} indicated that signature was required, and the signature verification fails then {@link ClientHelper.VoidTransaction} must be called.
		*
		* This method should be called to void an approved transaction to cancel the transaction and if supported by the acquirer/processor release the ring-fenced funds.
		* \param parameter {@link ParameterSet} collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.VoidReason} Optional. <BR>
		* 	{@link ParameterKeys.Reference} Required used in {@link ClientHelper.StartTransaction}.<BR>
		* \param response {@link ParameterSet} with parameter collection <BR>
		* 	{@link ParameterKeys.TransactionResult} Always present.<BR>
		* 	{@link ParameterKeys.ReceiptData} Present on approved.<BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link PaymentEngineErrorCode}.
		* 	{@link ParameterKeys.ErrorDescription} Present only when error condition encountered and a description message is available.
		* \return True if the command has been processed correctly by the server
		*/
		bool VoidTransaction(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Set the standby message to display on the payment device screens when they are idle state.
		* \param parameter {@link ParameterSet} collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.IdleDisplayMessage} Required.<BR>
		* \param response {@link ParameterSet} with a parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link PaymentEngineErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool SetIdleMessage(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Send a custom command to the ChipDNA Server, performing a different function depending on the parameters included in the command.
		* \param response {@link ParameterSet} with a parameter collection containing the following name-value pairs: <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link PaymentEngineErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool CustomCommand(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Some payment device physically lock the payment card, while processing a transaction. Call ReleaseCard to release the card when card processing has ended.
		*
		* When using a payment device that must release the card ChipDNA can be configured to release it automatically for example at the end of a transaction. Only supported for payment devices that lock the card when it is inserted.
		* \param parameter {@link ParameterSet} The parameter collection does not currently take any value. <BR>
		* \param response {@link ParameterSet} with parameter collection <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool ReleaseCard(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Gets the current information corresponding to the specified transaction.
		* \param parameter {@link ParameterSet} The parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.Reference} Required. <BR>
		* \param response {@link ParameterSet} <b>If transaction was found</b>, the response  is returned with a parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.Reference} Present on no error. <BR>
		* 	{@link ParameterKeys.TransactionResult} Present on no error.<BR>
		* 	{@link ParameterKeys.TransactionState} (Present on no error.<BR>
		* 	{@link ParameterKeys.CardEaseReferenceStage1} Present if authorization was submitted online.<BR>
		* 	{@link ParameterKeys.CardEaseReferenceStage2} Present if confirm or void was submitted online.<BR>
		* 	{@link ParameterKeys.CardHash} Present if transaction was submitted online.<BR>
		* 	{@link ParameterKeys.CardReference} Present if transaction was submitted online.<BR>
		* 	{@link ParameterKeys.CustomerVaultId} Present if available from the Omni Platform.<BR>
		* 	{@link ParameterKeys.TransactionId} Present if available from the Omni Platform and if authorization was submitted online.<BR>
		* 	<b>Present if transaction was not found or invalid input parameters were provided</b>, returns Response with a parameter collection containing the following name-value pairs:
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link PaymentEngineErrorCode}.
		* \return True if the command has been processed correctly by the server
		*/
		bool GetTransactionInformation(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Get the card insertion status for all connected devices.
		* \param parameter {@link ParameterSet} The parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.CardNotificationEvents} Optional. <BR>
		* \param response {@link ParameterSet} with parameter collection <BR>
		* 	{@link ParameterKeys.CardStatus} Present on no error. <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}.
		* \return True if the command has been processed correctly by the server
		*/
		bool GetCardStatus(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Opens a pass thru session on the selected device.
		* \param parameter {@link ParameterSet} The parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.PaymentDeviceIdentifier} Required. <BR>
		* \param response {@link ParameterSet} with parameter collection <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}.
		* \return True if the command has been processed correctly by the server
		*/
		bool OpenPassThruSession(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Closes a pass thru session on the selected device.
		* \param parameter {@link ParameterSet} The parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.PaymentDeviceIdentifier} Required. <BR>
		* \param response {@link ParameterSet} with parameter collection <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}.
		* \return True if the command has been processed correctly by the server
		*/
		bool ClosePassThruSession(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Send a pass thru command to selected device.
		* \param parameter {@link ParameterSet} The parameter collection containing the following name-value pairs:<BR>
		* 	{@link ParameterKeys.PaymentDeviceIdentifier} Required. <BR>
		* 	{@link ParameterKeys.Data} Required. <BR>
		* \param response {@link ParameterSet} with parameter collection <BR>
		* 	{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}.
		* \return True if the command has been processed correctly by the server
		*/
		bool SendPassThruCommand(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	Send a connect and configure command.
		*
		* \param parameter The parameter collection currently doesn't take any value.
		* \param response {@link ParameterSet} with parameter collection <BR>
		*
		
		
		
		
		{@link ParameterKeys.Errors} Present only when error condition encountered. Values may come from {@link ParameterTokens.ChipDnaErrorCode}
		* \return True if the command has been processed correctly by the server
		*/
		bool ConnectAndConfigure(ParameterSet& parameter, ParameterSet& response);

		/**
		* \brief
		*	When {@link ClientHelper.StartTransaction} has been successfully called, ChipDNA fires CardDetails events when the details are available.
		*
		* The following parameters may be returned: <BR>
		* {@link ParameterKeys.Track2ClearText} Present as needed.<BR>
		* {@link ParameterKeys.Track2Masked} Present as needed.<BR>
		* {@link ParameterKeys.PanClearText} Present as needed.<BR>
		* {@link ParameterKeys.PanMasked} Present as needed.<BR>
		* {@link ParameterKeys.CardHashCollection} Present as needed.<BR>
		* {@link ParameterKeys.OfflineToken} Present as needed.<BR>
		* {@link ParameterKeys.ExpiryDate} Present as needed.<BR>
		*/
		void CardDetailsEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	When {@link ClientHelper.StartTransaction} has been successfully called, ChipDNA fires {@link CardNotificationEvent} about card availability.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.Notification} Always present.<BR>
		* {@link ParameterKeys.PaymentDeviceModel} Always present.<BR>
		* {@link ParameterKeys.PaymentDeviceIdentifier} Always present.<BR>
		*/
		void CardNotificationEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	ChipDNA fires a TransactionFinished event when {@link ClientHelper.StartTransaction} has been successfully called and the transaction has finished. If the transaction is finished after the {@link ClientHelper.CardDetailsEvent}, the EventParameters contains a parameter list with the following name-value pairs. The transaction will be Approved or Declined and a receipt can be issued for the completed transaction. If the transaction is finished before the {@link ClientHelper.CardDetailsEvent}, the EventParameters contains only the Errors parameter indicating the transaction has been terminated.
		*
		* The following parameters will be returned: <BR>
		* If the transaction is completed the following parameters will be Present:<BR>
		* {@link ParameterKeys.TransactionResult} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.SignatureVerificationRequired} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.Reference} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.ReceiptData} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.CardEaseReference} Present on completion post {@link ClientHelper.CardDetailsEvent} and the authorization was submitted online.<BR>
		* {@link ParameterKeys.CardHash} Present on completion post {@link ClientHelper.CardDetailsEvent} and the authorization was submitted online.<BR>
		* {@link ParameterKeys.CardHashCollection} Present on completion post {@link ClientHelper.CardDetailsEvent} and the authorization was submitted online.<BR>
		* {@link ParameterKeys.CardReference} Present on completion post {@link ClientHelper.CardDetailsEvent} and the authorization was submitted online<BR>
		* {@link ParameterKeys.OfflineToken} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>.<BR>
		* {@link ParameterKeys.AuthDateTime} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.TotalAmount} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.PanMasked} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.ExpiryDate} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.AcquirerResponseCode} Present on completion post {@link ClientHelper.CardDetailsEvent} and the authorization was submitted online.<BR>
		* {@link ParameterKeys.CardSchemeId} Present on completion post {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.Errors} Present on decline or completion pre {@link ClientHelper.CardDetailsEvent}. Values may come from from {@link ParameterTokens.ChipDnaErrorCode}, {@link PaymentEngineErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* {@link ParameterKeys.ErrorDescription} Present only when error condition encountered and a description message is available.
		* If the transaction is terminated The following parameters will be returned: {@link ParameterKeys.Errors}.
		*/
		void TransactionFinishedEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	ChipDNA fires a SignatureVerificationRequested event when {@link ClientHelper.StartTransaction} has been successfully called  and an auto-confirm transaction requires signature verification. If the auto-confirm transaction requires signature verification, the EventParameters contains a parameter list with the following name-value pairs. The transaction will be Approved or Declined and a receipt can be issued for signature verification.
		*
		* The following parameters will be returned: <BR>
		* If the transaction is completed the following parameters will be Present:<BR>
		* {@link ParameterKeys.ReceiptData} Present on completion after {@link ClientHelper.CardDetailsEvent}.<BR>
		* {@link ParameterKeys.SignatureImage} Present if signature was captured on payment device.<BR>
		* {@link ParameterKeys.SignatureImageMediaType} Present if signature was captured on payment device.<BR>
		* {@link ParameterKeys.Errors} Present on decline or completion pre {@link ClientHelper.CardDetailsEvent}. Values may come from from {@link ParameterTokens.ChipDnaErrorCode}, {@link PaymentEngineErrorCode} and {@link ParameterTokens.PaymentDeviceErrorCode}
		* {@link ParameterKeys.ErrorDescription} Present only when error condition encountered and a description message is available.
		* If the transaction is terminated The following parameters will be returned: {@link ParameterKeys.Errors}.
		*/
		void SignatureVerificationRequestedEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Used to notify that a transaction is paused.
		*
		* When {@link ClientHelper.StartTransaction} has been successfully called and ChipDNA is configured to pause transactions, <BR>
		* 1. After the {@link ClientHelper.CardDetailsEvent}. <BR>
		* 2. Before online authorization (if requested). <BR>
		* TransactionPause events will be triggered for all ICC, contactless and magnetic stripe transactions. <BR>
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.PauseState} Always present.
		*/
		void TransactionPauseEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Used to notify of a progress update during a transaction. ChipDNA fires TransactionUpdate events as the customer progresses through the transaction. Each transaction update event describes the action that triggered the event, including EMV commands and data communication.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.Update} Always present.<BR>
		* {@link ParameterKeys.PaymentDeviceModel} Always present.<BR>
		* {@link ParameterKeys.PaymentDeviceIdentifier} Always present.<BR>
		*/
		void TransactionUpdateEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Used to notify that a voice referral is required during a transaction.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.VoiceReferralVerificationSource} Always present. If the voice referral result is required on the payment device, the Client application does not need to call {@link ClientHelper.ContinueVoiceReferral} otherwise the Client application should call {@link ClientHelper.ContinueVoiceReferral} when the process is complete.<BR>
		* {@link ParameterKeys.VoiceReferralTelephoneNumber} Present as needed.<BR>
		*/
		void VoiceReferralEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Used to notify that deferred authorization approval is required during a transaction.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.PinBlockPresent} Always present.<BR>
		* {@link ParameterKeys.DeferredAuthorizationReason} Always present.<BR>
		*/
		void DeferredAuthorizationEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	ChipDNA fires a VoiceReferral event when ChipDNA determines that voice referral verification is required.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.PaymentDeviceModel} Always present.<BR>
		* {@link ParameterKeys.PaymentDeviceIdentifier} Always present.<BR>
		* {@link ParameterKeys.IsAvailable} Always present.<BR>
		* {@link ParameterKeys.AvailabilityError} Always present.<BR>
		* {@link ParameterKeys.AvailabilityErrorInformation} Always present.<BR>
		*/
		void PaymentDeviceAvailabilityChangeEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	When {@link ClientHelper.RequestTmsUpdate} has been successfully called, ChipDNA fires a TmsUpdate event when the update is finished with the result of the request.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.TmsRequestType} Always present.<BR>
		* {@link ParameterKeys.TmsUpdateResult} Always present.<BR>
		* {@link ParameterKeys.Errors} Present if errors were encountered. Values may come from {@link ParameterTokens.ValidationErrorCode}, {@link ParameterTokens.ChipDnaErrorCode} and {@link TmsErrorCode}.
		*/
		void TmsUpdateEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Used to indicate the call to {@link ClientHelper.UpdateTransactionParameters} has been finished.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.UpdateTransactionParametersResult} Always present.<BR/>
		* {@link ParameterKeys.Errors} Present if errors were encountered. {@link UpdateTransactionFinishedErrorCode}
		**/
		void UpdateTransactionParametersFinishedEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Fired by ChipDNA when a PINpad sends a response during a pass thru session.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.PaymentDeviceModel} Always present.<BR>
		* {@link ParameterKeys.PaymentDeviceIdentifier} Always present.<BR/>
		* {@link ParameterKeys.Data} Always present.<BR/>
		**/
		void SendPassThruCommandResponseEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Fired by ChipDNA has stopped communicating with the PINpad and the pass thru session has begun.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.PaymentDeviceModel} Present on no error.<BR/>
		* {@link ParameterKeys.PaymentDeviceIdentifier} Present on no error.<BR/>
		* {@link ParameterKeys.Errors} Present if errors were encountered. Values may come from from {@link ParameterTokens.PaymentDeviceErrorCode}
		**/
		void OpenPassThruSessionResponseEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	When connectAndConfigure has completed this event will be fired with the result.
		*
		* \param onEventReceived
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.ConnectAndConfigureResult} Always Present.<BR>
		* {@link ParameterKeys.Errors} Present if errors were encountered. {@link PaymentEngineErrorCode} {@link ParameterTokens.ChipDnaErrorCode}
		*/
		void ConnectAndConfigureEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		* Fired by ChipDNA regarding information about the progression of calls to connectAndConfigure.
		*
		* \param onEventReceived
		*			The following parameters will be retuned: <BR>
		*			{@link ParameterKeys.ConfigurationUpdate} Always Present.
		*/
		void ConfigurationUpdateEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*	Fired by ChipDNA when DCC is offered to the cardholder.
		*
		* The following parameters will be returned: <BR>
		* {@link ParameterKeys.PaymentDeviceModel} Always present.<BR>
		* {@link ParameterKeys.PaymentDeviceIdentifier} Always present.<BR/>
		* {@link ParameterKeys.TotalAmount} Always present.<BR/>
		* {@link ParameterKeys.LocalTotalAmount} Always present.<BR/>
		* {@link ParameterKeys.CurrencyConversionRate} Always present.<BR/>
		* {@link ParameterKeys.CurrencyConversionProvider} Always present.<BR/>
		* {@link ParameterKeys.CurrencyConversionDisclaimer} Always present.<BR/>
		**/
		void DccRateInformationEvent(OnEventReceived onEventReceived);

		/**
		* \brief
		*  Used to notify of exceptions in the ClientHelper. A message detailing the error will be returned. If this occurs it is most likely due to communication problems with the ChipDNA Server
		*/
		void ErrorEvent(OnDisconnection onDisconnection);

	private:
		//Event Handlers	
		OnEventReceived cardDetails;
		OnEventReceived cardNotification;
		OnEventReceived transactionFinished;
		OnEventReceived transactionPause;
		OnEventReceived transactionUpdate;
		OnEventReceived voiceReferral;
		OnEventReceived deferredAuthorization;
		OnEventReceived signatureVerificationRequested;
		OnEventReceived paymentDeviceAvailabilityChange;
		OnEventReceived tmsUpdate;
		OnEventReceived updateTransactionParametersFinished;
		OnEventReceived sendPassThruCommandResponse;
		OnEventReceived openPassThruSessionResponse;
		OnEventReceived connectAndConfigureResponse;
		OnEventReceived configurationUpdate;
		OnEventReceived dccRateInformation;
		OnDisconnection errorEventMethod;
		static void onChipDnaClientEvent(std::string* eventType, Response* response);
		static void* handleEvent(void* o);

		//String Constants
		static const std::string REGISTER;
		static const std::string GET_VERSION;
		static const std::string SET_IDLE_MESSAGE;
		static const std::string GET_STATUS;
		static const std::string GET_MERCHANT_DATA;
		static const std::string GET_TRANSACTION_INFORMATION;
		static const std::string TERMINATE_TRANSACTION;
		static const std::string CONFIRM_TRANSACTION;
		static const std::string VOID_TRANSACTION;
		static const std::string START_TRANSACTION;
		static const std::string GET_CARD_DETAILS;
		static const std::string UPDATE_TRANSACTION_PARAMETERS;
		static const std::string CONTINUE_TRANSACTION;
		static const std::string LINKED_REFUND_TRANSACTION;
		static const std::string CONTINUE_VOICE_REFERRAL;
		static const std::string CONTINUE_DEFERRED_AUTHORIZATION;
		static const std::string CONTINUE_SIGNATURE_VERIFICATION;
		static const std::string RELEASE_CARD;
		static const std::string TMS_UPDATE;
		static const std::string UPDATE_TRANSACTION_PARAMETERS_FINISHED;
		static const std::string GET_CARD_STATUS;
		static const std::string OPEN_PASS_THRU_SESSION;
		static const std::string CLOSE_PASS_THRU_SESSION;
		static const std::string SEND_PASS_THRU_COMMAND;
		static const std::string CONNECT_AND_CONFIGURE;
		static const std::string CUSTOM_COMMAND;

		//Primitives
		std::string identifier;
		std::string apiKey;
		std::string address;
		int port{};
		bool isSslEnabled{};

		//Concurrency Objects
		pthread_t eventThread{};
		pthread_t reconnectionThread{};
		pthread_mutex_t connectMutex{};

		//Methods
		void processTransactionEvents();
		static void* reconnect(void * o);
		bool connect();
		static bool isConnected();
		bool registerForEvents();
		static ParameterSet getRegisterParameters();
		void onClientDisconnection(std::string &);
		void init(std::string identifier, std::string address, int port, bool enableSSL);
	};

}

#endif /* CDNACLIENT_H */
