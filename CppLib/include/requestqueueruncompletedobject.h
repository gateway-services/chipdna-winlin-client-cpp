#ifndef REQUESTQUEUERUNCOMPLETEDOBJECT_H
#define REQUESTQUEUERUNCOMPLETEDOBJECT_H

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include "requestqueuetypes.h"
#include "requestqueuereport.h"
#include "parameterset.h"
#include "pugixml.hpp"
#include "parameterkeys.h"

namespace ChipDnaClientLib {
	/**
	* \brief
	* 	Helper object to parse the response from {@link ChipDnaClientLib.ClientHelper.RequestQueueRunCompletedEvent}.
	**/
	class RequestQueueRunCompletedObject {
	public:
		/**
		* \brief
		*	Public Destructor.
		*/
		~RequestQueueRunCompletedObject();

		/**
		* \brief
		*  	Constructor for RequestQueueRunCompletedObject.
		**/
		RequestQueueRunCompletedObject();
		

		/**
		* \brief
		*	Get a string representation of the {@link RequestQueueRunCompletedObject} class.
		*/
		std::string ToString();

		/**
		* \brief
		*	Parse response data into objects, which are easier to use.
		*
		* \param  requestQueueRunCompletedDataResponse Response object to be parsed.
		* \return Parsed {@link RequestQueueRunCompletedObject} object.
		**/
		static RequestQueueRunCompletedObject* ParseFromResponse(ParameterSet& requestQueueRunCompletedDataResponse);

		/**
		* \brief
		*	Gets the {@link RequestQueueReport} for this run.
		*
		* \return The {@link RequestQueueReport}.
		**/
		RequestQueueReport GetRequestQueueReport();

		/**
		* \brief
		*	Gets the {@link ParameterTokens.PaymentEngineErrorCode} that might have occurred while processing the request queue.
			If no error occurred, this value is empty.
		*
		* \return The {@link ParameterTokens.PaymentEngineErrorCode} that might have occurred while processing the request queue.
		**/
		std::string GetErrors();

		/**
		* \brief
		*	Gets the {@link ParameterTokens::RequestQueueTypes} processed.
		*
		* \return The {@link ParameterTokens::RequestQueueTypes} processed.
		**/
		ParameterTokens::RequestQueueTypes GetRequestQueueType();

	private:
		ParameterTokens::RequestQueueTypes requestQueueType;
		std::string errors;
		RequestQueueReport requestQueueReport;
		static void ParseRequestQueueReport(RequestQueueRunCompletedObject* ptr_requestQueueRunCompletedObject, std::string requestQueueXmlStr);
	};
}
#endif