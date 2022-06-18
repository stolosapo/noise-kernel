#ifndef Tcp_h__
#define Tcp_h__

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <time.h>

#include "Thread.h"
#include "Exception.h"
#include "Logger.h"
#include "Signal.h"

using namespace std;

namespace NoiseKernel
{
    static const DomainErrorCode TCS0001;
    static const DomainErrorCode TCS0002;
    static const DomainErrorCode TCC0001;
    static const DomainErrorCode TCP0001;

    class TcpStream
    {
    private:
        static const int RECEIVE_SIZE = 256;

        int sd;
        string peerIP;
        int peerPort;

        TcpStream(int sd, struct sockaddr_in* address);
        TcpStream();
        TcpStream(const TcpStream& stream);

    public:
        friend class TcpAcceptor;
        friend class TcpConnector;

        ~TcpStream();

        ssize_t send(string message);
        ssize_t send(const char* buffer, size_t len);

        ssize_t receive(string& message);
        ssize_t receive(char* buffer, size_t len);
        ssize_t receiveAll(string& message);

        int connectionErrorCode();

        string getPeerIP();
        int getPeerPort();
    };

    class TcpConnector
    {
    private:
        int resolveHost(const char* host, struct in_addr* addr);

    public:
        TcpStream* connect(int port, const char* server);
    };

    class TcpAcceptor
    {
    private:
        int lsd;
        string address;
        int port;
        bool listening;

        TcpAcceptor();

    public:
        TcpAcceptor(int port, const char* address = "");
        virtual ~TcpAcceptor();

        int start();
        TcpStream* accept();
    };

    class TcpClientInfo
    {
    private:
        int index;

        Thread* thread;

        string name;
        string ip;
        string hostname;

        TcpStream *stream;
        void* server;

    public:
        TcpClientInfo(void *server, TcpStream *stream, Thread *thread, int index);
        TcpClientInfo(void *server, TcpStream *stream, int index);
        virtual ~TcpClientInfo();

        int getIndex();

        Thread* getThread();

        string getName();
        string getIp();
        string getHostname();
        string getIdentity();

        TcpStream* getStream();
        void* getServer();

        void setName(string name);
        void setIp(string ip);
        void setHostname(string hostname);
    };

    class TcpProtocol
    {
    private:
        bool isServer;

    public:
        TcpProtocol(bool isServer);
        virtual ~TcpProtocol();

        void handshake(TcpClientInfo *client);
        void authenticate(TcpClientInfo *client);

        virtual string prompt();

        virtual bool isHelp(string command);
        virtual string help();

        static bool exit(string command);
        static bool shutdown(string command);
        static bool error(string command);
        static void error(TcpClientInfo *client);

    protected:
        static const char* PROMPT;

        static const char* CLIENT_CONNECT;
        static const char* OK;
        static const char* DENIED;
        static const char* ERROR;

        static const char* HELP;
        static const char* EXIT;
        static const char* SHUTDOWN;

        bool getIsServer();

        void send(bool escape, TcpClientInfo *client, const char* command);
        void receive(bool escape, TcpClientInfo *client, const char* expected, const DomainErrorCode& errorCode);

        void serverSend(TcpClientInfo *client, const char* command);
        void serverReceive(TcpClientInfo *client, const char* expected, const DomainErrorCode& errorCode);

        void clientSend(TcpClientInfo *client, const char* command);
        void clientReceive(TcpClientInfo *client, const char* expected, const DomainErrorCode& errorCode);

    };

    class TcpServerConfig
    {
    private:
        int id;
        string name;
        string description;
        string hostname;
        int port;
        int poolSize;

    public:
        static const int DEFAULT_PORT;
        static const int DEFAULT_THREAD_POOL_SIZE;
        static const char* DEFAULT_HOSTNAME;

        TcpServerConfig(
            int id,
            string name,
            string description,
            string hostname,
            int port,
            int poolSize);
        virtual ~TcpServerConfig();

        int getId();
        string getName();
        string getDescription();
        string getHostname();
        int getPort();
        int getPoolSize();
    };

    class TcpClientConfig
    {
    private:
        int id;
        string name;
        string description;
        string serverName;
        int serverPort;

    public:
        static const int DEFAULT_PORT;
        static const char* DEFAULT_SERVERNAME;

        TcpClientConfig(
            int id,
            string name,
            string description,
            string serverName,
            int serverPort);
        virtual ~TcpClientConfig();

        int getId();
        string getName();
        string getDescription();
        string getServerName();
        int getServerPort();
    };

    class TcpServer
    {
    private:
        TcpAcceptor *acceptor;
        ThreadPool* pool;
        map<int, TcpClientInfo*> activeClients;

        time_t startTime;

        void* task(void*);
        static void* internalClientTask(void *context);

        Thread* getNextThread();
        void finalizeClient(TcpClientInfo *client);

    protected:
        SignalAdapter* sigSrv;
        LogService *logSrv;
        TcpServerConfig* config;
        TcpProtocol *protocol;

        virtual void initialize();

        virtual void cycle(TcpClientInfo *client, string input);

        virtual bool validateCommand(string command);
        virtual void processCommand(TcpClientInfo *client, string command);
        virtual void processErrorCommand(TcpClientInfo *client, string command);

    public:
        TcpServer(LogService *logSrv, SignalAdapter *sigSrv, TcpServerConfig *config, TcpProtocol *protocol);
        virtual ~TcpServer();

        LogService* logger();

        virtual void start();
        virtual void action();

        virtual double uptime();
        virtual int numberOfActiveConnections();
    };

    class TcpClient
    {
    private:
        TcpConnector *connector;
        TcpStream *stream;
        TcpClientConfig* config;
        SignalAdapter* sigSrv;

        void finalizeClient(TcpClientInfo *client);

    protected:
        LogService *logSrv;
        TcpProtocol *protocol;

        virtual void initialize();
        virtual bool cycle(TcpClientInfo *client);
        virtual void processCommand(TcpClientInfo *client, string command);

    public:
        TcpClient(LogService *logSrv, SignalAdapter *sigSrv, TcpClientConfig *config, TcpProtocol *protocol);
        virtual ~TcpClient();

        void start();
        virtual void action();
    };

}

#endif // Tcp_h__
