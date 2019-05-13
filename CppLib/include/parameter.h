#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

namespace ChipDnaClientLib {

	/**
	* \brief
	* 	Key-Value pair data structure.
	**/
	class Parameter {
	public:
		/**
		* \brief
		* 	Initializes a new instance of the Parameter class.
		**/
		Parameter(std::string key, std::string value);

		/**
		* \brief
		* 	Gets the key.
		**/
		std::string GetKey();
		
		/**
		* \brief
		* 	Gets the value.
		**/
		std::string GetValue();

		/**
		 * \brief
		 *	Get the string representation of the KeyValue pair
		 */
		std::string ToString();

	private:
		std::string key;
		std::string value;
	};
}
#endif