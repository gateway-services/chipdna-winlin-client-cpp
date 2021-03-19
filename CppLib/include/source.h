#ifndef SOURCE_H
#define SOURCE_H

#include <string>
#include <map>

namespace ChipDnaClientLib {

	namespace ParameterTokens {
		
		/**
		* \brief
		* 	Source from where the CardHash was generated.
		*/
		enum Source {
			/**
			* \brief
			* 	Unknown.
			*/
			Unknown,

			/**
			* \brief
			* 	Provided by the platform.
			*/
			Platform,

			/**
			* \brief
			* 	Provided by the platform.
			*/
			PaymentDevice,

		};

		struct SourceMapGenerator {
			static std::map<std::string, Source> CreateMap() {
				std::map<std::string, Source> map;
				map["Unknown"] = Unknown;
				map["Platform"] = Platform;
				map["PaymentDevice"] = PaymentDevice;
				return map;
			}
		};

		/**
		* \brief
		* 	Converts a string to a {@link Source} value.
		**/
		const std::map<std::string, Source> StringToSource = SourceMapGenerator::CreateMap();
	}
}
#endif