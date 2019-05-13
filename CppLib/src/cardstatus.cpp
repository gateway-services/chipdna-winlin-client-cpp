#include <cstring>
#include <sstream>
#include "parameterkeys.h"
#include "cardstatus.h"
#include "pugixml.hpp"

namespace ChipDnaClientLib {

	static const pugi::char_t* ARRAY_OF_DEVICE_CARD_STATUS = "ArrayOfDeviceCardStatus";
	static const pugi::char_t* DEVICE_CARD_STATUS = "DeviceCardStatus";
	static const pugi::char_t* PAYMENT_DEVICE_MODEL = "PaymentDeviceModel";
	static const pugi::char_t* PAYMENT_DEVICE_ID = "PaymentDeviceId";
	static const pugi::char_t* CARD_INSERTION_STATUS = "CardInsertionStatus";

	CardStatus::CardStatus() {
		DeviceCardStatusList = std::vector<DeviceCardStatus>();
	}

	CardStatus::~CardStatus() = default;

	std::string CardStatus::ToString() {
		std::stringstream ss;
		ss << "DeviceCardStatusList:" << std::endl;

		for (auto& i : DeviceCardStatusList) {
			ss << "\t" << "PaymentDeviceModel: " << i.paymentDeviceModel << ", "
				<< "PaymentDeviceId: " << i.paymentDeviceId << ", "
				<< "CardInsertionStatus: " << i.cardInsertionStatus << std::endl;
		}

		return ss.str();
	}
	
	CardStatus * CardStatus::ParseFromResponse(ParameterSet & cardStatusResponse) {
		auto ptr_status = new CardStatus();
		const auto versionXml = cardStatusResponse.GetValue(ParameterKeys::CardStatus);
		{
			auto buffer = new char[versionXml.size()];
			std::memcpy(buffer, versionXml.c_str(), versionXml.size());
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, versionXml.size());

			if (result) {
				auto arrayNode = doc.child(ARRAY_OF_DEVICE_CARD_STATUS);
				auto paramNode = arrayNode.child(DEVICE_CARD_STATUS);
				
				while (paramNode != nullptr) {
					DeviceCardStatus deviceCardStatus;
					deviceCardStatus.paymentDeviceModel = paramNode.child(PAYMENT_DEVICE_MODEL).text().get();
					deviceCardStatus.paymentDeviceId = paramNode.child(PAYMENT_DEVICE_ID).text().get();
					deviceCardStatus.cardInsertionStatus = paramNode.child(CARD_INSERTION_STATUS).text().get();
					ptr_status->DeviceCardStatusList.push_back(deviceCardStatus);
					paramNode = paramNode.next_sibling(DEVICE_CARD_STATUS);
				}
			}

			delete[] buffer;
			buffer = nullptr;
		}

		return ptr_status;
	}
}