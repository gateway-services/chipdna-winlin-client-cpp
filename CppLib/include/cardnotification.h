#ifndef CARDNOTIFICATION_H
#define CARDNOTIFICATION_H

#include <map>

namespace ChipDnaClientLib {
	
	namespace ParameterTokens {

		/**
		* \brief
		*	Parameter Values for handling card notifications.
		*/
		enum CardNotification {
			/**
			* \brief
			* 	Card inserted.
			*/
			Inserted,

			/**
			* \brief
			* 	Card tapped.
			*/
			Tapped,

			/**
			* \brief
			* 	Card swiped.
			*/
			Swiped,

			/**
			* \brief
			* 	Card removed.
			*/
			Removed
		};
		
		struct CardNotificationMapGenerator {
			static std::map<std::string, CardNotification> CreateMap() {
				std::map<std::string, CardNotification> map;

				map["Inserted"] = Inserted;
				map["Tapped"] = Tapped;
				map["Swiped"] = Swiped;
				map["Removed"] = Removed;

				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link CardNotification} value.
		**/
		const std::map<std::string, CardNotification> StringToCardNotification = CardNotificationMapGenerator::CreateMap();
	}

}
#endif