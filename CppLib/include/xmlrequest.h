#ifndef XMLREQUEST_H
#define XMLREQUEST_H

#include <string> 
#include <map>
#include "responsecontainer.h"

namespace ChipDnaClientLib {
	
	static const std::string ChipDnaTag = "ChipDna";
	static const std::string MessageTag = "Message";
	static const std::string id = "id";
	static const std::string ParametersTag = "Parameters";
	static const std::string ParameterTag = "Parameter";
	static const std::string DefaultRequestType = "request";
	static const std::string xmlVersion = "1.0";

	class XmlRequest {
	public:
		
		static std::vector<ResponseContainer> ParseRequestXml(const std::string xml);

		static std::string CreateAllRequests(std::vector<ResponseContainer> response);
	};
}
#endif