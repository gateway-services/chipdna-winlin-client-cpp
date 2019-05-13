#ifndef RESPONSE_H
#define RESPONSE_H

#include <map>
#include <vector>
#include "parameter.h"

namespace ChipDnaClientLib {

	/**
	* \brief
	* A collection class for messages sent from ChipDNA Server
	*/
	class Response {
	public:

		/**
		* \brief
		*	The Number of items in the collection
		*/
		int Count();
		
		/**
		* \brief
		*	Is the collection empty
		*/
		bool IsEmpty();
		
		/**
		* \brief
		*	Does the collection contain the specified key
		*/
		bool ContainsKey(const std::string);
		
		/**
		* \brief
		*	Retrieve a value from the collection, given the specified key
		*/
		std::string GetValue(const std::string key);
		
		/**
		* \brief
		*	Get the string representation of the Response object
		*/
		std::string ToString();
		
		/**
		* \brief
		*	Get the Response object as a list of Parameters
		*/
		std::vector<Parameter> ToList();
		
		/**
		* \brief
		*	Get the internal map
		*/
		std::map<std::string, std::string> GetMap();

		/**
		* \brief
		*	The Default Constructor
		*/
		Response();

		/**
		* \brief
		*	Construct the Class using a std::map 
		*/
		Response(const std::map<std::string, std::string> & map);
	
	private:
		std::map<std::string, std::string> internalMap;
	};
}
#endif