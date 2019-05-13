#include "clientbase.h"
#include "xmlrequest.h"
#include <sstream>
#include "clienthelper.h"

namespace ChipDnaClientLib {

#pragma region Static Methods

	static int IndexOfAll(const std::string stringToSearch, const std::vector<char> searchCharacters, const int startIndex) {
		if (stringToSearch.empty() || searchCharacters.empty())
			return -1;

		const int stringSize = stringToSearch.size();

		if (startIndex < 0 || startIndex > stringSize)
			return -1;

		for (int i = startIndex; i < stringSize; ++i) {
			const char character = stringToSearch[i];

			for (char searchCharacter : searchCharacters) {
				if (character == searchCharacter) {
					return i;
				}
			}
		}

		return -1;
	}

	static void ClearQueue(std::queue<std::string> & queue) {
		while (queue.empty()) {
			queue.pop();
		}
	}

	static void AddRange(std::vector<char>& bufferToFill, char bufferToCopy[], const int length) {
		for (int i = 0; i < length; i++) {
			bufferToFill.push_back(bufferToCopy[i]);
		}
	}

	static void VectorToCharArray(std::vector<char>& buffer, char c[]) {
		for (int i = 0; i < buffer.size(); i++) {
			c[i] = buffer.at(i);
		}
	}

	static void EmptyMethod(std::string &) { }

#pragma endregion

#pragma region Public Methods

	void ClientBase::ClientDisconnectionEvent(OnDisconnection onEventDisconnection) {
		disconnectionCallback = onEventDisconnection;
	}

	void ClientBase::RemoveClientDisconnection() {
		if (disconnectionCallback) {
			disconnectionCallback = EmptyMethod;			
		}
	}

	bool ClientBase::IsConnected() {
		return !isShuttingDown;
	}

	ClientBase::ClientBase() : errorOccured(false), isShuttingDown(true), sslEnabled(false) {
		pthread_mutex_init(&writeList_mutex, nullptr);
		pthread_mutex_init(&readList_mutex, nullptr);
		pthread_cond_init(&writeList_cond, nullptr);
		pthread_cond_init(&readList_cond, nullptr);
	}

#pragma endregion

#pragma region Private Methods

	void ClientBase::start() {
		errorOccured = false;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		pthread_create(&readerThread, &attr, &ClientBase::read, static_cast<void *>(this));
		pthread_create(&writerThread, &attr, &ClientBase::write, static_cast<void *>(this));
		pthread_create(&progressThread, &attr, &ClientBase::process, static_cast<void *>(this));

		pthread_attr_destroy(&attr);
	}

	bool ClientBase::shutdown(bool forcingClose, bool closed) {
		if (isShuttingDown) return true;
		isShuttingDown = true;
		closeSockets();
		clearDataStructures();

		if (!closed && disconnectionCallback) {
			std::string errorMessage = "Connection Failure: Lost connection with the server";
			disconnectionCallback(errorMessage);
		}
		return true;
	}

	void ClientBase::addWriteXmlItem(ResponseContainer request) {
		pthread_mutex_lock(&writeList_mutex);
		writeList.push(request);
		pthread_cond_broadcast(&writeList_cond);
		pthread_mutex_unlock(&writeList_mutex);
	}

	bool ClientBase::closeSockets() {
		errorOccured = true;
		if (sslEnabled) {
			BIO_free_all(bio);
			SSL_CTX_free(ctx);
			sslEnabled = false;
		}
#if !_WIN32
		if (!sslEnabled) {
			shutdown(_socket, SHUT_RDWR);
		}
#endif
		if (!sslEnabled)
			close(_socket);
#ifdef _WIN32
		if (!sslEnabled) {
			if (wsaStarted)
				WSACleanup();
		}
#endif
		return true;
	}

	void * ClientBase::write(void *threadid) {
		int result = 1;
		char stx = '\x02';
		char etx = '\x03';
		auto clientBase = static_cast<ClientBase *>(threadid);
		while (clientBase->IsConnected()) {
			if (result <= 0) {
				{ break; }
			}
			pthread_mutex_lock(&clientBase->writeList_mutex);
			if (clientBase->writeList.empty()) {
				pthread_cond_wait(&clientBase->writeList_cond, &clientBase->writeList_mutex);
			}
			std::vector<ResponseContainer> listToWrite;
			while (!clientBase->writeList.empty()) {
				listToWrite.push_back(clientBase->writeList.front());
				clientBase->writeList.pop();
			}
			pthread_mutex_unlock(&clientBase->writeList_mutex);
			if (!clientBase->isShuttingDown && !clientBase->errorOccured) {
				std::string xml = XmlRequest::CreateAllRequests(listToWrite);
				if (xml.empty()) {
					continue;
				}
				result = clientBase->write(&stx, sizeof stx);
				if (result == -1) { break; }
				result = clientBase->write(xml.c_str(), xml.size());
				if (result == -1) { break; }
				result = clientBase->write(&etx, sizeof etx);
				if (result == -1) { break; }
			}
		}
		clientBase->shutdown(false, false);
		pthread_exit(nullptr);

		return nullptr;
	}

