#ifndef PAYMENTENGINEERRORCODE_H
#define PAYMENTENGINEERRORCODE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Payment device error codes.
		**/
		enum  PaymentEngineErrorCode {

			/**
			* \brief
			* 	The transaction Authorization Type is invalid.
			*/
			InvalidTransactionAuthType,

			/**
			* \brief
			* 	A duplicate transaction entry has been found.
			*/
			DuplicateTransactionEntryFound,

			/**
			* \brief
			* 	Modification of the amount is not permitted.
			*/
			AmountModificationNotPermitted,

			/**
			* \brief
			* 	A duplicate transaction request entry has been found.
			*/
			DuplicateRequestEntryFound,

			/**
			* \brief
			* 	A duplicate transaction register entry has been found.
			*/
			DuplicateRegisterEntryFound,

			/**
			* \brief
			* 	The storage is corrupt and cannot be used.
			*/
			StorageCorrupt,

			/**
			* \brief
			* 	Invalid path.
			*/
			InvalidPath,

			/**
			* \brief
			* 	Access to the remote server has failed.
			*/
			RemoteServerAccessFailed,

			/**
			* \brief
			* 	Access to the remote server has been denied.
			*/
			RemoteServerAccessDenied,

			/**
			* \brief
			* 	The specified amount in the request is invalid.
			*/
			AmountInvalid,

			/**
			* \brief
			* 	The request does not contain an amount.
			*/
			AmountMissing,

			/**
			* \brief
			* 	The specified amount in the request is too large.
			*/
			AmountTooLarge,

			/**
			* \brief
			* 	The specified amount in the request is too small.
			*/
			AmountTooSmall,

			/**
			* \brief
			* 	The specified card in the request has been banned.
			*/
			CardBanned,

			/**
			* \brief
			* 	The card details referenced by the CardReference and CardHash could not be found.
			*/
			CardDetailsNotFound,

			/**
			* \brief
			* 	The card details referenced by the CardReference and CardHash are unavailable.
			*/
			CardDetailsUnavailable,

			/**
			* \brief
			* 	The specified CardEase reference in the request is invalid.
			*/
			CardEaseReferenceInvalid,

			/**
			* \brief
			* 	The request does not contain a CardEase reference.
			*/
			CardEaseReferenceMissing,

			/**
			* \brief
			* 	The specified card hash in the request is not valid.
			*/
			CardHashInvalid,

			/**
			* \brief
			* 	The specified card reference in the request is not valid.
			*/
			CardReferenceInvalid,

			/**
			* \brief
			* 	The specified card scheme in the request is not supported.
			*/
			CardSchemeNotSupported,

			/**
			* \brief
			* 	The specified card usage in the request has been exceeded.
			*/
			CardUsageExceeded,

			/**
			* \brief
			* 	No error code.
			*/
			Empty,

			/**
			* \brief
			* 	The specified card in the request has expired.
			*/
			ExpiredCard,

			/**
			* \brief
			* 	The specified expiry date in the request is invalid.
			*/
			ExpiryDateInvalid,

			/**
			* \brief
			* 	The request does not contain an expiry date.
			*/
			ExpiryDateMissing,

			/**
			* \brief
			* 	An invalid piece of information was sent in the request.
			*/
			InvalidData,

			/**
			* \brief
			* 	The specified request type is invalid.
			*/
			InvalidMessageType,

			/**
			* \brief
			* 	The request XML is invalid.
			*/
			InvalidXmlRequest,

			/**
			* \brief
			* 	The specified issue number in the request is invalid.
			*/
			IssueNoInvalid,

			/**
			* \brief
			* 	The request does not contain an issue number.
			*/
			IssueNoMissing,

			/**
			* \brief
			* 	The specified message type in the request is invalid.
			*/
			MessageTypeInvalid,

			/**
			* \brief
			* 	The message type in the request is missing.
			*/
			MessageTypeMissing,

			/**
			* \brief
			* 	The specified transaction in the request is not allowed.
			*/
			NotAllowed,

			/**
			* \brief
			* 	The specified PAN in the request fails the Luhn check.
			*/
			PanFailsLuhnCheck,

			/**
			* \brief
			* 	The specified PAN in the request is invalid.
			*/
			PanInvalid,

			/**
			* \brief
			* 	The request does not contain a PAN.
			*/
			PanMissing,

			/**
			* \brief
			* 	The specified PAN in the request is too long.
			*/
			PanTooLong,

			/**
			* \brief
			* 	The specified PAN in the request is too short.
			*/
			PanTooShort,

			/**
			* \brief
			* 	The specified card in the request is not yet effective.
			*/
			PreValidCard,

			/**
			* \brief
			* 	The specified start date in the request is invalid.
			*/
			StartDateInvalid,

			/**
			* \brief
			* 	The request does not contain a start date.
			*/
			StartDateMissing,

			/**
			* \brief
			* 	The CardEase platform is temporarily unavailable.
			*/
			TemporarilyUnavailable,

			/**
			* \brief
			* 	The specified terminal id in the request is disabled.
			*/
			TerminalIdDisabled,

			/**
			* \brief
			* 	The specified terminal id in the request is invalid.
			*/
			TerminalIdInvalid,

			/**
			* \brief
			* 	The request does not contain a terminal id.
			*/
			TerminalIdMissing,

			/**
			* \brief
			* 	The specified terminal id in the request is unknown.
			*/
			TerminalIdUnknown,

			/**
			* \brief
			* 	The specified terminal id usage in the request has been exceeded.
			*/
			TerminalUsageExceeded,

			/**
			* \brief
			* 	The transaction has already been refunded in full.
			*/
			TransactionAlreadyRefunded,

			/**
			* \brief
			* 	The specified transaction in the request has already been settled.
			*/
			TransactionAlreadySettled,

			/**
			* \brief
			* 	The specified transaction in the request has already been voided.
			*/
			TransactionAlreadyVoided,

			/**
			* \brief
			* 	The specified transaction has already been confirmed.
			*/
			TransactionAlreadyConfirmed,

			/**
			* \brief
			* 	The specified transaction key in the request is incorrect.
			*/
			TransactionKeyIncorrect,

			/**
			* \brief
			* 	The specified transaction key in the request is invalid.
			*/
			TransactionKeyInvalid,

			/**
			* \brief
			* 	The specified transaction key in the request is missing.
			*/
			TransactionKeyMissing,

			/**
			* \brief
			* 	The specified transaction in the request was not found.
			*/
			TransactionNotFound,

			/**
			* \brief
			* 	The specified transaction in the request was originally declined.
			*/
			TransactionOriginallyDeclined,

			/**
			* \brief
			* 	It is not possible to decrypt the XML.
			*/
			XmlDecryptionError,

			/**
			* \brief
			* 	The request does not contain all of the expected XML elements.
			*/
			XmlElementMissing,

			/**
			* \brief
			* 	The transaction source could not be determined.
			*/
			UnknownTransactionSource,

			/**
			* \brief
			* 	The specified transaction is not of type SALE.
			*/
			TransactionNotSale,

			/**
			* \brief
			* 	Offline is not supported.
			*/
			OfflineNotSupported,

			/**
			* \brief
			* 	The floor limit has been exceeded.
			*/
			FloorLimitExceeded,

			/**
			* \brief
			* 	The original transaction completion failed.
			*/
			OriginalTansactionCompletionFailed,

			/**
			* \brief
			* 	The transaction failed due to a communication error with the server.
			*/
			ServerCommunicationError,

			/**
			* \brief
			* 	The transaction failed due to an error in the server request.
			*/
			ServerRequestError,

			/**
			* \brief
			* 	The transaction failed due to an error in the server response.
			*/
			ServerResponseError,

			/**
			* \brief
			* 	The transaction failed as no response was received from the server.
			*/
			NoResponseFromServer,

			/**
			* \brief
			* 	The third digit of the service code indicates this is either an ATM or cash only card and cannot be used for a transaction.
			*/
			AtmCashOnlyCard,

			/**
			* \brief
			* 	The transaction was approved but not committed.
			*/
			TransactionNotCommitted,

			/**
			* \brief
			* 	Transaction type pre-auth cannot be confirmed.
			*/
			ConfirmPreAuthNotAllowed,

			/**
			* \brief
			* 	Transaction type pre-auth cannot be voided.
			*/
			VoidPreAuthNotAllowed,

			/**
			* \brief
			* 	Transaction type pre-auth cannot be authorised offline.
			*/
			PreAuthOfflineNotAllowed,

			/**
			* \brief
			* 	Unexpected deferred authorization response.
			*/
			DeferredAuthorizationResponseNotExpected,

			/**
			* \brief
			* 	Deferred authorization has expired.
			*/
			DeferredAuthorizationExpired,

			/**
			* \brief
			* 	Deferred authorization has not been processed online.
			*/
			DeferredAuthorizationNotProcessedOnline,

			/**
			* \brief
			* 	End of Day Tipping is not enabled on transaction.
			*/
			EndOfDayTippingNotEnabled,

			/**
			* \brief
			* 	Tipping is not allowed.
			*/
			TippingNotAllowed,

			/**
			* \brief
			* 	Modification of the gratuity is not applicable.
			*/
			GratuityModificationNotApplicable,

			/**
			* \brief
			* 	The offline transaction volume limit has been exceeded.
			*/
			OfflineTransactionVolumeLimitExceeded,

			/**
			* \brief
			* 	The offline transaction value limit has been exceeded
			*/
			OfflineTransactionValueLimitExceeded,

			/**
			* \brief
			* 	The original transaction completion is still being processed.
			*/
			OriginalTansactionCompletionInProgress,

			/**
			* \brief
			*	The API key is missing.
			*/
			ApiKeyMissing,

			/**
			* \brief
			*	The API key is invalid.
			*/
			ApiKeyInvalid,

			/**
			* \brief
			*	The POS GUID is missing.
			*/
			PosGuidMissing,

			/**
			* \brief
			*	The POS GUID is invalid.
			*/
			PosGuidInvalid,

			/**
			* \brief
			*	The Application ID is missing.
			*/
			ApplicationIdMissing,
			/**
			* \brief
			*	The transaction was rejected by the payment gateway.
			*/
			RejectedTransaction,

			/**
			* \brief
			*	The terminal is required to register with the payment gateway by calling ConnectAndConfigure.
			*/
			RegistrationRequired,

			/**
			* \brief
			*	Device registration failed.
			*/
			DeviceRegistrationFailed

		};


		struct PaymentEngineErrorCodeMapGenerator {
			static std::map<std::string, PaymentEngineErrorCode> CreateMap() {
				std::map<std::string, PaymentEngineErrorCode> map;
				map["InvalidTransactionAuthType"] = InvalidTransactionAuthType;
				map["DuplicateTransactionEntryFound"] = DuplicateTransactionEntryFound;
				map["AmountModificationNotPermitted"] = AmountModificationNotPermitted;
				map["DuplicateRequestEntryFound"] = DuplicateRequestEntryFound;
				map["DuplicateRegisterEntryFound"] = DuplicateRegisterEntryFound;
				map["StorageCorrupt"] = StorageCorrupt;
				map["InvalidPath"] = InvalidPath;
				map["RemoteServerAccessFailed"] = RemoteServerAccessFailed;
				map["RemoteServerAccessDenied"] = RemoteServerAccessDenied;
				map["AmountInvalid"] = AmountInvalid;
				map["AmountMissing"] = AmountMissing;
				map["AmountTooLarge"] = AmountTooLarge;
				map["AmountTooSmall"] = AmountTooSmall;
				map["CardBanned"] = CardBanned;
				map["CardDetailsNotFound"] = CardDetailsNotFound;
				map["CardDetailsUnavailable"] = CardDetailsUnavailable;
				map["CardEaseReferenceInvalid"] = CardEaseReferenceInvalid;
				map["CardEaseReferenceMissing"] = CardEaseReferenceMissing;
				map["CardHashInvalid"] = CardHashInvalid;
				map["CardReferenceInvalid"] = CardReferenceInvalid;
				map["CardSchemeNotSupported"] = CardSchemeNotSupported;
				map["CardUsageExceeded"] = CardUsageExceeded;
				map["Empty"] = Empty;
				map["ExpiredCard"] = ExpiredCard;
				map["ExpiryDateInvalid"] = ExpiryDateInvalid;
				map["ExpiryDateMissing"] = ExpiryDateMissing;
				map["InvalidData"] = InvalidData;
				map["InvalidMessageType"] = InvalidMessageType;
				map["InvalidXmlRequest"] = InvalidXmlRequest;
				map["IssueNoInvalid"] = IssueNoInvalid;
				map["IssueNoMissing"] = IssueNoMissing;
				map["MessageTypeMissing"] = MessageTypeMissing;
				map["NotAllowed"] = NotAllowed;
				map["PanFailsLuhnCheck"] = PanFailsLuhnCheck;
				map["PanInvalid"] = PanInvalid;
				map["PanMissing"] = PanMissing;
				map["PanTooLong"] = PanTooLong;
				map["PanTooShort"] = PanTooShort;
				map["PreValidCard"] = PreValidCard;
				map["StartDateInvalid"] = StartDateInvalid;
				map["StartDateMissing"] = StartDateMissing;
				map["TemporarilyUnavailable"] = TemporarilyUnavailable;
				map["TerminalIdDisabled"] = TerminalIdDisabled;
				map["TerminalIdInvalid"] = TerminalIdInvalid;
				map["TerminalIdMissing"] = TerminalIdMissing;
				map["TerminalIdUnknown"] = TerminalIdUnknown;
				map["TerminalUsageExceeded"] = TerminalUsageExceeded;
				map["TransactionAlreadyRefunded"] = TransactionAlreadyRefunded;
				map["TransactionAlreadySettled"] = TransactionAlreadySettled;
				map["TransactionAlreadyVoided"] = TransactionAlreadyVoided;
				map["TransactionAlreadyConfirmed"] = TransactionAlreadyConfirmed;
				map["TransactionKeyIncorrect"] = TransactionKeyIncorrect;
				map["TransactionKeyInvalid"] = TransactionKeyInvalid;
				map["TransactionKeyMissing"] = TransactionKeyMissing;
				map["TransactionNotFound"] = TransactionNotFound;
				map["TransactionOriginallyDeclined"] = TransactionOriginallyDeclined;
				map["BadXmlDecryptionErrorCard"] = XmlDecryptionError;
				map["XmlElementMissing"] = XmlElementMissing;
				map["UnknownTransactionSource"] = UnknownTransactionSource;
				map["TransactionNotSale"] = TransactionNotSale;
				map["OfflineNotSupported"] = OfflineNotSupported;
				map["FloorLimitExceeded"] = FloorLimitExceeded;
				map["OriginalTansactionCompletionFailed"] = OriginalTansactionCompletionFailed;
				map["ServerCommunicationError"] = ServerCommunicationError;
				map["ServerRequestError"] = ServerRequestError;
				map["ServerResponseError"] = ServerResponseError;
				map["NoResponseFromServer"] = NoResponseFromServer;
				map["AtmCashOnlyCard"] = AtmCashOnlyCard;
				map["TransactionNotCommitted"] = TransactionNotCommitted;
				map["ConfirmPreAuthNotAllowed"] = ConfirmPreAuthNotAllowed;
				map["VoidPreAuthNotAllowed"] = VoidPreAuthNotAllowed;
				map["PreAuthOfflineNotAllowed"] = PreAuthOfflineNotAllowed;
				map["DeferredAuthorizationResponseNotExpected"] = DeferredAuthorizationResponseNotExpected;
				map["DeferredAuthorizationExpired"] = DeferredAuthorizationExpired;
				map["DeferredAuthorizationNotProcessedOnline"] = DeferredAuthorizationNotProcessedOnline;
				map["EndOfDayTippingNotEnabled"] = EndOfDayTippingNotEnabled;
				map["TippingNotAllowed"] = TippingNotAllowed;
				map["OfflineTransactionVolumeLimitExceeded"] = OfflineTransactionVolumeLimitExceeded;
				map["OfflineTransactionValueLimitExceeded"] = OfflineTransactionValueLimitExceeded;
				map["GratuityModificationNotApplicable"] = GratuityModificationNotApplicable;
				map["OriginalTansactionCompletionInProgress"] = OriginalTansactionCompletionInProgress;
				map["ApiKeyMissing"] = ApiKeyMissing;
				map["ApiKeyInvalid"] = ApiKeyInvalid;
				map["PosGuidMissing"] = PosGuidMissing;
				map["PosGuidInvalid"] = PosGuidInvalid;
				map["ApplicationIdMissing"] = ApplicationIdMissing;
				map["RejectedTransaction"] = RejectedTransaction;
				map["RegistrationRequired"] = RegistrationRequired;
				map["DeviceRegistrationFailed"] = DeviceRegistrationFailed;
				return map;
			}
		};
		
		/**
		* \brief
		* 	Converts a string to a {@link PaymentEngineErrorCode} value.
		**/
		const std::map<std::string, PaymentEngineErrorCode> StringToPaymentEngineErrorCode = PaymentEngineErrorCodeMapGenerator::CreateMap();
	}
}
#endif