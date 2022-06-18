#ifndef TcpAcceptor_h__
#define TcpAcceptor_h__

#include <string>
#include <netinet/in.h>
#include "TcpStream.h"

using namespace std;

namespace NoiseKernel
{
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
}

#endif // TcpAcceptor_h__
