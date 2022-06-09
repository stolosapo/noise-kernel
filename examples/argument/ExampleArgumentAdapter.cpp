#include "ExampleArgumentAdapter.h"

using namespace NoiseKernel;

ExampleArgumentAdapter::ExampleArgumentAdapter(ArgumentProvider* provider): ArgumentAdapter(provider)
{

}

ExampleArgumentAdapter::~ExampleArgumentAdapter()
{

}

string ExampleArgumentAdapter::title()
{
    return "Example for Arguments of NoiseKernel";
}

void ExampleArgumentAdapter::registerArguments()
{
    registerArg("name", "The Name of the example");
    registerArg("description", "The Description");
    registerArg("number", "The Number");
}

string ExampleArgumentAdapter::getName()
{
    return getStringValue("name");
}

string ExampleArgumentAdapter::getDescription()
{
    return getStringValue("description");
}

int ExampleArgumentAdapter::getANumber()
{
    return getIntValue("number");
}

