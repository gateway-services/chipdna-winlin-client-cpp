#ifndef PAYMENTDEVICEERRORCODE_H
#define PAYMENTDEVICEERRORCODE_H

#include <map>

 namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	The error codes for PaymentDeviceException
		**/
		enum PaymentDeviceErrorCode {

			/**
			* \brief
			* 	Payment device is not initialized
			*/
			PaymentDeviceNotInitialized,

			/**
			* \brief
			* 	Error parsing amount
			*/
			ErrorParsingAmount,

			/**
			* \brief
			* 	Transaction processing error
			*/
			TransactionProcessingError,

			/**
			* \brief
			* 	Unexpected Voice Referral Response
			*/
			VoiceReferralResponseNotExpected,

			/**
			* \brief
			* 	Unexpected Deferred Authorization Response
			*/
			DeferredAuthorizationResponseNotExpected,

			/**
			* \brief
			* 	Transaction requested for confirm or void not found
			*/
			TransactionForConfirmVoidNotFound,

			/**
			* \brief
			* 	Terminal properties missing
			*/
			TerminalPropertiesMissing,

			/**
			* \brief
			* 	Configuration missing
			*/
			DeviceConfigMissing,

			/**
			* \brief
			* 	Unsupported protocol
			*/
			DeviceConfigProtocolUnsupported,

			/**
			* \brief
			* 	Error in device config protocol value
			*/
			DeviceConfigProtocolValueError,

			/**
			* \brief
			* 	Error in device config port value
			*/
			DeviceConfigPortValueError,

			/**
			* \brief
			* 	Error in TCP/IP value for device config
			*/
			DeviceConfigTcpIpValueError,

			/**
			* \brief
			* 	Transaction Reference is missing
			*/
			TransactionReferenceMissing,

			/**
			* \brief
			* 	Voice Referral Auth code is missing
			*/
			VoiceReferralAuthCodeMissing,

			/**
			* \brief
			* 	Cannot continue when there is no paused transaction
			*/
			CannotContinueTransactionNotPaused,

			/**
			* \brief
			* 	Transaction Update not allowed
			*/
			TransactionUpdateNotAllowed,

			/**
			* \brief
			* 	Transaction Update parameters missing
			*/
			TransactionUpdateParametersMissing,

			/**
			* \brief
			* 	Voice Referral Confirm for for different amount not allowed
			*/
			ConfirmVoiceReferralDifferentAmountNotAllowed,

			/**
			* \brief
			*	 Release card not supported
			*/
			ReleaseCardNotSupported,

			/**
			* \brief
			* 	Force Decline not allowed
			*/
			TransactionForceDeclineNotAllowed,

			/**
			* \brief
			* 	PINPad does not support refunds
			*/
			PinPadRefundsNotSupported,

			/**
			* \brief
			* 	(PINPad) Transaction Terminated.
			*/
			PinPadInvalidData,

			/**
			* \brief
			* 	Unable to initialize PIN pad for operation.
			*/
			UnableToInitializePinpad,

			/**
			* \brief
			* 	The transaction could not be started on the PIN pad.
			*/
			UnableToStartPinpadProcess,

			/**
			* \brief
			* 	Failed to transmit message to PIN pad.
			*/
			FailedToTransmitPinpadMessage,

			/**
			* \brief
			* 	The connection to the PINpad is closed.
			*/
			PinpadConnectionClosed,

			/**
			* \brief
			* 	The request received from the PIN pad is not expected
			*/
			UnexpectedRequestFromPinpad,

			/**
			* \brief
			* 	Terminal has not been configured correctly to perform a transaction (a property is missing).
			*/
			TerminalConfigurationError,

			/**
			* \brief
			* 	(PINPad) Transaction Terminated.
			*/
			PinPadTransactionTerminated,

			/**
			* \brief
			* 	(Chip) Application Selection Failure.
			*/
			ChipApplicationSelectionFailure,

			/**
			* \brief
			* 	(Chip) Initiate Application Processing Failure.
			*/
			ChipInitiateApplicationProcessingFailure,

			/**
			* \brief
			* 	(Chip) Offline Data Authentication Failure.
			*/
			ChipOfflineDataAuthenticationFailure,

			/**
			* \brief
			* 	(Chip) Process Restrictions Failure.
			*/
			ChipProcessRestrictionsFailure,

			/**
			* \brief
			* 	(Chip) Terminal Risk Management Failure.
			*/
			ChipTerminalRiskManagementFailure,

			/**
			* \brief
			* 	(Chip) Cardholder Verification Method Failure.
			*/
			ChipCardholderVerificationMethodFailure,

			/**
			* \brief
			* 	(Chip) Terminal Action Analysis Failure.
			*/
			ChipTerminalActionAnalysisFailure,

			/**
			* \brief
			* 	(Chip) Card Action Analysis Failure.
			*/
			ChipCardActionAnalysisFailure,

			/**
			* \brief
			* 	(Chip) Completion Failure.
			*/
			ChipCompletionFailure,

			/**
			* \brief
			* 	(EPOS) Transaction Terminated.
			*/
			EposTransactionTerminated,

			/**
			* \brief
			* 	(Chip) No Answer to Reset.
			*/
			ChipNoAnswerToReset,

			/**
			* \brief
			* 	(Swipe) Read Failure.
			*/
			SwipeReadFailure,

			/**
			* \brief
			* 	(Chip) Card Removed.
			*/
			ChipCardRemoved,

			/**
			* \brief
			* 	(PINPad) User Cancelled.
			*/
			PinPadUserCancelled,

			/**
			* \brief
			* 	(Chip) No Supported Applications.
			*/
			ChipNoSupportedApplications,

			/**
			* \brief
			* 	(Chip) Card Blocked.
			*/
			ChipCardBlocked,

			/**
			* \brief
			* 	(Chip) Read Failure.
			*/
			ChipReadFailure,

			/**
			* \brief
			* 	Terminal has not been configured to support the selected application.
			*/
			ApplicationNotSupported,

			/**
			* \brief
			* 	The third digit of the service code indicates this is either an ATM or cash only card and cannot be used for a transaction.
			*/
			AtmCashOnlyCard,

			/**
			* \brief
			* 	(PIN pad) CardHolder Action Timed Out.
			*/
			CardHolderActionTimedOut,

			/**
			* \brief
			* 	Invalid card, card responded incorrectly, no MSR fall back allowed.
			*/
			InvalidCardResponseError,

			/**
			* \brief
			* 	Transaction already in progress.
			*/
			TransactionAlreadyInProgressError,

			/**
			* \brief
			* 	Data missing from command APDU (data field should list missing object(s)).
			*/
			MissingDataInCommandError,

			/**
			*\brief
			* 	Missing file (data field should list missing file).
			*/
			MissingFileError,

			/**
			* \brief
			* 	P2PE was not enabled
			*/
			PinpadP2PeDisabled,

			/**
			* \brief
			* 	Command not available
			*/
			ImproperCommand,

			/**
			* \brief
			* 	Command not supported
			*/
			UnsupportedCommand,

			/**
			* \brief
			* 	Improper command sequence used
			*/
			InvalidCommandSequence,

			/**
			* \brief
			* 	Card did not respond as expected. May be expired or blocked
			*/
			BadCard,

			/**
			* \brief
			* 	Card is expired
			*/
			ExpiredCard,

			/**
			* \brief
			* 	The card details are unavailable.
			*/
			CardDetailsUnavailable,

			/**
			* \brief
			* 	The card has been used too many times on this payment system.
			*/
			CardUsageExceeded,

			/**
			* \brief
			* 	Amount invalid
			*/
			PinPadAmountInvalid,

			/**
			* \brief
			* 	Amount too large
			*/
			PinpadAmountTooLarge,

			/**
			* \brief
			* 	More than one card detected
			*/
			ContactlessCollision,

			/**
			* \brief
			* 	Amount is zero
			*/
			ContactlessAmountZero,

			/**
			* \brief
			* 	Contactless device requested contact transaction. Either Swipe or use Chip
			*/
			ContactlessUseAnotherInterface,

			/**
			* \brief
			* 	Use Chip
			*/
			ContactlessUseChip,

			/**
			* \brief
			* 	Misconfiguration on DCC transaction support.
			**/
			DccTransactionsNotSupported,

			/**
			* \brief
			*	A new pass thru session cannot be opened because one is already open.
			**/
			PassThruSessionAlreadyOpen,

			/**
			* \brief
			*	There is no open pass thru session to close.
			**/
			PassThruSessionIsNotOpen,

			/**
			* \brief
			*	A pass thru session cannot be opened because a transaction is in progress.
			**/
			TransactionInProgress,

			/**
			* \brief
			*	A transaction cannot be started because ChipDNA is in a pass thru session.
			**/
			PassThruSessionInProgress,

			/**
			* \brief
			* 	A pass thru session cannot be opened because one has already been opened but ChipDNA is waiting for the device to become available.
			**/
			PassThruSessionAlreadyWaitingToOpen,

			/**
			* \brief
			* 	This payment device does not support pass thru.
			**/
			PassThruNotSupported,

			/**
			* \brief
			* 	This command is not found in the configured whitelist file so cannot be used via pass thru.
			**/
			PaymentDeviceCommandNotAllowed,

			/**
			* \brief
			* 	Pass thru commands cannot be processed because configuration is missing.
			**/
			PassThruConfigMissing,

			/**
			* \brief
			* 	The transaction cannot continue because the presented card is a allowlisted non-payment card.
			**/
			AllowlistedCardPresented,

			/**
			* \brief
			* 	Online PIN key is missing, transaction requiring Online PIN cannot be carried out.
			**/
			OnlinePinKeyMissing,
		};

		struct PaymentDeviceErrorCodeMapGenerator {
			static std::map<std::string, PaymentDeviceErrorCode> CreateMap() {
				std::map<std::string, PaymentDeviceErrorCode> map;
				map["PaymentDeviceNotInitialized"] = PaymentDeviceNotInitialized;
				map["ErrorParsingAmount"] = ErrorParsingAmount;
				map["TransactionProcessingError"] = TransactionProcessingError;
				map["VoiceReferralResponseNotExpected"] = VoiceReferralResponseNotExpected;
				map["DeferredAuthorizationResponseNotExpected"] = DeferredAuthorizationResponseNotExpected;
				map["TransactionForConfirmVoidNotFound"] = TransactionForConfirmVoidNotFound;
				map["TerminalPropertiesMissing"] = TerminalPropertiesMissing;
				map["DeviceConfigMissing"] = DeviceConfigMissing;
				map["DeviceConfigProtocolUnsupported"] = DeviceConfigProtocolUnsupported;
				map["DeviceConfigProtocolValueError"] = DeviceConfigProtocolValueError;
				map["DeviceConfigPortValueError"] = DeviceConfigPortValueError;
				map["DeviceConfigTcpIpValueError"] = DeviceConfigTcpIpValueError;
				map["TransactionReferenceMissing"] = TransactionReferenceMissing;
				map["VoiceReferralAuthCodeMissing"] = VoiceReferralAuthCodeMissing;
				map["CannotContinueTransactionNotPaused"] = CannotContinueTransactionNotPaused;
				map["TransactionUpdateNotAllowed"] = TransactionUpdateNotAllowed;
				map["TransactionUpdateParametersMissing"] = TransactionUpdateParametersMissing;
				map["ConfirmVoiceReferralDifferentAmountNotAllowed"] = ConfirmVoiceReferralDifferentAmountNotAllowed;
				map["ReleaseCardNotSupported"] = ReleaseCardNotSupported;
				map["TransactionForceDeclineNotAllowed"] = TransactionForceDeclineNotAllowed;
				map["PinPadRefundsNotSupported"] = PinPadRefundsNotSupported;
				map["PinPadInvalidData"] = PinPadInvalidData;
				map["UnableToInitializePinpad"] = UnableToInitializePinpad;
				map["UnableToStartPinpadProcess"] = UnableToStartPinpadProcess;
				map["FailedToTransmitPinpadMessage"] = FailedToTransmitPinpadMessage;
				map["PinpadConnectionClosed"] = PinpadConnectionClosed;
				map["UnexpectedRequestFromPinpad"] = UnexpectedRequestFromPinpad;
				map["TerminalConfigurationError"] = TerminalConfigurationError;
				map["PinPadTransactionTerminated"] = PinPadTransactionTerminated;
				map["ChipApplicationSelectionFailure"] = ChipApplicationSelectionFailure;
				map["ChipInitiateApplicationProcessingFailure"] = ChipInitiateApplicationProcessingFailure;
				map["ChipOfflineDataAuthenticationFailure"] = ChipOfflineDataAuthenticationFailure;
				map["ChipProcessRestrictionsFailure"] = ChipProcessRestrictionsFailure;
				map["ChipTerminalRiskManagementFailure"] = ChipTerminalRiskManagementFailure;
				map["ChipCardholderVerificationMethodFailure"] = ChipCardholderVerificationMethodFailure;
				map["ChipTerminalActionAnalysisFailure"] = ChipTerminalActionAnalysisFailure;
				map["ChipCardActionAnalysisFailure"] = ChipCardActionAnalysisFailure;
				map["ChipCompletionFailure"] = ChipCompletionFailure;
				map["EposTransactionTerminated"] = EposTransactionTerminated;
				map["ChipNoAnswerToReset"] = ChipNoAnswerToReset;
				map["SwipeReadFailure"] = SwipeReadFailure;
				map["ChipCardRemoved"] = ChipCardRemoved;
				map["PinPadUserCancelled"] = PinPadUserCancelled;
				map["ChipNoSupportedApplications"] = ChipNoSupportedApplications;
				map["ChipCardBlocked"] = ChipCardBlocked;
				map["ChipReadFailure"] = ChipReadFailure;
				map["ApplicationNotSupported"] = ApplicationNotSupported;
				map["AtmCashOnlyCard"] = AtmCashOnlyCard;
				map["CardHolderActionTimedOut"] = CardHolderActionTimedOut;
				map["InvalidCardResponseError"] = InvalidCardResponseError;
				map["TransactionAlreadyInProgressError"] = TransactionAlreadyInProgressError;
				map["MissingDataInCommandError"] = MissingDataInCommandError;
				map["MissingFileError"] = MissingFileError;
				map["PinpadP2PeDisabled"] = PinpadP2PeDisabled;
				map["ImproperCommand"] = ImproperCommand;
				map["UnsupportedCommand"] = UnsupportedCommand;
				map["InvalidCommandSequence"] = InvalidCommandSequence;
				map["BadCard"] = BadCard;
				map["ExpiredCard"] = ExpiredCard;
				map["CardDetailsUnavailable"] = CardDetailsUnavailable;
				map["CardUsageExceeded"] = CardUsageExceeded;
				map["PinPadAmountInvalid"] = PinPadAmountInvalid;
				map["PinpadAmountTooLarge"] = PinpadAmountTooLarge;
				map["ContactlessCollision"] = ContactlessCollision;
				map["ContactlessAmountZero"] = ContactlessAmountZero;
				map["ContactlessUseAnotherInterface"] = ContactlessUseAnotherInterface;
				map["ContactlessUseChip"] = ContactlessUseChip;
				map["DccTransactionsNotSupported"] = DccTransactionsNotSupported;
				map["PassThruSessionAlreadyOpen"] = PassThruSessionAlreadyOpen;
				map["PassThruSessionIsNotOpen"] = PassThruSessionIsNotOpen;
				map["TransactionInProgress"] = TransactionInProgress;
				map["PassThruSessionInProgress"] = PassThruSessionInProgress;
				map["PassThruSessionAlreadyWaitingToOpen"] = PassThruSessionAlreadyWaitingToOpen;
				map["PassThruNotSupported"] = PassThruNotSupported;
				map["PaymentDeviceCommandNotAllowed"] = PaymentDeviceCommandNotAllowed;
				map["PassThruConfigMissing"] = PassThruConfigMissing;
				map["AllowlistedCardPresented"] = AllowlistedCardPresented;
				map["OnlinePinKeyMissing"] = OnlinePinKeyMissing;

				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link PaymentDeviceErrorCode} value.
		**/
		const std::map<std::string, PaymentDeviceErrorCode> StringToPaymentDeviceErrorCode = PaymentDeviceErrorCodeMapGenerator::CreateMap();
	}
}

#endif