#include <sstream>
#include <cstdlib>
#include <cstring>
#include "parameterkeys.h"
#include "merchantdata.h"

namespace ChipDnaClientLib {

#pragma region Merchant Data Methods

	MerchantData::MerchantData() {}

	MerchantData::~MerchantData() = default;

	std::vector<Merchant> MerchantData::GetMerchantList() {
		return merchantVector;
	}

	MerchantData* MerchantData::ParseFromResponse(ParameterSet & merchantDataResponse) {
		
		auto ptr_merchantData = new MerchantData();

		std::string xmlResponse = merchantDataResponse.GetValue(ParameterKeys::MerchantData);
		ParseXmlData(xmlResponse, &ptr_merchantData->merchantVector, MERCHANT_TAG);

		return ptr_merchantData;
	}

	void MerchantData::ParseXmlData(std::string xmlString, std::vector<Merchant> *results, std::string tag) {
		char* buffer;
		buffer = new char[xmlString.size()];
		std::memcpy(buffer, xmlString.c_str(), xmlString.size());

		pugi::xml_document doc;

		pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, xmlString.size());
		if (result) {

			pugi::xml_node merchantListNode = doc.first_child();
			for (auto& node : merchantListNode)
			{
				std::vector<Merchant::Currency> merchantCurrencies;
				std::vector<ParameterTokens::TransactionTypeId> merchantTransactionTypes;
				std::vector<ParameterTokens::CardSchemeId> merchantCardSchemes;

				std::string merchantName = RetrieveStringValue(node, NAME_TAG);
				std::string merchantCategoryCode = RetrieveAttribute(node, CATEGORY_CODE_ATTRIBUTE);
				std::string merchantNumber = RetrieveAttribute(node, ID_ATTRIBUTE);

				RetrieveListOfCurrencies(node.child(MERCHANT_CURRENCIES_TAG.c_str()), &merchantCurrencies);
				RetrieveListOfTransactionSchemes(node.child(MERCHANT_TRANSACTION_TYPES_TAG.c_str()), &merchantTransactionTypes);
				RetrieveListOfCardSchemesId(node.child(MERCHANT_CARD_SCHEMES_TAG.c_str()), &merchantCardSchemes);
				
				Merchant merchant(merchantName, merchantNumber, merchantCategoryCode, merchantCurrencies, merchantTransactionTypes, merchantCardSchemes);

				results->push_back(merchant);
			}
		}
		delete[] buffer;
		buffer = nullptr;
	}

	void MerchantData::RetrieveListOfCurrencies(pugi::xml_node nodeWithChildren, std::vector<Merchant::Currency> *results) {
		for (auto &node : nodeWithChildren)
		{
			std::string charCode = RetrieveAttribute(node, CURRENCY_CHAR_CODE_ATTRIBUTE);
			std::string exponent = RetrieveAttribute(node, CURRENCY_EXPONENT_ATTRIBUTE);
			std::string numericCode = RetrieveAttribute(node, CURRENCY_NUMERIC_CODE_ATTRIBUTE);
			std::string symbol = RetrieveAttribute(node, CURRENCY_SYMBOL_ATTRIBUTE);

			Merchant::Currency currency(numericCode, symbol, charCode, exponent);
			results->push_back(currency);
		}
	}
	void MerchantData::RetrieveListOfTransactionSchemes(pugi::xml_node nodeWithChildren, std::vector<ParameterTokens::TransactionTypeId> *results) {
		for (auto& node : nodeWithChildren)
		{
			std::string value = RetrieveAttribute(node, ID_ATTRIBUTE);
			results->push_back(ParameterTokens::IntToTransactionTypeId.at(atoi(value.c_str())));
		}
	}

	std::string MerchantData::RetrieveStringValue(pugi::xml_node node, std::string tag) {
		return node.child(tag.c_str()).child_value();
	}

	std::string MerchantData::RetrieveAttribute(pugi::xml_node node, std::string attributeId) {
		return node.attribute(attributeId.c_str()).value(); 
	}

	void MerchantData::RetrieveListOfCardSchemesId(pugi::xml_node nodeWithChildren, std::vector<ParameterTokens::CardSchemeId> *results) {
		for (auto& node : nodeWithChildren)
		{
			std::string value = RetrieveAttribute(node, ID_ATTRIBUTE);
			results->push_back(ParameterTokens::IntToCardSchemeId.at(atoi(value.c_str())));
		}
	}

	std::string MerchantData::ToString() {
		std::stringstream ss;
		int index = 1;
		for (auto & merchant : merchantVector) {

			ss << "---------- " << "Merchant Data Account" << index++ << "  ------------\r\n\r\n";
			ss << merchant.ToString();
		}
		return ss.str();
	}

#pragma endregion 

}