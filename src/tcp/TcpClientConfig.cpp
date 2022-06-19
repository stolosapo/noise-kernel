#include "../Tcp.h"

#include <string>

using namespace std;
using namespace NoiseKernel;

const int TcpClientConfig::DEFAULT_PORT = 51717;
const char* TcpClientConfig::DEFAULT_SERVERNAME = "localhost";

TcpClientConfig::TcpClientConfig(
    int id,
    string name,
    string description,
    string serverName,
    int serverPort)
    : id(id), name(name), description(description), serverName(serverName), serverPort(serverPort)
{

}

TcpClientConfig::~TcpClientConfig()
{

}

int TcpClientConfig::getId()
{
    return id;
}

string TcpClientConfig::getName()
{
    return name;
}

string TcpClientConfig::getDescription()
{
    return description;
}

string TcpClientConfig::getServerName()
{
    return serverName;
}

int TcpClientConfig::getServerPort()
{
    return serverPort;
}
