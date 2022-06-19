#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../Tcp.h"
#include "../utils/StringHelper.h"
#include "../utils/Console.h"

using namespace std;
using namespace NoiseKernel;

TcpClient::TcpClient(LogService *logger, SignalAdapter *sigSrv, TcpClientConfig *config, TcpProtocol *protocol)
    : logger(logger), sigSrv(sigSrv), config(config), protocol(protocol)
{
    this->connector = NULL;
}

TcpClient::~TcpClient()
{
    if (connector != NULL)
    {
        delete connector;
    }
}

void TcpClient::finalizeClient(TcpClientConnection *client)
{
    if (client != NULL)
    {
        delete client;
    }
}

void TcpClient::start()
{
    TcpClientConnection *client;

    client = NULL;

    try
    {
        logger->trace("Client is connecting to server...");
        stream = connector->connect(config->getServerPort(), config->getServerName().c_str());

        if (!stream)
        {
            throw DomainException(TCC0001);
        }

        client = new TcpClientConnection(this, stream, 0);

        protocol->handshake(client);

        logger->info("Client is connected");

        bool cont = true;
        while (cont)
        {
            /* Check for interruption */
            if (sigSrv->gotSigInt())
            {
                logger->debug("Stopping client.. ");
                break;
            }

            /* Proccess client */
            cont = cycle(client);
        }
    }
    catch (DomainException& e)
    {
        logger->error(handle(e));
    }

    finalizeClient(client);
}

void TcpClient::action()
{
    this->initialize();
    this->start();
}

void TcpClient::initialize()
{
    connector = new TcpConnector();

    string strServerName = config->getServerName();
    int serverPort = config->getServerPort();
    string strServerPort = numberToString<int>(serverPort);

    logger->info("Client Name: " + config->getName());
    logger->info("Client Description: " + config->getDescription());
    logger->info("Server Server Name: " + strServerName);
    logger->info("Server Port: " + strServerPort);
}

bool TcpClient::cycle(TcpClientConnection *client)
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
        logger->error(serverInput);
    }

    return true;
}

void TcpClient::processCommand(TcpClientConnection *client, string command)
{
    cout << command << endl;
}
