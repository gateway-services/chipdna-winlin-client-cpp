#ifndef VOIDREASON_H
#define VOIDREASON_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	The void reasons.
		**/
		enum VoidReason {

			/**
			* \brief
			* 	The terminal failed to print a receipt.
			*/
			PrintFailure,

			/**
			* \brief
			* 	The cardholder signature was declined.
			*/
			SignatureDeclined,

			/**
			* \brief
			* 	The terminal failed to issue goods or services.
			*/
			FulfillmentFailure

		};

		struct VoidReasonMapGenerator {
			static std::map<std::string, VoidReason> CreateMap() {
				std::map<std::string, VoidReason> map;
				map["PrintFailure"] = PrintFailure;
				map["SignatureDeclined"] = SignatureDeclined;
				map["FulfillmentFailure"] = FulfillmentFailure;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link VoidReason} value.
		**/
		const std::map<std::string, VoidReason> StringToVoidReason = VoidReasonMapGenerator::CreateMap();

	}
}
#endif
