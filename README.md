# Muntjac port of Newlib
This is a port of Newlib for baremetal (no operating system) [Muntjac](https://github.com/lowRISC/muntjac). Newlib provides everything needed for the C standard library to work.

The general Newlib README is below.

## Build instructions
You will need a RISC-V compiler, and set the `RISCV_TOOLS` environment variable to its root directory. We use the Muntjac toolchain from [lowrisc-toolchains](https://github.com/lowRISC/lowrisc-toolchains).

```
mkdir build
cd build
export PATH=$RISCV_TOOLS/bin/:$PATH
../configure --target=riscv64-unknown-elf --prefix=$RISCV_TOOLS
make -j CFLAGS_FOR_TARGET="-g -O2 -mcmodel=medany"
make install
```

## Limitations
This port is not yet complete. Be aware of the following:

* Your existing toolchain will be converted to work with baremetal Muntjac only. There is currently no way to switch between baremetal and OS versions. Make a copy of the toolchain first if you need to switch between the two options.
* Every compiler invocation needs to have the following option added: `-specs baremetal.specs`. e.g. `riscv64-unknown-elf-gcc -specs baremetal.specs -o hello helloworld.c`
* Only a subset of system calls have been implemented (`write` and `exit` so far).

# README for GNU development tools

This directory contains various GNU compilers, assemblers, linkers, 
debuggers, etc., plus their support routines, definitions, and documentation.

If you are receiving this as part of a GDB release, see the file gdb/README.
If with a binutils release, see binutils/README;  if with a libg++ release,
see libg++/README, etc.  That'll give you info about this
package -- supported targets, how to use it, how to report bugs, etc.

It is now possible to automatically configure and build a variety of
tools with one command.  To build all of the tools contained herein,
run the `configure` script here, e.g.:

	./configure 
	make

To install them (by default in /usr/local/bin, /usr/local/lib, etc),
then do:

	make install

(If the configure script can't determine your type of computer, give it
the name as an argument, for instance `./configure sun4`.  You can
use the script `config.sub` to test whether a name is recognized; if
it is, config.sub translates it to a triplet specifying CPU, vendor,
and OS.)

If you have more than one compiler on your system, it is often best to
explicitly set CC in the environment before running configure, and to
also set CC when running make.  For example (assuming sh/bash/ksh):

	CC=gcc ./configure
	make

A similar example using csh:

	setenv CC gcc
	./configure
	make

Much of the code and documentation enclosed is copyright by
the Free Software Foundation, Inc.  See the file COPYING or
COPYING.LIB in the various directories, for a description of the
GNU General Public License terms under which you can copy the files.

REPORTING BUGS: Again, see gdb/README, binutils/README, etc., for info
on where and how to report problems.
