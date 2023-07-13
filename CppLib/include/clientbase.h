#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <queue>
#include "responsecontainer.h"
#include <functional>

#ifdef _WIN32
#include <ws2tcpip.h>
#define close(x) closesocket(x)
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#endif

/* OpenSSL headers */
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "clienthelper.h"

typedef std::function<void(std::string & details)> OnClientDisconnection;

namespace ChipDnaClientLib {	

	/**
	 * \brief
	 * Base class for establishing the client transport layer
	 */
	class ClientBase {
	public:

		/**
		 * \brief Set the client disconnection callback method
		 */
		void ClientDisconnectionEvent(OnDisconnection onEventDisconnection);

		/**
		* \brief Clear the client disconnection callback method
		*/
		void RemoveClientDisconnection();

		/**
		* \brief The client is connected if not shut down or in the process of shutting down
		*/
		bool IsConnected();

		/**
		* \brief Construct the class and initialise thread objects
		*/
		ClientBase();

	private:
		pthread_t writerThread{};
		pthread_t readerThread{};
		pthread_t progressThread{};
		pthread_mutex_t writeList_mutex{};
		pthread_cond_t writeList_cond{};
		pthread_mutex_t readList_mutex{};
		pthread_cond_t readList_cond{};
		std::queue<std::string> readList;
		std::queue<ResponseContainer> writeList;

		static void * write(void *threadid);
		static void * read(void *threadid);
		static void * process(void *threadid);		
		volatile bool errorOccured;
		int read(char*, int);
		int write(const char*, int);

	protected:
		BIO * bio{};
		SSL_CTX * ctx{};
		int _socket{};
		bool wsaStarted{};
		void start();
		volatile bool isShuttingDown;
		bool closeSockets();
		virtual void clearDataStructures() final;
		virtual void processMessages(std::string) = 0;
		virtual void reportError(std::string) = 0;
		virtual bool shutdown(bool, bool);
		void addWriteXmlItem(ResponseContainer);
		bool sslEnabled;
		OnDisconnection disconnectionCallback;
	};

	/**
	 * \brief Empty callback for client disconnection
	 */
	static void EmptyMethod(std::string &);
}
#endif