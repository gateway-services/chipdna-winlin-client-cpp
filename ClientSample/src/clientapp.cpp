#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "client.h"
#include <stdlib.h>
#include "pugixml.hpp"
#include "configparser.h"

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#include <sys/stat.h>
#define GetCurrentDir getcwd
#endif

static std::string IP_ADDRESS = "IP Address";
static std::string SOCKETDATA = "Server";
static std::string TERMINAL_ID = "TerminalId";
static std::string IDENTIFIER = "Identifier";
static std::string POS_ID = "PosId";
static std::string PORT = "Port";
static std::string SAVE_RECEIPT = "SaveReceipt";
static std::string PROVIDER_NAME = "SslHostName";
static std::string EXIT_MESSAGE = "\nPress a key to exit!\n";
static int DEFAULT_PORT = 1869;
static std::string DEFAULT_IP_ADDRESS = "127.0.0.1";

void printPause(std::string msg) {
	std::cout << msg << std::endl;
	std::cin.get();
}

int main(int argc, char* argv[])
{
	ChipDNA::Configparser p;	
	p.setConfigFile("client.config.xml");

	try {
		p.loadFile();
	}
	catch (std::exception& e) {
		std::cout << "Configuration file is in not correct format or not found" << std::endl;
		std::cout << "Please Ensure you are passing in: ";
		std::cout << IDENTIFIER << " (Required), " << SOCKETDATA << "(Optional), " << SAVE_RECEIPT << "(Optional)," << PROVIDER_NAME << "(Optional)," << std::endl;
		printPause(EXIT_MESSAGE);
		return 1;		
	}

	std::string tid;
	std::string posId;
	if (p.terminalid() != "") {
		tid = p.terminalid();
	}
	else if (p.posId() != "" && p.apiKey() != "") {
		posId = p.posId();
	}else if (p.apiKey() == "")
	{
		std::cout << std::endl << "Config file does not contain valid credentials" << std::endl;
		printPause(EXIT_MESSAGE);
		return 1;
	}

	if (p.terminalid() != "" && p.posId() != "") {
		std::cout << std::endl <<"Both Terminal ID and Pos ID passed to client" << std::endl;
		printPause(EXIT_MESSAGE);
		return 1;
	}

	if (p.terminalid() != "" && p.apiKey() != "") {
		std::cout << std::endl << "Both Terminal ID and API key passed to client" << std::endl;
		printPause(EXIT_MESSAGE);
		return 1;
	}

	if (posId != "" && p.apiKey() == "") {
		std::cout << std::endl << "No API key has been passed to the client" << std::endl;
		printPause(EXIT_MESSAGE);
		return 1;
	}

	std::string ip = DEFAULT_IP_ADDRESS;
	int port;
	if (p.connectaddress()!="")	
		ip = p.connectaddress();	
	else	
		std::cout << "Using default ip address " << DEFAULT_IP_ADDRESS << std::endl;
	
	if ((p.connectport() != ""))
	{
		port = atoi(p.connectport().c_str());
		if (port == 0)
		{
			std::cout << "Unable to parse port input {0}" << std::endl;
			printPause(EXIT_MESSAGE);
			return 1;
		}
	}
	else
	{
		std::cout << "Using default port " << DEFAULT_PORT << std::endl;
		port = DEFAULT_PORT;
	}

	bool enableSSL = false;
	
	if (p.sslhost() == "")
		std::cout << "No SSL argument passed in --> default is non-SSL connection" << std::endl;
	else if (p.sslhost().compare("true")==0)
		enableSSL = true;
		
	bool saveReceipt = false;

	if (p.savereceipt() == "")	
		std::cout << "No save_receipt argument passed in --> default is false" << std::endl;		
	else if (p.savereceipt().compare("true")==0)
	saveReceipt = true;

	std::string identifier = tid;
	std::string idLabel = TERMINAL_ID;
	if (identifier == "" && posId != "") {
		identifier = posId;
		idLabel = POS_ID;
	}
	else if (identifier == "") {
		idLabel = POS_ID;
	}

	std::cout << idLabel << " = " << ((identifier == "")? "null" : identifier) << std::endl;
	std::cout << IP_ADDRESS << " = " << ip << std::endl;
	std::cout << PORT << " = " << port << std::endl;
	std::cout << SAVE_RECEIPT << " = " << ((saveReceipt) ? "True" : "False") << std::endl;
	ChipDNA::Client c(identifier, ip, port, enableSSL, saveReceipt, p);
	printPause(EXIT_MESSAGE);
	return 0;
}

