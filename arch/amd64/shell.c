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

// Kernel header(s)
#include <amd64/asm.h>
#include <amd64/console.h>
#include <amd64/cpuid.h>
#include <amd64/multiboot.h>
#include <amd64/shell.h>
#include <kernel/kernel.h>
#include <kernel/types.h>
#include <lib/string.h>

// External functions / variables
extern char keyboard_getchar(void);     // Defined in "keyboard.c"

// Internal variables
static char input[SHELL_BUFSIZ] = {0};


char* shell_readline(char *prompt) {
    char *next = input;
    char *end = input + SHELL_BUFSIZ - 1;
    uchar_t backspaces = 0;

    console_printf(FG_WHITE, "%s", prompt);
    memset(input, '\0', SHELL_BUFSIZ);

    while (1) {
        char letter = keyboard_getchar();

        // Handle Newline
        if (letter == '\n') {
            backspaces = 0;
            console_printf(FG_WHITE, "%c", letter);
            break;
        }
        // Handle Backspace
        else if (letter == '\b' && next != input) {
            backspaces--;
            next--;
            *next = '\0';
            console_printf(FG_WHITE, "%c", letter);
        }
        // Handle printable characters
        else if (letter >= 32 && letter <= 126 && next != end) {
            backspaces++;
            *next = letter;
            *next++;
            console_printf(FG_WHITE, "%c", letter);
        }
    }

    return input;
}


void shell_cmd_kinfo(void) {
    // Get Kernel size
    ulong_t size = ((ulong_t) &KERNEL_SIZE) / 1024;
    console_printf(FG_WHITE, "Size in memory:\t\t%uKB\n", size);
    console_printf(FG_WHITE, "Physical address:\t%x\n", &KERNEL_LMA);
    console_printf(FG_WHITE, "Bootstrap address:\t%x\n", &BOOTSTRAP);
    console_printf(FG_WHITE, "Text section:\t\t%x\n", &SECTION_TEXT);
    console_printf(FG_WHITE, "Data section:\t\t%x\n", &SECTION_DATA);
    console_printf(FG_WHITE, "BSS section:\t\t%x\n", &SECTION_BSS);
    console_printf(FG_WHITE, "Free memory:\t\t%x\n", &KERNEL_END);
}


void shell_cmd_cpuinfo(void) {
    // Get CPU vendor name
    char id[13] = {0};
    cpuid_vendor(id);
    console_printf(FG_WHITE, "vendor_id: ");

    // Print CPU vendor name
    if (!strncmp(id, VENDOR_INTEL, strlen(id))) {
        console_printf(FG_CYAN_L, "%s\n", id);
    } else if (!strncmp(id, VENDOR_AMD, strlen(id))) {
        console_printf(FG_RED_L, "%s\n", id);
    } else {
        console_printf(FG_GREY_L, "%s\n", id);
    }

    // Get and print number of processors
    console_printf(FG_WHITE, "processors: %u\n", cpuid_cpus());
}


void shell_cmd_multiboot(ulong_t magic) {
    if (magic == MULTIBOOT_BOOT_MAGIC) {
        multiboot_dump();
    } else {
        console_printf(FG_WHITE, "Kernel not booted via Multiboot\n");
    }
}


void shell_cmd_shutdown() {
    outw(0x604, 0x2000);
}
