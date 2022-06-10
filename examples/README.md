# example of using `noisekernel` lib

## build example
```bash
g++ -g -c -o example.o example.cpp
g++ -g -c -o ExampleArgumentAdapter.o argument/ExampleArgumentAdapter.cpp
g++ -g -c -o MockDelegate.o observer/MockDelegate.cpp
g++ -g -c -o MockEventHandler.o observer/MockEventHandler.cpp
g++ -g -c -o MockSender.o observer/MockSender.cpp
g++ example.o ExampleArgumentAdapter.o MockDelegate.o MockEventHandler.o MockSender.o -o example -lnoisekernel
./example
```
