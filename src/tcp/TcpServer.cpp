#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "../Tcp.h"
#include "../utils/StringHelper.h"

using namespace std;
using namespace NoiseKernel;

TcpServer::TcpServer(LogService *logger, SignalAdapter *sigSrv, TcpServerConfig *config, TcpProtocol *protocol)
    : logger(logger), sigSrv(sigSrv), config(config), protocol(protocol)
{
    startTime = time(0);

    this->acceptor = NULL;
    this->pool = NULL;
}

TcpServer::~TcpServer()
{
    if (this->acceptor != NULL)
    {
        delete this->acceptor;
    }

    if (this->pool != NULL)
    {
        delete this->pool;
    }

    for (map<int, TcpClientInfo*>::iterator it = activeClients.begin();
        it != activeClients.end();
        ++it)
    {
        if (it->second != NULL)
        {
            delete it->second;
            logger->info("Finalized client: " + numberToString<int>(it->first));
        }
    }

    activeClients.clear();

    logger->trace("Server finalized!");
}

void* TcpServer::task(void *tcpClientInfo)
{
    TcpClientInfo* client = (TcpClientInfo*) tcpClientInfo;
    TcpStream* stream = client->getStream();
    string identity = client->getIdentity();
    string input = "";  

    try
    {
        /* Check new client for acceptance */
        protocol->handshake(client);
        logger->trace("Server accepted new client: [" + identity + "]");

        /* receive messages */
        while (stream->receive(input) > 0)
        {
            /* Proccess input */
            cycle(client, input);
        }

        logger->trace("Client [" + identity + "] terminated");
    }
    catch (DomainException& e)
    {
        logger->error(handle(e));
    }

    finalizeClient(client);

    return NULL;
}

void* TcpServer::internalClientTask(void *tcpClientInfo)
{
    TcpClientInfo *client = (TcpClientInfo*) tcpClientInfo;
    TcpServer* server = (TcpServer *) (client->getServer());
    return server->task(tcpClientInfo);
}

Thread* TcpServer::getNextThread()
{
    Thread* th = pool->getNext();

    if (th == NULL)
    {
        return NULL;
    }

    th->attachDelegate(&TcpServer::internalClientTask);

    return th;
}

void TcpServer::finalizeClient(TcpClientInfo* client)
{
    pool->putBack(client->getThread());

    map<int, TcpClientInfo*>::iterator it = activeClients.find(client->getIndex());
    if (it != activeClients.end())
    {
        activeClients.erase(it);
    }

    delete client;
}

double TcpServer::uptime()
{
    return difftime(time(0), startTime);
}

int TcpServer::numberOfActiveConnections()
{
    return pool->numberOfActiveThreads();
}

void TcpServer::start()
{
    int clientCount = 0;

    logger->trace("Server is starting...");

    if (acceptor->start() != 0)
    {
        throw DomainException(TCS0001);
    }

    logger->info("Server is started");

    while (!sigSrv->gotSigInt())
    {
        if (!pool->hasNext())
        {
            continue;
        }

        /* Accept new client */
        TcpStream* stream = acceptor->accept();
        if (stream == NULL)
        {
            continue;
        }

        /* Take next thread */
        Thread* th = getNextThread();
        if (th == NULL)
        {
            delete stream;
            continue;
        }

        /* Create new client and start in new thread */
        TcpClientInfo* client = new TcpClientInfo(this, stream, th, clientCount);
        th->start(client);

        /* Add this client to active clients */
        activeClients[client->getIndex()] = client;

        /* Increase thead counter */
        clientCount++;
    }

    logger->debug("Stopping server..");
}

void TcpServer::serve()
{
    this->initialize();
    this->start();
}

void TcpServer::initialize()
{
    string hostname = config->getHostname();
    int port = config->getPort();
    int poolSize = config->getPoolSize();

    /* Initialize acceptor */
    acceptor = new TcpAcceptor(port, hostname.c_str());

    /* Initialize thread pool */
    pool = new ThreadPool(poolSize);

    logger->info("Server Name: " + config->getName());
    logger->info("Server Description: " + config->getDescription());
    logger->info("Server Hostname: " + hostname);
    logger->info("Server Port: " + numberToString<int>(port));
    logger->info("Server Poolsize: " + numberToString<int>(poolSize));
}

void TcpServer::cycle(TcpClientInfo *client, string input)
{
    string trace = "received [" + client->getIdentity() + "] - " + input;
    logger->trace(trace);

    if (validateCommand(input))
    {
        /* Process Message */
        processCommand(client, input);
    }
    else
    {
        /* Process Error Message */
        processErrorCommand(client, input);
    }
}

bool TcpServer::validateCommand(string command)
{
    return true;
}

void TcpServer::processCommand(TcpClientInfo *client, string command)
{
    TcpStream *stream = client->getStream();
    stream->send(command);
}

void TcpServer::processErrorCommand(TcpClientInfo *client, string command)
{
    /* send error message back */
    TcpProtocol::error(client);
}
