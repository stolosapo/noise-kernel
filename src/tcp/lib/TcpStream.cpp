#include <arpa/inet.h>
#include <iostream>
#include "TcpStream.h"

using namespace std;
using namespace NoiseKernel;

TcpStream::TcpStream(int sd, struct sockaddr_in* address) : sd(sd)
{
    char ip[50];
    inet_ntop(
        PF_INET,
        (struct in_addr*)&(address->sin_addr.s_addr),
        ip,
        sizeof(ip)-1);

    peerIP = ip;
    peerPort = ntohs(address->sin_port);
}

TcpStream::TcpStream()
{

}

TcpStream::TcpStream(const TcpStream& stream)
{

}

TcpStream::~TcpStream()
{
    close(sd);
}

string TcpStream::getPeerIP()
{
    return this->peerIP;
}

int TcpStream::getPeerPort()
{
    return this->peerPort;
}

ssize_t TcpStream::send(const char* buffer, size_t len)
{
    return write(sd, buffer, len);
}

ssize_t TcpStream::send(string message)
{
    return send(message.c_str(), message.size());
}

ssize_t TcpStream::receive(char* buffer, size_t len)
{
    return read(sd, buffer, len);
}

ssize_t TcpStream::receive(string& message)
{
    char line[RECEIVE_SIZE];
    int len = receive(line, sizeof(line));

    if (len > 0)
    {
        line[len] = 0;
        message = (string) line;
    }
    else
    {
        message = "";
    }

    return len;
}

ssize_t TcpStream::receiveAll(string& message)
{
    string result = "";
    int cnt = 0;
    ssize_t currentSize = receive(result);
    ssize_t totalSize = currentSize;

    while (currentSize == RECEIVE_SIZE && cnt < 50)
    {
        cnt++;

        string s = "";
        currentSize = receive(s);

        result += s;
        totalSize += currentSize;
    }

    if (cnt >= 50)
    {
        result += "\n";
        result += "\n========================\n";
        result += "\n TOO LARGE RECEIVE TEXT \n";
        result += "\n MISSING TEXT...        \n";
        result += "\n========================\n";
        result += "\n";
    }

    message = result;

    return totalSize;
}

int TcpStream::connectionErrorCode()
{
    int error_code;
    socklen_t error_code_size = sizeof(error_code);
    getsockopt(sd, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
    return error_code;
}
