#ifndef PARAMETERKEYS_H
#define PARAMETERKEYS_H
#include <string>

namespace ChipDnaClientLib {

	/**
	* \brief
	*	Parameter keys used in communication between ChipDNA Server and Clients.
	*/
	class ParameterKeys {
	public:
		/**
		* \brief
		* 	Parameter key for the amount. Value is in minor units e.g. �123� for �1.23.
		*
		* KEY = AMOUNT
		*/
		static const std::string Amount;

		/**
		* \brief
		* 	Parameter key for the amount type. Valid values are: Actual or Estimate
		*
		* KEY = AMOUNT_TYPE
		*/
		static const std::string AmountType;

		/**
		* \brief
		* 	Parameter key for the gratuity. Valid values are: Value is in minor units e.g. �123� for �1.23.
		*
		* KEY = GRATUITY
		*/
		static const std::string Gratuity;

		/**
		* \brief
		* 	Parameter key for tipping support. Valid values are: None or Both or OnDevice or EndOfDay or Default
		*
		* KEY = TIPPING_SUPPORT
		*/
		static const std::string TippingSupport;

		/**
		* \brief
		* 	Parameter key for close transaction. Valid values are: True or False
		*
		* KEY = CLOSE_TRANSACTION
		*/
		static const std::string CloseTransaction;

		/**
		* \brief
		*	Parameter key for acquirer response code.
		*
		* KEY = AQUIRER_RESPONSE_CODE
		*/
		static const std::string AcquirerResponseCode;

		/**
		* \brief
		* 	Parameter key for the auth code. Value can be alpha numeric, up to 12 characters max.
		*
		* KEY = AUTH_CODE
		*/
		static const std::string AuthCode;

		/**
		* \brief
		* 	Parameter key for the authorization date and time. Value format is yyyyMMddHHmmss.
		*
		* KEY = AUTH_DATE_TIME
		*/
		static const std::string AuthDateTime;

		/**
		* \brief
		* 	Parameter key for the application identifier.
		*
		* KEY = AID
		*/
		static const std::string Aid;

		/**
		* \brief
		* 	Parameter key for the batch reference. This can be used to group transactions together.
		*
		Value must be printable ASCII characters excluding the following nine characters �<>|:*?/\ maximum 50 characters and may not contain leading or trailing spaces. <br/>
		* KEY =BATCH_REFERENCE
		*/
		static const std::string BatchReference;


		/**
		* \brief
		* 	Parameter key for the transactions processing status of the ChipDNA server in XML format representing {@link ServerStatus}.
		*
		* KEY = CHIPDNA_STATUS
		*/
		static const std::string ChipDnaStatus;

		/**
		* \brief
		*	Parameter key for the build version of the ChipDNA server.
		*
		* KEY = CHIPDNA_VERSION
		*/
		static const std::string ChipDnaVersion;

		/**
		* \brief
		* 	Parameter key for the release name of the ChipDNA server.
		*
		* KEY = CHIPDNA_RELEASE_NAME
		*/
		static const std::string ChipDnaReleaseName;

		/**
		* \brief
		*	Parameter key for the application name of the ChipDNA server.
		*
		* KEY = CHIPDNA_APP_NAME
		*/
		static const std::string ChipDnaApplicationName;

		/**
		* \brief
		* 	Parameter key for the unique GUID generated for a transaction if the authorization was submitted online to the Creditcall payment platform.
		*
		* ASCII 36 characters in the format of a GUID. <br/>
		* KEY = CARDEASE_REFERENCE
		*/
		static const std::string CardEaseReference;

		/**
		* \brief
		* 	Parameter key for the unique GUID generated for a transaction if the authorization was submitted online to the Creditcall payment platform.
		*
		* KEY = CARDEASE_REFERENCE_STAGE_1
		*/
		static const std::string CardEaseReferenceStage1;

		/**
		* \brief
		Parameter key for the unique GUID generated for a transaction if the completion (i.e confirm or void) was submitted online to the Creditcall payment platform.
		*
		* KEY = CARDEASE_REFERENCE_STAGE_2
		*/
		static const std::string CardEaseReferenceStage2;

