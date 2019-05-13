#ifndef CHIPDNASTATUS_H
#define CHIPDNASTATUS_H

#include <string>
#include <vector>
#include <map>
#include "parameterset.h"
#include "chipdnaserverissue.h"
#include "paymentdeviceconfigurationstate.h"
#include "paymentdeviceavailabilityerror.h"
#include "paymentplatformstate.h"

namespace ChipDnaClientLib {

	/**
	* \brief
	*	Struct for containing availability error information.
	**/
	typedef struct {
		std::string key;
		std::string value;
	} AvailabilityErrorStruct;

	/**
	* \brief
	* 	Data object with payment device status.
	**/
	typedef struct {
		std::string DeviceId;
		std::string DeviceModel;
		std::string IsAvailable;
		std::string ConfigurationState;
		std::string IsProcessingTransaction;
		std::string AvailabilityError;
		std::vector<AvailabilityErrorStruct> AvailabilityErrorList;

	} PaymentDeviceStruct;

#pragma region ChipDna Status XML Tags

	//VERSION_INFORMATION
	static const std::string VERSION_TAG = "Parameter";
	static const std::string VERSION_KEY = "Key";
	static const std::string VERSION_VALUE = "Value";

	// Payment Platform Status
	static const std::string PAYMENT_PLATFORM_TAG = "PaymentPlatformStatus";
	static const std::string MACHINE_LOCAL_DATE_TIME = "MachineLocalDateTime";
	static const std::string PAYMENT_PLATFORM_LOCAL_DATE_TIME = "PaymentPlatformLocalDateTime";
	static const std::string PAYMENT_PLATFORM_FORM_LOCAL_DATE_TIME_FORMAT = "PaymentPlatformLocalDateTimeFormat";
	static const std::string STATE = "State";

	// Request Queue Status
	static const std::string REQUEST_QUEUE_TAG = "RequestQueueStatus";
	static const std::string CREDIT_REQUEST_COUNT = "CreditRequestCount";
	static const std::string CREDIT_CONFIRM_REQUEST_COUNT = "CreditConfirmRequestCount";
	static const std::string CREDIT_VOID_REQUEST_COUNT = "CreditVoidRequestCount";
	static const std::string DEBIT_REQUEST_COUNT = "DebitRequestCount";
	static const std::string DEBIT_CONFIRM_REQUEST_COUNT = "DebitConfirmRequestCount";
	static const std::string DEBIT_VOID_REQUEST_COUNT = "DebitVoidRequestCount";

	// Payment Device Status
	static const std::string PAYMENT_DEVICE_TAG = "PaymentDeviceStatus";
	static const std::string DEVICE_ID = "ConfiguredDeviceId";
	static const std::string DEVICE_MODEL = "ConfiguredDeviceModel";
	static const std::string DEVICE_STATE = "ConfigurationState";
	static const std::string PROCESSING_TRANSACTION = "ProcessingTransaction";
	static const std::string IS_AVAILABLE = "IsAvailable";
	static const std::string AVAILABILITY_ERROR = "AvailabilityError";
	static const std::string AVAILABILITY_ERROR_TAG = "AvailabilityErrorInformation";
	static const std::string PAYMENT_DEVICE_AVAILABILITY_ERROR = "PaymentDeviceAvailabilityErrorInformation";

	// ChipDNA Status
	static const std::string SERVER_STATUS_TAG = "ServerStatus";
	static const std::string IS_PROCESSING_TRANSACTION = "IsProcessingTransaction";
	static const std::string CHIPDNA_SERVER_ISSUE = "ChipDnaServerIssue";

	// TMS Status
	static const std::string DAYS_UNTIL_UPDATE_IS_REQUIRED = "DaysUntilConfigUpdateIsRequired";
	static const std::string LAST_CONFIG_UPDATE_DATE_TIME = "LastConfigUpdateDateTime";
	static const std::string REQUIRED_CONFIG_UPDATE_DATE_TIME = "RequiredConfigUpdateDateTime";

	// Virtual Terminal Status
	static const std::string VIRTUAL_TERMINAL_STATUS_TAG = "VirtualTerminalStatus";
	static const std::string VIRTUAL_TERMINAL_ID = "VirtualTerminalId";
	static const std::string VIRTUAL_TERMINAL_ENABLED = "VirtualTerminalEnabled";

#pragma endregion

	/**
	* \brief
	* 	ChipDNA container class to store the parsed response from {@link ClientHelper::GetStatus}.
	**/
	class ChipDnaStatus {
	public:

#pragma region ChipDnaStatus Aux Classes

