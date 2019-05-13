#ifndef UPDATETRANSACTIONFINISHEDERRORCODE_H
#define UPDATETRANSACTIONFINISHEDERRORCODE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Update transaction parameters finished Event error code.
		**/
		enum UpdateTransactionFinishedErrorCode {

			/**
			* \brief
			* 	No errors occurred.
			**/
			None,

			/**
			* \brief
			* 	Payment device disconnected while trying to update the transaction parameters.
			**/
			PaymentDeviceDisconnected,

		};

		struct UpdateTransactionFinishedErrorCodeMapGenerator {
			static std::map<std::string, UpdateTransactionFinishedErrorCode> CreateMap() {
				std::map<std::string, UpdateTransactionFinishedErrorCode> map;
				map["None"] = None;
				map["PaymentDeviceDisconnected"] = PaymentDeviceDisconnected;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link UpdateTransactionFinishedErrorCode} value.
		**/
		const std::map<std::string, UpdateTransactionFinishedErrorCode> StringToUpdateTransactionFinishedErrorCode = UpdateTransactionFinishedErrorCodeMapGenerator::CreateMap();

	}
}
#endif