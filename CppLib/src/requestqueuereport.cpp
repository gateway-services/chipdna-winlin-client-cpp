#include "requestqueuereport.h"

namespace ChipDnaClientLib {

#pragma region Request Queue Report

#pragma region RequestQueueReport class

	int RequestQueueReport::GetRequestQueuePropertyNodeValue(const pugi::xml_node queueNode, const std::string propertyName) {
		const auto propertyNode = queueNode.child(propertyName.c_str());
		if (propertyNode.empty()) return 0;

		const std::string propertyNodeValue = propertyNode.child_value();
		return std::atoi(propertyNodeValue.c_str());
	}

	RequestQueueReport::RequestQueueReport() : Pending(nullptr), Failed(nullptr) {}

	RequestQueueReport::~RequestQueueReport() = default;

	RequestQueueReport::PendingQueue* RequestQueueReport::GetPendingQueue()
	{
		return Pending;
	}

	RequestQueueReport::FailedQueue* RequestQueueReport::GetFailedQueue()
	{
		return Failed;
	}

	auto RequestQueueReport::Deserialize(const pugi::xml_node node, const ParameterTokens::RequestQueueTypes requestQueueType) -> void
	{
		if (requestQueueType == ParameterTokens::RequestQueueTypes::Pending || requestQueueType == ParameterTokens::RequestQueueTypes::PendingAndFailed) {
			Pending = new PendingQueue();
			Pending->Deserialize(node.child("Pending"));
		}

		if (requestQueueType == ParameterTokens::RequestQueueTypes::Failed || requestQueueType == ParameterTokens::RequestQueueTypes::PendingAndFailed) {
			Failed = new FailedQueue();
			Failed->Deserialize(node.child("Failed"));
		}
	}

	std::string RequestQueueReport::ToString()
	{
		std::stringstream ss;
		if (Pending != nullptr) {
			ss << Pending->ToString();
		}
		if (Failed != nullptr) {
			ss << Failed->ToString();
		}
		return ss.str();
	}

#pragma endregion

#pragma region FailedQueueRequestResponse class
	RequestQueueReport::FailedQueueRequestResponse::FailedQueueRequestResponse() : Count(0), Processed(0),
		FailedToProcess(0) {}

	RequestQueueReport::FailedQueueRequestResponse::~FailedQueueRequestResponse() {}

	int RequestQueueReport::FailedQueueRequestResponse::GetCount() {
		return Count;
	}

	int RequestQueueReport::FailedQueueRequestResponse::GetProcessed() {
		return Processed;
	}

	int RequestQueueReport::FailedQueueRequestResponse::GetFailedToProcess() {
		return FailedToProcess;
	}

	void RequestQueueReport::FailedQueueRequestResponse::Deserialize(const pugi::xml_node node, const std::string nodeName) {
		if (node.empty()) return;
		auto requestNode = node.child(nodeName.c_str());
		if (requestNode.empty()) return;

		Count = RequestQueueReport::GetRequestQueuePropertyNodeValue(requestNode, "Count");
		Processed = RequestQueueReport::GetRequestQueuePropertyNodeValue(requestNode, "Processed");
		FailedToProcess = RequestQueueReport::GetRequestQueuePropertyNodeValue(requestNode, "FailedToProcess");
	}

	std::string ChipDnaClientLib::RequestQueueReport::FailedQueueRequestResponse::ToString() {
		std::stringstream ss;
		ss << "Count: " << Count << "\n";
		ss << "Processed: " << Processed << "\n";
		ss << "Failed to process: " << FailedToProcess << "\n";
		return ss.str();
	}

#pragma endregion

#pragma region PendingQueueRequestResponse class

	RequestQueueReport::PendingQueueRequestResponse::PendingQueueRequestResponse() : MovedToFailed(0) {}

	RequestQueueReport::PendingQueueRequestResponse::~PendingQueueRequestResponse() = default;

	int RequestQueueReport::PendingQueueRequestResponse::GetMovedToFailed() {
		return MovedToFailed;
	}

	void RequestQueueReport::PendingQueueRequestResponse::Deserialize(pugi::xml_node node, const std::string nodeName) {
		FailedQueueRequestResponse::Deserialize(node, nodeName);

		if (node.empty()) return;
		auto requestNode = node.child(nodeName.c_str());
		if (requestNode.empty()) return;

		MovedToFailed = GetRequestQueuePropertyNodeValue(requestNode, "MovedToFailed");
	}

	std::string RequestQueueReport::PendingQueueRequestResponse::ToString() {
		std::stringstream ss;
		ss << FailedQueueRequestResponse::ToString();
		ss << "Moved to failed: " << MovedToFailed << "\n";
		return ss.str();
	}

#pragma endregion

#pragma region PendingQueue class

	RequestQueueReport::PendingQueueRequestResponse RequestQueueReport::PendingQueue::GetDebitConfirm() {
		return DebitConfirm;
	}

	RequestQueueReport::PendingQueueRequestResponse RequestQueueReport::PendingQueue::GetCreditConfirm() {
		return CreditConfirm;
	}

	RequestQueueReport::PendingQueueRequestResponse RequestQueueReport::PendingQueue::GetDebit() {
		return Debit;
	}

	void RequestQueueReport::PendingQueue::Deserialize(const pugi::xml_node xmlNode) {
		Debit.Deserialize(xmlNode, "DebitRequests");
		CreditConfirm.Deserialize(xmlNode, "CreditConfirmRequests");
		DebitConfirm.Deserialize(xmlNode, "DebitConfirmRequests");
	}

	std::string RequestQueueReport::PendingQueue::ToString() {
		std::stringstream ss;
		ss << "\n---------- Pending Queue ----------\n";
		ss << "\n---------- Debit Confirm ----------\n";
		ss << DebitConfirm.ToString();
		ss << "\n---------- Credit Confirm ----------\n";
		ss << CreditConfirm.ToString();
		ss << "\n---------- Debit ----------\n";
		ss << Debit.ToString();
		return ss.str();
	}

	RequestQueueReport::PendingQueue::~PendingQueue() = default;

	RequestQueueReport::PendingQueue::PendingQueue() = default;

#pragma endregion

#pragma region FailedQueue class

	RequestQueueReport::FailedQueueRequestResponse RequestQueueReport::FailedQueue::GetDebitConfirm() {
		return DebitConfirm;
	}

	RequestQueueReport::FailedQueueRequestResponse RequestQueueReport::FailedQueue::GetCreditConfirm() {
		return CreditConfirm;
	}

	RequestQueueReport::FailedQueueRequestResponse RequestQueueReport::FailedQueue::GetDebit() {
		return Debit;
	}

	void RequestQueueReport::FailedQueue::Deserialize(const pugi::xml_node xmlNode) {
		Debit.Deserialize(xmlNode, "DebitRequests");
		CreditConfirm.Deserialize(xmlNode, "CreditConfirmRequests");
		DebitConfirm.Deserialize(xmlNode, "DebitConfirmRequests");
	}

	std::string RequestQueueReport::FailedQueue::ToString() {
		std::stringstream ss;
		ss << "\n---------- Failed Queue ----------\n";
		ss << "\n---------- Debit Confirm ----------\n";
		ss << DebitConfirm.ToString();
		ss << "\n---------- Credit Confirm ----------\n";
		ss << CreditConfirm.ToString();
		ss << "\n---------- Debit ----------\n";
		ss << Debit.ToString();
		return ss.str();
	}

	RequestQueueReport::FailedQueue::~FailedQueue() = default;

	RequestQueueReport::FailedQueue::FailedQueue() = default;

#pragma endregion

#pragma endregion 
}