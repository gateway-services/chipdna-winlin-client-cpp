#ifndef MERCHANT_H
#define MERCHANT_H

#include <string>
#include <vector>
#include "parameterset.h"
#include "cardschemeid.h"
#include "transactiontypeid.h"

namespace ChipDnaClientLib {

	/**
	* \brief
	*  	Data object with merchant account information.
	**/
	class Merchant {
	public:

		/**
		* \brief
		*	Container class to store Currency data.
		*/
		class Currency {
		public:

			/**
			* \brief
			*	Constructor to initialize all data.
			*/
			Currency(std::string numericCode, std::string symbol, std::string charCode, std::string exponent);

			/**
			* \brief
			*	Gets the currency numeric code.
			*/
			std::string GetNumericCode();

			/**
			* \brief
			*	Gets the currency symbol.
			*/
			std::string GetSymbol();

			/**
			* \brief
			*	Gets the currency char code.
			*/
			std::string GetCharCode();

			/**
			* \brief
			*	Gets the currency exponent.
			*/
			std::string GetExponent();

			/**
			* \brief
			*	Gets a string representation of the MerchantTransactionType class.
			*/
			std::string ToString();

			/**
			* \brief
			*	Distructor
			*/
			~Currency();

		private:
			std::string numericCode;
			std::string symbol;
			std::string charCode;
			std::string exponent;
		};

		/**
		* \brief
		* 	Gets the merchant name as string.
		*/
		std::string GetName();

		/**
		* \brief
		* 	Gets the merchant category code as String.
		*/
		std::string GetCategoryCode();

		/**
		* \brief
		* 	Gets the merchant number used for processing.
		*/
		std::string GetNumber();

		/**
		* \brief
		* 	Gets the transaction types enabled for this merchant in a vector of {@link MerchantTransactionType}.
		*/
		std::vector<ParameterTokens::TransactionTypeId> GetTransactionTypes();

		/**
		* \brief
		* 	Gets the currencies enabled for this merchant in a vector of of {@link Currency}.
		*/
		std::vector<Currency> GetCurrencies();

		/**
		* \brief
		* 	Gets the Card Schemes enabled for this merchant in a vector of {@link ParameterTokens::CardSchemeId}.
		*/
		std::vector<ParameterTokens::CardSchemeId> GetCardSchemes();

		/**
		* \brief Get a string representation of the merchant class.
		*/
		std::string ToString();

		/**
		* \brief
		*	Public constructor
		*/
		Merchant(std::string name, std::string number, std::string categoryCode,
			std::vector<Currency> currencies, std::vector<ParameterTokens::TransactionTypeId> transactionTypes,
			std::vector<ParameterTokens::CardSchemeId> cardSchemes);

		/**
		* \brief
		*	Public destructor
		*/
		~Merchant();

	private:
		std::string name;
		std::string categoryCode;
		std::string number;

		std::vector<ParameterTokens::TransactionTypeId> transactionTypes;
		std::vector<ParameterTokens::CardSchemeId> cardSchemes;
		std::vector<Currency> currencies;

		std::string GetCardSchemeName(ParameterTokens::CardSchemeId value);
		std::string GetTransactionTypeIdName(ParameterTokens::TransactionTypeId value);
	};
}
#endif