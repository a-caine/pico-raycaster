#include "raycaster.hpp"

#include "room.hpp"

#include "pico_display.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;

static ST7789 st7789(PicoDisplay::WIDTH, PicoDisplay::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
static PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

static uint16_t w = st7789.width;
static uint16_t h = st7789.height;


/** Reset the state of all pixels. */
void clear() {
    graphics.set_pen(0,0,0);
    graphics.clear();
}

/** Render the pixel state inside the graphics object to the screen. */
void draw() {
    st7789.update(&graphics);
}

/** Set up the camera with some default values. */
void setup_camera() {
    // Set up the default camera variables.
    // This is largely down to how you want to initially configure your raycaster
}

/** Cast all of the rays. */
void raycast() {
    // Needs to cast out all of the rays from the camera
}

/** Cast a ray out of the camera and render it to the screen.*/
void cast_ray(uint16_t x) {

    // This is the main bulk of the project, so I have provided some explanation of the steps needed below

    // Calculate the position and direction vectors of the ray

    // Find the length of the ray from the current position to the next x or y-side

    // Find the length of the ray from one x or y-side to the next x or y-side

    // Calculate the step and initial distance to the x or y side

    // Perform DDA - https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)

    // Calculate the perpendicular distance to the wall

    // Draw the line to the screen
}


/** Render a vertical line to the screen. */
void draw_vertical_line(int16_t x, int16_t start, int16_t end, uint8_t col, uint8_t brightness) {

    // Render one of the rays results to the screen

    // You may want to render the ground and ceiling, or leave them empty
}

/** Move the camera given the delta time. */
void move(bool backward, double d_time) {
    // This method is only called when the player wants to move.
}

/** Rotate the camera given the delta time. */
void rotate(bool clockwise, double d_time) {

    // Here clockwise represents turning to the right
}

/** Render the frames per second. */
void draw_fps(uint8_t fps) {
    graphics.set_pen(0, 0, 0);

    std::string fps_txt = "FPS: ";
    fps_txt += std::to_string(fps);

    graphics.text(fps_txt, Point(10, 10), 500, 2.5, 0.0, 1);
}


