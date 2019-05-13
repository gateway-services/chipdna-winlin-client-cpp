#ifndef PAYMENTDEVICECONFIGURATIONSTATE_H
#define PAYMENTDEVICECONFIGURATIONSTATE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Payment device configuration state.
		**/
		enum PaymentDeviceConfigurationState {

			/**
			* \brief
			* 	Payment device is not configured.
			*/
			NotConfigured,

			/**
			* \brief
			* 	Payment device configuration is in progress.
			*/
			ConfigurationInProgress,

			/**
			* \brief
			* 	Payment device firmware update is in progress.
			*/
			FirmwareUpdateInProgress,

			/**
			* \brief
			* 	Payment device is configured.
			**/
			Configured

		};

		struct PaymentDeviceConfigurationStateMapGenerator {
			static std::map<std::string, PaymentDeviceConfigurationState> CreateMap() {
				std::map<std::string, PaymentDeviceConfigurationState> map;
				map["NotConfigured"] = NotConfigured;
				map["ConfigurationInProgress"] = ConfigurationInProgress;
				map["FirmwareUpdateInProgress"] = FirmwareUpdateInProgress;
				map["Configured"] = Configured;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link PaymentDeviceConfigurationState} value.
		**/
		const std::map<std::string, PaymentDeviceConfigurationState> StringToPaymentDeviceConfigurationState = PaymentDeviceConfigurationStateMapGenerator::CreateMap();
	}
}
#endif
