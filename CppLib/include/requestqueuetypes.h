#ifndef REQUESTQUEUETYPE_H
#define REQUESTQUEUETYPE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	The types of request queues that can be run.
		**/
		enum RequestQueueTypes {
			/**
			* \brief
			* 	The request queue of the pending transactions.
			*/
			Pending,

			/**
			* \brief
			* 	The request queue of the failed transactions.
			*/
			Failed,

			/**
			* \brief
			* 	The request queue of both the pending and failed transactions.
			*/
			PendingAndFailed,
		};

		struct RequestQueueTypeMapGenerator {
			static std::map<std::string, RequestQueueTypes> CreateMap() {
				std::map<std::string, RequestQueueTypes> map;
				map["Pending"] = Pending;
				map["Failed"] = Failed;
				map["PendingAndFailed"] = PendingAndFailed;
				return map;
			}
		};

		struct RequestQueueTypeMapReverseGenerator {
			static std::map<RequestQueueTypes, std::string> CreateMap() {
				std::map<RequestQueueTypes, std::string> map;
				map[Pending] = "Pending";
				map[Failed] = "Failed";
				map[PendingAndFailed] = "PendingAndFailed";
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link RequestQueueTypes} value.
		**/
		const std::map<std::string, RequestQueueTypes> StringToRequestQueueType = RequestQueueTypeMapGenerator::CreateMap();

		/**
		* \brief
		* 	Converts a {@link RequestQueueTypes} value to a string.
		**/
		const std::map<RequestQueueTypes, std::string> RequestQueueTypeToString = RequestQueueTypeMapReverseGenerator::CreateMap();
	}
}
#endif