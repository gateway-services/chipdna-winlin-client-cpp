#ifndef PAYMENTPLATFORMSTATE_H
#define PAYMENTPLATFORMSTATE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Payment Engine Error Codes.
		**/
		enum PaymentPlatformState {
			/**
			* \brief
			* 	Server connection unsuccessful.
			*/
			Unavailable,

			/**
			* \brief
			* 	Server connection successful.
			*/
			Available
		};

		struct PaymentPlatformStateMapGenerator {
			static std::map<std::string, PaymentPlatformState> CreateMap() {
				std::map<std::string, PaymentPlatformState> map;
				map["Unavailable"] = Unavailable;
				map["Available"] = Available;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link PaymentPlatformState} value.
		**/
		const std::map<std::string, PaymentPlatformState> StringToPaymentPlatformState = PaymentPlatformStateMapGenerator::CreateMap();

	}
}
#endif