# example of using `noisekernel` lib

## build example
```bash
g++ -g -c -o example.o example.cpp
g++ -g -c -o ExampleArgumentAdapter.o argument/ExampleArgumentAdapter.cpp
g++ example.o ExampleArgumentAdapter.o -o example -lnoisekernel
./example
```