		/**
		* \brief
		*	Key-Value class for device availability error information.
		**/
		class PaymentDeviceAvailabilityErrorInformation {
		public:
			/**
			* \brief
			* 	Gets the error name
			*/
			std::string GetName();

			/**
			* \brief
			* 	Gets the error description
			*/
			std::string GetValue();

			/**
			* \brief
			* 	Gets the string representation of the device availability error
			*/
			std::string ToString();

			/**
			* \brief
			* 	Default constructor.
			*/
			PaymentDeviceAvailabilityErrorInformation();

			/**
			* \brief
			* 	Construct the class with the error name and description
			*/
			PaymentDeviceAvailabilityErrorInformation(std::string, std::string);

		private:
			std::string name;
			std::string value;

		};

		/**
		* \brief
		* 	ChipDNA Version Information
		**/
		class VersionInfo {
		public:
			/**
			* \brief
			*	Gets the server application name.
			*/
			std::string GetAppHostName();

			/**
			* \brief
			* 	Gets the ChipDNA server version.
			*/
			std::string GetVersion();

			/**
			* \brief
			* 	Gets the ChipDNA server release name
			*/
			std::string GetReleaseName();

			/**
			* \brief
			*	Gets the string representation of the ChipDNA version information
			*/
			std::string ToString();

			/**
			* \brief
			* 	Default constructor
			*/
			VersionInfo();

			/**
			* \brief Construct the class with a map containing ChipDNA Version parameters
			* \param status A std::map containing {@link ParameterKeys} entries for ChipDnaApplicationName, ChipDnaVersion, ChipDnaReleaseName
			*/
			VersionInfo(std::map<std::string, std::string> & status);

		private:
			std::string appHostName;
			std::string version;
			std::string releaseName;
		};

		/**
		* \brief
		* 	The status info about ChipDNA's connection to the payment platform.
		**/
		class PaymentPlatformStatus {
		public:
			/**
			* \brief
			* 	Gets the payment platform connection state.
			* \return {@link ParameterTokens}
			*/
			ParameterTokens::PaymentPlatformState GetState();

			/**
			* \brief
			*	Gets the date time format for {@link GetMachineLocalDateTimeFormat()}.
			*/
			std::string GetMachineLocalDateTimeFormat();

			/**
			* \brief
			*	Gets the local time on ChipDNA server machine.
			*/
			std::string GetMachineLocalDateTime();

			/**
			* \brief
			* 	Gets the local time returned from the payment platform.
			*/
			std::string GetPaymentPlatformLocalDateTime();

			/**
			* \brief
			* 	Gets the date time format for {@link GetMachineLocalDateTimeFormat()}.
			*/
			std::string GetPaymentPlatformLocalDateTimeFormat();

			/**
			 * \brief
			 *	Get the string representation of ChipDNA's connection to the payment platform
			 **/
			std::string ToString();

			/**
			* \brief
			* 	Default constructor.
			*/
			PaymentPlatformStatus();

			/**
			* \brief
			* \brief Construct the class with a map containing Payment Platform Status parameters
			* \param status A std::map containing entries for State, MachineLocalDateTime, PaymentPlatformLocalDateTime, PaymentPlatformLocalDateTimeFormat
			*/
			PaymentPlatformStatus(std::map<std::string, std::string> & status);

		private:
			std::string state;
			std::string machineLocalDateTimeFormat;
			std::string machineLocalDateTime;
			std::string paymentPlatformLocalDateTime;
			std::string paymentPlatformLocalDateTimeFormat;
		};

		/**
		* \brief
		*	The status info about the queue of requests to be sent to the payment platform.
		**/
		class RequestQueueStatus {
		public:
			/**
			* \brief
			* 	Gets the number of credit requests in the queue.
			*/
			int GetCreditRequestCount();

			/**
			* \brief
			* 	Gets the number of credit void requests in the queue.
			*/
			int GetCreditVoidRequestCount();

			/**
			* \brief
			* 	Gets the number of credit confirm requests in the queue.
			*/
			int GetCreditConfirmRequestCount();

			/**
			* \brief
			* 	Gets the number of debit requests in the queue.
			*/
			int GetDebitRequestCount();

			/**
			* \brief
			* 	Get the number of debit confirm requests in the queue.
			*/
			int GetDebitConfirmRequestCount();

			/**
			* \brief
			* 	Gets the number of debit void requests in the queue.
			*/
			int GetDebitVoidRequestCount();

			/**
			* \brief
			* 	Gets the total number of requests in the queue.
			*/
			int GetTotalRequestCount();

			/**
			 * \brief
			 *	Get the string representation of the queue of requests to be sent to the payment platform
			 */
			std::string ToString();

