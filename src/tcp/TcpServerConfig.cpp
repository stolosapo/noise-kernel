#include "../Tcp.h"

#include <string>

using namespace std;
using namespace NoiseKernel;

const int TcpServerConfig::DEFAULT_PORT = 51717;
const int TcpServerConfig::DEFAULT_THREAD_POOL_SIZE = 5;
const char* TcpServerConfig::DEFAULT_HOSTNAME = "localhost";

TcpServerConfig::TcpServerConfig(
    int id,
    string name,
    string description,
    string hostname,
    int port,
    int poolSize)
    : id(id), name(name), description(description), hostname(hostname), port(port), poolSize(poolSize)
{

}

TcpServerConfig::~TcpServerConfig()
{

}

int TcpServerConfig::getId()
{
    return id;
}

string TcpServerConfig::getName()
{
    return name;
}

string TcpServerConfig::getDescription()
{
    return description;
}

string TcpServerConfig::getHostname()
{
    return hostname;
}

int TcpServerConfig::getPort()
{
    return port;
}

int TcpServerConfig::getPoolSize()
{
    return poolSize;
}
