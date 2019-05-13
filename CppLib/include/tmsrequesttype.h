#ifndef TMSREQUESTTYPE_H
#define TMSREQUESTTYPE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	TMS request type for API call.
		**/
		enum TmsRequestType {
			/**
			* \brief
			* 	A TMS configuration update is requested.
			*/
			TmsConfiguration
		};

		struct TmsRequestTypeMapGenerator {
			static std::map<std::string, TmsRequestType> CreateMap() {
				std::map<std::string, TmsRequestType> map;
				map["TmsConfiguration"] = TmsConfiguration;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link TmsRequestType} value.
		**/
		const std::map<std::string, TmsRequestType> StringToTmsRequestType = TmsRequestTypeMapGenerator::CreateMap();
	}
}
#endif