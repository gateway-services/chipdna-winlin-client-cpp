#ifndef TRANSACTIONSOURCE_H
#define TRANSACTIONSOURCE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Type of transaction source
		*
		*/
		enum TransactionSource {
			/**
			* \brief
			* 	Unknown
			*/
			UNKNOWN,

			/**
			* \brief
			* 	Chip
			*/
			ICC,

			/**
			* \brief
			* 	Mag stripe
			*/
			MAG,

			/**
			* \brief
			* 	Contactless ICC.
			*/
			CONTACTLESS_ICC,

			/**
			* \brief
			* 	Contactless MAG stripe.
			**/
			CONTACTLESS_MAG
		};

		struct TransactionSourceMapGenerator {
			static std::map<std::string, TransactionSource> CreateMap() {
				std::map<std::string, TransactionSource> map;
				map["UNKNOWN"] = UNKNOWN;
				map["ICC"] = ICC;
				map["MAG"] = MAG;
				map["CONTACTLESS_ICC"] = CONTACTLESS_ICC;
				map["CONTACTLESS_MAG"] = CONTACTLESS_MAG;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link TransactionSource} value.
		**/
		const std::map<std::string, TransactionSource> StringToTransactionSource = TransactionSourceMapGenerator::CreateMap();
	}
}
#endif