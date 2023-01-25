#pragma once

#include <uefi.h>

/* Scalable Screen Font (https://gitlab.com/bztsrc/scalable-font2) */
typedef struct {
    unsigned char  magic[4];
    unsigned int   size;
    unsigned char  type;
    unsigned char  features;
    unsigned char  width;
    unsigned char  height;
    unsigned char  baseline;
    unsigned char  underline;
    unsigned short fragments_offs;
    unsigned int   characters_offs;
    unsigned int   ligature_offs;
    unsigned int   kerning_offs;
    unsigned int   cmap_offs;
} __attribute__((packed)) ssfn_font_t;
/* framebuffer properties */
unsigned int width, height, pitch;
unsigned char *lfb;
/* font to be used */
ssfn_font_t *font;

void kprintf(const char *format_string, ...);
void printString(int x, int y, char *s);

