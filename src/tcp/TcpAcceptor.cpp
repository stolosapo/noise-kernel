#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "../Tcp.h"

using namespace NoiseKernel;

TcpAcceptor::TcpAcceptor()
{

}

TcpAcceptor::TcpAcceptor(int port, const char* address)
    : lsd(0), port(port), address(address), listening(false)
{

}

TcpAcceptor::~TcpAcceptor()
{
    if (lsd > 0)
    {
        close(lsd);
    }
}

int TcpAcceptor::start()
{
    if (listening == true)
    {
        return 0;
    }

    lsd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(port);

    if (this->address.size() > 0)
    {
        inet_pton(PF_INET, this->address.c_str(), &(address.sin_addr));
    }
    else
    {
        address.sin_addr.s_addr = INADDR_ANY;
    }

    int optval = 1;
    setsockopt(lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    int result = bind(lsd, (struct sockaddr*)&address, sizeof(address));
    if (result != 0)
    {
        perror("bind() failed");
        return result;
    }

    result = listen(lsd, 5);
    if (result != 0)
    {
        perror("listen() failed");
        return result;
    }

    listening = true;
    return result;
}

TcpStream* TcpAcceptor::accept()
{
    if (listening == false)
    {
        return NULL;
    }

    struct sockaddr_in address;
    socklen_t len = sizeof(address);
    memset(&address, 0, sizeof(address));
    int sd = ::accept(lsd, (struct sockaddr*)&address, &len);
    if (sd < 0)
    {
        perror("accept() failed");
        return NULL;
    }

    return new TcpStream(sd, &address);
}
