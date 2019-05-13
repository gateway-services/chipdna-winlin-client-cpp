#include "responsecontainer.h"

namespace ChipDnaClientLib {

	ResponseContainer::ResponseContainer() {
		SetId("");
		SetResponseType("");
		SetResponseName("");
		SetVersion("");
		SetTerminalId("");
	}
	ResponseContainer::ResponseContainer(std::string chipDnaVersion, std::string id, std::string responseName,
		std::string responseType, std::string terminalId, std::string apiKey, Response response) {
		SetId(id);
		SetResponseType(responseType);
		SetResponseName(responseName);
		SetVersion(chipDnaVersion);
		SetResponse(response);
		SetTerminalId(terminalId);
		SetApiKey(apiKey);
	}

	std::string ResponseContainer::GetId() {
		return id;
	}
	void ResponseContainer::SetId(std::string id) {
		this->id = id;
	}
	std::string ResponseContainer::GetVersion() {
		return ChipDnaVersion;
	}
	void ResponseContainer::SetVersion(std::string version) {
		ChipDnaVersion = version;
	}
	std::string ResponseContainer::GetResponseName() {
		return responseName;
	}
	void ResponseContainer::SetResponseName(std::string responseName) {
		this->responseName = responseName;
	}
	std::string ResponseContainer::GetResponseType() {
		return responseType;
	}
	void ResponseContainer::SetResponseType(std::string responseType) {
		this->responseType = responseType;
	}
	Response ResponseContainer::GetResponse() {
		return response;
	}
	void ResponseContainer::SetResponse(Response response) {
		this->response = response;
	}
	std::string ResponseContainer::GetTerminalId() { return identifier; }
	void ResponseContainer::SetTerminalId(std::string terminalId) { this->identifier = terminalId; }
	void ResponseContainer::SetApiKey(std::string apiKey) {
		this->apiKey = apiKey;
	}
	std::string ResponseContainer::GetApiKey() {
		return apiKey;
	}
}