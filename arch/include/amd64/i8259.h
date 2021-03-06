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

#ifndef AMD64_I8259_H
#define AMD64_I8259_H

// Kernel header(s)
#include <kernel/types.h>

// Master PIC
#define I8259_MASTER_CMD    0x20
#define I8259_MASTER_DATA   0x21

// Slave PIC
#define I8259_SLAVE_CMD     0xA0
#define I8259_SLAVE_DATA    0xA1

// Device IRQ numbers
#define I8259_IRQ_TIMER     0x00
#define I8259_IRQ_KEYBOARD  0x01


/*
 * Masks the given IRQ.
 * Arugment:
 *   byte_t irq: The IRQ number to mask.
 */
void i8259_set_mask(byte_t irq);


/*
 * Unmasks the given IRQ.
 * Argument:
 *   byte_t irq: The IRQ number to unmask.
 */
void i8259_clear_mask(byte_t irq);


/*
 * Disables all IRQs (masks them).
 */
void i8259_mask(void);


/*
 * Enables all IRQs (unmasks them).
 */
void i8259_unmask(void);

#endif