		/**
		* \brief
		* 	Parameter key for unique token generated by the Creditcall payment gateway that can be used to identify a card without using the PAN.
		*
		* KEY = CARD_HASH
		*/
		static const std::string CardHash;

		/**
		* \brief
		* 	Parameter key for list of tokens generated by Creditcal payment gateway and or payment device that can be used to identify a card with out the PAN. Value in XML format representing List of {@link CardHash}
		*
		* KEY = CARD_HASH_COLLECTION
		*/
		static const std::string CardHashCollection;

		/**
		* \brief
		* 	Parameter key for the unique reference generated by the Creditcall payment gateway that can be used to identify a card without using the PAN.
		*
		* KEY = CARD_REFERENCE
		*/
		static const std::string CardReference;

		/**
		* \brief
		* 	Parameter key for card scheme.
		*
		* KEY = CARD_SCHEME
		*/
		static const std::string CardScheme;

		/**
		* \brief
		*	Parameter key for card scheme id.
		*
		* Key = CARD_SCHEME_ID
		*/
		static const std::string CardSchemeId;

		/**
		* \brief
		*	Parameter key for the card account type.
		*
		* Key = ACCOUNT_TYPE
		*/
		static const std::string AccountType;

		/**
		* \brief
		* 	Parameter key for cardholder verification performed.
		*
		* KEY = CARDHOLDER_VERIFICATION
		*/
		static const std::string CardholderVerification;

		/**
		* \brief
		* 	PaymentDeviceConnectionStatus Parameter key for the payment device connection status. Value can be Connected or Disconnected.
		*
		* KEY = CONNECTION_STATUS
		*/
		static const std::string PaymentDeviceConnectionStatus;

		/**
		* \brief
		*	Parameter key for errors sent from ChipDNA server. Comma separated error codes.
		*
		* KEY = ERRORS
		*/
		static const std::string Errors;
		
		/**
		* \brief
		*	Parameter key for error description from the omni-platform where available.
		*
		* KEY = ERROR_DESCRIPTION
		*/
		static const std::string ErrorDescription;

		/**
		* \brief
		*	Text encoding (Either ASCII or UTF8).
		*
		* KEY = ENCODING
		*/
		static const std::string Encoding;

		/**
		* \brief
		* 	Parameter key for the expiry date for the card. Value uses the format YYMM.
		*
		* KEY = EXPIRY_DATE
		*/
		static const std::string ExpiryDate;

		/**
		* \brief
		*	Parameter key for the force decline flag. Value can be true or false.
		*
		* KEY = FORCE_DECLINE
		*/
		static const std::string ForceDecline;

		/**
		* \brief
		* 	Parameter key for the display message for idle screen on PED.
		*
		* KEY = IDLE_MESSAGE
		*/
		static const std::string IdleDisplayMessage;

		/**
		* \brief
		* 	Parameter key for the name of the merchant.
		*
		* KEY = MERCHANT_NAME
		*/
		static const std::string MerchantName;

		/**
		* \brief
		* 	Parameter key for the merchant ID.
		*
		* KEY = MERCHANT_ID_MASKED
		*/
		static const std::string MerchantIdMasked;

		/**
		* \brief
		* 	Parameter key for notification of which card event has occurred. Value can be one of {@link CardNotification}.
		*
		* KEY = NOTIFICATION
		*/
		static const std::string Notification;

		/**
		* \brief
		* 	Parameter key for the offline token generated for the card details if the payment device supports this functionality.
		*
		* KEY = OFFLINE_TOKEN
		*/
		static const std::string OfflineToken;

		/**
		* \brief
		* 	Parameter key for the primary account number. Full PAN where end-to-end encryption is not enabled. This has a maximum length of 19 digits.
		*
		* KEY = PAN_CLEAR_TEXT
		*/
		static const std::string PanClearText;

		/**
		* \brief
		* 	Parameter key for the masked primary account number showing only the first 6 (if available) and last 4 digits.
		*
		* KEY = PAN_MASKED
		*/
		static const std::string PanMasked;

		/**
		* \brief
		* 	Parameter key for the card sequence number.
		*
		* KEY = PAN_SEQUENCE
		*/
		static const std::string PanSequence;

