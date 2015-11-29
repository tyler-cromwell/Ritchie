# AMD64
This directory contains all AMD64 specific code.

## Contents

#### Directories
- `boot` - Contains code needed for booting/starting the Kernel on an AMD64 machine.

#### Files
- `cpuid.c` - Functions that make use of the CPUID instruction.
- `exceptions.asm` - Implements the system Exception handlers.
- `idt.c` - Defines the Interrupt Descriptor Table.
- `interrupts.h` - Forward declarations for all interrupt handlers in C.
- `irqs.asm` - Implements the Interrupt Request handlers.