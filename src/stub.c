#include "kernel.h"



extern unsigned int width, height, pitch;
extern unsigned char *lfb;
int kprintf_x = 0, kprintf_y = 0;
/**
 * Display string using a bitmap font without the SSFN library
 */
void printString(int x, int y, char *s) {
    unsigned char *ptr, *chr, *frg;
    unsigned int c;
    uintptr_t o, p;
    int i, j, k, l, m, n;
    while(*s) {
        c = 0; s += mbtowc((wchar_t*)&c, (const char*)s, 4);
        if(c == '\r') { x = 0; continue; } else
        if(c == '\n') { x = 0; y += font->height; continue; }
        for(ptr = (unsigned char*)font + font->characters_offs, chr = 0, i = 0; i < 0x110000; i++) {
            if(ptr[0] == 0xFF) { i += 65535; ptr++; }
            else if((ptr[0] & 0xC0) == 0xC0) { j = (((ptr[0] & 0x3F) << 8) | ptr[1]); i += j; ptr += 2; }
            else if((ptr[0] & 0xC0) == 0x80) { j = (ptr[0] & 0x3F); i += j; ptr++; }
            else { if((unsigned int)i == c) { chr = ptr; break; } ptr += 6 + ptr[1] * (ptr[0] & 0x40 ? 6 : 5); }
        }
        if(!chr) continue;
        ptr = chr + 6; o = (uintptr_t)lfb + y * pitch + x * 4;
        for(i = n = 0; i < chr[1]; i++, ptr += chr[0] & 0x40 ? 6 : 5) {
            if(ptr[0] == 255 && ptr[1] == 255) continue;
            frg = (unsigned char*)font + (chr[0] & 0x40 ? ((ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]) :
                ((ptr[4] << 16) | (ptr[3] << 8) | ptr[2]));
            if((frg[0] & 0xE0) != 0x80) continue;
            o += (int)(ptr[1] - n) * pitch; n = ptr[1];
            k = ((frg[0] & 0x1F) + 1) << 3; j = frg[1] + 1; frg += 2;
            for(m = 1; j; j--, n++, o += pitch)
                for(p = o, l = 0; l < k; l++, p += 4, m <<= 1) {
                    if(m > 0x80) { frg++; m = 1; }
                    if(*frg & m) *((unsigned int*)p) = 0xFFFFFF;
                }
        }
        x += chr[4]+1; y += chr[5];
    }
}


void kprintf(const char *format_string, ...) {
    va_list args;

    // Ищем первый аргумент
    va_start(args, format_string);

    // Обработка и парсинг строки форматов
    while (*format_string != '\0') {
        if (*format_string == '%') {
            format_string++;
            if (*format_string == 'x') {
                //com1_log_printhex(va_arg(args, unsigned long long));
            } else if (*format_string == '8') {
                //com1_log_printdec((unsigned char)va_arg(args, char*)[0]);
            } else if (*format_string == 'd') {
                //com1_log_printdec(va_arg(args, int));
            } else if (*format_string == 'l') {
                //com1_log_printdec(va_arg(args, long));
            } else if (*format_string == 'f') {
                //com1_log_printfloat(va_arg(args, double), 7);
            } else if (*format_string == 'u') {
                //com1_log_printudec(va_arg(args, unsigned int));
            } else if (*format_string == 's') {
                printString(kprintf_x, kprintf_y, va_arg(args, char*)); 
            } else if (*format_string == 'c') {
                char temp_str[2];
                temp_str[0] = (char)va_arg(args, int);
                temp_str[1] = 0;
                printString(kprintf_x, kprintf_y, temp_str);  
                kprintf_x += 10;
            }
        } else {
            char temp_str[2];
            temp_str[0] = *format_string;
            temp_str[1] = 0;
            printString(kprintf_x++, kprintf_y, temp_str);
            kprintf_x += 10;
        }
        format_string++;
    }
    
    // Освобождаем память
    va_end(args);
}

