#include <string>
#include <iostream>
#include "../Tcp.h"
#include "../utils/StringHelper.h"

using namespace std;
using namespace NoiseKernel;

TcpClientInfo::TcpClientInfo(void *server, TcpStream *stream, Thread *thread, int index)
{
    this->index = index;

    this->stream = stream;
    this->server = server;
    this->thread = thread;
}

TcpClientInfo::TcpClientInfo(void *server, TcpStream *stream, int index)
{
    this->index = index;

    this->stream = stream;
    this->server = server;
}

TcpClientInfo::~TcpClientInfo()
{
    if (stream != NULL)
    {
        delete stream;
    }
}

int TcpClientInfo::getIndex()
{
    return index;
}

Thread* TcpClientInfo::getThread()
{
    return thread;
}

string TcpClientInfo::getName()
{
    return name;
}

string TcpClientInfo::getIp()
{
    return ip;
}

string TcpClientInfo::getHostname()
{
    return hostname;
}

string TcpClientInfo::getIdentity()
{
    string strIndex = numberToString<int>(index);

    if (thread == NULL)
    {
        return strIndex;
    }

    return strIndex + " - " + thread->getStringId();
}

TcpStream* TcpClientInfo::getStream()
{
    return stream;
}

void* TcpClientInfo::getServer()
{
    return server;
}

void TcpClientInfo::setName(string name)
{
    this->name = name;
}

void TcpClientInfo::setIp(string ip)
{
    this->ip = ip;
}

void TcpClientInfo::setHostname(string hostname)
{
    this->hostname = hostname;
}
