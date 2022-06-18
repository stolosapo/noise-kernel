#ifndef TcpStream_h__
#define TcpStream_h__

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using namespace std;

namespace NoiseKernel
{
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
}

#endif // TcpStream_h__
