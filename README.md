# Overengineered

The game is implemented in C++ and built with the gcc/make toolchain. Clang/LLVM
have been tested and compile just fine on Darwin. The Makefile automatically
compiles the needed source files and rebuilds only what has changed.

## Dependencies

The game depens on the C++ standard library, the C standard library (for unix
system calls) and `ncurses` which must have a version greater or equal than `6`.
Please note that, at the time of writing, the default version shipped with OSX
is `5.2` and it is therefore mandatory to install the library manually or via
a package manager such as [homebrew](https://brew.sh).

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

## Commands

Walking, jumping, and crossing platforms can be achieved with any of the following:
* `wasd` keys
* `hjkl` keys (vim-style)
* arrow keys

Additionally, you can use `q` or `e` for a diagonal jump in one of two directions.

Simply pressing `o` at any time activates your character's standard skill. Using `p` while their mana gauge is full will empty it and unleash a high-level move.

The `ESC` button lets you abandon the current game, potentially updating the leaderboard with your score.

## Support

Supported platforms include Linux and OSX/Darwin. The software has been tested
on MacOS inside both the iTerm2 and Alacritty terminal and on Linux on a variety
of terminals and distributions, with various standard libraries and compilers.

## Credits

Made by Mattia Girolimetto, Andreea Scrob, Luca Tagliavini, and Stefano Volpe.
