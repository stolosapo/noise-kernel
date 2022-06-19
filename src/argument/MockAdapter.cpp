#include "MockAdapter.h"

using namespace NoiseKernel;

MockAdapter::MockAdapter(ArgumentProvider* provider): ArgumentAdapter(provider)
{

}

MockAdapter::~MockAdapter()
{

}

string MockAdapter::title()
{
    return "This a Mock adapter, which accepts the following arguments";
}

void MockAdapter::registerArguments()
{
    registerArg("arg1", "This is a mock string argument for test");
    registerArg("arg2", "This is a mock int argument for test");
    registerArg("arg3", "This is a mock bool argument for test");
    registerArg("tcpserver", "If is a tcp server");
    registerArg("tcpclient", "If is a tcp client");
}

string MockAdapter::getArg1()
{
    return getStringValue("arg1");
}

int MockAdapter::getArg2()
{
    return getIntValue("arg2");
}

bool MockAdapter::getArg3()
{
    return getBoolValue("arg3");
}

bool MockAdapter::isTcpServer()
{
    return hasArg("tcpserver");
}

bool MockAdapter::isTcpClient()
{
    return hasArg("tcpclient");
}
