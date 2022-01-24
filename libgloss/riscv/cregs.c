// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <machine/cregs.h>

void pcount_reset() {
  asm volatile(
    "csrw minstret,       x0\n"
    "csrw mcycle,         x0\n"
  );
}

void pcount_enable(int enable) {
  // Note cycle is disabled with everything else
  unsigned int inhibit_val = enable ? 0x0 : 0xFFFFFFFFFFFFFFFF;
  // CSR 0x320 was called `mucounteren` in the privileged spec v1.9.1, it was
  // then dropped in v1.10, and then re-added in v1.11 with the name
  // `mcountinhibit`. We use the numeric value here for maximum compatibility.
  CSR_WRITE(0x320, inhibit_val);
}
