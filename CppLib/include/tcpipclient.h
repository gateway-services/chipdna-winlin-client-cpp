#ifndef TCPIPCLIENT_H
#define TCPIPCLIENT_H

#include "clientbase.h"
#include "parameterset.h"
#include "response.h"

typedef std::function<void(std::string * eventType, ChipDnaClientLib::Response * response)> OnChipDnaClientEvent;

namespace ChipDnaClientLib {

	/**
	* \brief
	*  	Subclass for establishing a client transport layer over TCP/IP
	*/
	class TcpIpClient : public ClientBase {
	public:
		
		/**
		* \brief
		*	The Default Constructor
		*/
		TcpIpClient();
		
		/**
		* \brief
		*	The Default Destructor
		*/
		virtual ~TcpIpClient();
		
		/**
		* \brief
		*	Connect to server with TCP/IP
		*	\param ipAddress The server address
		*	\param port The server port
		*	\return The client has connected successfully
		*/
		bool Connect(std::string ipAddress, std::string port);
		
		/**
		* \brief
		*	Open to server with TCP/IP and SSL
		*	\param ipAddress The server address
		*	\param port The server port
		*	\param ssl Connect with SSL
		*	\return The client has connected successfully
		*/
		bool Connect(std::string ipAddress, std::string port, bool ssl);
		
		/**
		* \brief
		*	Close the TCP/IP connection
		*	\return The client has disconnected
		*/
		bool Disconnect();
		
		/**
		* \brief
		*	Is a response object waiting, given its ID
		*	\param id The id of the response object to search for
		*	\return The response with the specified ID is waiting
		*/
		bool ResponseIsWaiting(std::string id);
		
		/**
		* \brief
		*	Invoke a ChipDNA command
		*	\param parameters The command parameter set
		*	\param response The container for the command response
		*	\param terminalId The target Terminal ID
		*	\param methodName The command name
		*	\return The command has executed successfully
		*/
		bool StartCommand(ParameterSet& parameters, ParameterSet& response, std::string terminalId, std::string methodName);
		
		/**
		* \brief
		*	Invoke a ChipDNA command
		*	\param parameters The command parameter set
		*	\param response The container for the command response
		*	\param identifier An identifier for either the POS or Terminal ID
		*	\param methodName The command name
		*	\param apiKey The API Key for this terminal
		*	\return The command has executed successfully
		*/
		bool StartCommand(ParameterSet& parameters, ParameterSet& response, std::string identifier, std::string methodName, std::string apiKey);
		
		/**
		* \brief
		*	Subscribe a Client Event Listener method
		*	\param onChipDnaClientEvent The subscribing method 
		*/
		void ClientEventListener(OnChipDnaClientEvent onChipDnaClientEvent);
		
		/**
		* \brief
		*	Unsubscribe the Client Event Listener method
		*/
		void RemoveClientEventListener();


	private:
		void waitForResponse(std::string);
		std::map<std::string, ResponseContainer> responseMap;
		SSL* ssl;
		bool connectSSL(std::string ipAddress, std::string port);
		ResponseContainer getResponse(std::string id);
		void addResponse(ResponseContainer container);
		void clear();

		pthread_mutex_t completedRequests_mutex{};
		pthread_mutex_t getId_mutex{};
		pthread_cond_t completedRequests_cond{};
		std::map < std::string, ResponseContainer> completedRequests;
		OnChipDnaClientEvent chipDnaClientEvent;
		std::string getId();
				
	protected:
		void processMessages(std::string) override;
		bool shutdown(bool, bool) override;
		void reportError(std::string) override;
	};
}
#endif
