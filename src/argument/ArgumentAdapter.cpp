#include "../Argument.h"

#include "../utils/StringHelper.h"

using namespace NoiseKernel;

ArgumentAdapter::ArgumentAdapter(ArgumentProvider* provider) : provider(provider)
{

}

ArgumentAdapter::~ArgumentAdapter()
{
    registeredArgs.clear();
}

bool ArgumentAdapter::argExist(const string& name) const
{
	return registeredArgs.find(name) != registeredArgs.end();
}

void ArgumentAdapter::registerArg(string name, string description)
{
    if (argExist(name))
    {
        return;
    }

    registeredArgs[name] = description;
}

bool ArgumentAdapter::hasArg(string name) const
{
    return provider->hasArg(name);
}

string ArgumentAdapter::getStringValue(string name) const
{
    return provider->getStringValue(name);
}

int ArgumentAdapter::getIntValue(string name) const
{
    return provider->getIntValue(name);
}

bool ArgumentAdapter::getBoolValue(string name) const
{
    return provider->getBoolValue(name);
}

string ArgumentAdapter::help()
{
    string strTitle = title();
    int titleSize = strTitle.size();

    string h = strTitle + "\n";

    h += pad("=", titleSize) + "\n\n";

    for (map<string, string>::iterator it = registeredArgs.begin();
		it != registeredArgs.end();
		++it)
    {
        h += "  --" + it->first + "\t\t" + it->second + "\n";
    }

    h += "\n";

    return h;
}
