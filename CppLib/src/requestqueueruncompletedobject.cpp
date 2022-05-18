#include "requestqueueruncompletedobject.h"

namespace ChipDnaClientLib {

#pragma region Request Queue Run Completed Methods

	RequestQueueRunCompletedObject::RequestQueueRunCompletedObject() : requestQueueType(
		ParameterTokens::RequestQueueTypes::Pending), requestQueueReport(RequestQueueReport()) {}

	RequestQueueRunCompletedObject::~RequestQueueRunCompletedObject() = default;

	RequestQueueReport RequestQueueRunCompletedObject::GetRequestQueueReport() {
		return requestQueueReport;
	}

	std::string RequestQueueRunCompletedObject::GetErrors() {
		return errors;
	}

	ParameterTokens::RequestQueueTypes RequestQueueRunCompletedObject::GetRequestQueueType() {
		return requestQueueType;
	}

	RequestQueueRunCompletedObject* RequestQueueRunCompletedObject::ParseFromResponse(ParameterSet& response) {
		const auto ptr_requestQueueRunCompletedObject = new RequestQueueRunCompletedObject();
		ptr_requestQueueRunCompletedObject->requestQueueType = ParameterTokens::StringToRequestQueueType.at(response.GetValue(ParameterKeys::RequestQueueType));

		const std::string errors = response.GetValue(ParameterKeys::Errors);
		if (!errors.empty()) {
			ptr_requestQueueRunCompletedObject->errors = errors;
		}

		ParseRequestQueueReport(ptr_requestQueueRunCompletedObject, response.GetValue(ParameterKeys::RequestQueueReport));

		return ptr_requestQueueRunCompletedObject;
	}

	void RequestQueueRunCompletedObject::ParseRequestQueueReport(RequestQueueRunCompletedObject* ptr_requestQueueRunCompletedObject, std::string requestQueueXmlStr) {
		auto buffer = new char[requestQueueXmlStr.size()];
		std::memcpy(buffer, requestQueueXmlStr.c_str(), requestQueueXmlStr.size());

		pugi::xml_document doc;
		pugi::xml_parse_result const result = doc.load_buffer_inplace(buffer, requestQueueXmlStr.size());

		if (result)
			ptr_requestQueueRunCompletedObject->requestQueueReport.Deserialize(doc.first_child(), ptr_requestQueueRunCompletedObject->requestQueueType);

		delete[] buffer;
		buffer = nullptr;
	}

	std::string RequestQueueRunCompletedObject::ToString() {
		std::stringstream ss;
		ss << "-------------------- Request Queue Event --------------------\n\n";
		ss << "Queue Type: " << ParameterTokens::RequestQueueTypeMapReverseGenerator::CreateMap()[requestQueueType] << "\n";
		if (!errors.empty())
			ss << errors << "\n";

		ss << requestQueueReport.ToString();
		return ss.str();
	}
#pragma endregion 

}