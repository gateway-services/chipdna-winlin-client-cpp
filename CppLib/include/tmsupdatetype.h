#ifndef TMSUPDATETYPE_H
#define TMSUPDATETYPE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Type of TMS update.
		**/
		enum TmsUpdateType {
			/**
			* \brief
			* 	Only new or updated configuration settings are downloaded.
			**/
			Partial,
			/**
			* \brief
			* 	All configuration settings are downloaded.
			**/
			Full
		};
		
		struct TmsUpdateTypeMapGenerator {
			static std::map<std::string, TmsUpdateType> CreateMap() {
				std::map<std::string, TmsUpdateType> map;
				map["Partial"] = Partial;
				map["Full"] = Full;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link TmsUpdateType} value.
		**/
		const std::map<std::string, TmsUpdateType> StringToTmsUpdateType = TmsUpdateTypeMapGenerator::CreateMap();

	}
}
#endif