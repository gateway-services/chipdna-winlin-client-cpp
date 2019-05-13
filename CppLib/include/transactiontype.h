#ifndef TRANSACTIONTYPE_H
#define TRANSACTIONTYPE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Transaction Type.
		**/
		enum TransactionType {
			/**
			* \brief
			* 	Sale.
			*/
			Sale,

			/**
			* \brief
			* 	Refund.
			*/
			Refund,

			/**
			* \brief
			* 	AccountVerification.
			*/
			AccountVerification
		};

		struct TransactionTypeMapGenerator {
			static std::map<std::string, TransactionType> CreateMap() {
				std::map<std::string, TransactionType> map;
				map["Sale"] = Sale;
				map["Refund"] = Refund;
				map["AccountVerification"] = AccountVerification;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link TransactionType} value.
		**/
		const std::map<std::string, TransactionType> StringToTransactionType = TransactionTypeMapGenerator::CreateMap();

	}
}
#endif