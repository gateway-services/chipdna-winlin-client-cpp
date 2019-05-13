#ifndef TERMINATEREASON_H
#define TERMINATEREASON_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Reason for termination.
		**/
		enum TerminateReason {
			/**
			* \brief
			* 	Empty.
			*/
			Empty,

			/**
			* \brief
			* 	Terminated by client
			*/
			EPOSTerminated
		};

		struct TerminateReasonMapGenerator {
			static std::map<std::string, TerminateReason> CreateMap() {
				std::map<std::string, TerminateReason> map;
				map["Empty"] = Empty;
				map["EPOSTerminated"] = EPOSTerminated;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link TerminateReason} value.
		**/
		const std::map<std::string, TerminateReason> StringToTerminateReason = TerminateReasonMapGenerator::CreateMap();
	}
}
#endif