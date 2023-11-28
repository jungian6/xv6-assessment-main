#include "types.h"
#include "defs.h"
#include "memlayout.h"
#define VIDEO_MEMORY 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define WHITE 0x0F
#define BLACK 0x00
//#include <string.h> // Include the header for memset

static uchar* phys_to_virt(uint pa) {
    return (uchar*)(pa + KERNBASE);
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


