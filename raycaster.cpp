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
    camera.pos_x = START_X;
    camera.pos_y = START_Y;
    camera.dir_x = -1;
    camera.dir_y = 0;
    camera.camera_width = st7789.width;
    camera.plane_x = 0;
    camera.plane_y = 0.66;
}

/** Cast all of the rays. */
void raycast() {
    for (uint16_t x = 0; x < w; x++) {
        cast_ray(x);
    }
}

/** Cast a ray out of the camera and render it to the screen.*/
void cast_ray(uint16_t x) {
    // Calculate the position and direction vectors of the ray

    // Converts the x position of the screen to the x position on the camera plane (from -1 to 1, with 0 being the center)
    double camera_x = 2 * x / double(w) - 1;

    // Calculate the direction of the ray using the camera planes position and the offset set above
    double ray_dir_x = camera.dir_x + camera.plane_x * camera_x;
    double ray_dir_y = camera.dir_y + camera.plane_y * camera_x;


    // Figure out which tile of the room we are in
    int16_t floor_x = int16_t(camera.pos_x);
    int16_t floor_y = int16_t(camera.pos_y);

    // Length of the ray from the current position to the next x or y-side
    double side_distance_x, side_distance_y;

    // Length of the ray from one x or y-side to the next x or y-side
    // Set value to infinity if div by zero
    double d_dist_x = (ray_dir_x == 0) ? infinity() : std::abs(1 / ray_dir_x);
    double d_dist_y = (ray_dir_y == 0) ? infinity() : std::abs(1 / ray_dir_y);

    // Which direction to step in the x or y direction (+/- 1)
    int8_t step_x;
    int8_t step_y;

    // Determine whether the ray hit a wall or not
    uint8_t hit = 0;
    // Determine whether the wall hit was north/south or east/west
    bool ns_side;


    // Firstly calculate the step and initial side distance
    if (ray_dir_x < 0.0) {
        step_x = -1;
        side_distance_x = (camera.pos_x - floor_x) * d_dist_x;
    } else {
        step_x = 1;
        side_distance_x = (floor_x + 1.0 - camera.pos_x) * d_dist_x;
    }

    if (ray_dir_y < 0) {
        step_y = -1;
        side_distance_y = (camera.pos_y - floor_y) * d_dist_y;
    } else {
        step_y = 1;
        side_distance_y = (floor_y + 1.0 - camera.pos_y) * d_dist_y;
    }


    // Perform DDA - https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
    while (!hit) {
        if (side_distance_x < side_distance_y) {
            // Step in the x direction
            side_distance_x += d_dist_x;
            floor_x += step_x;
            ns_side = false;
        } else {
            // Step in the y direction
            side_distance_y += d_dist_y;
            floor_y += step_y;
            ns_side = true;
        }

        // Check if a ray has hit a wall or not
        hit = room[floor_x][floor_y];
    }

    // Store the perpendicular distance to the wall.
    double p_wall_dist;


    // If we hit a wall, calculate the perpendicular distance to the wall
    if (ns_side)
        p_wall_dist = (side_distance_y - d_dist_y);
    else
        p_wall_dist = (side_distance_x - d_dist_x);

    // Calculate the height of the line to draw on the screen
    int16_t line_height = (uint16_t)(h / p_wall_dist);

    // Calculate the pixels to draw between
    int16_t draw_start = h / 2 + (-line_height / 2);
    if (draw_start < 0) draw_start = 0;
    int16_t draw_end = h / 2 + (line_height / 2);
    if (draw_end >= h) draw_end = h - 1;

    draw_vertical_line(x, draw_start, draw_end, hit, (ns_side) ? 1 : 2);
}


/** Render a vertical line to the screen. */
void draw_vertical_line(int16_t x, int16_t start, int16_t end, uint8_t col, uint8_t brightness) {
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
            r = 255 / brightness;
            break;
        case 2:
            g = 255 / brightness;
            break;
        case 3:
            b = 255 / brightness;
            break;
        case 4:
            r = 128 / brightness;
            g = 128 / brightness;
            break;
        case 5:
            g = 255 / brightness;
            b = 128 / brightness;
            break;
    }

    graphics.set_pen(r, g, b);
    for (uint16_t i = start; i <= end; i++) {
        graphics.set_pixel(Point(x, i));
    }
}

/** Move the camera by the specified amounts. */
void move(uint8_t dir, double speed) {
    switch (dir) {
        case 0: // Forward
            camera.pos_x += camera.dir_x * speed;
            camera.pos_y += camera.dir_y * speed;
            break;
    }
    
}


