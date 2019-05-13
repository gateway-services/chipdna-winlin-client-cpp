#include <stdexcept>

#include "BaseConfigParser.h"

#include <limits.h>
#include <stdlib.h>

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#define GetCurrentFile _fullpath
#else
#include <unistd.h>
#include <sys/stat.h>
#define GetCurrentDir getcwd
#define GetCurrentFile realpath
#endif

namespace ChipDNA {

	BaseConfigParser::~BaseConfigParser()
	{
		// Intentional NOOP
	}

	void BaseConfigParser::setConfigFile(const std::string fileName)
	{
		configfilename_ = fileName;
	}

	void BaseConfigParser::loadFile()
	{
		configfilename_ = getRealPath(configfilename_);
		if (doc_.load_file(configfilename_.c_str())) {
			afterLoad();
		}
		else {
			throw std::invalid_argument("The specified file failed to load...");
		}
	}

	const std::string BaseConfigParser::getElementTextByProperties(const std::string& propertyName) const
	{
		pugi::xml_node node = getElementByProperties(propertyName);
		if (node != NULL) {
			return std::string(node.text().as_string());
		}
		return "";
	}

	const pugi::xml_node BaseConfigParser::getElementByProperties(const std::string& propertyName) const
	{
		return doc_.document_element().child(propertyName.c_str());
	}

	const node_iter_range BaseConfigParser::getNamedNodeIterator(const std::string& name) const
	{
		return doc_.document_element().children(name.c_str());
	}

	void BaseConfigParser::afterLoad()
	{
		// Intentional NOOP
	}

	std::string BaseConfigParser::getRealPath(const std::string& path) const
	{
		char *real_path = new char[260];
#ifdef WIN32
		GetCurrentFile(real_path, path.c_str(), 260);
		std::string real_path_str = std::string(real_path);
		delete[] real_path;
		return real_path_str;
#else
		char * writable = new char[path.size() + 1];
		std::copy(path.begin(), path.end(), writable);
		writable[path.size()] = '\0';
		real_path = GetCurrentFile((const char*)writable, real_path);

		std::string real_path_str = std::string(real_path);
		delete[] writable;
		delete[] real_path;
		return real_path_str;
#endif
	}
}

