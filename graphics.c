#include "types.h"
#include "defs.h"
#define VIDEO_MEMORY 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define WHITE 0x0F
//#include <string.h> // Include the header for memset

void clear320x200x256() {
    unsigned char *video_memory = (unsigned char *) VIDEO_MEMORY;

    // Set the entire screen to black
    memset(video_memory, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT);
}


int setpixel(int hdc, int x, int y) {
    // The hdc parameter is not used in this stage
    (void) hdc;

    // Check if the coordinates are within the screen boundaries
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return -1; // Return -1 if the coordinates are out of bounds
    }

    // Calculate the address in the video memory
    unsigned char *video_memory = (unsigned char *) VIDEO_MEMORY;
    unsigned int offset = y * SCREEN_WIDTH + x;

    // Set the pixel color to white
    video_memory[offset] = WHITE;

    return 0; // Return 0 on success
}
