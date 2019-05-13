#include "xmlrequest.h"
#include <sstream>
#include "tcpipclient.h"
#include <iostream>
#include <cstring>
#include "pugixml.hpp"

namespace ChipDnaClientLib {

	std::vector<ResponseContainer> XmlRequest::ParseRequestXml(const std::string xml) {
		auto buffer = new char[xml.size()];
		std::memcpy(buffer, xml.c_str(), xml.size());

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, xml.size());
		if (!result) {
			std::cout << "Error in Parsing" << std::endl;
		}

		std::vector<ResponseContainer> items;
		pugi::xml_node chipDnaNode = doc.child("ChipDna");

		while (chipDnaNode != nullptr) {
			std::string version = chipDnaNode.attribute("version").value();
			pugi::xml_node messageNode = chipDnaNode.child("Message");

			while (messageNode != nullptr) {
				ResponseContainer response;
				response.SetVersion(version);
				response.SetResponseType(messageNode.attribute("type").value());
				response.SetTerminalId(messageNode.attribute("clientId").value());
				response.SetResponseName(messageNode.attribute("name").value());
				response.SetId(messageNode.attribute("id").value());
				response.SetApiKey(messageNode.attribute("apikey").value());

				std::map<std::string, std::string> map;
				pugi::xml_node params = messageNode.child("Parameters");
				pugi::xml_node paramNode = params.child("Parameter");

				while (paramNode != nullptr) {
					const std::string key = paramNode.attribute("name").value();
					const std::string value = paramNode.text().get();
					map[key] = value;
					paramNode = paramNode.next_sibling("Parameter");
				}

				response.SetResponse(Response(map));
				items.push_back(response);
				messageNode = messageNode.next_sibling("Message");
			}

			chipDnaNode = chipDnaNode.next_sibling("ChipDna");
		}

		delete[] buffer;
		return items;
	}

	std::string XmlRequest::CreateAllRequests(std::vector<ResponseContainer> response) {
		pugi::xml_document doc;
		for (auto& resp : response) {
			pugi::xml_node chipDnaNode = doc.append_child("ChipDna");
			chipDnaNode.append_attribute("version") = "1.0.0";

			pugi::xml_node messageNode = chipDnaNode.append_child("Message");
			messageNode.append_attribute("id") = resp.GetId().c_str();
			messageNode.append_attribute("name") = resp.GetResponseName().c_str();
			messageNode.append_attribute("clientId") = resp.GetTerminalId().c_str();
			messageNode.append_attribute("type") = resp.GetResponseType().c_str();

			if (!resp.GetApiKey().empty()) {
				messageNode.append_attribute("apikey") = resp.GetApiKey().c_str();
			}

			pugi::xml_node parametersNode = messageNode.append_child("Parameters");
			std::vector<Parameter> params = resp.GetResponse().ToList();
			for (auto& param : params) {
				pugi::xml_node paramNode = parametersNode.append_child("Parameter");
				paramNode.append_attribute("name") = param.GetKey().c_str();
				std::string valaue = param.GetValue();
				paramNode.text().set(valaue.c_str());
			}

			std::ostringstream ss;
			doc.save(ss, "", pugi::format_raw);
			return ss.str();
		}
		return {};
	}
}