#ifndef RECEIPTITEMTYPE_H
#define RECEIPTITEMTYPE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	The receipt item type.
		**/
		enum ReceiptItemType {
			/**
			* \brief
			* 	Optional on all receipts.
			*/
			Optional,

			/**
			* \brief
			* 	Mandatory on all receipts.
			*/
			Mandatory,

			/**
			* \brief
			* 	Mandatory (Items is for cardholder receipt only).
			*/
			MandatoryCardHolder,

			/**
			* \brief
			* 	Debug.
			*/
			Debug
		};

		struct ReceiptItemTypeMapGenerator {
			static std::map<std::string, ReceiptItemType> CreateMap() {
				std::map<std::string, ReceiptItemType> map;
				map["Optional"] = Optional;
				map["Mandatory"] = Mandatory;
				map["MandatoryCardHolder"] = MandatoryCardHolder;
				map["Debug"] = Debug;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link ReceiptItemType} value.
		**/
		const std::map<std::string, ReceiptItemType> StringToReceiptItemType = ReceiptItemTypeMapGenerator::CreateMap();
	}
}
#endif