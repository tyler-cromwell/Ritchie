#ifndef DRIVERS_CONSOLE_H
#define DRIVERS_CONSOLE_H

#include <stddef.h>
#include <stdint.h>

/* Text colors */
#define FG_BLACK        0x00
#define FG_BLUE         0x01
#define FG_GREEN        0x02
#define FG_CYAN         0x03
#define FG_RED          0x04
#define FG_MAGENTA      0x05
#define FG_BROWN        0x06
#define FG_GREY_L       0x07
#define FG_GREY         0x08
#define FG_BLUE_L       0x09
#define FG_GREEN_L      0x0a
#define FG_CYAN_L       0x0b
#define FG_RED_L        0x0c
#define FG_MAGENTA_L    0x0d
#define FG_BROWN_L      0x0e
#define FG_WHITE        0x0f

/* Background highlighting */
#define BG_BLUE         0x10
#define BG_GREEN        0x20
#define BG_CYAN         0x30
#define BG_RED          0x40
#define BG_MAGENTA      0x50
#define BG_BROWN        0x60
#define BG_GREY_L       0x70
#define BG_GREY         0x80
#define BG_BLUE_L       0x90
#define BG_GREEN_L      0xa0
#define BG_CYAN_L       0xb0
#define BG_RED_L        0xc0
#define BG_MAGENTA_L    0xd0
#define BG_BROWN_L      0xe0
#define BG_WHITE        0xf0

#ifdef __file
    /* Macro wrapper to avoid a bunch of ifdef __file checks */
    #define __console_write(message, length) { \
        console_write(message, length, FG_GREY_L); \
    }
#endif

extern void console_clear(void);
extern void console_set_background(uint8_t);
extern size_t console_write(char*, size_t, uint8_t);

#endif