	int ClientBase::write(const char* buffer, int length) {
		if (!sslEnabled) {
			return send(_socket, buffer, length, 0);
		}

		return BIO_write(bio, buffer, length);
	}

	void * ClientBase::read(void *threadid) {
		std::vector<char> characterList;
		characterList.push_back('\x02');
		characterList.push_back('\x03');
		std::vector<char> characterList2;
		characterList2.push_back('\x02');

		std::vector<char> byteVector;
		std::stringstream stringStream;
		char incoming_data_buffer[8190];
		int bytesRead = 0;

		auto clientBase = static_cast<ClientBase *>(threadid);
		while (!clientBase->isShuttingDown && !clientBase->errorOccured) {

			bytesRead = clientBase->read(incoming_data_buffer, 4095);

			if (bytesRead > 0) {
				AddRange(byteVector, incoming_data_buffer, bytesRead);
			}
			else {
				// Zero bytes returned when stream has been closed but not socket.
				// However still want to shut down this client.
				break;
			}

			stringStream << std::string(&byteVector[0], byteVector.size());

			std::string stringToParse = stringStream.str();
			stringStream.str("");

			int stxIndex = stringToParse.find('\x02');
			int etxIndex = -1;

			while (stxIndex >= 0) {
				// Find the next delimeter char either STX or ETX
				etxIndex = IndexOfAll(stringToParse, characterList, stxIndex + 1);
				if (etxIndex == -1) {
					break;
				}

				if (stringToParse[etxIndex] == '\x03') {
					// An ETX so retain string in between the STX and ETX
					pthread_mutex_lock(&clientBase->readList_mutex);
					clientBase->readList.push(stringToParse.substr(stxIndex + 1, etxIndex - stxIndex - 1));
					pthread_cond_broadcast(&clientBase->readList_cond);
					pthread_mutex_unlock(&clientBase->readList_mutex);
				}

				// Look for the next STX from the index of the delimiter in case this was an STX
				stxIndex = IndexOfAll(stringToParse, characterList2, etxIndex);
			}

			if (stxIndex == -1 && etxIndex == -1) {
				// Clear all data as does not contain any message data
				byteVector.clear();
			}
			else if (etxIndex >= 0) {
				// Remove any completed messages that have been handled upto and including the 
				// last ETX in the buffer
				std::string messageToBeRemoved = stringToParse.substr(0, etxIndex + 1);
				byteVector.erase(byteVector.begin(), byteVector.begin() + messageToBeRemoved.size());
			}
			else if (stxIndex > 0) {
				// Remove data up to the start of the partial message
				std::string messageToBeRemoved = stringToParse.substr(0, stxIndex);
				byteVector.erase(byteVector.begin(), byteVector.begin() + messageToBeRemoved.size());
			}
		}

		clientBase->shutdown(false, false);
		pthread_exit(nullptr);

		return nullptr;
	}
	
	int ClientBase::read(char* buffer, int length) {
		if (!sslEnabled) {
			return recv(_socket, buffer, length, 0);
		}

		return BIO_read(bio, buffer, length);
	}
	
	void * ClientBase::process(void *threadid) {
		auto clientBase = static_cast<ClientBase *>(threadid);
		std::vector<std::string> xmlString;

		while (clientBase->IsConnected()) {
			for (const auto& i : xmlString) {
				clientBase->processMessages(i);
			}
			xmlString.clear();

			pthread_mutex_lock(&clientBase->readList_mutex);
			if (clientBase->readList.empty())
				pthread_cond_wait(&clientBase->readList_cond, &clientBase->readList_mutex);
			pthread_mutex_unlock(&clientBase->readList_mutex);

			while (!clientBase->readList.empty()) {
				xmlString.push_back(clientBase->readList.front());
				clientBase->readList.pop();
			}
		}
		clientBase->shutdown(false, false);
		pthread_exit(nullptr);

		return nullptr;
	}

	void ClientBase::clearDataStructures() {
		pthread_mutex_lock(&readList_mutex);

		while (!readList.empty()) {
			readList.pop();
		}

		pthread_cond_broadcast(&readList_cond);
		pthread_mutex_unlock(&readList_mutex);
		pthread_mutex_lock(&writeList_mutex);

		while (!writeList.empty()) {
			writeList.pop();
		}

		pthread_cond_broadcast(&writeList_cond);
		pthread_mutex_unlock(&writeList_mutex);
	}
	
#pragma endregion 
}
