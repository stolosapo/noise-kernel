# noise-kernel
A simple C++ library with many goodies... like Threads, Tasks, Arguments, Observables, GPIO and more

### TODO: Replace this across the project..
```
noisekernel    = the library name, to be installed
```

![GitHub release (latest by date)](https://img.shields.io/github/v/release/stolosapo/noise-kernel)

![Build](https://github.com/stolosapo/noise-kernel/actions/workflows/makefile.yml/badge.svg) 

### Prepare compilation
```bash
./autogen.sh
```

### Installation
```bash
./configure
make
sudo make install
sudo ldconfig /usr/local/lib
```

### Uninstallation
```bash
sudo make uninstall
```

### Run
```bash
noisekernel
```

## Clean all untracked files
```bash
git clean -xdf
```

### Use Library
If everything installed fine then pass `-lnoisekernel` parameter in linker, when build your application.
Then use it in your app like in `example/`.
