#include <string>
#include <iostream>
#include "../Tcp.h"
#include "../utils/StringHelper.h"

using namespace std;
using namespace NoiseKernel;

TcpClientConnection::TcpClientConnection(void *server, TcpStream *stream, Thread *thread, int index)
{
    this->index = index;

    this->stream = stream;
    this->server = server;
    this->thread = thread;
}

TcpClientConnection::TcpClientConnection(void *server, TcpStream *stream, int index)
{
    this->index = index;

    this->stream = stream;
    this->server = server;
}

TcpClientConnection::~TcpClientConnection()
{
    if (stream != NULL)
    {
        delete stream;
    }
}

int TcpClientConnection::getIndex()
{
    return index;
}

Thread* TcpClientConnection::getThread()
{
    return thread;
}

string TcpClientConnection::getName()
{
    return name;
}

string TcpClientConnection::getIp()
{
    return ip;
}

string TcpClientConnection::getHostname()
{
    return hostname;
}

string TcpClientConnection::getIdentity()
{
    string strIndex = numberToString<int>(index);

    if (thread == NULL)
    {
        return strIndex;
    }

    return strIndex + " - " + thread->getStringId();
}

TcpStream* TcpClientConnection::getStream()
{
    return stream;
}

void* TcpClientConnection::getServer()
{
    return server;
}

void TcpClientConnection::setName(string name)
{
    this->name = name;
}

void TcpClientConnection::setIp(string ip)
{
    this->ip = ip;
}

void TcpClientConnection::setHostname(string hostname)
{
    this->hostname = hostname;
}
