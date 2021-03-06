/* Copyright lowRISC contributors.
   Licensed under the Apache License, Version 2.0, see LICENSE for details.
   SPDX-License-Identifier: Apache-2.0 */

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

/* System calls and I/O cannot be cached, so they go straight to the host
   machine. This uncached address must match the AddressBase parameter in
   Muntjac's last-level cache and any relevant TileLink modules. */
MEMORY
{
   program (rwx)  : ORIGIN = 0x80000000, LENGTH = 0x10000
   uncached (rw)  : ORIGIN = 0x80010000, LENGTH = 0x40
   data (rw)      : ORIGIN = 0x80010040, LENGTH = 128M - 0x10040
}

SECTIONS
{

  .text.init : { *(.text.init) } > program

  .text :
  {
    . = ALIGN(0x1000);
    *(.text)
    *(.text.*)
  } > program

  .data :
  {
    . = ALIGN(0x1000);
    __data_begin = .;
    /* Small data before large data */
    *(.sdata)
    *(.sdata.*)
    *(.data)
    *(.data.*)
  } > data

  .rodata :
  {
    . = ALIGN(8);
    /* Small RO data before large RO data */
    *(.srodata)
    *(.srodata.*)
    *(.rodata)
    *(.rodata.*)
  } > data

  .bss :
  {
    . = ALIGN(8);
    /* Small BSS before large BSS */
    *(.sbss)
    *(.sbss.*)
    *(.bss)
    *(.bss.*)
    *(COMMON)

    . = ALIGN(8);
    __bss_end = .;
  } > data

  /* Sensible default taken from the default linker script.
     `riscv64-unknown-elf-ld --verbose` */
  __global_pointer = MAX(__data_begin + 0x800, __bss_end - 0x800);

  _end = .;

  .io :
  {
    . = ALIGN(8);
    tohost = .;
    *(.tohost)

    . += 8;
    . = ALIGN(8);
    fromhost = .;
    *(.fromhost)
  } > uncached

  PROVIDE(__stack_start = ORIGIN(data) + LENGTH(data));

}
