#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../Tcp.h"
#include "../utils/StringHelper.h"
#include "../utils/Console.h"

using namespace std;
using namespace NoiseKernel;

TcpClient::TcpClient(LogService *logSrv, SignalAdapter *sigSrv, TcpClientConfig *config)
    : logSrv(logSrv), sigSrv(sigSrv), config(config)
{
    this->connector = NULL;
    this->protocol = NULL;
}

TcpClient::~TcpClient()
{
    if (connector != NULL)
    {
        delete connector;
    }

    if (protocol != NULL)
    {
        delete protocol;
    }
}

void TcpClient::finalizeClient(TcpClientInfo *client)
{
    if (client != NULL)
    {
        delete client;
    }
}

void TcpClient::start()
{
    TcpClientInfo *client;

    client = NULL;

    try
    {
        logSrv->trace("Client is connecting to server...");
        stream = connector->connect(config->getServerPort(), config->getServerName().c_str());

        if (!stream)
        {
            throw DomainException(TCC0001);
        }

        client = new TcpClientInfo(this, stream, 0);

        protocol->handshake(client);

        logSrv->info("Client is connected");

        bool cont = true;
        while (cont)
        {
            /* Check for interruption */
            if (sigSrv->gotSigInt())
            {
                logSrv->debug("Stopping client.. ");
                break;
            }

            /* Proccess client */
            cont = cycle(client);
        }
    }
    catch (DomainException& e)
    {
        logSrv->error(handle(e));
    }

    finalizeClient(client);
}

void TcpClient::action()
{
    this->protocol = createProtocol();

    this->initialize();

    this->start();
}

TcpProtocol* TcpClient::createProtocol()
{
    return new TcpProtocol(false);
}

void TcpClient::initialize()
{
    connector = new TcpConnector();

    string strServerName = config->getServerName();
    int serverPort = config->getServerPort();
    string strServerPort = numberToString<int>(serverPort);

    logSrv->info("Client Name: " + config->getName());
    logSrv->info("Client Description: " + config->getDescription());
    logSrv->info("Server Server Name: " + strServerName);
    logSrv->info("Server Port: " + strServerPort);
}

bool TcpClient::cycle(TcpClientInfo *client)
{
    TcpStream *stream = client->getStream();

    /* Prompt user for input */
    cout << protocol->prompt();
    string userInput = inLine();

    if (userInput == "")
    {
        return true;
    }

    if (protocol->isHelp(userInput))
    {
        cout << protocol->help();
        return true;
    }

    if (TcpProtocol::exit(userInput))
    {
        return false;
    }

    /* Send messege to server */
    stream->send(userInput);

    /* Get error if exist */
    int errorCode = stream->connectionErrorCode();
    if (errorCode != 0) {
        cout << "ErrorCode: " << errorCode << endl;
    }

    /* Receive messege from server */
    string serverInput = "";
    ssize_t size = stream->receiveAll(serverInput);

    if (TcpProtocol::exit(serverInput))
    {
        return false;
    }

    if (!TcpProtocol::error(serverInput))
    {
        processCommand(client, serverInput);
    }
    else
    {
        logSrv->error(serverInput);
    }

    return true;
}

void TcpClient::processCommand(TcpClientInfo *client, string command)
{
    cout << command << endl;
}
