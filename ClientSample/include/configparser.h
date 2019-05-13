#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <map>
#include <vector>
#include <stdexcept>

#include "BaseConfigParser.h"
#include "ExtraParameter.h"

namespace ChipDNA {

	class Configparser : public BaseConfigParser
	{
	public:
		pugi::xml_document doc;
		std::string configfilename;
		~Configparser();
		std::string getterminalid(std::string propertyName);
		std::string connectaddress();
		std::string connectport();
		std::string terminalid();
		std::string posId();
		std::string apiKey();
		std::string sslhost();
		std::string savereceipt();
		const std::vector<ExtraParameter> getExtraParameters(const std::string& command);

	private:
		void afterLoad();
		void parseCommandParams(const pugi::xml_node& node);

	private:
		std::map<std::string, std::vector<ExtraParameter> > commands_;
	};

}
#endif