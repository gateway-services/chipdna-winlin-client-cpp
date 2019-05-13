#ifndef PAYMENTDEVICEAVAILABILITYERROR_H
#define PAYMENTDEVICEAVAILABILITYERROR_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Payment device availability error codes.
		**/
		enum class PaymentDeviceAvailabilityError {

			/**
			* \brief
			* 	No error.
			**/
			None,

			/**
			* \brief
			* 	Communication link error.
			**/
			CommsLink,

			/**
			* \brief
			* 	Payment device ID mismatch.
			**/
			DeviceIdMismatch,

			/**
			* \brief
			* 	Firmware version not supported.
			**/
			InvalidFirmwareVersion,

			/**
			* \brief
			* 	Payment device not configured.
			**/
			DeviceNotConfigured,

			/**
			* \brief
			* 	Payment device model mismatch.
			**/
			DeviceModelMismatch,

			/**
			* \brief
			* 	Payment device model mismatch.
			**/
			DeviceModelMismatchAfterReboot
		};

		struct PaymentDeviceAvailabilityErrorMapGenerator {
			static std::map<std::string, PaymentDeviceAvailabilityError> CreateMap() {
				std::map<std::string, PaymentDeviceAvailabilityError> map;
				map["None"] = PaymentDeviceAvailabilityError::None;
				map["CommsLink"] = PaymentDeviceAvailabilityError::CommsLink;
				map["DeviceIdMismatch"] = PaymentDeviceAvailabilityError::DeviceIdMismatch;
				map["InvalidFirmwareVersion"] = PaymentDeviceAvailabilityError::InvalidFirmwareVersion;
				map["DeviceNotConfigured"] = PaymentDeviceAvailabilityError::DeviceNotConfigured;
				map["DeviceModelMismatch"] = PaymentDeviceAvailabilityError::DeviceModelMismatch;
				map["DeviceModelMismatchAfterReboot"] = PaymentDeviceAvailabilityError::DeviceModelMismatchAfterReboot;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link PaymentDeviceAvailabilityError} value.
		**/
		const std::map<std::string, PaymentDeviceAvailabilityError> StringToPaymentDeviceAvailabilityError = PaymentDeviceAvailabilityErrorMapGenerator::CreateMap();
	}
}
#endif