		/**
		* \brief
		* 	Parameter key for payment platform status. The status of the Creditcall payment gateway in XML format representing{@link ChipDnaStatus.PaymentPlatformStatus}.
		*
		* KEY = PAYMENT_PLATFORM_STATUS
		*/
		static const std::string PaymentPlatformStatus;

		/**
		* \brief
		* 	Parameter key for the status of each payment device configured with the ChipDNA server for this client in XML format representing {@link ChipDnaStatus.PaymentDeviceStatus}.
		*
		* KEY = PAYMENT_DEVICE_STATUSES
		*/
		static const std::string PaymentDeviceStatus;

		/**
		* \brief
		* 	Parameter key for receipt data in XML format representing {@link ReceiptData}.
		*
		* KEY = RECEIPT_DATA
		*/
		static const std::string ReceiptData;

		/**
		* \brief
		* 	Parameter key for the status of the queue of requests to be sent to the Creditcall payment gateway in XML format representing {@link ChipDnaStatus.RequestQueueStatus}.
		*
		* KEY = REQUEST_QUEUE_STATUS
		*/
		static const std::string RequestQueueStatus;

		/**
		* \brief
		* 	Parameter key for the unique reference of the transaction supplied by the integrating application.
		*
		* Value must be printable ASCII characters excluding the following nine characters �<>|:*?/\ maximum 50 characters and may not contain leading or trailing spaces.  <br/>
		* KEY = REFERENCE
		*/
		static const std::string Reference;

		/**
		* \brief
		* 	Parameter key for the unique reference for the sale transaction.
		*
		* Value must be printable ASCII characters excluding the following nine characters �<>|:*?/\ maximum 50 characters and may not contain leading or trailing spaces. <br/>
		* KEY = SALE_REFERENCE
		*/
		static const std::string SaleReference;

		/**
		* \brief
		* 	This is in the format yyyyMMddHHmmss but only matches what is specified for example yyyyMMdd, yyyyMMddHH etc.
		*
		* A minimum of the date yyyyMMdd must be specified. Although an optional parameter supplying this improves the performance of the look up of the original sale transaction.<br/>
		* KEY = SALE_DATE_TIME
		*/
		static const std::string SaleDateTime;

		/**
		* \brief
		* 	Parameter key for the service code.
		*
		* KEY = SERVICE_CODE
		*/
		static const std::string ServiceCode;

		/**
		* \brief
		* 	Parameter Key for Signature Verification Request flag. Value can be True or False.
		*
		* KEY = SIGNATURE_VERIFICATION_REQUIRED
		*/
		static const std::string SignatureVerificationRequired;

		/**
		* \brief
		* 	Parameter key for signature captured flag. Value can be true or false.
		*
		* Key = SIGNATURE_CAPTURED;
		**/
		static const std::string SignatureCaptured;

		/**
		* \brief
		* 	Parameter key for signature image. Value contains base 64 encoded raw image data.
		*
		* KEY = SIGNATURE_IMAGE
		**/
		static const std::string SignatureImage;

		/**
		* \brief
		* 	Parameter key for signature image media type. Value contains the media type of the decoded raw image.
		*
		* KEY = SIGNATURE_IMAGE_MEDIA_TYPE
		**/
		static const std::string SignatureImageMediaType;

		/**
		* \brief
		* 	Parameter key for the message to display on the payment device when transaction is terminated.
		*
		* [EOL] should be used to indicate line breaks in the display message.  <br/>
		* KEY = TERMINATE_DISPLAY_MESSAGE
		*/
		static const std::string TerminateDisplayMessage;

		/**
		* \brief
		* 	Parameter key for the terminal ID. Value is masked except last 4 digits.
		*
		* KEY = TERMINAL_ID_MASKED
		*/
		static const std::string TerminalIdMasked;

		/**
		* \brief
		* 	Parameter key for the Creditcall terminal ID.
		*
		* KEY = TERMINAL_ID
		**/
		static const std::string TerminalId;

		/**
		* \brief
		* 	Parameter key for the reason for terminating transaction. Valid values can be one of {@link ParameterTokens.TerminateReason}.
		*
		* KEY = TERMINATE_REASON
		*/
		static const std::string TerminateReason;

		/**
		* \brief
		* 	Parameter key for the result of the transaction. Value can be Approved or Declined.
		*
		* KEY = TRANSACTION_RESULT
		*/
		static const std::string TransactionResult;

