# example of using `noisekernel` lib

## build example
```bash
g++ -g -c -o example.o example.cpp
g++ -g -c -o mocks.o mocks/mocks.cpp
g++ example.o mocks.o -o example -pthread -lnoisekernel
./example
```
