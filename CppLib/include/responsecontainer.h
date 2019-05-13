#ifndef RESPONSECONTAINER_H
#define RESPONSECONTAINER_H

#include <string>
#include "response.h"

namespace ChipDnaClientLib {
	
	/**
	 * \brief 
	 *  Container class for Client-Server Messages
	 */
	class ResponseContainer {
	public:
		/**
		 * \brief 
		 */
		ResponseContainer();

		/**
		* \brief
		*/
		ResponseContainer(std::string chipDnaVersion, std::string id, std::string responseName,
			std::string responseType, std::string terminalId, std::string apiKey, Response response);

		/**
		* \brief
		*/
		std::string GetId();

		/**
		* \brief
		*/
		void SetId(std::string id);

		/**
		* \brief
		*/
		std::string GetVersion();

		/**
		* \brief
		*/
		void SetVersion(std::string version);

		/**
		* \brief
		*/
		std::string GetResponseName();
		
		/**
		* \brief
		*/
		void SetResponseName(std::string responseName);

		/**
		* \brief
		*/
		std::string GetResponseType();

		/**
		* \brief
		*/
		void SetResponseType(std::string responseType);

		/**
		* \brief
		*/
		Response GetResponse();

		/**
		* \brief
		*/
		void SetResponse(Response response);

		/**
		* \brief
		*/
		std::string GetTerminalId();

		/**
		* \brief
		*/
		void SetTerminalId(std::string terminalId);

		/**
		* \brief
		*/
		std::string GetApiKey();

		/**
		* \brief
		*/
		void SetApiKey(std::string apiKey);

	private:
		std::string ChipDnaVersion;
		std::string id;
		std::string responseName;
		std::string responseType;
		std::string identifier;
		std::string apiKey;
		Response response;
	};
}
#endif // !RESPONSECONTAINER_H