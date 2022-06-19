#include "../Exception.h"

using namespace NoiseKernel;

RuntimeException::RuntimeException(const char* cause) : _cause(cause)
{

}

RuntimeException::~RuntimeException() throw()
{

}

const char* RuntimeException::what() const throw()
{
    return _cause;
}

const char* RuntimeException::cause() const throw()
{
    return _cause;
}
