#ifndef STATE_H
#define STATE_H

#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {

		/**
		* \brief
		* 	Transaction completion state.
		**/
		enum  State {
			/**
			* \brief
			* 	Transaction was not committed.
			*/
			Uncommitted,

			/**
			* \brief
			* 	Transaction was committed.
			*/
			Committed,

			/**
			* \brief
			* 	Transaction was voided.
			*/
			Voided
		};

		struct StateMapGenerator {
			static std::map<std::string, State> CreateMap() {
				std::map<std::string, State> map;
				map["Uncommitted"] = Uncommitted;
				map["Committed"] = Committed;
				map["Voided"] = Voided;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link State} value.
		**/
		const std::map<std::string, State> StringToState = StateMapGenerator::CreateMap();

	}
}
#endif