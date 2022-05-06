#include "configparser.h"
#include "pugixml.hpp"
#include "client.h"

#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <stdlib.h>

#ifdef WIN32
#define GetCurrentFile _fullpath
#else
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#define GetCurrentFile realpath
#endif
#include <algorithm>
#include <string> 
#include <exception>

namespace ChipDNA {

	static const std::string COMMAND_NODE_TAG = "Command";
	static const std::string COMMANDS_NODE_TAG = "Commands";
	static const std::string PARAMS_NODE_TAG = "Parameters";
	static const std::string PARAM_TAG = "Parameter";
	static const std::string NAME_ATTRIBUTE = "name";

	static const std::string TERMINAL_ID_TAG = "TerminalId";
	static const std::string POS_ID_TAG = "PosId";
	static const std::string API_KEY_TAG = "ApiKey";
	static const std::string SOCKETDATA_TAG = "Server";
	static const std::string SAVE_RECEIPT_TAG = "SaveReceipt";
	static const std::string PROVIDER_NAME_TAG = "SslHostName";
	static const std::string MERCHAT_STREET_ADDRESS_TAG = "MerchantStreetAddress";
	static const std::string MERCHANT_CITY_STATE_ZIP_TAG = "MerchantCityStateZip";
	static const std::string MERCHANT_PHONE_NUMBER_TAG = "MerchantPhoneNumber";

	Configparser::~Configparser()
	{
	}

	std::string Configparser::terminalid()
	{
		return getElementTextByProperties(TERMINAL_ID_TAG);
	}

	std::string Configparser::posId() {
		return getElementTextByProperties(POS_ID_TAG);
	}

	std::string Configparser::apiKey() {
		return getElementTextByProperties(API_KEY_TAG);
	}

	std::string Configparser::merchantStreetAddress() {
		return getElementTextByProperties(MERCHAT_STREET_ADDRESS_TAG);
	}

	std::string Configparser::merchantCityStateZip() {
		return getElementTextByProperties(MERCHANT_CITY_STATE_ZIP_TAG);
	}

	std::string Configparser::merchantPhoneNumber() {
		return getElementTextByProperties(MERCHANT_PHONE_NUMBER_TAG);
	}

	std::string Configparser::connectaddress()
	{
		std::string address = getElementTextByProperties(SOCKETDATA_TAG);
		int p = address.find(":");
		if (p != std::string::npos)
		{
			return address.substr(0, p);
		}
		return "";
	}

	std::string Configparser::connectport()
	{
		std::string address = getElementTextByProperties(SOCKETDATA_TAG);
		int p = address.find(":");
		if (p != std::string::npos)
		{
			return address.substr(p + 1, address.length() - p - 1);
		}
		return "";
	}

	std::string Configparser::sslhost()
	{
		std::string host = getElementTextByProperties(PROVIDER_NAME_TAG);
		std::transform(host.begin(), host.end(), host.begin(), tolower);
		return host;
	}

	std::string Configparser::savereceipt()
	{
		std::string host = getElementTextByProperties(SAVE_RECEIPT_TAG);
		std::transform(host.begin(), host.end(), host.begin(), tolower);
		return host;
	}

	void Configparser::afterLoad()
	{
		pugi::xml_node commandNode = getElementByProperties(COMMANDS_NODE_TAG);
		node_iter_range commands = commandNode.children(COMMAND_NODE_TAG.c_str());

		for (node_iter it = commands.begin(); it != commands.end(); it++) {
			parseCommandParams(*it);
		}
	}

	void Configparser::parseCommandParams(const pugi::xml_node& node)
	{
		pugi::xml_attribute commandName = node.attribute(NAME_ATTRIBUTE.c_str());
		pugi::xml_node paramsNode = node.child(PARAMS_NODE_TAG.c_str());

		if (!commandName.empty() && !paramsNode.empty()) {
			node_iter_range params = paramsNode.children(PARAM_TAG.c_str());
			for (auto& param : params) {
				commands_[std::string(commandName.value())].push_back(ExtraParameter(param));
			}
		}
	}

	const std::vector<ExtraParameter> Configparser::getExtraParameters(const std::string& command)
	{
		if (commands_.count(command) > 0) {
			return commands_.at(command);
		}
		else {
			return std::vector<ExtraParameter>();
		}
	}
}