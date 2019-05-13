#ifndef CARDHASH_H
#define CARDHASH_H

#include <string.h>
#include <vector>
#include "source.h"
#include "scope.h"

namespace ChipDnaClientLib {	

	/**
	* \brief
	*  	Contains data representing information about a generated card hash.
	**/
	class CardHash {

	public:
		/**
		* \brief
		*  	Source from where the CardHash was generated.
		*
		* \return {@link Source}
		**/
		ParameterTokens::Source GetSource();

		/**
		* \brief
		*  	Scope defines the set of devices that would generate this same hash for a particular card.
		*
		* \return {@link Scope}
		**/
		ParameterTokens::Scope GetScope();

		/**
		* \brief
		*  	The CardHash value.
		**/
		std::string GetValue();

		/**
		* \brief
		*  	Construct a CardHash object from the device scope, card source and hash value
		**/
		CardHash(std::string scope, std::string source, std::string value);

		/**
		* \brief Parses the XML from {@link ParameterKeys#CardHashCollection} returned from {@link ClientHelper.CardDetailsEvent} and {@link ClientHelper.TransactionFinishedEvent}.
		* \param xml The XML string to parse
		* \return A vector of card hash objects
		*/
		std::vector<CardHash> static ParseCardHashFromXml(const std::string & xml);

		/**
		 * \brief Get the string representation of the CardHash object
		 */
		std::string ToString();

	private:
		std::string source;
		std::string scope;
		std::string value;

	};

}
#endif