#include <iostream>
#include "Argument.h"
#include "Signal.h"
#include "argument/MockAdapter.h"
#include "Tcp.h"
#include "Logger.h"

using namespace std;

void runTcpServer(NoiseKernel::SignalAdapter *signalAdapter);
void runTcpClient(NoiseKernel::SignalAdapter *signalAdapter);

int main(int argc, char* argv[])
{
    cout << "noisekernel Library" << endl << endl;

    NoiseKernel::ArgumentProvider provider(argc, argv);
    MockAdapter adapter(&provider);
    adapter.registerArguments();
    cout << adapter.help() << endl;

    NoiseKernel::SignalAdapter signalAdapter;
    signalAdapter.registerSignals();
    signalAdapter.setup();
    // cout << "Got SIGINT: " << signalAdapter.gotSigInt() << endl;
    // raise(SIGINT);
    // cout << "Got SIGINT and reset it: " << signalAdapter.gotSigIntAndReset() << endl;

    if (adapter.isTcpServer())
    {
        runTcpServer(&signalAdapter);
    }
    else if (adapter.isTcpClient())
    {
        runTcpClient(&signalAdapter);
    }

    cout << "Bye Bye.." << endl;
}

void runTcpServer(NoiseKernel::SignalAdapter *signalAdapter)
{
    cout << "This is a TCP Server from noisekernel Library" << endl << endl;

    NoiseKernel::LogService logger = NoiseKernel::buildBasicLogService();
    NoiseKernel::TcpProtocol protocol(true);
    NoiseKernel::TcpServerConfig config(
        1,
        "TcpServer",
        "This is a simple Tcp Server",
        NoiseKernel::TcpServerConfig::DEFAULT_HOSTNAME,
        NoiseKernel::TcpServerConfig::DEFAULT_PORT,
        NoiseKernel::TcpServerConfig::DEFAULT_THREAD_POOL_SIZE
    );
    NoiseKernel::TcpServer server(
        &logger,
        signalAdapter,
        &config,
        &protocol
    );

    server.action();

    cout << "TCP Server stopped" << endl << endl;
}

void runTcpClient(NoiseKernel::SignalAdapter *signalAdapter)
{
    cout << "This is a TCP Client from noisekernel Library" << endl << endl;

    NoiseKernel::LogService logger = NoiseKernel::buildBasicLogService();
    NoiseKernel::TcpProtocol protocol(false);
    NoiseKernel::TcpClientConfig config(
        1,
        "TcpConfig",
        "This is a simple Tcp client",
        NoiseKernel::TcpClientConfig::DEFAULT_SERVERNAME,
        NoiseKernel::TcpClientConfig::DEFAULT_PORT
    );
    NoiseKernel::TcpClient client(
        &logger,
        signalAdapter,
        &config,
        &protocol
    );

    client.action();

    cout << "TCP Client stopped" << endl << endl;
}
