#ifndef MERCHANTDATA_H
#define MERCHANTDATA_H

#include <string>
#include <vector>
#include "merchant.h"
#include "parameterset.h"
#include "pugixml.hpp"

namespace ChipDnaClientLib {

#pragma region XML Tags

	static const std::string NAME_TAG = "Name";
	static const std::string MERCHANT_TAG = "Merchant";
	static const std::string MERCHANT_CURRENCIES_TAG = "Currencies";
	static const std::string MERCHANT_TRANSACTION_TYPES_TAG = "TransactionTypes";
	static const std::string MERCHANT_CARD_SCHEMES_TAG = "CardSchemes";

	static const std::string CATEGORY_CODE_ATTRIBUTE = "mcc";
	static const std::string ID_ATTRIBUTE = "id";

	static const std::string CURRENCY_SYMBOL_ATTRIBUTE = "symbol";
	static const std::string CURRENCY_EXPONENT_ATTRIBUTE = "exponent";
	static const std::string CURRENCY_NUMERIC_CODE_ATTRIBUTE = "numeric-code";
	static const std::string CURRENCY_CHAR_CODE_ATTRIBUTE = "char-code";

#pragma endregion

	/**
	* \brief
	* 	Container class to store the parsed response from {@link ClientHelper::GetMerchantData}.
	**/
	class MerchantData {
	public:

		/**
		* \brief
		*	Public Destructor.
		*/
		~MerchantData();

		/**
		* \brief 
		*	Get a string representation of the Merchant Data class.
		*/
		std::string ToString();

		/**
		* \brief 
		*	Return all available merchant accounts organized in a list of merchant.
		* \return a vector of {@link Merchant}
		*/
		std::vector<Merchant> GetMerchantList();

		/**
		* \brief
		*	Parse response data into objects, which are easier to use.
		*
		* \param  merchantDataResponse Response object to be parsed.
		* \return Parsed {@link MerchantData} object.
		**/
		static MerchantData* ParseFromResponse(ParameterSet & merchantDataResponse);

	private:
		std::vector<Merchant> merchantVector;

		static void ParseXmlData(std::string xmlString, std::vector<Merchant> *results, std::string tag);
		static void RetrieveListOfTransactionSchemes(pugi::xml_node nodeWithChildren, std::vector<ParameterTokens::TransactionTypeId> *results);
		static void RetrieveListOfCurrencies(pugi::xml_node nodeWithChildren, std::vector<Merchant::Currency> *results);
		static void RetrieveListOfCardSchemesId(pugi::xml_node nodeWithChildren, std::vector<ParameterTokens::CardSchemeId> *results);
		static std::string RetrieveStringValue(pugi::xml_node node, std::string tag);
		static std::string RetrieveAttribute(pugi::xml_node node, std::string attribute);
		MerchantData();
	};
}
#endif