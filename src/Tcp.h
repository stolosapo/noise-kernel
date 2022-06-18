#ifndef Tcp_h__
#define Tcp_h__

#include <string>
#include "lib/TcpStream.h"
#include "Thread.h"
#include "Exception.h"

using namespace std;

namespace NoiseKernel
{
    static const DomainErrorCode TCS0001;
    static const DomainErrorCode TCS0002;
    static const DomainErrorCode TCC0001;
    static const DomainErrorCode TCP0001;

    class ClientInfo
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
        ClientInfo(void *server, TcpStream *stream, Thread *thread, int index);
        ClientInfo(void *server, TcpStream *stream, int index);
        virtual ~ClientInfo();

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

        void handshake(ClientInfo *client);
        void authenticate(ClientInfo *client);

        virtual string prompt();

        virtual bool isHelp(string command);
        virtual string help();

        static bool exit(string command);
        static bool shutdown(string command);
        static bool error(string command);
        static void error(ClientInfo *client);

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

        void send(bool escape, ClientInfo *client, const char* command);
        void receive(bool escape, ClientInfo *client, const char* expected, const DomainErrorCode& errorCode);

        void serverSend(ClientInfo *client, const char* command);
        void serverReceive(ClientInfo *client, const char* expected, const DomainErrorCode& errorCode);

        void clientSend(ClientInfo *client, const char* command);
        void clientReceive(ClientInfo *client, const char* expected, const DomainErrorCode& errorCode);

    };

}

#endif // Tcp_h__
