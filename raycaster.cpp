#include "raycaster.hpp"

#include "room.hpp"

#include "pico_display.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;

ST7789 st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

static uint16_t w = st7789.width;
static uint16_t h = st7789.height;

/** Set up the camera with some default values. */
void setup_camera() {
    camera.pos_x = START_X;
    camera.pos_y = START_Y;
    camera.dir_x = -1;
    camera.dir_y = 0;
}

void clear() {
    graphics.set_pen(0,0,0);
    graphics.clear();
}

void draw() {
    st7789.update(&graphics);
}

/** Render a vertical line to the screen. */
void draw_vertical_line(int16_t x, int16_t start, int16_t end, uint8_t col) {
    if (end < start) {
        // Swap the positions
        start += end;
        end = start - end;
        start -= end;
    }
    // Ignore any out of bounds lines
    if (end < 0 || start >= h || x < 0 || x >= w) return;

    // Clip the start and end position to the screen
    if (start < 0 ) start = 0; 
    if (end >= h) end = h - 1;

    uint8_t r, g, b;
    r = 0;
    g = 0;
    b = 0;

    switch (col) {
        case 1:
            r = 255;
            break;
        case 2:
            g = 255;
            break;
        case 3:
            b = 255;
            break;
        case 4:
            r = 128;
            g = 128;
        case 5:
            g = 255;
            b = 128;
    }

    graphics.set_pen(r, g, b);
    for (uint16_t i = start; i <= end; i++) {
        graphics.set_pixel(Point(x, i));
    }
}