		/**
		* \brief
		* 	Parameter key for transaction state. Valid values can be one of {@link State}.
		*
		* KEY = TRANSACTION_STATE
		*/
		static const std::string TransactionState;

		/**
		* \brief
		* 	Parameter key for the transaction source. Valid values can be one of {@link ParameterTokens.TransactionSource}.
		*
		* KEY = TRANSACTION_SOURCE
		*/
		static const std::string TransactionSource;

		/**
		* \brief
		* 	Parameter key for the transaction type. Valid values can be one of {@link ParameterTokens.TransactionType}.
		*
		* KEY = TRANSACTION_TYPE
		*/
		static const std::string TransactionType;

		/**
		* \brief
		* 	Parameter key for the full card track 2 data where end-to-end encryption is not enabled.
		*
		* KEY = TRACK2_CLEAR_TEXT
		*/
		static const std::string Track2ClearText;

		/**
		* \brief
		* 	Parameter key for the masked track 2 data from the card.
		*
		* This shows the first 6 and last 4 digits of the PAN, the expiration date (YYMM) and the 3 digits service code.  <br/>
		* KEY = TRACK2_MASKED
		*/
		static const std::string Track2Masked;

		/**
		* \brief
		*	Parameter key for the payment device language.
		*
		* Valid values are three letter language codes from ISO 639-2. <br/>
		* KEY = TERMINAL_LANGUAGE
		*/
		static const std::string TerminalLanguage;

		/**
		* \brief
		* 	Parameter key for the total amount for the transaction in minor units.
		* KEY = TOTAL_AMOUNT
		*/
		static const std::string TotalAmount;

		/**
		* \brief
		* 	Parameter key for the local total amount for the transaction in minor units.
		* KEY = LOCAL_TOTAL_AMOUNT
		*/
		static const std::string LocalTotalAmount;

		/**
		* \brief
		* 	Parameter key for the transaction currency for the transaction in minor units.
		* KEY = TRANSACTION_CURRENCY
		*/
		static const std::string TransactionCurrency;

		/**
		* \brief
		* 	Parameter key for the local transaction currency for the transaction in minor units.
		* KEY = LOCAL_TRANSACTION_CURRENCY
		*/
		static const std::string LocalTransactionCurrency;

		/**
		* \brief
		* 	Parameter key for the update event that has occurred during a transaction.
		*
		* KEY = UPDATE
		*/
		static const std::string Update;

		/**
		* \brief
		* 	Parameter key for the voice referral result. Value can be true or false.
		*
		* KEY = VOICE_REFERRAL_APPROVED
		*/
		static const std::string VoiceReferralApproved;

		/**
		* \brief
		* 	Parameter key for the deferred authorization result. Value can be true or false.
		*
		* KEY = DEFERRED_AUTHORIZATION_APPROVED
		*/
		static const std::string DeferredAuthorizationApproved;

		/**
		* \brief
		* 	Parameter key for if there is a pin block present. Value can be true or false.
		*
		* KEY = PIN_BLOCK_PRESENT
		*/
		static const std::string PinBlockPresent;

		/**
		* \brief
		* 	Parameter key for the whether the result of the voice referral should be entered on the POS device or the payment device.
		*
		* KEY = VOICE_REFERRAL_VERIFICATION_SOURCE
		*/
		static const std::string VoiceReferralVerificationSource;

		/**
		* \brief
		* 	Parameter key for the telephone number that the merchant must call to perform the voice referral.
		*
		* KEY = VOICE_REFERRAL_TELEPHONE_NUMBER
		*/
		static const std::string VoiceReferralTelephoneNumber;

		/**
		* \brief
		* 	Parameter key for the reason for void. Valid values can be one of {@link VoidReason}.
		*
		* KEY = VOID_REASON
		*/
		static const std::string VoidReason;

		/**
		* \brief
		* 	Parameter key for version information of ChipDNA in XML format for {@link ChipDnaStatus.VersionInfo}.
		*
		* KEY = VERSION_INFORMATION
		*/
		static const std::string VersionInformation;

		/**
		* \brief
		* 	Parameter key for pause state. The state when pause event was triggered. See {@link PauseTransactionState} for possible values.
		*
		* KEY = PAUSE_STATE
		*/
		static const std::string PauseState;

