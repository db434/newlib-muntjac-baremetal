// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <errno.h>
#include <reent.h>
#include <stdint.h>

// Communication with the host system.
extern volatile uint64_t tohost;
extern volatile uint64_t fromhost;

// Data to write to tohost to indicate the service being requested.
// If the service takes an argument, the least significant byte will be used.
const uint64_t putchar_code = 0x0101000000000000;
const uint64_t sysexit_code = 0x0000000000000000;

char inbyte() {
  return fromhost & 0xff;
}

char outbyte(char c) {
  tohost = putchar_code | (c & 0xff);

  return c;
}

_ssize_t _write(int fd, const void *buf, size_t nbytes) {
	char* bytes = (char*) buf;

  // Print everything to the terminal for now.
  // TODO: Use fd (and don't always output \r?).

	for (int i=0; i<nbytes; i++) {
		if (bytes[i] == '\n') {
			outbyte('\r');
		}
		outbyte(bytes[i]);
	}

	return nbytes;
}

void _exit(int code) {
  tohost = sysexit_code | (code & 0xff);

  // Might not have a return address set up so never return.
  while(1);
}

int _close(int fildes) {
	errno = ENOSYS;
	return -1;
}

int _execve(const char *name, char * const *argv,	char * const *env) {
	errno = ENOSYS;
	return -1;
}

int _fork() {
	errno = ENOSYS;
	return -1;
}

int _fstat(int fildes, struct stat *st) {
	errno = ENOSYS;
	return -1;
}

int _getpid() {
	errno = ENOSYS;
	return -1;
}

int _gettimeofday(struct timeval  *ptimeval, void *ptimezone) {
	errno = ENOSYS;
	return -1;
}

int _isatty(int file) {
	errno = ENOSYS;
	return 0;
}

int _kill(int pid, int sig) {
	errno = ENOSYS;
	return -1;
}

int _link(const char *existing, const char *new) {
	errno = ENOSYS;
	return -1;
}

_off_t _lseek(int file, _off_t ptr, int dir) {
	errno = ENOSYS;
	return -1;
}

int _open(const char *file, int flags, int mode) {
	errno = ENOSYS;
	return -1;
}

_ssize_t _read(int file, void *ptr, size_t len) {
	errno = ENOSYS;
	return -1;
}

int _readlink(const char *path, char *buf, size_t bufsize) {
	errno = ENOSYS;
	return -1;
}

int _stat(const char *path, struct stat *buf) {
	errno = EIO;
	return -1;
}

int _unlink(const char * path) {
	errno = EIO;
	return (-1);
}
