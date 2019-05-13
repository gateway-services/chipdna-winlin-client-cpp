#ifndef LIBRARYVERSION_H
#define LIBRARYVERSION_H

#include <string>

namespace ChipDnaClientLib {

	/**
	 * \brief Class to group client library meta information
	 */
	class LibraryVersion {
	public:
		static const std::string ClientVersionTag;
		static const std::string ClientReleaseNameTag;
		static const std::string ClientOsTag;
		static const std::string ClientTypeTag;

		static const std::string ClientLibraryReleaseName;
		static const std::string ClientLibraryVersion;
		static const std::string ClientLibraryType;
	};
}
#endif /* LIBRARYVERSION_H */