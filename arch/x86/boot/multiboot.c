/* C Standard Library Headers,
   these don't need to link against libc */
#include <stddef.h>

/* Kernel Headers */
#include <drivers/console.h> // Delete
#include <kernel/mem.h>
#include <kernel/string.h> // Delete
#include <x86/multiboot.h>

#define MMAP_MAX        20  /* Maximum memory map entries (completely arbitrary for now) */
#define MMAP_AVAILABLE  1   /* Memory available for use */
#define MMAP_RESERVED   2   /* Reserved memory */

/* Multiboot information structures */
static struct MultibootInfo* info;
static struct MultibootMmap mmap[MMAP_MAX];

/*
 * Initializes all applicable structures from information passed in from the Bootloader.
 * Argument(s):
 *   struct MultibootInfo* mbinfo: Pointer to the info struct created by the Bootloader.
 */
void multiboot_init(struct MultibootInfo* mbinfo) {
    info = mbinfo;

    /* Initialize the Memory Map */
    if (info->flags & MULTIBOOT_MMAP) {
        /* Partition the memory map buffer into an array of structs */
        memcpy(mmap, (void*) info->mmap_addr, info->mmap_length);
        
        size_t ents = info->mmap_length / sizeof(struct MultibootMmap);

        console_printf(FG_CYAN, "Memory Map:\n0");
        for (size_t i = 0; i < ents; i++) {
            char* l = itoa(mmap[i].base_addr / 1024);
            if (strlen(l) >= 4) {
                l = itoa(mmap[i].base_addr / 1024 / 1024);
                console_printf(FG_CYAN, "%sMB - ", l);
            }
            else console_printf(FG_CYAN, "%sKB - ", l);

            char* h = itoa((mmap[i].base_addr + mmap[i].length) / 1024);
            if (strlen(h) >= 4) {
                h = itoa((mmap[i].base_addr + mmap[i].length) / 1024 / 1024);
                console_printf(FG_CYAN, "%sMB (", h);
            }
            else console_printf(FG_CYAN, "%sKB (", h);

            char* len = itoa(mmap[i].length / 1024);
            console_printf(FG_CYAN, "%sKB, ", len);
            
            if (mmap[i].type == MMAP_AVAILABLE)
                console_printf(FG_CYAN, "Available");
            else if (mmap[i].type == MMAP_RESERVED)
                console_printf(FG_CYAN, "Reserved");
            else
                console_printf(FG_CYAN, "?");

            console_printf(FG_CYAN, ")\n");
        }

        /* Create an entry for the Kernel */
        struct MultibootMmap kernel = {
            .size = 20,
            .base_addr = 0x01000000,    /* Start 16MB into RAM */
            .length = 16 * 1024 * 1024, /* Region is 16MB wide, gives space to grow */
            .type = MMAP_RESERVED       /* Don't overwrite the kernel */
        };

        for (size_t i = 0; i < ents; i++) {
            uint64_t ent_addr_upper = mmap[i].base_addr + mmap[i].length;
            uint64_t kernel_addr_upper = kernel.base_addr + kernel.length;

            /* If the kernel region fits in the first available region */
            if (mmap[i].type == MMAP_AVAILABLE &&
                kernel.base_addr >= mmap[i].base_addr &&
                kernel_addr_upper <= ent_addr_upper) {
                ;
                // Partition that AVAILABLE space
                // Shift (memmove) map forward 16MB from end of first partition
                // Insert (memcpy) kernel struct
                break;
            }
        }
    }

    if (info->flags & MULTIBOOT_DRIVES) {}
}
