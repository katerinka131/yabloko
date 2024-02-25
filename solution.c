#include "drivers/vga.h"
#include "drivers/port.h"

void vga_set_cursor(unsigned offset) {
    unsigned char low = offset & 0xFF;
    unsigned char high = (offset >> 8) & 0xFF;

    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, high);
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, low);
}

void vga_putc(char c) {
    unsigned offset = vga_get_cursor();
    if (c != '\n') {
        vga_set_char(offset, c);
        offset ++;
    }
    if (c == '\n') {
        offset += COLS - offset % COLS;
    }

    if (offset >= (COLS * ROWS)) {
        for (unsigned int i = 0; i < (ROWS - 1); i++)
            for (unsigned int j = 0; j < COLS; j++)
                video_memory[(i * COLS + j) * 2] = video_memory[((i + 1) * COLS + j) * 2];
        for (unsigned int j = 0; j < COLS; j++)
            video_memory[((ROWS - 1) * COLS + j) * 2] = ' ';

        offset = offset - COLS;
    }    
    vga_set_cursor(offset);
}
