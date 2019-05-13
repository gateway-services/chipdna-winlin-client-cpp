#include "response.h"
#include <sstream>

namespace ChipDnaClientLib {

	int Response::Count() {
		return internalMap.size();
	}

	bool Response::IsEmpty() {
		return internalMap.empty();
	}

	bool Response::ContainsKey(const std::string key) {
		return internalMap.find(key) != internalMap.end();
	}

	std::string Response::GetValue(const std::string key) {
		if (!ContainsKey(key))
			return "";

		return internalMap[key];
	}

	std::string Response::ToString() {
		std::stringstream stringStream;
		for (auto& it : internalMap) {
			stringStream << "[ " << it.first << ", " << it.second << " ]" << std::endl;
		}

		return stringStream.str();
	}

	std::vector< Parameter> Response::ToList() {
		std::vector<Parameter> list;
		for (auto& it : internalMap) {
			list.emplace_back(it.first, it.second);
		}

		return list;
	}

	std::map<std::string, std::string> Response::GetMap() {
		return internalMap;
	}

	Response::Response() {
		internalMap = std::map<std::string, std::string>();
	}

	Response::Response(const std::map<std::string, std::string> & map) {
		internalMap = map;
	}
}