		/**
		* \brief
		* 	Parameter key for the payment device model.
		*
		* KEY = PAYMENT_DEVICE_MODEL
		*/

		static const std::string PaymentDeviceModel;

		/**
		* \brief
		* 	Parameter key for the payment device identifier.
		*
		* KEY = PAYMENT_DEVICE_IDENTIFIER
		*/

		static const std::string PaymentDeviceIdentifier;

		/**
		* \brief
		* 	Parameter key for the payment device availability. Value may be true or false.
		*
		* KEY = IS_AVAILABLE
		*/

		static const std::string IsAvailable;

		/**
		* \brief
		* 	Parameter key for the payment device availability error. Value may be one of {@link PaymentDeviceAvailabilityError}.
		*
		* KEY = AVAILABILITY_ERROR
		*/
		static const std::string AvailabilityError;

		/**
		* \brief
		* 	Parameter key for the payment device availability error information. Value contains XML data for {@link ChipDnaStatus::PaymentDeviceAvailabilityErrorInformation}.
		*
		* KEY = AVAILABILITY_ERROR_INFORMATION
		*/

		static const std::string AvailabilityErrorInformation;

		/**
		* \brief
		* 	Parameter key for TMS status in XML format representing.
		*
		* KEY = TMS_STATUS
		*/
		static const std::string TmsStatus;

		/**
		* \brief
		* 	Parameter Key for the TMS Configuration Update flag. Value can be one of {@link TmsUpdateType}.
		*
		* KEY = UPDATE_TYPE
		*/
		static const std::string TmsUpdateType;

		/**
		* \brief
		* 	Parameter key for the TMS configuration update schedule. Value may be one of  {@link TmsUpdateSchedule}.
		*
		* KEY = CONFIGURATION_UPDATE_SCHEDULE
		*/
		static const std::string ConfigurationUpdateSchedule;

		static const std::string ConnectionFailure;

		/**
		* \brief
		* 	Parameter key for the TMS configuration request flag. Value can be one of {@link TmsRequestType}.
		*
		* KEY = TMS_REQUEST_TYPE
		**/
		static const std::string TmsRequestType;

		/**
		* \brief
		* 	Parameter key for the result of the TMS update. Values can be one of {@link TmsUpdateResult}.
		*
		* KEY = TMS_UPDATE_RESULT
		**/
		static const std::string TmsUpdateResult;

		/**
		* \brief
		* 	Parameter key for update transaction parameter result. Value is either true or false.
		*
		* KEY = UPDATE_TRANSACTION_PARAMETERS_RESULT
		**/
		static const std::string UpdateTransactionParametersResult;

		/**
		* \brief
		* 	Parameter key for PAN key entry.
		*
		* KEY = PAN_KEY_ENTRY
		**/
		static const std::string PanKeyEntry;

		/**
		* \brief
		* 	Parameter key for the cardholder's address.
		*
		* KEY = CARDHOLDER_ADDRESS
		**/
		static const std::string CardholderAddress;

		/**
		* \brief
		* 	Parameter key for the cardholder's zipcode.
		*
		* KEY = CARDHOLDER_ZIPCODE
		**/
		static const std::string CardholderZipcode;

		/**
		* \brief
		* 	Parameter key for enabling or disabling card notification events outside of a transaction.
		*
		* KEY = CARD_NOTIFICATION_EVENTS
		**/
		static const std::string CardNotificationEvents;

		/**
		* \brief
		* 	Parameter key for Card Status collection in XML format.
		*
		* KEY = CARD_STATUS
		**/
		static const std::string CardStatus;

		/**
		* \brief
		* 	Parameter key for if DCC should be enabled for this transaction. Value is either true or false.
		*
		* KEY = DCC
		**/
		static const std::string Dcc;

		/**
		* \brief
		* 	Parameter key for Merchant's Address.
		*
		* KEY = MERCHANT_ADDRESS
		**/
		static const std::string MerchantAddress;

		/**
		* \brief
		* 	Parameter key for Merchant's City.
		*
		* KEY = MERCHANT_CITY
		**/
		static const std::string MerchantCity;

