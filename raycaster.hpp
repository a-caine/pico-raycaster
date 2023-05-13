#ifndef _RAYCASTER_HPP
#define _RAYCASTER_HPP

#include "pico/stdlib.h"

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

void clear();
void draw();

/** Setup the camera for the raycaster. */
void setup_camera();


/** Render a vertical line to the screen. */
void draw_vertical_line(int16_t x, int16_t start, int16_t end, uint8_t col);




#endif