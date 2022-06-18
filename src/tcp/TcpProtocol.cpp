#include "../../Tcp.h"
#include "../../Exception.h"

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

void TcpProtocol::error(ClientInfo *client)
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

void TcpProtocol::handshake(ClientInfo *client)
{
    clientSend(client, CLIENT_CONNECT);
    serverReceive(client, CLIENT_CONNECT, TCP0001);

    serverSend(client, OK);
    clientReceive(client, OK, TCP0001);
}

void TcpProtocol::authenticate(ClientInfo *client)
{

}

void TcpProtocol::send(bool escape, ClientInfo *client, const char* command)
{
    if (escape)
    {
        return;
    }

    client->getStream()->send(command);
}

void TcpProtocol::receive(bool escape, ClientInfo *client, const char* expected, const DomainErrorCode& errorCode)
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

void TcpProtocol::serverSend(ClientInfo *client, const char* command)
{
    send(!isServer, client, command);
}

void TcpProtocol::serverReceive(ClientInfo *client, const char* expected, const DomainErrorCode& errorCode)
{
    receive(!isServer, client, expected, errorCode);
}

void TcpProtocol::clientSend(ClientInfo *client, const char* command)
{
    send(isServer, client, command);
}

void TcpProtocol::clientReceive(ClientInfo *client, const char* expected, const DomainErrorCode& errorCode)
{
    receive(isServer, client, expected, errorCode);
}