		/**
		* \brief
		* 	Parameter key for Merchant's State.
		*
		* KEY = MERCHANT_STATE
		**/
		static const std::string MerchantState;

		/**
		* \brief
		* 	Parameter key for Merchant's County.
		*
		* KEY = MERCHANT_COUNTY
		**/
		static const std::string MerchantCounty;

		/**
		* \brief
		* 	Parameter key for Merchant's Zip Code.
		*
		* KEY = MERCHANT_ZIP_CODE
		**/
		static const std::string MerchantZipCode;

		/**
		* \brief
		* 	Parameter key for Merchant's Country.
		*
		* KEY = MERCHANT_COUNTRY
		**/
		static const std::string MerchantCountry;

		/**
		* \brief
		* 	Parameter key for User Data.
		*
		* KEY = USER_DATA
		**/
		static const std::string UserData;

		/**
		* \brief
		* 	Parameter key for Extended Reference.
		*
		* KEY = EXTENDED_REFERENCE
		**/
		static const std::string ExtendedReference;

		/**
		* \brief
		* 	Parameter key for address verification result.
		*
		* KEY = ADDRESS_VERIFICATION_RESULT
		**/
		static const std::string AddressVerificationResult;

		/**
		* \brief
		* 	Parameter key for CSC verification result.
		*
		* KEY = CSC_VERIFICATION_RESULT
		**/
		static const std::string CscVerificationResult;

		/**
		* \brief
		* 	Parameter key for zip code verification result. Value can be Empty, Matched, NotChecked, NotMatched, NotSupplied or PartialMatch
		*
		* KEY = ZIP_CODE_VERIFICATION_RESULT
		**/
		static const std::string ZipCodeVerificationResult;

		/**
		* \brief
		* 	Parameter key for the pass thru command and response data.
		*
		* KEY = DATA
		**/
		static const std::string Data;

		/**
		* \brief
		* 	Parameter key for the Virtual Terminal Identifier.
		*
		* KEY = VIRTUAL_TERMINAL_ID
		**/
		static const std::string VirtualTerminalId;

		/**
		* \brief
		* 	Parameter key for the Virtual Transaction Key.
		*
		* KEY = VIRTUAL_TRANSACTION_KEY
		**/
		static const std::string VirtualTransactionKey;

		/**
		* \brief
		* 	Parameter key for the status of each virtual terminal configured on the current host terminal in XML format representing {@link ChipDnaStatus.VirtualTerminalStatus}.
		*
		* KEY = VIRTUAL_TERMINAL_STATUS
		**/
		static const std::string VirtualTerminalStatus;

		/**
		* \brief
		* 	Parameter key for Deferred Authorization Reason.
		*
		* KEY = DEFERRED_AUTHORIZATION_REASON
		**/
		static const std::string DeferredAuthorizationReason;

		/**
		* \brief
		* 	Parameter key for if Quick Chip should be enabled for this transaction. Value is either true or false.
		*
		* KEY = QUICK_CHIP
		**/
		static const std::string QuickChip;

		/**
		* \brief
		*	Parameter key for an API key.
		*
		* KEY = API_KEY
		*/
		static const std::string ApiKey;

		/**
		* \brief
		*	Parameter key for the result of calls to ConnectAndConfigure.
		*
		* KEY = CONNECT_AND_CONFIGURE_RESULT
		*/
		static const std::string ConnectAndConfigureResult;

		/**
		* \brief
		*	Parameter key for updates sent during configuration.
		*
		* KEY = CONFIGURATION_UPDATE
		*/
		static const std::string ConfigurationUpdate;

		/**
		* \brief
		*	Parameter key for the POS identifier
		*
		* KEY = POS_ID
		*/
		static const std::string PosId;

		/**
		* \brief
		*	Parameter key for the POS GUID.
		*
		* KEY = POS_GUID
		*/
		static const std::string PosGuid;

		/**
		* \brief
		*	Identifier for a transaction performed on the payment gateway.
		*
		* KEY = TRANSACTION_ID
		*/
		static const std::string TransactionId;

		/**
		* \brief
		* 	Parameter key for the reference id returned by schemes during online authorizations.
		*
		* KEY = SCHEME_REFERENCE_ID
		**/
		static const std::string SchemeReferenceId;

