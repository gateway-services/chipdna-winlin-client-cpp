#ifndef PARAMETERSET_H
#define PARAMETERSET_H

#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::string> KeyValue;

namespace ChipDnaClientLib {

	/**
	* \brief
	* 	Data structure to hold the key/value pairs to send to {@link ClientHelper} methods.
	**/
	class ParameterSet {
	public:
		/**
		* \brief
		*  	Constructor for ParameterSet.
		**/
		ParameterSet();

		/**
		* \brief
		* 	Constructor for ParameterSet.
		*
		*\param keyValue a Key value type aka std::map<std::string, std::string>.
		**/
		ParameterSet(KeyValue & keyValue);

		/**
		* \brief
		* 	Constructor for ParameterSet with starting key and int value pair.
		*
		*\param key Key.
		*\param value Value.
		**/
		ParameterSet(std::string key, int value);

		/**
		* \brief
		*
		* Constructor for ParameterSet with starting key and value pair.
		*
		*\param key Key.
		*\param value Value.
		**/
		ParameterSet(std::string key, std::string value);

		/**
		* \brief
		* 	Adds the value with the specified key.
		*
		*\param key Key.
		*\param value Value.
		**/
		void Add(std::string key, std::string value);

		/**
		* \brief
		* 	Adds the value with the specified key.
		*
		*\param key Key.
		*\param value Value.
		**/
		void Add(std::string key, int value);

		/**
		* \brief
		*	Removes the value with the specified key.
		*
		*\param key Key.
		**/
		void Remove(std::string key);

		/**
		* \brief
		*	Returns a map of the structure data.
		*
		*\return Structures data as aka std::map<std::string, std::string>.
		**/
		const KeyValue GetMap();

		/**
		* \brief
		*	Count of items.
		*
		* \return Count of the number of items contained.
		**/
		int Count();

		/**
		* \brief
		*	Determines if the ParameterSet has items within.
		*
		*\return true if empty else false.
		**/
		bool IsEmpty();

		/**
		* \brief
		*	Informs if the key is within the ParameterSet.
		*
		* \param key A string key.
		* \return true if the key is contained in the ParameterSet.
		**/
		bool ContainsKey(std::string key);

		/**
		* \brief
		* 	Returns the value that is matched to the key if it is there.
		*
		* \param key A string key.
		* \return The value that is linked to the key.
		**/
		std::string GetValue(std::string key);

		/**
		* \brief
		* 	Returns a string of all the items that are contained in the ParameterSet.
		*
		*\return A string representing all the items in the data set.
		**/
		std::string ToString();
		
		/**
		* \brief
		*   Adds the contents of one ParameterSet
		*
		*\return the new ParameterSet
		**/
		ParameterSet operator+=(const ParameterSet& other);
		
		private:
			KeyValue keyValue;
	};
}
#endif