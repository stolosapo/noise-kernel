#include "../Tcp.h"
#include "../Exception.h"

using namespace NoiseKernel;

const char* TcpProtocol::PROMPT = "tfk> ";

const char* TcpProtocol::CLIENT_CONNECT = "client_connect";
const char* TcpProtocol::OK = "ok";
const char* TcpProtocol::DENIED = "denied";
const char* TcpProtocol::ERROR = "error";

const char* TcpProtocol::HELP = "help";
const char* TcpProtocol::EXIT = "exit";
const char* TcpProtocol::SHUTDOWN = "shutdown";

TcpProtocol::TcpProtocol(bool isServer) : isServer(isServer)
{

}

TcpProtocol::~TcpProtocol()
{
    isServer = false;
}


bool TcpProtocol::isHelp(string command)
{
    return command == string(HELP);
}

string TcpProtocol::help()
{
    return "";
}

bool TcpProtocol::exit(string command)
{
    return command == string(EXIT);
}

bool TcpProtocol::shutdown(string command)
{
    return command == string(SHUTDOWN);
}

bool TcpProtocol::error(string command)
{
    return command == string(ERROR);
}

void TcpProtocol::error(TcpClientInfo *client)
{
    client->getStream()->send(string(ERROR));
}

string TcpProtocol::prompt()
{
    return string(PROMPT);
}

bool TcpProtocol::getIsServer()
{
    return isServer;
}

void TcpProtocol::handshake(TcpClientInfo *client)
{
    clientSend(client, CLIENT_CONNECT);
    serverReceive(client, CLIENT_CONNECT, TCP0001);

    serverSend(client, OK);
    clientReceive(client, OK, TCP0001);
}

void TcpProtocol::authenticate(TcpClientInfo *client)
{

}

void TcpProtocol::send(bool escape, TcpClientInfo *client, const char* command)
{
    if (escape)
    {
        return;
    }

    client->getStream()->send(command);
}

void TcpProtocol::receive(bool escape, TcpClientInfo *client, const char* expected, const DomainErrorCode& errorCode)
{
    if (escape)
    {
        return;
    }

    string input = "";
    client->getStream()->receive(input);

    if (input == string(expected))
    {
        return;
    }

    throw DomainException(errorCode);
}

void TcpProtocol::serverSend(TcpClientInfo *client, const char* command)
{
    send(!isServer, client, command);
}

void TcpProtocol::serverReceive(TcpClientInfo *client, const char* expected, const DomainErrorCode& errorCode)
{
    receive(!isServer, client, expected, errorCode);
}

void TcpProtocol::clientSend(TcpClientInfo *client, const char* command)
{
    send(isServer, client, command);
}

void TcpProtocol::clientReceive(TcpClientInfo *client, const char* expected, const DomainErrorCode& errorCode)
{
    receive(isServer, client, expected, errorCode);
}
