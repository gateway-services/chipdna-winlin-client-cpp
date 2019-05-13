#ifndef CLIENTERRORCODE_H
#define CLIENTERRORCODE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Error codes that can be return by {@link ClientHelper} through a ClientException or {@link ParameterKeys.Errors}
		**/
		enum ClientErrorCode {

			/**
			* \brief
			*	Client cannot connected to the server.
			**/
			ClientConnectionFailure,
			/**
			* \brief
			* 	Client is not currently connected to the server.
			**/
			ClientNotConnectedToServer
		};

		struct ClientErrorCodeMapGenerator {
			static std::map<std::string, ClientErrorCode> CreateMap() {
				std::map<std::string, ClientErrorCode> map;
				map["ClientConnectionFailure"] = ClientConnectionFailure;
				map["ClientNotConnectedToServer"] = ClientNotConnectedToServer;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link ClientErrorCode} value.
		**/
		const std::map<std::string, ClientErrorCode> StringToClientErrorCode = ClientErrorCodeMapGenerator::CreateMap();
	}
}
#endif