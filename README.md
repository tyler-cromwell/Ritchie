# Ritchie

## What is Ritchie?
Ritchie is a hobbyist Operating System Kernel I am working on to learn more about different CPU architectures (currently x86/amd64), Operating System concepts, and to get more C/Assembly programming practice.<br/>
<br/>
This project is named in honor of the late, great [Dennis Ritchie][dmr].

## Repository Hierarchy
- `arch` - Architecture specific code.
- `drivers` - Driver code.
- `include` - Platform independent header files.
- `kernel` - Kernel core.

## Branches
- `master` - Mainline branch. Documentation changes, bug fixes, and feature/subsystem merges are committed to this branch.
- `<branch>` - All other branches are meant for development of specific features/subsystems (i.e. `multiboot`, `paging`).

## Coding Convention
- All uppercase for Macros and Constants with underscores for spaces (i.e. `FG_WHITE`).
- Camelcase for Structs and Typedefs (i.e. `GdtDescriptor`).
- All lowercase, underscores for spaces, and subsystem prefix for function names (i.e. `cpuid_vendor`, `gdt_init`).
   - Double underscore prefix for functions or function-like macros that should not be called directly (`__console_write`).
- Data types only in forward declarations (`strncpy(char*, char*, size_t)`).

## Toolchain
- `Makefile` - This Makefile is used to build the kernel and test it.
  - `make` - Builds the kernel image file.
  - `make iso` - Builds an iso image with GRUB as the bootloader.
  - `make burn` - Burns the iso image to the given device file.
  - `make qemu` - Boots the kernel directly under QEMU.
  - `make qemu-iso` - Boots the iso image under QEMU.
  - `make clean` - Deletes all object files and the kernel image file.
- `link.ld` - Simple linker script that determines the physical address the kernel is loaded at during boot.
- `grub.cfg` - Basic GRUB config file, tells GRUB to use Multiboot to load the kernel.

[dmr]: http://en.wikipedia.org/wiki/Dennis_Ritchie
