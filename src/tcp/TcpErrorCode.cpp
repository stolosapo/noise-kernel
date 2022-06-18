#include "../Tcp.h"

using namespace NoiseKernel;

// Server Errors
const DomainErrorCode NoiseKernel::TCS0001 = DomainErrorCode("TCS0001", "Could not start the Server");
const DomainErrorCode NoiseKernel::TCS0002 = DomainErrorCode("TCS0002", "Server denied access to the client: %s");

// Client Errors
const DomainErrorCode NoiseKernel::TCC0001 = DomainErrorCode("TCC0001", "Could not connect the Server");

// Protocol Errors
const DomainErrorCode NoiseKernel::TCP0001 = DomainErrorCode("TCP0001", "Handshake error");

