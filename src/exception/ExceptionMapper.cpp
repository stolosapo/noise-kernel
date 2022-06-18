#include "../Exception.h"

using namespace NoiseKernel;

string NoiseKernel::handle(RuntimeException& e)
{
	return string(e.what());
}

string NoiseKernel::handle(DomainException& e)
{
	string message = e.message();

	string fullError = string(e.code()) + ": " + e.message();

	return fullError;
}
