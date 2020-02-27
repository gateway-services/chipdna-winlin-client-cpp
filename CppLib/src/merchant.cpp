#include <sstream>
#include <iostream>
#include <string>
#include "merchant.h"

namespace ChipDnaClientLib {

#pragma region Merchant Methods

	Merchant::Merchant(std::string name, std::string number, std::string categoryCode, std::vector<Merchant::Currency> currencies,
		std::vector<ParameterTokens::TransactionTypeId> transactionTypes, std::vector<ParameterTokens::CardSchemeId> cardSchemes) {

		this->name = name;
		this->number = number;
		this->categoryCode = categoryCode;
		this->currencies = currencies;
		this->transactionTypes = transactionTypes;
		this->cardSchemes = cardSchemes;
	}

	std::string Merchant::GetName()
	{
		return name;
	}
	std::string Merchant::GetCategoryCode()
	{
		return categoryCode;
	}

	std::string Merchant::GetNumber()
	{
		return number;
	}

	std::vector<Merchant::Currency> Merchant::GetCurrencies()
	{
		return currencies;
	}

	std::vector<ParameterTokens::TransactionTypeId> Merchant::GetTransactionTypes()
	{
		return transactionTypes;
	}

	std::vector<ParameterTokens::CardSchemeId> Merchant::GetCardSchemes()
	{
		return cardSchemes;
	}

	std::string Merchant::ToString() {
		std::stringstream ss;
		ss << "Merchant name: " << GetName() << "\r\n";
		ss << "Merchant category code: " << GetCategoryCode() << "\r\n";
		ss << "Merchant number: " << GetNumber() << "\r\n";

		ss << "\r\n---------- " << "Card schemes enabled for this merchant" << "\r\n\r\n";
		for (auto const &value : GetCardSchemes()) {
			ss << "Card scheme id: " << value << ", label: " << GetCardSchemeName(value) << "\r\n";
		}
		ss << "\r\n---------- " << "Currencies enabled for this merchant" << "\r\n\r\n";

		for (auto &value : GetCurrencies()) {
			ss << value.ToString() << "\r\n";
		}

		ss << "\r\n---------- " << "Transaction types enabled for this merchant" << "\r\n\r\n";
		for (auto &value : GetTransactionTypes()) {
			ss << "Transaction type id: " << value << ", label: " << GetTransactionTypeIdName(value) << "\r\n";
		}
		return ss.str();
	}

	std::string Merchant::GetCardSchemeName(ParameterTokens::CardSchemeId value) {
		for (auto it = ParameterTokens::StringToCardSchemeId.begin(); it != ParameterTokens::StringToCardSchemeId.end(); ++it) {
			if (it->second == value) {
				return it->first;
			}
		}
		return "";
	}

	std::string Merchant::GetTransactionTypeIdName(ParameterTokens::TransactionTypeId value) {
		for (auto it = ParameterTokens::StringToTransactionTypeId.begin(); it != ParameterTokens::StringToTransactionTypeId.end(); ++it) {
			if (it->second == value) {
				return it->first;
			}
		}
		return "";
	}

	Merchant::~Merchant() = default;
#pragma endregion 

#pragma region Currency Data methods

	Merchant::Currency::Currency(std::string numericCode, std::string symbol, std::string charCode, std::string exponent) {
		this->numericCode = numericCode;
		this->symbol = symbol;
		this->charCode = charCode;
		this->exponent = exponent;
	}

	std::string Merchant::Currency::GetNumericCode() {
		return numericCode;
	}

	std::string Merchant::Currency::GetSymbol() {
		return symbol;
	}

	std::string Merchant::Currency::GetCharCode() {
		return charCode;
	}

	std::string Merchant::Currency::GetExponent() {
		return exponent;
	}

	std::string Merchant::Currency::ToString() {
		std::stringstream ss;
		ss << "Symbol: " <<  symbol
			<< ", Numeric code: " << numericCode
			<< ", Char code: " << charCode
			<< ", Exponent: " << exponent;
		return ss.str();
	}

	Merchant::Currency::~Currency() = default;

#pragma endregion 

}