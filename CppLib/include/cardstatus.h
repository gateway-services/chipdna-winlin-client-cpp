#ifndef CARDSTATUS_H
#define CARDSTATUS_H

#include <string>
#include <vector>
#include "parameterset.h"

namespace ChipDnaClientLib {

	typedef struct {
		std::string paymentDeviceModel;
		std::string paymentDeviceId;
		std::string cardInsertionStatus;
	} DeviceCardStatus;

	/**
	 * \brief ChipDNA container class to store the parsed response from {@link ClientHelper.GetCardStatus}.
	 */
	class CardStatus {
	public:

		/**
		* \brief
		* Public default destructor
		*/
		~CardStatus();

		/**
		 * \brief
		 * Get String Representation of the Card status response
		 */
		std::string ToString();

		/**
		* \brief
		*	Parse response data into objects, which are easier to use.
		*
		* \param  cardStatusResponse Response object to be parsed.
		* \return Parsed {@link CardStatus} object.
		**/
		static CardStatus * ParseFromResponse(ParameterSet & cardStatusResponse);

		/**
		* \brief
		* Collection of per-device Card Statuses
		*/
		std::vector<DeviceCardStatus> DeviceCardStatusList;
		
	private:
		CardStatus();
	};
}

#endif