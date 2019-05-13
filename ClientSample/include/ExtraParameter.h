#ifndef _H_EXTRAPARAM
#define _H_EXTRAPARAM

#include <string>

#include "pugixml.hpp"

namespace ChipDNA {

	class ExtraParameter {

	public:
		explicit ExtraParameter(pugi::xml_node& paramNode);
		const std::string& getKey() const;
		const std::string& getDescription() const;
		const std::string& getDefaultValue() const;
		const bool isInput() const;

	private:
		ExtraParameter(const std::string& key, const std::string& description, const std::string& defaultVal, const bool isInput);
		bool getTypeValue(const pugi::xml_node& node);
		static const std::string getAttributeValue(const pugi::xml_node& node, const std::string& name);

	private:
		std::string description_;
		std::string key_;
		std::string defaultValue_;
		bool isInput_;
	};
}

#endif