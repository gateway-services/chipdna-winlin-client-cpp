#ifndef CHIPDNAERRORCODE_H
#define CHIPDNAERRORCODE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Configuration error codes that can be returned by ChipDNA.
		*
		*/
		enum ChipDnaErrorCode {
			/**
			* \brief
			* 	ChipDNA encountered an unexpected error.
			*/
			UnexpectedChipDnaError,

			/**
			* \brief
			* 	Not enough disk space for ChipDNA to perform transactions.
			*/
			InsufficientDiskSpace,

			/**
			* \brief
			* 	ChipDNA application is disabled.
			*/
			ApplicationDisabled,

			/**
			* \brief
			* 	ChipDNA has not been successfully initialized
			*/
			SystemNotInitialized,

			/**
			* \brief
			* 	ChipDNA already initialized.
			*/
			SystemInitializeDuplicate,

			/**
			* \brief
			* 	A configuration update from the TMS is required.
			*/
			ConfigurationUpdateRequired,

			/**
			* \brief
			* 	ChipDNA Storage has not been successfully initialized.
			*/
			StorageNotInitialized,

			/**
			* \brief
			*	 Terminal ID not found in initialized ChipDNA server
			*/
			TerminalIdMismatch,

			/**
			* \brief
			* 	Terminal ID not provided.
			**/
			TerminalIdMissing,

			/**
			* \brief
			* 	Transaction already in progress
			*/
			TransactionInProgress,
			/**
			* \brief
			* 	Transaction update is still being processed.
			**/
			TransactionUpdateInProgress,

			/**
			* \brief
			* 	No transaction in progress.
			*/
			TransactionNotStarted,

			/**
			* \brief
			* 	Payment device update in progress.
			*/
			PaymentDeviceUpdateInProgress,

			/**
			* \brief
			* 	No payment hardware has been detected.
			*/
			NoPaymentDeviceFound,

			/**
			* \brief
			* 	Linked refunds are not supported.
			*/
			LinkedRefundsNotSupported,

			/**.
			* \brief
			* 	Invalid TMS configuration format.
			*/
			InvalidConfigurationFormat,

			/**
			* \brief
			* 	TMS configuration not found.
			*/
			TerminalConfigurationNotFound,

			/**
			* \brief
			* 	Duplicate terminal detected
			*/
			DuplicateTerminal,

			/**
			* \brief
			* 	Duplicate payment device detected.
			*/
			DuplicatePaymentDevice,

			/**
			* \brief
			* 	Encryption certificate is required.
			*/
			EncryptionCertRequired,

			/**
			* \brief
			*	Encryption certificate is invalid.
			**/
			EncryptionCertInvalid,

			/**
			* \brief
			* 	Payment device is inactive.
			**/
			InactivePaymentDevice,

			/**
			* \brief
			*	Device model is not supported by ChipDNA.
			**/
			UnsupportedPaymentDevice,

			/**
			* \brief
			* 	Error while generating MAC.
			**/
			MacGenerationFailed,

			/**
			* \brief
			* 	Transaction not paused.
			**/
			TransactionNotPaused,

			/**
			* \brief
			* 	Transaction type Account Verification not supported.
			**/
			AccountVerificationNotSupported,

			/**
			* \brief
			* 	Standalone refunds are not supported.
			**/
			StandaloneRefundsNotSupported,

			/**
			* \brief
			* 	PAN Key Entry not supported.
			**/
			PanKeyEntryNotSupported,

			/**
			* \brief
			* 	Signature Verification not supported.
			**/
			SignatureVerificationNotSupported,

			/**
			* \brief
			* 	Data required for void is missing.
			**/
			TransactionVoidDataMissing,

			/**
			* \brief
			* 	Transaction type Account Verification cannot be authorized offline.
			**/
			AccountVerificationOfflineNotAllowed,

			/**
			* \brief
			* 	PAN Key Entry transactions cannot be authorized offline.
			**/
			PanKeyEntryOfflineNotAllowed,

			/**
			* \brief
			* 	Transaction update not allowed.
			**/
			TransactionUpdateNotAllowed,

			/**
			* \brief
			* 	Misconfiguration on DCC transaction support.
			**/
			DccTransactionsNotSupported,

			/**
			* \brief
			* 	Misconfiguration on TippingSupported for End of Day Tipping.
			**/
			EndOfDayTippingNotSupported,

			/**
			* \brief
			* 	Misconfiguration on TippingSupported for On Device Tipping.
			**/
			OnDeviceTippingNotSupported,

			/**
			* \brief
			* 	Misconfiguration on TippingSupported.
			**/
			TippingNotSupported,

			/**
			* \brief
			* 	Common Use is not supported.
			**/
			CommonUseNotSupported,

			/**
			* \brief
			* 	Virtual Terminal was not found.
			**/
			VirtualTerminalNotFound,

			/**
			* \brief
			* 	Virtual Terminal ID is required, but was not supplied.
			**/
			VirtualTerminalIdMissing,

			/**
			* \brief
			* 	Virtual Transaction Key is required, but was not supplied.
			**/
			VirtualTransactionKeyMissing,

			/**
			* \brief
			* 	 The command cannot be processed because this payment device is not available.
			**/
			PaymentDeviceUnavailable,

			/**
			* \brief
			* 	The command cannot be processed because this payment device does not exist.
			**/
			PaymentDeviceDoesNotExist,

			/**
			* \brief
			* 	Misconfiguration on Quick Chip transaction support.
			**/
			QuickChipTransactionsNotSupported,

			/**
			* \brief
			* Error in posGuid attribute for terminal config is invalid.
			*/
			TerminalConfigPosGuidValueError,

			/**
			* \brief
			* The API key was required but not supplied.
			*/
			ApiKeyMissing,

			/**
			* \brief
			* 	The registration server details were required but not supplied.
			*/
			RegistrationServerConfigurationMissing,

			/**
			* \brief
			* 	The registration request has failed.
			*/
			RegistrationFailed,

			/**
			* \brief
			* 	Registration failed to retrieve a terminal ID.
			*/
			RegistrationFailedToRetrieveTerminalId,

			/**
			* \brief
			* 	Registration failed to retrieve a transaction key.
			*/
			RegistrationFailedToRetrieveTransactionKey,

			/**
			* \brief
			* 	A call to connect and configure is required.
			*/
			ConnectAndConfigureRequired
		};

		struct ChipDnaErrorCodeMapGenerator {
			static std::map<std::string, ChipDnaErrorCode> CreateMap() {
				std::map<std::string, ChipDnaErrorCode> map;
				map["UnexpectedChipDnaError"] = UnexpectedChipDnaError;
				map["SystemNotInitialized"] = SystemNotInitialized;
				map["SystemInitializeDuplicate"] = SystemInitializeDuplicate;
				map["ConfigurationUpdateRequired"] = ConfigurationUpdateRequired;
				map["UnexpectedChipDnaError"] = UnexpectedChipDnaError;
				map["StorageNotInitialized"] = StorageNotInitialized;
				map["TerminalIdMismatch"] = TerminalIdMismatch;
				map["TransactionInProgress"] = TransactionInProgress;
				map["TransactionNotStarted"] = TransactionNotStarted;
				map["PaymentDeviceUpdateInProgress"] = PaymentDeviceUpdateInProgress;
				map["NoPaymentDeviceFound"] = NoPaymentDeviceFound;
				map["LinkedRefundsNotSupported"] = LinkedRefundsNotSupported;
				map["InvalidConfigurationFormat"] = InvalidConfigurationFormat;
				map["TerminalConfigurationNotFound"] = TerminalConfigurationNotFound;
				map["DuplicateTerminal"] = DuplicateTerminal;
				map["DuplicatePaymentDevice"] = DuplicatePaymentDevice;
				map["EncryptionCertRequired"] = EncryptionCertRequired;
				map["TransactionVoidDataMissing"] = TransactionVoidDataMissing;
				map["StandaloneRefundsNotSupported"] = StandaloneRefundsNotSupported;
				map["AccountVerificationNotSupported"] = AccountVerificationNotSupported;
				map["TransactionNotPaused"] = TransactionNotPaused;
				map["MacGenerationFailed"] = MacGenerationFailed;
				map["UnsupportedPaymentDevice"] = UnsupportedPaymentDevice;
				map["InactivePaymentDevice"] = InactivePaymentDevice;
				map["EncryptionCertInvalid"] = EncryptionCertInvalid;
				map["TransactionUpdateInProgress"] = TransactionUpdateInProgress;
				map["TerminalIdMissing"] = TerminalIdMissing;
				map["InsufficientDiskSpace"] = InsufficientDiskSpace;
				map["AccountVerificationOfflineNotAllowed"] = AccountVerificationOfflineNotAllowed;
				map["PanKeyEntryOfflineNotAllowed"] = PanKeyEntryOfflineNotAllowed;
				map["TransactionUpdateNotAllowed"] = TransactionUpdateNotAllowed;
				map["DccTransactionsNotSupported"] = DccTransactionsNotSupported;
				map["EndOfDayTippingNotSupported"] = EndOfDayTippingNotSupported;
				map["OnDeviceTippingNotSupported"] = OnDeviceTippingNotSupported;
				map["TippingNotSupported"] = TippingNotSupported;
				map["CommonUseNotSupported"] = CommonUseNotSupported;
				map["VirtualTerminalNotFound"] = VirtualTerminalNotFound;
				map["VirtualTerminalIdMissing"] = VirtualTerminalIdMissing;
				map["PaymentDeviceUnavailable"] = PaymentDeviceUnavailable;
				map["PaymentDeviceDoesNotExist"] = PaymentDeviceDoesNotExist;
				map["QuickChipTransactionsNotSupported"] = QuickChipTransactionsNotSupported;
				map["TerminalConfigPosGuidValueError"] = TerminalConfigPosGuidValueError;
				map["ApiKeyMissing"] = ApiKeyMissing;
				map["RegistrationServerConfigurationMissing"] = RegistrationServerConfigurationMissing;
				map["RegistrationFailed"] = RegistrationFailed;
				map["RegistrationFailedToRetrieveTerminalId"] = RegistrationFailedToRetrieveTerminalId;
				map["RegistrationFailedToRetrieveTrnasactionkey"] = RegistrationFailedToRetrieveTransactionKey;
				map["ConnectionAndConfigureRequired"] = ConnectAndConfigureRequired;

				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link ChipDnaErrorCode} value.
		**/
		const std::map<std::string, ChipDnaErrorCode> StringToChipDnaErrorCode = ChipDnaErrorCodeMapGenerator::CreateMap();
	}
}
#endif