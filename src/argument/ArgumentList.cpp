#include "../Argument.h"

#include <iostream>

using namespace std;
using namespace NoiseKernel;

ArgumentList::ArgumentList(vector<Argument> args) : arguments(args)
{

}

ArgumentList::~ArgumentList()
{

}

const vector<Argument> ArgumentList::getArguments() const
{
    return arguments;
}

int ArgumentList::size() const
{
    return arguments.size();
}

bool ArgumentList::exist(string name) const
{
    for (int i = 0; i < arguments.size(); i++)
    {
        Argument arg = arguments.at(i);

        if (arg.getName() == name)
        {
            return true;
        }
    }

    return false;
}

string ArgumentList::get(string name) const
{
    for (int i = 0; i < arguments.size(); i++)
    {
        Argument arg = arguments.at(i);

        if (arg.getName() == name)
        {
            return arg.getValue();
        }
    }

    return "";
}
