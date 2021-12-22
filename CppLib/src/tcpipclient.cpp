#include "tcpipclient.h"
#include <sstream>
#include <iostream>
#include "xmlrequest.h"
#include "response.h"
#include "parameterkeys.h"
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

namespace ChipDnaClientLib {

#ifdef _WIN32
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>
#include <Wincrypt.h>


	static X509_STORE * GetCert(X509_STORE *store) {
		HCERTSTORE hSystemStore;
		PCCERT_CONTEXT pCertContext = nullptr;

		if (!((hSystemStore = CertOpenSystemStore(0, L"MY")))) {
			std::cout << "Could not open the MY system store.";

			return nullptr;
		}

		while ((pCertContext = CertEnumCertificatesInStore(
			hSystemStore,
			pCertContext)))
		{
			const unsigned char *pData = pCertContext->pbCertEncoded;
			auto x509 = d2i_X509(nullptr, &pData, pCertContext->cbCertEncoded);
			if (x509)
			{
				std::cout << X509_STORE_add_cert(store, x509);
				X509_free(x509);
			}
		}

		CertFreeCertificateContext(pCertContext);
		CertCloseStore(hSystemStore, 0);

		return store;
	}

#endif

	static int idCounter = 0;

	std::string TcpIpClient::getId() {
		std::stringstream stringStream;
		time_t t = time(nullptr);   // get time now
		struct tm * now = localtime(&t);

		pthread_mutex_lock(&getId_mutex);
		stringStream << now->tm_year + 1900 << '-'
			<< now->tm_mon + 1 << '-'
			<< now->tm_mday << "-"
			<< now->tm_hour
			<< now->tm_min
			<< now->tm_sec
			<< ++idCounter;
		pthread_mutex_unlock(&getId_mutex);

		return stringStream.str();
	}

	TcpIpClient::TcpIpClient() : ssl(nullptr) {
		pthread_mutex_init(&completedRequests_mutex, nullptr);
		pthread_cond_init(&completedRequests_cond, nullptr);
		pthread_mutex_init(&getId_mutex, nullptr);
	}

	TcpIpClient::~TcpIpClient() {
		Disconnect();
	}

	bool TcpIpClient::connectSSL(const std::string ipAddress, const std::string port) {
		SSL_library_init();
		ERR_load_BIO_strings();
		SSL_load_error_strings();
		OpenSSL_add_all_algorithms();
		ctx = SSL_CTX_new(SSLv23_client_method());
#ifdef _WIN32
		X509_STORE* store = SSL_CTX_get_cert_store(ctx);

		if (store == nullptr) {
			std::cout << "unable to open store";
			return false;
		}

		if (!GetCert(store)) {
			std::cout << "unable to load certificates";
			SSL_CTX_free(ctx);
			return false;
		}
#else
		if (!SSL_CTX_load_verify_locations(ctx, NULL, "/etc/ssl/certs"))
		{
			ERR_print_errors_fp(stderr);
			SSL_CTX_free(ctx);
			return false;
		}
#endif
		bio = BIO_new_ssl_connect(ctx);

		/* Set the SSL_MODE_AUTO_RETRY flag */
		BIO_get_ssl(bio, &ssl);
		SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
		std::stringstream stringStream;
		stringStream << ipAddress << ":" << port;
		BIO_set_conn_hostname(bio, stringStream.str().c_str());

		if (BIO_do_connect(bio) <= 0) {
			ERR_print_errors_fp(stderr);
			//BIO_free(bio);
			SSL_CTX_free(ctx);
			return false;
		}

		/* Check the certificate */
		if (SSL_get_verify_result(ssl) != X509_V_OK) {
			std::cout << "Certificate verification error: " << SSL_get_verify_result(ssl) << std::endl;
			SSL_CTX_free(ctx);
			return false;
		}

		return true;
	}


	bool TcpIpClient::Connect(const std::string ipAddress, const std::string port) {
		return Connect(ipAddress, port, false);
	}

	bool TcpIpClient::Connect(const std::string ipAddress, const std::string port, const bool ssl) {
		if (IsConnected()) {
			return true;
		}

		if (ssl) {

			if (!connectSSL(ipAddress, port)) {
				return false;
			}
			sslEnabled = true;
		}
		else {
			int iResult;

#ifdef _WIN32
			WSADATA wsaData;
			iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				return false;
			}
			wsaStarted = true;
#endif

			struct addrinfo *result = nullptr;
			struct addrinfo hints {};
			_socket = INVALID_SOCKET;

			memset(&hints, 0, sizeof hints);
			hints.ai_family = PF_INET;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;

			// Resolve the server address and port
			iResult = getaddrinfo(ipAddress.c_str(), port.c_str(), &hints, &result);
			if (iResult != 0) {
				if (result != nullptr) {
					freeaddrinfo(result);
				}
				return false;
			}

			struct addrinfo* ptr = result;
			// Create a SOCKET for connecting to server
			_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (_socket == INVALID_SOCKET) {
				if (result != nullptr) {
					freeaddrinfo(result);
				}
				return false;
			}

			iResult = connect(_socket, ptr->ai_addr, int(ptr->ai_addrlen));
			if (iResult == SOCKET_ERROR) {
				close(_socket);
				_socket = INVALID_SOCKET;

				if (result != nullptr) {
					freeaddrinfo(result);
				}

				return false;
			}

			freeaddrinfo(result);
		}

