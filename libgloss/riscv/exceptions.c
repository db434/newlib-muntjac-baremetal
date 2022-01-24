// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <stdint.h>
#include <stdio.h>
#include <machine/cregs.h>

unsigned int get_mepc() {
  uint32_t result;
  CSR_READ(mepc, result);
  return result;
}

unsigned int get_mcause() {
  uint32_t result;
  CSR_READ(mcause, result);
  return result;
}

unsigned int get_mtval() {
  uint32_t result;
  CSR_READ(mtval, result);
  return result;
}

// Don't actually handle exceptions, just print and abort.
void simple_exc_handler(void) {
  printf("EXCEPTION!!!\n");
  printf("============\n");
  printf("MEPC:   0x%x\n", get_mepc());
  printf("MCAUSE: 0x%x\n", get_mcause());
  printf("MTVAL:  0x%x\n", get_mtval());

  exit(1);
}
