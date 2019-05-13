#include "parameterset.h"
#include <sstream>

namespace ChipDnaClientLib {

#pragma region Static Methods

	static std::string intToString(const int number) {
		return static_cast<std::ostringstream*>(&(std::ostringstream() << number))->str();
	}

#pragma endregion 

#pragma region Constructors

	ParameterSet::ParameterSet() {
		keyValue = KeyValue();
	}

	ParameterSet::ParameterSet(const std::string key, const std::string value) {
		keyValue = KeyValue();
		if (!key.empty()) {
			keyValue[key] = value;
		}
	}

	ParameterSet::ParameterSet(const std::string key, const int value) {
		keyValue = KeyValue();
		if (!key.empty())
			keyValue[key] = intToString(value);
	}

	ParameterSet::ParameterSet(KeyValue & keyValue) {
		this->keyValue = keyValue;
	}

#pragma endregion 

#pragma region Public Methods

	void ParameterSet::Add(const std::string key, const std::string value) {
		if (!key.empty()) {
			keyValue[key] = value;
		}
	}

	void ParameterSet::Add(const std::string key, const int value) {
		if (!key.empty()) {
			keyValue[key] = intToString(value);
		}
	}

	void ParameterSet::Remove(const std::string key) {
		if (!key.empty()) {
			keyValue.erase(key);
		}
	}

	const KeyValue ParameterSet::GetMap() {
		return keyValue;
	}

	int ParameterSet::Count() {
		return keyValue.size();
	}

	bool ParameterSet::IsEmpty() {
		return keyValue.empty();
	}

	bool ParameterSet::ContainsKey(const std::string key) {
		return !(keyValue.find(key) == keyValue.end());
	}

	std::string ParameterSet::GetValue(const std::string key) {		
		return (!ContainsKey(key)) ? "" : keyValue[key];
	}

	std::string ParameterSet::ToString() {
		std::stringstream stringStream;
		for (auto& it : keyValue) {
			stringStream << "[ " << it.first << ", " << it.second << " ]" << std::endl;
		}

		return stringStream.str();
	}

	ParameterSet ParameterSet::operator+=(const ParameterSet& other) {
		keyValue.insert(other.keyValue.begin(), other.keyValue.end());
		return *this;
	}

	#pragma endregion

}