			/**
			* \brief
			* 	Default constructor
			*/
			RequestQueueStatus();

			/**
			* \brief Construct the class with a map containing Payment Platform Status parameters
			* \param status A std::map containing entries for State, MachineLocalDateTime, PaymentPlatformLocalDateTime, PaymentPlatformLocalDateTimeFormat
			*/
			RequestQueueStatus(std::map<std::string, std::string> & status);

		private:
			int creditRequestCount;
			int creditVoidRequestCount;
			int creditConfirmRequestCount;
			int debitRequestCount;
			int debitConfirmRequestCount;
			int debitVoidRequestCount;
		};

		/**
		* \brief
		* 	ChipDNA server status in relation to transaction processing ability.
		**/
		class ServerStatus {
		public:

			/**
			* \brief
			* 	Indicates when a transaction is in progress.
			*/
			bool IsProcessingTransaction();

			/**
			* \brief
			* 	Gets information about issues that may limit transaction processing functionality in the server.
			*
			* \return {@link ChipDnaServerIssue}
			*/
			ParameterTokens::ChipDnaServerIssue GetChipDnaServerIssue();

			/**
			* \brief
			* 	Get the string representation of the ChipDNA server status
			*/
			std::string ToString();

			/**
			* \brief
			* 	Default constructor.
			*/
			ServerStatus();

			/**
			* \brief Construct the class with a map containing ChipDNA Server Status parameters
			* \param status A std::map containing entries for IsProcessingTransaction and ChipDnaServerIssue
			*/
			ServerStatus(std::map<std::string, std::string> &status);

		private:
			bool processingTransaction;
			std::string processingTransactionAsString;
			std::string chipDnaServerIssue;
		};

		/**
		* \brief
		* 	Information regarding TMS updates.
		*/
		class TmsStatus {
		public:
			/**
			* \brief
			* 	* 	Get the format string for the TmsStatus {@link TmsStatus.GetLastConfigUpdateDateTime()} Property
			* \return DateTime format as string.
			*/
			static std::string GetDateTimeFormat();

			/**
			* \brief
			* 	The time and date of the last TMS config update.
			* \return Last TMS update.
			*/
			std::string GetLastConfigUpdateDateTime();

			/**
			* \brief
			* 	The number of days until a TMS config update must take place.
			* \return Days until a TMS update is required.
			*/
			int GetDaysUntilConfigUpdateIsRequired();

			/**
			* \brief
			* 	The time and date of the last TMS config update.
			*/
			std::string GetRequiredConfigUpdateDateTime();

			/**
			* \brief
			* 	The string representation of the TMS Update Status
			*/
			std::string ToString();

			/**
			* \brief
			* 	Default constructor.
			*/
			TmsStatus();

			/**
			* \brief Construct the class with a map containing TMS Status parameters
			* \param status A std::map containing entries for LastConfigUpdateDateTime, DaysUntilConfigUpdateIsRequired and RequiredConfigUpdateDateTime
			*/
			TmsStatus(std::map<std::string, std::string>& status);

		private:
			std::string lastConfigUpdateDateTime;
			std::string daysUntilConfigUpdateIsRequired;
			std::string requiredConfigUpdateDateTime;
		};

		/**
		* \brief
		*  	Data object with payment device status.
		**/
		class PaymentDeviceStatus {
		public:
			/**
			* \brief
			* 	Gets the payment device identifier.
			*/
			std::string GetConfiguredDeviceId();

			/**
			* \brief
			*	Gets the payment device model.
			*/
			ParameterTokens::PaymentDeviceConfigurationState GetConfigurationState();

			/**
			* \brief
			Indicates whether the payment device is processing a transaction.
			*/
			bool IsProcessingTransaction();

			/**
			* \brief
			*	Indicates whether the payment device is available.
			*/
			bool IsAvailable();

			/**
			* \brief
			*	Gets the payment device availability error. Value may be one of {@link PaymentDeviceAvailabilityError}.
			*
			* \return {@link PaymentDeviceAvailabilityError}.
			*/
			ParameterTokens::PaymentDeviceAvailabilityError GetAvailabilityError();

			/**
			* \brief
			*	Gets payment device availability error information. See {@link PaymentDeviceAvailabilityErrorInformation}.
			*
			* \return list of see {@link PaymentDeviceAvailabilityErrorInformation}.
			*/
			std::vector<PaymentDeviceAvailabilityErrorInformation> GetAvailabilityErrorInformation();

			/**
			* \brief
			*	Gets the payment device model.
			*/
			std::string GetConfiguredDeviceModel();

