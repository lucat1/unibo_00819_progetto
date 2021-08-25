# Overengineered

The game is implemented in C++ and built with the gcc/make toolchain. Clang/LLVM
have been tested and compile just fine on Darwin. The Makefile automatically
compiles the needed source files and rebuilds only what has changed.

## Building, Running and Testing

For the purpose of this step, be aware that compile flags can be changed by
providing make with the `CXXFLAGS` and `LDFLAGS` variables. Furthermore the
compiler can be set via the `CXX` variable. `g++` is used by default
(i.e. `make CXX=clang++`). Directly editing the `Makefile` source code also
works, but is not advised.

To compile and link the game binary run:

```sh
$ make
```

The default binary path can be executed with:

```sh
$ make run
```

The test suite can be run via:

```sh
$ make test
```

For the final release binaries please keep in mind that the game needs the `assets`
folder and its contents to run. Therefore always include this folder at the same
level sa the binary executable when packaging release tarballs.

## Support

Supported platforms include Linux and OSX/Darwin. The software has been tested
on MacOS inside both the iTerm2 and Alacritty terminal and on Linux on a variety
of terminals and distributions, with various standard libraries and compilers.

## Credits

Made by Mattia Girolimetto, Andreea Scrob, Luca Tagliavini, and Stefano Volpe.
