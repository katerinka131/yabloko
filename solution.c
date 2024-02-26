#include "drivers/vga.h"

void show_vga_symbol_table(void) {
    vga_clear_screen();
    int size = 0;
    char x;
    while (size < 16) {
        if (size < 10) {
            x = size + '0';
        } 
        if ( size >= 10) {
            x = 'a' - 10 + size;
        }
        vga_set_char(2 * size + 2, x);
        size++;
    }

    size = 0;
    while (size < 16) {
        if (size < 10) {
            vga_set_char(COLS * (size + 1), '0' + size);
        }
        if (size >= 10) {
            vga_set_char(COLS * (size + 1), 'a' + size - 10);
        }
        for (int i = 0; i < 16; i++) {
            vga_set_char(2 * (i + 1) +  COLS * ( size + 1), 16 * size + i);
        }
        size++;
    }
    
}