			/**
			* \brief
			* 	Get a string representation of the payment device status
			*/
			std::string ToString();

			/**
			* \brief
			* 	Default constructor.
			*/
			PaymentDeviceStatus();

			/**
			* \brief Construct the class from a Payment Device struct
			* \param device Reference to a {@link PaymentDeviceStruct}
			*/
			PaymentDeviceStatus(PaymentDeviceStruct &device);

		private:
			std::string configuredDeviceId;
			std::string configurationState;
			bool processingTransaction;
			std::string processingTransactionAsString;
			bool available;
			std::string availableAsString;
			std::string availabilityError;
			std::vector<PaymentDeviceAvailabilityErrorInformation> availabilityErrorInformation;
			std::string configuredDeviceModel;

		};

		/**
		* \brief
		* 	Virtual Terminal status.
		**/
		class VirtualTerminalStatus {
		public:
			/**
			* \brief
			* 	Virtual Terminal Identifier.
			*
			* \return Virtual Terminal Identifier string
			*/
			std::string GetVirtualTerminalId();

			/**
			* \brief
			* 	Indicates whether Virtual Terminal is enabled
			*/
			bool IsVirtualTerminalEnabled();

			/**
			* \brief The string representation of the Virtual Terminal Status			
			*/
			std::string ToString();

			/**
			* \brief
			* 	Default constructor.
			*/
			VirtualTerminalStatus();

			/**
			* \brief
			* 	Construct the class from a virtual terminal id
			* 	\param theVirtualTerminalId The Virtual Terminal Id
			* 	\param isVirtualTerminalEnabled A string which is parsed as true when its value is "True", "true" or "Y"
			*/
			VirtualTerminalStatus(std::string theVirtualTerminalId, std::string isVirtualTerminalEnabled);

		private:
			bool virtualTerminalEnabled;
			std::string virtualTerminalId;
		};

#pragma endregion

		/**
		* \brief Get a string representation of the ChipDNA Status class
		*/
		std::string ToString();

		/**
		* \brief
		*	Parse response data into objects, which are easier to use.
		*
		* \param  statusResponse Response object to be parsed.
		* \return Parsed {@link ChipDnaStatus} object.
		**/
		static ChipDnaStatus* ParseFromResponse(ParameterSet & statusResponse);

		/**
		* \brief
		*	Parses XML that is returned by {@link ClientHelper.PaymentDeviceAvailabilityChangeEvent} parameter {@link ParameterKeys.AvailabilityErrorInformation}.
		*
		* \param xml from {@link ParameterKeys.AvailabilityErrorInformation}.
		* @return vector of {@link PaymentDeviceAvailabilityErrorInformation}.
		*/
		static std::vector<PaymentDeviceAvailabilityErrorInformation> ParseFromAvailabilityErrorInformation(const std::string xml);

		/**
		* \brief
		*	Gets the payment platform status.
		*
		* \return {@link PaymentPlatformStatus}
		*/
		PaymentPlatformStatus GetPaymentPlatformStatus();

		/**
		* \brief
		*	Gets a list of payment devices status.
		*
		* \return vector of {@link PaymentDeviceStatus}
		*/
		std::vector<PaymentDeviceStatus> GetPaymentDeviceStatus();

		/**
		* \brief
		*	Gets the ChipDNA server status.
		*
		* \return {@link ServerStatus)
		*/
		ServerStatus GetServerStatus();

		/**
		* \brief
		*	Gets the request queue status.
		*
		* @return {@link RequestQueueStatus }
		*/
		RequestQueueStatus GetRequestQueueStatus();

		/**
		* \brief
		*	Gets the ChipDNA version info.
		*
		* \return {@link VersionInfo}
		*/
		VersionInfo GetVersionInfo();

		/**
		* \brief
		*	Gets the TMS status info.
		*
		* \return {@link TmsStatus}
		*/
		TmsStatus GetTmsStatus();

		/**
		* \brief
		*	Public Destructor
		*/
		~ChipDnaStatus();

	private:
		std::vector<AvailabilityErrorStruct> versionInfoList;
		std::vector<PaymentDeviceStruct> paymentDeviceList;
		std::map<std::string, std::string> status;
		PaymentPlatformStatus paymentPlatformStatus;
		std::vector<PaymentDeviceStatus> paymentDeviceStatus;
		ServerStatus serverStatus;
		RequestQueueStatus requestQueueStatus;
		VersionInfo versionInfo;
		TmsStatus tmsStatus;
		std::vector<VirtualTerminalStatus> virtualTerminalStatus;

		ChipDnaStatus();
	};

}
#endif