#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "stdbool.h"
#define VIDEO_MEMORY 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define WHITE 0x0F
#define BLACK 0x00
//#include <string.h> // Include the header for memset

static 	int current_x = 0;
static	int current_y = 0;

static uchar* phys_to_virt(uint pa) {
    return (uchar*)(pa + KERNBASE);
}

static int abs(int n) {
    return (n < 0) ? -n : n;
}


void clear320x200x256() {
    
    unsigned char *video_memory = phys_to_virt(VIDEO_MEMORY);

    int total_pixels = SCREEN_WIDTH * SCREEN_HEIGHT;

    for (int i = 0; i < total_pixels; i++) {
        video_memory[i] = BLACK;
    }
}


int sys_setpixel(void) {
    // The hdc parameter is not used in this stage
    int hdc;

    int x;
    int y;

    argint(0, &hdc);

    argint(0, &x);
    argint(1, &y);

    // Check if the coordinates are within the screen boundaries
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return -1; // Return -1 if the coordinates are out of bounds
    }



    // Calculate the address in the video memory
    unsigned char *video_memory = phys_to_virt(VIDEO_MEMORY);
    unsigned int offset = y * SCREEN_WIDTH + x;

    // Set the pixel color to white
    video_memory[offset] = WHITE;

    return 0; // Return 0 on success
}

int sys_moveto(void) {

    int hdc, x, y;


    argint(0, &hdc);
    argint(1, &x);  // Changed index to 1 for x
    argint(2, &y);  // Changed index to 2 for y


    // Clip the coordinates to screen boundaries
    if (x < 0) x = 0;
    if (x >= SCREEN_WIDTH) x = SCREEN_WIDTH - 1;
    if (y < 0) y = 0;
    if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;

    // Update the current graphics position
    current_x = x;
    current_y = y;

    return 0;  // Success
}

int sys_lineto(void) {
    int hdc, x1, y1;

    argint(0, &hdc);
    argint(1, &x1);  // Get x1 coordinate
    argint(2, &y1);  // Get y1 coordinate

    int x0 = current_x, y0 = current_y; // Starting point is current position
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
    int err = dx + dy, e2; // error value e_xy

    while (true) {
        // Draw the pixel at (x0, y0)
        if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT) {
            unsigned char *video_memory = phys_to_virt(VIDEO_MEMORY);
            video_memory[y0 * SCREEN_WIDTH + x0] = WHITE;
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }

    // Update the current graphics position
    current_x = x1;
    current_y = y1;

    return 0; // Success
}




