#ifndef PAUSETRANSACTIONSTATE_H
#define PAUSETRANSACTIONSTATE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Pause transaction state.
		**/
		enum PauseTransactionState {
			/**
			* \brief
			* 	Pause state occurring after card details collected.
			*/
			PostCardDetails
		};

		struct PauseTransactionStateMapGenerator {
			static std::map<std::string, PauseTransactionState> CreateMap() {
				std::map<std::string, PauseTransactionState> map;
				map["PostCardDetails"] = PostCardDetails;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link PauseTransactionState} value.
		**/
		const std::map<std::string, PauseTransactionState> StringToPauseTransactionState = PauseTransactionStateMapGenerator::CreateMap();
	}
}
#endif