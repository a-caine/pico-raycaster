#include "pico_display.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "button.hpp"
#include "pico/stdlib.h"
#include <stdint.h>

#include "raycaster.hpp"

using namespace pimoroni;

Button forward_button(PicoDisplay::X);
Button backward_button(PicoDisplay::Y);
Button rleft_button(PicoDisplay::B);
Button rright_button(PicoDisplay::A);

double old_time;

/** Simple function to get the system time in us as a double. */
double clock() {
    return double(time_us_64());
}

int main() {

    stdio_init_all();

    setup_camera();

    // Timestamp the current time
    
    old_time = clock();

    while(true) {

        // Figure out the delta time (time between frames)
        double curr_time = clock();
        double d_time = (curr_time - old_time) / 1e6;
        old_time = curr_time;
    
        // Clear the screen
        clear();
        // Render the scene
        raycast();
        // Render the frames per second
        draw_fps(uint8_t(1 / d_time));
        // Draw the scene to the screen
        draw();

        // Update the cameras position accordingly
        if (forward_button.raw()) {
            move(false, d_time);
        } else if (backward_button.raw()) {
            move(true, d_time);
        }

        // Rotate the camera if pressing the rotate buttons
        if (rleft_button.raw()) {
            rotate(true, d_time);
        } else if (rright_button.raw()) {
            rotate(false, d_time);
        }
    }
}