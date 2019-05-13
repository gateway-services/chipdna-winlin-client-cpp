#include "ExtraParameter.h"

#include <exception>
#include <string>
#include <stdexcept>

namespace ChipDNA {

	static const std::string BAD_NODE_ERROR_DESCRIPTION = "Passed node is not in the correct format";
	static const std::string KEY_TAG_NAME = "name";
	static const std::string DESCRIPTION_TAG_NAME = "description";
	static const std::string TYPE_TAG_NAME = "type";
	static const std::string PRESET_VAL = "preset";
	static const std::string INPUT_VAL = "input";
	static const std::string DEFAULT_VAL_TAG_NAME = "default";


	ExtraParameter::ExtraParameter(pugi::xml_node& paramNode) :
		description_(getAttributeValue(paramNode, DESCRIPTION_TAG_NAME)),
		key_(paramNode.text().as_string()),
		defaultValue_(getAttributeValue(paramNode, DEFAULT_VAL_TAG_NAME)),
		isInput_(getAttributeValue(paramNode, TYPE_TAG_NAME) == INPUT_VAL)
	{
	}

	ExtraParameter::ExtraParameter(const std::string& key, const std::string& description, const std::string& defaultVal, const bool input):
		description_( description ),
		key_( key ),
		defaultValue_( defaultVal ),
		isInput_( input )
	{
	}
	
	bool ExtraParameter::getTypeValue(const pugi::xml_node& node)
	{
		std::string type = getAttributeValue(node, TYPE_TAG_NAME);
		if (type == INPUT_VAL) {
			return true;
		}
		else if (type == PRESET_VAL) {
			return false;
		}
		throw std::invalid_argument("'type' must be one of either 'preset' or 'input'");
	}

	const std::string ExtraParameter::getAttributeValue(const pugi::xml_node& node, const std::string& name)
	{
		pugi::xml_attribute theAttribute = node.attribute(name.c_str());
		if (!theAttribute.empty()) {
			return theAttribute.value();
		}
		return "";
	}

	const std::string& ExtraParameter::getKey() const
	{
		return key_;
	}

	const std::string& ExtraParameter::getDescription() const
	{
		return description_;
	}

	const std::string& ExtraParameter::getDefaultValue() const
	{
		return defaultValue_;
	}

	const bool ExtraParameter::isInput() const
	{
		return isInput_;
	}
} 