#include "parameter.h"
#include <sstream>

namespace ChipDnaClientLib {

	Parameter::Parameter(const std::string key, const std::string value) {
		this->key = key;
		this->value = value;
	}

	std::string Parameter::GetKey() { return key; }

	std::string Parameter::GetValue() { return value; }

	std::string Parameter::ToString() {
		std::stringstream stringStream;
		stringStream << "[ " << key << ", " << value << " ]" << std::endl;
		
		return stringStream.str();
	}
}