		/**
		* \brief
		*	Parameter key for customer vault identifier.
		*
		* KEY = CUSTOMER_VAULT_ID
		*/
		static const std::string CustomerVaultId;

		/**
		* \brief
		*	parameter key for customer vault command.
		*
		* KEY = CUSTOMER_VAULT_COMMAND
		*/
		static const std::string CustomerVaultCommand;

		/**
		* \brief
		* 	Parameter key for the currency conversion rate returned during DCC transactions.
		*
		* KEY = CURRENCY_CONVERSION_RATE
		**/
		static const std::string CurrencyConversionRate;

		/**
		* \brief
		* 	Parameter key for the currency conversion provider returned during DCC transactions.
		*
		* KEY = CURRENCY_CONVERSION_PROVIDER
		**/
		static const std::string CurrencyConversionProvider;

		/**
		* \brief
		* 	Parameter key for the currency conversion disclaimer returned during DCC transactions.
		*
		* KEY = CURRENCY_CONVERSION_DISCLAIMER
		**/
		static const std::string CurrencyConversionDisclaimer;

		/**
		* \brief
		* 	Parameter key for the STAN.
		*
		* KEY = STAN
		**/
		static const std::string Stan;

		/**
		* \brief
		*	Parameter key for the card holder first name.
		*
		* KEY = CARD_HOLDER_FIRST_NAME
		*/
		static const std::string CardHolderFirstName;

		/**
		* \brief
		*	Parameter key for the card holder last name.
		*
		* KEY = CARD_HOLDER_LAST_NAME
		*/
		static const std::string CardHolderLastName;

		/**
		*\brief
		*   Parameter key for merchant defined field one.
		*
		* KEY = MERCHANT_DEFINED_FIELD_01
		*/
		static const std::string MerchantDefinedField01;

		/**
		*\brief
		*   Parameter key for merchant defined field two.
		*
		* KEY = MERCHANT_DEFINED_FIELD_02
		*/
		static const std::string MerchantDefinedField02;

		/**
		*\brief
		*   Parameter key for merchant defined field three.
		*
		* KEY = MERCHANT_DEFINED_FIELD_03
		*/
		static const std::string MerchantDefinedField03;

		/**
		*\brief
		*   Parameter key for merchant defined field four.
		*
		* KEY = MERCHANT_DEFINED_FIELD_04
		*/
		static const std::string MerchantDefinedField04;

		/**
		*\brief
		*   Parameter key for merchant defined field five.
		*
		* KEY = MERCHANT_DEFINED_FIELD_05
		*/
		static const std::string MerchantDefinedField05;

		/**
		*\brief
		*   Parameter key for merchant defined field six.
		*
		* KEY = MERCHANT_DEFINED_FIELD_06
		*/
		static const std::string MerchantDefinedField06;

		/**
		*\brief
		*   Parameter key for merchant defined field seven.
		*
		* KEY = MERCHANT_DEFINED_FIELD_07
		*/
		static const std::string MerchantDefinedField07;

		/**
		*\brief
		*   Parameter key for merchant defined field eight.
		*
		* KEY = MERCHANT_DEFINED_FIELD_08
		*/
		static const std::string MerchantDefinedField08;

		/**
		*\brief
		*   Parameter key for merchant defined field nine.
		*
		* KEY = MERCHANT_DEFINED_FIELD_09
		*/
		static const std::string MerchantDefinedField09;

		/**
		*\brief
		*   Parameter key for merchant defined field ten.
		*
		* KEY = MERCHANT_DEFINED_FIELD_10
		*/
		static const std::string MerchantDefinedField10;

		/**
		*\brief
		*   Parameter key for merchant defined field eleven.
		*
		* KEY = MERCHANT_DEFINED_FIELD_11
		*/
		static const std::string MerchantDefinedField11;

		/**
		*\brief
		*   Parameter key for merchant defined field twelve.
		*
		* KEY = MERCHANT_DEFINED_FIELD_12
		*/
		static const std::string MerchantDefinedField12;

		/**
		*\brief
		*   Parameter key for merchant defined field thirteen.
		*
		* KEY = MERCHANT_DEFINED_FIELD_13
		*/
		static const std::string MerchantDefinedField13;

