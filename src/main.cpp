#include <iostream>
#include "Argument.h"
#include "argument/MockAdapter.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "noisekernel Library" << endl << endl;

    NoiseKernel::ArgumentProvider provider(argc, argv);
    MockAdapter adapter(&provider);
    adapter.registerArguments();

    cout << adapter.help() << endl;

    cout << "Bye Bye.." << endl;
}