		isShuttingDown = false;
		start();

		return true;
	}

	bool TcpIpClient::Disconnect() {
		shutdown(true, true);
		clear();

		return true;
	}

	bool TcpIpClient::shutdown(bool forcingClose, bool closed) {
		ClientBase::shutdown(forcingClose, closed);
		clear();

		return true;
	}

	void TcpIpClient::reportError(std::string error) { }

	void TcpIpClient::processMessages(std::string xml) {
		std::vector<ResponseContainer> reponses = XmlRequest::ParseRequestXml(xml);

		for (auto& resp : reponses) {
			if (resp.GetResponseType() == "response") {
				pthread_mutex_lock(&completedRequests_mutex);
				responseMap[resp.GetId()] = resp;
				pthread_cond_broadcast(&completedRequests_cond);
				pthread_mutex_unlock(&completedRequests_mutex);
			}
			else if (resp.GetResponseType() == "event") {
				if (chipDnaClientEvent) {
					chipDnaClientEvent(new std::string(resp.GetResponseName()), new Response(resp.GetResponse()));
				}
			}
		}
	}

	void TcpIpClient::waitForResponse(const std::string id) {
		if (ResponseIsWaiting(id)) {
			return;
		}

		pthread_mutex_lock(&completedRequests_mutex);
		pthread_cond_wait(&completedRequests_cond, &completedRequests_mutex);
		pthread_mutex_unlock(&completedRequests_mutex);
	}

	bool TcpIpClient::ResponseIsWaiting(const std::string id) {
		pthread_mutex_lock(&completedRequests_mutex);
		std::map<std::string, ResponseContainer>::iterator it;
		if ((it = responseMap.find(id)) == responseMap.end()) {
			pthread_mutex_unlock(&completedRequests_mutex);
			return false;
		}
		pthread_mutex_unlock(&completedRequests_mutex);

		return true;
	}

	void TcpIpClient::addResponse(ResponseContainer container) {
		pthread_mutex_lock(&completedRequests_mutex);
		responseMap[container.GetId()] = container;
		pthread_cond_broadcast(&completedRequests_cond);
		pthread_mutex_unlock(&completedRequests_mutex);
	}

	ResponseContainer TcpIpClient::getResponse(const std::string id) {
		if (ResponseIsWaiting(id)) {
			pthread_mutex_lock(&completedRequests_mutex);
			ResponseContainer temp = responseMap[id];
			pthread_mutex_unlock(&completedRequests_mutex);
			return temp;
		}

		return ResponseContainer();
	}

	bool TcpIpClient::StartCommand(ParameterSet & parameters, ParameterSet & response, std::string terminalId, const std::string methodName) {
		return this->StartCommand(parameters, response, terminalId, methodName, "");
	}

	bool TcpIpClient::StartCommand(ParameterSet & parameters, ParameterSet & response, std::string identifier, const std::string methodName, std::string apiKey) {
		if (!IsConnected()) {
			response.Add(ParameterKeys::Errors, "ClientNotConnectedToServer");
			return true;
		}

		std::string id = getId();
		std::map<std::string, std::string> paramMap = parameters.GetMap();
		Response resp(paramMap);
		ResponseContainer request("1.0", id, methodName, "request", identifier, apiKey, resp);
		addWriteXmlItem(request);

		do {
			waitForResponse(id);
		} while (!ResponseIsWaiting(id) && IsConnected());

		if (!IsConnected()) {
			response.Add(ParameterKeys::Errors, "ClientNotConnectedToServer");
			return true;
		}

		pthread_mutex_lock(&completedRequests_mutex);
		ResponseContainer responseContainer = responseMap[id];
		pthread_mutex_unlock(&completedRequests_mutex);

		std::vector<Parameter> paramList = responseContainer.GetResponse().ToList();
		for (auto param : paramList) {
			response.Add(param.GetKey(), param.GetValue());
		}

		responseMap.erase(id);
		return true;
	}

	void TcpIpClient::clear() {
		pthread_mutex_lock(&completedRequests_mutex);
		responseMap.clear();
		pthread_cond_broadcast(&completedRequests_cond);
		pthread_mutex_unlock(&completedRequests_mutex);
	}

	void TcpIpClient::ClientEventListener(OnChipDnaClientEvent onChipDnaClientEvent) {
		chipDnaClientEvent = onChipDnaClientEvent;
	}
	
	static void emptyCallback(std::string* string, Response* resp) { }

	void TcpIpClient::RemoveClientEventListener() {
		
		chipDnaClientEvent = emptyCallback;
	}
}
