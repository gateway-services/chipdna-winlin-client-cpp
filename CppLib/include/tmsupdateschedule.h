#ifndef TMSUPDATESCHEDULE_H
#define TMSUPDATESCHEDULE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	TMS update Schedule.
		**/
		enum TmsUpdateSchedule {
			/**
			* \brief
			* 	Requests ChipDNA to perform a TMS configuration update and apply the update immediately.
			*/
			Immediate,

			/**
			* \brief
			* 	Requests ChipDNA to perform a TMS configuration update and apply the update at the next planned maintenance mode.
			*/
			MaintenanceTime
		};

		struct TmsUpdateScheduleMapGenerator {
			static std::map<std::string, TmsUpdateSchedule> CreateMap() {
				std::map<std::string, TmsUpdateSchedule> map;
				map["Immediate"] = Immediate;
				map["MaintenanceTime"] = MaintenanceTime;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link TmsUpdateSchedule} value.
		**/
		const std::map<std::string, TmsUpdateSchedule> StringToTmsUpdateSchedule = TmsUpdateScheduleMapGenerator::CreateMap();

	}
}
#endif