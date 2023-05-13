#ifndef _RAYCASTER_HPP
#define _RAYCASTER_HPP

#include "pico/stdlib.h"

#define MOVE_SPEED 5
#define ROTATE_SPEED 3

static volatile struct {
    // Position vector
    double pos_x; // Position of the camera in the x direction
    double pos_y; // position of the camera in the y direction

    // Direction vector
    double dir_x; // angle of the camera in the x direction
    double dir_y; // angle of the camera in the y direction

    // Camera plane
    double plane_x;
    double plane_y;

    // Camera width (screen width)
    double camera_width;
} camera;

// Define the functions to actually render the raycasters

/** Reset the state of all pixels. */
void clear();
/** Render the pixel state inside the graphics object to the screen. */
void draw();

/** Setup the camera for the raycaster. */
void setup_camera();

/** Cast all of the rays. */
void raycast();

/** Cast a ray out of the camera and render it to the screen.*/
void cast_ray(uint16_t x);

/** Render a vertical line to the screen. */
void draw_vertical_line(int16_t x, int16_t start, int16_t end, uint8_t col, uint8_t brightness);

/** Move the camera given the delta time. */
void move(bool backwards, double d_time);

/** Rotate the camera given the delta time. */
void rotate(bool clockwise, double d_time);

/** Render the frames per second. */
void draw_fps(uint8_t fps);


#endif