#include <iostream>
#include <Argument.h>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "noisekernel Library" << endl << endl;

    NoiseKernel::ArgumentParser parser;
    parser.print(argc, argv);

    cout << "Bye Bye.." << endl;
}
