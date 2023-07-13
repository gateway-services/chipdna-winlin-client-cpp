#ifndef REQUESTQUEUEREPORT_H
#define REQUESTQUEUEREPORT_H

#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "pugixml.hpp"
#include <sstream>
#include "requestqueuetypes.h"

namespace ChipDnaClientLib {
	/**
	 * \brief Class to handle the request queue report.
	 */
	class RequestQueueReport {
	public:
		/**
		 * \brief Class to handle the failed request queue properties.
		 */
		class FailedQueueRequestResponse {
		public:
			/**
			 * \brief
			 *   Gets the total number of requests.
			 *
			 * \return Count.
			 */
			int GetCount();

			/**
			* \brief
			*   Gets the number of requests processed.
			*
			* \return Processed.
			*/
			int GetProcessed();

			/**
			* \brief
			*   Gets the number of requests that failed to process.
			*
			* \return FailedToProcess.
			*/
			int GetFailedToProcess();

			/**
			 * \brief
			 *   Parses a certain {@link ChipDnaClientLib.ClientHelper.RequestQueueRunCompletedEvent} {@link RequestQueueReport} request queue property.
			 */
			void Deserialize(pugi::xml_node node, std::string nodeName);

			/**
			* \brief
			*	Gets a string representation of a certain failed request queue property.
			*
			* \return A string representation of a certain failed request queue property.
			*/
			std::string ToString();

			/**
			* \brief
			*  	Constructor for FailedQueueRequestResponse.
			**/
			FailedQueueRequestResponse();

			/**
			* \brief
			*   Public default destructor.
			*/
			~FailedQueueRequestResponse();
		private:
			int Count = 0;
			int Processed = 0;
			int FailedToProcess = 0;
		};

		/**
		* \brief
		*   Class to handle the pending request queue properties.
		*/
		class PendingQueueRequestResponse : public FailedQueueRequestResponse {
		public:
			/**
			* \brief
			*   Gets the number of requests from the pending queue that were moved to the failed queue.
			*
			* \return MovedToFailed.
			*/
			int GetMovedToFailed();

			/**
			 * \brief
			 *   Parses a certain {@link ChipDnaClientLib.ClientHelper.RequestQueueRunCompletedEvent} {@link RequestQueueReport} request queue property.
			 */
			void Deserialize(pugi::xml_node node, std::string nodeName);

			/**
			* \brief
			*	Gets a string representation of a certain pending request queue property.
			*
			* \return A string representation of a certain pending request queue property.
			*/
			std::string ToString();

			/**
			* \brief
			*  	Constructor for PendingQueueRequestResponse.
			**/
			PendingQueueRequestResponse();

			/**
			* \brief
			*   Public default destructor
			*/
			~PendingQueueRequestResponse();
		private:
			int MovedToFailed = 0;
		};

		/**
		* \brief
		*   Class to handle the pending request queue.
		*/
		class PendingQueue {
		public:
			/**
			 * \brief
			 *   Gets the debit confirm requests from the pending queue.
			 *
			 * \return DebitConfirm.
			 */
			PendingQueueRequestResponse GetDebitConfirm();

			/**
			* \brief
			*   Gets the credit confirm requests from the pending queue.
			*
			* \return CreditConfirm.
			*/
			PendingQueueRequestResponse GetCreditConfirm();

			/**
			 * \brief
			 *   Gets the debit requests from the pending queue.
			 *
			 * \return Debit.
			 */
			PendingQueueRequestResponse GetDebit();

			/**
			 * \brief
			 *   Parses the {@link ChipDnaClientLib.ClientHelper.RequestQueueRunCompletedEvent} {@link RequestQueueReport} pending queue.
			 */
			void Deserialize(pugi::xml_node rootNode);

			/**
			* \brief
			*	Gets a string representation of the pending queue.
			* 
			* \return A string representation of the pending queue.
			*/
			std::string ToString();

			/**
			* \brief
			*  	Constructor for PendingQueue.
			**/
			PendingQueue();

			/**
			* \brief
			*   Public default destructor
			*/
			~PendingQueue();
		private:
			PendingQueueRequestResponse DebitConfirm;
			PendingQueueRequestResponse CreditConfirm;
			PendingQueueRequestResponse Debit;
		};

		/**
		* \brief
		*   Class to handle the failed request queue.
		*/
		class FailedQueue {
		public:
			/**
			* \brief
			*   Gets the debit confirm requests from the failed queue.
			*
			* \return A {@link FailedQueueRequestResponse} object containing the debit confirm requests.
			*/
			FailedQueueRequestResponse GetDebitConfirm();

			/**
			* \brief
			*   Gets the credit confirm requests from the failed queue.
			*
			* \return A {@link FailedQueueRequestResponse} object containing the credit confirm requests.
			*/
			FailedQueueRequestResponse GetCreditConfirm();

			/**
			* \brief
			*   Gets the debit requests from the failed queue.
			*
			* \return A {@link FailedQueueRequestResponse} object containing the debit confirm requests.
			*/
			FailedQueueRequestResponse GetDebit();

			/**
			 * \brief
			 *   Parses the {@link ChipDnaClientLib.ClientHelper.RequestQueueRunCompletedEvent} {@link RequestQueueReport} failed queue.
			 */
			void Deserialize(pugi::xml_node rootNode);

			/**
			* \brief
			*	Gets a string representation of the failed queue.
			*
			* \return A string representation of the failed queue.
			*/
			std::string ToString();

			/**
			* \brief
			*  	Constructor for FailedQueue.
			**/
			FailedQueue();

			/**
			* \brief
			*   Public default destructor
			*/
			~FailedQueue();
		private:
			FailedQueueRequestResponse DebitConfirm;
			FailedQueueRequestResponse CreditConfirm;
			FailedQueueRequestResponse Debit;
		};
	private:
		PendingQueue* Pending;
		FailedQueue* Failed;
		static int GetRequestQueuePropertyNodeValue(pugi::xml_node queueNode, std::string propertyName);
	public:
		/**
		* \brief
		*  	Constructor for RequestQueueReport.
		**/
		RequestQueueReport();

		/**
		* \brief
		*   Public default destructor
		*/
		~RequestQueueReport();

		/**
		* \brief
		*   Gets the report detailing the results of processing the pending queue.
		*
		* \returnThe report detailing the results of processing the pending queue.
		*/
		PendingQueue* GetPendingQueue();
		
		/**
		* \brief
		*   Gets the report detailing the results of processing the failed queue.
		*
		* \return The report detailing the results of processing the failed queue.
		*/
		FailedQueue* GetFailedQueue();

		/**
		* \brief
		*	Parses the {@link ChipDnaClientLib.ClientHelper.RequestQueueRunCompletedEvent} {@link RequestQueueReport}.
		*/
		void Deserialize(pugi::xml_node node, ParameterTokens::RequestQueueTypes requestQueueType);

		/**
		* \brief
		*	Gets a string representation of the {@link RequestQueueReport}
		*
		* \return A string representation of the {@link RequestQueueReport}
		*/
		std::string ToString();
	};
}

#endif