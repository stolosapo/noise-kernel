#ifndef TcpConnector_h__
#define TcpConnector_h__

#include <netinet/in.h>
#include "TcpStream.h"

namespace NoiseKernel
{
    class TcpConnector
    {
    private:
        int resolveHost(const char* host, struct in_addr* addr);

    public:
        TcpStream* connect(int port, const char* server);
    };
}

#endif // TcpConnector_h__
