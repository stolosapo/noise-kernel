#include <iostream>
#include <noisekernel/Argument.h>
#include "argument/ExampleArgumentAdapter.h"

using namespace std;

int argument_example(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    cout << "Example noisekernel" << endl << endl;

    argument_example(argc, argv);
}

int argument_example(int argc, char* argv[])
{
    cout << "Example for arguments of noisekernel" << endl << endl;

    // First we create an new provider
    NoiseKernel::ArgumentProvider provider(argc, argv);

    // Then a new instance of the adapter that we have create for the specific system
    ExampleArgumentAdapter adapter(&provider);

    // not forget to register the arguments
    adapter.registerArguments();

    // and is ready for use
    cout << "Name: " << adapter.getName() << endl
        << "Description: " << adapter.getDescription() << endl
        << "Number: " << adapter.getANumber() << endl << endl
        << adapter.help() << endl;
}
