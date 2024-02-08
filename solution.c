#include "drivers/uart.h"
#include <stdarg.h>

void kprintf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    ...
    // fetch next argument
    unsigned arg = va_arg(ap, unsigned);
    ...
    va_end(ap);
}
