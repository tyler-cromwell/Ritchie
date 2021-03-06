/**********************************************************************
  Copyright (C) 2015-Present Tyler Cromwell <tjc6185@gmail.com>

  This file is part of Mantle.

  Mantle is free software: you can redistribute it and/or modify
  it under Version 2 of the terms of the GNU General Public License
  as published by the Free Software Foundation.

  Mantle is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY of FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Mantle.
  If not, see <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>
**********************************************************************/

// C Standard Library header(s)
#include <stdint.h>

// Kernel header(s)
#include <amd64/asm.h>
#include <kernel/types.h>

// Master PIC
#define MASTER_CMD  0x20
#define MASTER_DATA 0x21

// Slave PIC
#define SLAVE_CMD   0xA0
#define SLAVE_DATA  0xA1


void i8259_set_mask(byte_t irq) {
    word_t port;
    byte_t value;

    // Determine PIC
    if (irq < 8) {
        port = MASTER_DATA;
    } else {
        port = SLAVE_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value);
}


void i8259_clear_mask(byte_t irq) {
    word_t port;
    byte_t value;

    // Determine PIC
    if (irq < 8) {
        port = MASTER_DATA;
    } else {
        port = SLAVE_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}


void i8259_mask(void) {
    outb(MASTER_DATA, 0xff);
    outb(SLAVE_DATA,  0xff);
}


void i8259_unmask(void) {
    outb(MASTER_DATA, 0x00);
    outb(SLAVE_DATA,  0x00);
}
