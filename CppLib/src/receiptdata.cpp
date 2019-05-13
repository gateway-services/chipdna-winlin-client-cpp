#include "receiptdata.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "pugixml.hpp"

namespace ChipDnaClientLib {

	bool sortReceipt(ReceiptItem a, ReceiptItem b) {
		return a.Priority < b.Priority;
	}

	ReceiptData * ReceiptData::GetReceiptDataFromXml(std::string xml) {
		auto receipt_ptr = new ReceiptData();
		auto buffer = new char[xml.size()];
		
		std::memcpy(buffer, xml.c_str(), xml.size());
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, xml.size());
		if (result) {
			auto receiptEntriesNode = doc.child("ReceiptData").child("ReceiptEntries");
			auto arrayNode = receiptEntriesNode.child("ReceiptEntry");

			while (arrayNode != nullptr) {
				ReceiptItem item;
				item.ReceiptEntryId = arrayNode.child("ReceiptEntryId").text().get();
				item.Value = arrayNode.child("Value").text().get();
				item.Label = arrayNode.child("Label").text().get();
				item.ReceiptItemType = ParameterTokens::StringToReceiptItemType.at(arrayNode.child("ReceiptItemType").text().get());
				std::stringstream ss(arrayNode.child("Priority").text().get());
				ss >> item.Priority;
				receipt_ptr->items.push_back(item);
				arrayNode = arrayNode.next_sibling("ReceiptEntry");
			}
		}

		delete[] buffer;
		buffer = nullptr;		
		return receipt_ptr;
	}

	std::vector<ReceiptItem>& ReceiptData::GetItems() {
		std::sort(items.begin(), items.end(), sortReceipt);
		return items;
	}

	ReceiptData::~ReceiptData() {
		items.clear();
	}

	ReceiptData::ReceiptData() {
		items = std::vector<ReceiptItem>();
	}
}