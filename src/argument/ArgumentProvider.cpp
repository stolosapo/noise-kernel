#include "../Argument.h"
#include "../utils/StringHelper.h"

using namespace NoiseKernel;

ArgumentProvider::ArgumentProvider(int argc, char* argv[])
{
    ArgumentParser parser;
    ArgumentList list = parser.parse(argc, argv);

    this->arguments = static_cast<ArgumentList*>(new ArgumentList(list));
}

ArgumentProvider::~ArgumentProvider()
{
    if (arguments != NULL)
    {
        delete arguments;
    }
}

bool ArgumentProvider::hasArg(string name) const
{
    return arguments->exist(name);
}

string ArgumentProvider::getStringValue(string name) const
{
    return arguments->get(name);
}

int ArgumentProvider::getIntValue(string name) const
{
    string value = getStringValue(name);

    if (value == "")
    {
        return 0;
    }

    return stringToNumber<int>(value);
}

bool ArgumentProvider::getBoolValue(string name) const
{
    string value = getStringValue(name);

    if (value == "true")
    {
        return true;
    }

    return false;
}
