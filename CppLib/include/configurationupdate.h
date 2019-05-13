#ifndef CARDNOTIFICATION_H
#define CARDNOTIFICATION_H

#include <map>

namespace ChipDnaClientLib {
	
	namespace ParameterTokens {

		/**
		* \brief
		*	Enums for updates returned in the ConfigurationUpdateEvent during calls to connectAndConfigure.
		*/
		enum ConfigurationUpdate {
			/**
			* \brief
			*	The update sent indicating that ConnectAndConfigure has started.
			*/
			ConnectAndConfigureStarted,

			/**
			* \brief
			*	The update sent indication that Registration is taking place.
			*/
			Registering
		};

		struct ConfigurationUpdateMapGenerator {
			static std::map<std::string, ConfigurationUpdate> CreateMap() {
				std::map<std::string, ConfigurationUpdate> map;
				map["ConnectAndConfigureStarted"] = ConnectAndConfigureStarted;
				map["Registering"] = Registering;
				return map;
			}
		};

		/**
		* \brief
		*	Converts a string to a {@link ConfigurationUpdate} value.
		*/
		const std::map<std::string, ConfigurationUpdate> StringToConfigurationUpdate = ConfigurationUpdateMapGenerator::CreateMap();
	}
}
#endif