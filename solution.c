#include "drivers/uart.h"
#include <stdarg.h>

void print_int(unsigned int value, int base, void (*print)(char)) {
    char *t = "0123456789abcdef";
    char buffer[32]; 
    int i = 0;
    if (value == 0) {
        print('0');
        return;
    }
    while (value > 0) {
        buffer[i++] = t[value % base];
        value = value / base;
    }
    while (i > 0) {
        print(buffer[--i]);
    }
}

void kprintf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    for (; *fmt; ++fmt) {
        if (*fmt != '%') {
            uartputc(*fmt);
        }
        if (*fmt == '%') {
            if (*(++fmt) == 'x') {
                print_int(va_arg(ap, unsigned int), 16, uartputc);
                continue;
            }
            print_int(va_arg(ap, unsigned int), 10, uartputc);
            continue;
        }
    va_end(ap);
    }
}

