
#ifndef RECEIPTDATA_H
#define RECEIPTDATA_H

#include<vector>
#include <string>
#include "receiptitemtype.h"

namespace ChipDnaClientLib {

	/**
	* \brief
	*	Single Receipt Entry
	*/
	struct ReceiptItem {
		/**
		* \brief
		* 	Receipt entry ID.
		*/
		std::string ReceiptEntryId;

		/**
		* \brief
		* 	Receipt value.
		*/
		std::string Value;

		/**
		* \brief
		* 	Receipt label.
		*/
		std::string Label;

		/**
		* \brief
		* 	Entry type, See {@link ReceiptItemType} for values.
		*/
		ParameterTokens::ReceiptItemType ReceiptItemType;

		/**
		* \brief
		* 	Priority.
		*/
		int Priority;
	};

	typedef struct ReceiptItem ReceiptItem;

	/**
	* \brief
	* 	Receipt data helper for parsing receipt data XML.
	**/
	class ReceiptData {
	public:
		/**
		* \brief
		*	Convert receipt data from XML to {@link ReceiptData}.
		*
		* \param xml containing receipt data.
		* \return {@link ReceiptData} parsed from XML.
		**/
		static ReceiptData* GetReceiptDataFromXml(std::string xml);

		/**
		* \brief
		*	Gets all Receipt entries.
		*
		* \return vector of {@link ReceiptItems}.
		**/
		std::vector<ReceiptItem> & GetItems();

		~ReceiptData();

	private:
		ReceiptData();
		std::vector<ReceiptItem> items;
	};
}
#endif