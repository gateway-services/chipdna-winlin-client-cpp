#ifndef BASECONFIGPARSER_H
#define BASECONFIGPARSER_H


#include "pugixml.hpp"

namespace ChipDNA {

	typedef pugi::xml_named_node_iterator node_iter;
	typedef pugi::xml_object_range<node_iter> node_iter_range;

	class BaseConfigParser
	{

	public:
		virtual ~BaseConfigParser() = 0;
		void setConfigFile(const std::string fileName);
		void loadFile();

	protected:
		const std::string getElementTextByProperties(const std::string& propertyName) const;
		const pugi::xml_node getElementByProperties(const std::string& propertyName) const;
		const node_iter_range getNamedNodeIterator(const std::string& name) const;

	private:
		std::string getRealPath(const std::string& path) const;
		virtual void afterLoad();

	private:
		pugi::xml_document doc_;
		std::string configfilename_;
	};
}
#endif
