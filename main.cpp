#include "pico_display.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "button.hpp"
#include "pico/stdlib.h"
#include <stdint.h>

#include "raycaster.hpp"

using namespace pimoroni;

Button reset_button(PicoDisplay::X);



int main() {

    stdio_init_all();

    

    // Give the chip some time to set up
    sleep_ms(500);

    while(true) {


    
        clear();
        for (int x = 0; x < 100; x++) {
            draw_vertical_line(x, x - 25, x, 3);
        }
        draw();

    }
}