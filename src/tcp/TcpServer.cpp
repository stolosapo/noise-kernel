#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "../Tcp.h"
#include "../utils/StringHelper.h"

using namespace std;
using namespace NoiseKernel;

TcpServer::TcpServer(LogService *logSrv, SignalAdapter *sigSrv, TcpServerConfig *config, TcpProtocol *protocol)
    : logSrv(logSrv), sigSrv(sigSrv), config(config), protocol(protocol)
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
            logSrv->info("Finalized client: " + numberToString<int>(it->first));
        }
    }

    activeClients.clear();

    logSrv->trace("Server finalized!");
}

void* TcpServer::task(void *context)
{
    TcpClientInfo* client = (TcpClientInfo *) context;

    TcpServer* server = (TcpServer *) (client->getServer());
    LogService* logger = server->logSrv;
    TcpStream* stream = client->getStream();


    string input = "";

    string identity = client->getIdentity();

    try
    {
        /* Check new client for acceptance */
        server->protocol->handshake(client);

        logger->trace("Server accepted new client: [" + identity + "]");


        /* receive messages */
        while (stream->receive(input) > 0)
        {

            /* Proccess input */
            server->cycle(client, input);
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

void* TcpServer::internalClientTask(void *context)
{
    return ((TcpServer *)context)->task(context);
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
    TcpServer* server = (TcpServer *) (client->getServer());

    server->pool->putBack(client->getThread());

    map<int, TcpClientInfo*>::iterator it = server->activeClients.find(client->getIndex());
    if (it != server->activeClients.end())
    {
        server->activeClients.erase(it);
    }

    delete client;
}

LogService* TcpServer::logger()
{
    return this->logSrv;
}

double TcpServer::uptime()
{
    time_t now = time(0);
    return difftime(now, startTime);
}

int TcpServer::numberOfActiveConnections()
{
    return pool->numberOfActiveThreads();
}

void TcpServer::start()
{
    int clientCount = 0;

    logSrv->trace("Server is starting...");

    if (acceptor->start() != 0)
    {
        throw DomainException(TCS0001);
    }

    logSrv->info("Server is started");

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
        string name = "TcpClient" + numberToString<int>(clientCount);
        // th->setName(name.c_str());


        /* Add this client to active clients */
        activeClients[client->getIndex()] = client;


        /* Increase thead counter */
        clientCount++;
    }

    logSrv->debug("Stopping server..");
}

void TcpServer::action()
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

    logSrv->info("Server Name: " + config->getName());
    logSrv->info("Server Description: " + config->getDescription());
    logSrv->info("Server Hostname: " + hostname);
    logSrv->info("Server Port: " + numberToString<int>(port));
    logSrv->info("Server Poolsize: " + numberToString<int>(poolSize));
}

void TcpServer::cycle(TcpClientInfo *client, string input)
{
    LogService* logger = ((TcpServer*) client->getServer())->logger();

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

    logger = NULL;
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
