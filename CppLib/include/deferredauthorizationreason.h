#ifndef DEFERREDAUTHORIZATIONREASON_H
#define DEFERREDAUTHORIZATIONREASON_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		*	Enums for deferred authorization reasons.
		*/
		enum DeferredAuthorizationReason {
			/**
			* \brief
			* 	None.
			*/
			None,

			/**
			* \brief
			* 	Connection Failed.
			*/
			ConnectionFailed,

			/**
			* \brief
			* 	Communication Failed.
			*/
			CommunicationFailed,

			/**
			* \brief
			* 	Processing Failed.
			*/
			ProcessingFailed,

			/**
			* \brief
			* 	Offline Only
			*/
			OfflineOnly
		};

		struct DeferredAuthorizationReasonMapGenerator {
			static std::map<std::string, DeferredAuthorizationReason> CreateMap() {
				std::map<std::string, DeferredAuthorizationReason> map;
				map["None"] = None;
				map["ConnectionFailed"] = ConnectionFailed;
				map["CommunicationFailed"] = CommunicationFailed;
				map["ProcessingFailed"] = ProcessingFailed;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link DeferredAuthorizationReason} value.
		**/
		const std::map<std::string, DeferredAuthorizationReason> StringToDeferredAuthorizationReason = DeferredAuthorizationReasonMapGenerator::CreateMap();

	}
}
#endif