		/**
		*\brief
		*   Parameter key for merchant defined field fourteen.
		*
		* KEY = MERCHANT_DEFINED_FIELD_14
		*/
		static const std::string MerchantDefinedField14;

		/**
		*\brief
		*   Parameter key for merchant defined field fifteen.
		*
		* KEY = MERCHANT_DEFINED_FIELD_15
		*/
		static const std::string MerchantDefinedField15;

		/**
		*\brief
		*   Parameter key for merchant defined field sixteen.
		*
		* KEY = MERCHANT_DEFINED_FIELD_16
		*/
		static const std::string MerchantDefinedField16;

		/**
		*\brief
		*   Parameter key for merchant defined field seventeen.
		*
		* KEY = MERCHANT_DEFINED_FIELD_17
		*/
		static const std::string MerchantDefinedField17;

		/**
		*\brief
		*   Parameter key for merchant defined field eighteen.
		*
		* KEY = MERCHANT_DEFINED_FIELD_18
		*/
		static const std::string MerchantDefinedField18;

		/**
		*\brief
		*   Parameter key for merchant defined field nineteen.
		*
		* KEY = MERCHANT_DEFINED_FIELD_19
		*/
		static const std::string MerchantDefinedField19;

		/**
		*\brief
		*   Parameter key for merchant defined field twenty.
		*
		* KEY = MERCHANT_DEFINED_FIELD_20
		*/
		static const std::string MerchantDefinedField20;

		/**
		*\brief
		*   Parameter key for triggering auto confirmation of a transaction.
		*
		* KEY = AUTO_CONFIRM
		*/
		static const std::string AutoConfirm;

		/**
		*\brief
		*   Parameter key for triggering completion of background firmware update.
		*
		* KEY = COMPLETE_BACKGROUND_FIRMWARE_UPDATE
		*/
		static const std::string CompleteBackgroundFirmwareUpdate;

		/**
		*\brief
		*   Parameter key for the Tax Amount.
		*
		* KEY = TAX_AMOUNT
		*/
		static const std::string TaxAmount;

		/**
		*\brief
		*   Parameter key for the Purchase Order Number.
		*
		* KEY = PO_NUMBER
		*/
		static const std::string PurchaseOrderNumber;

		/**
		*\brief
		*   Parameter key for Address Line One in Billing Information.
		*
		* KEY = BILLING_ADDRESS_1
		*/
		static const std::string BillingAddress1;

		/**
		*\brief
		*   Parameter key for Address Line Two in Billing Information.
		*
		* KEY = BILLING_ADDRESS_2
		*/
		static const std::string BillingAddress2;

		/**
		*\brief
		*   Parameter key for the City in Billing Information.
		*
		* KEY = BILLING_CITY
		*/
		static const std::string BillingCity;

		/**
		*\brief
		*   Parameter key for the State in Billing Information.
		*
		* KEY = BILLING_STATE
		*/
		static const std::string BillingState;

		/**
		*\brief
		*   Parameter key for the Postal Code in Billing Information. Can be used interchangeably with BILLING_ZIP_CODE.
		*
		* KEY = BILLING_POSTAL_CODE
		*/
		static const std::string BillingPostalCode;

		/**
		*\brief
		*   Parameter key for the Zip Code in Billing Information. Can be used interchangeably with BILLING_POSTAL_CODE.
		*
		* KEY = BILLING_ZIP_CODE
		*/
		static const std::string BillingZipCode;

		/**
		*\brief
		*   Parameter key for the Country in Billing Information.
		*
		* KEY = BILLING_COUNTRY
		*/
		static const std::string BillingCountry;

		/**
		*\brief
		*   Parameter key for Email Address in Billing Information.
		*
		* KEY = BILLING_EMAIL_ADDRESS
		*/
		static const std::string BillingEmailAddress;

		/**
		*\brief
		*   Parameter key for Phone Number in Billing Information.
		*
		* KEY = BILLING_PHONE_NUMBER
		*/
		static const std::string BillingPhoneNumber;

		/**
		*\brief
		*   Parameter key for the result of Signature Verification.
		*
		* KEY = SIGNATURE_VERIFICATION_RESULT
		*/
		static const std::string SignatureVerificationResult;	};
}
#endif // PARAMETERKEYS_H