#include "cardhash.h"
#include <cstring>
#include "pugixml.hpp"

namespace ChipDnaClientLib {

	static const std::string OUTER_TAG = "ArrayOfCardHash";
	static const std::string CARD_HASH_TAG = "CardHash";
	static const std::string SOURCE_TAG = "Source";
	static const std::string VALUE_TAG = "Value";
	static const std::string SCOPE_TAG = "Scope";

	ParameterTokens::Source CardHash::GetSource() {
		return ParameterTokens::StringToSource.at(source);
	}

	ParameterTokens::Scope CardHash::GetScope() {
		return ParameterTokens::StringToScope.at(scope);
	}

	std::string CardHash::GetValue() {
		return value;
	}

	CardHash::CardHash(std::string scope, std::string source, std::string value) {
		this->source = source;
		this->scope = scope;
		this->value = value;
	}

	std::vector<CardHash> CardHash::ParseCardHashFromXml(const std::string & xml) {
		auto buffer = new char[xml.size()];
		std::memcpy(buffer, xml.c_str(), xml.size());
		std::vector<CardHash> cardHashes;
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, xml.size());

		if (result) {
			auto arrayNode = doc.child(OUTER_TAG.c_str());
			auto node = arrayNode.child(CARD_HASH_TAG.c_str());

			while (node != nullptr) {
				std::string source = node.child(SOURCE_TAG.c_str()).text().get();
				std::string scope = node.child(SCOPE_TAG.c_str()).text().get();
				std::string value = node.child(VALUE_TAG.c_str()).text().get();

				cardHashes.emplace_back(scope, source, value);
				node = node.next_sibling(CARD_HASH_TAG.c_str());
			}
		}

		delete[] buffer;
		buffer = nullptr;

		return cardHashes;
	}

	std::string CardHash::ToString() {
		return "Source: " + source + " Scope:" + scope + " Value: " + value;
	}

}

