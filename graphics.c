#include "types.h"
#include "defs.h"
#include "memlayout.h"
#include "stdbool.h"
#include "deviceContext.h"
#include "x86.h"


#define VIDEO_MEMORY 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define WHITE 15
#define BLACK 0
#define MAX_DC 10  // Maximum number of device contexts

struct device_context dc_pool[MAX_DC];
bool dc_in_use[MAX_DC] = {false}; // Indicates whether each DC is in use

static uchar *phys_to_virt(uint pa)
{
    return (uchar *)(pa + KERNBASE);
}


static int abs(int n)
{
    return (n < 0) ? -n : n;
}

void clear320x200x256()
{

    unsigned char *video_memory = phys_to_virt(VIDEO_MEMORY);

    int total_pixels = SCREEN_WIDTH * SCREEN_HEIGHT;

    for (int i = 0; i < total_pixels; i++)
    {
        video_memory[i] = BLACK;
    }
}

int sys_setpixel(void) {
    int hdc, x, y;

    if (argint(0, &hdc) < 0)
        return -1; // Error in retrieving hdc

    if (argint(1, &x) < 0)
        return -1; // Error in retrieving x

    if (argint(2, &y) < 0)
        return -1; // Error in retrieving y

    // Clip the coordinates to screen boundaries
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return -1;

    // Set the pixel
    unsigned char *video_memory = phys_to_virt(VIDEO_MEMORY);
    unsigned int offset = y * SCREEN_WIDTH + x;
    video_memory[offset] = 15;

    return 0;
}


int sys_moveto(void)
{
    int hdc, x, y;

    if (argint(0, &hdc) < 0)
        return -1; // Error in retrieving hdc

    if (argint(1, &x) < 0)
        return -1; // Error in retrieving x

    if (argint(2, &y) < 0)
        return -1; // Error in retrieving y


    // Clip the coordinates to screen boundaries
    if (x < 0) x = 0;
    if (x >= SCREEN_WIDTH) x = SCREEN_WIDTH - 1;
    if (y < 0) y = 0;
    if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;


    // Update the current graphics position
    dc_pool[hdc].current_x = x;
    dc_pool[hdc].current_y = y;
    

    return 0; // Success
}

int sys_lineto(void)
{
    int hdc, x1, y1;

    if (argint(0, &hdc) < 0)
        return -1; // Error in retrieving hdc

    if (argint(1, &x1) < 0)
        return -1; // Error in retrieving x

    if (argint(2, &y1) < 0)
        return -1; // Error in retrieving y

    // Apply clipping to destination coordinates
    // Clip the coordinates to screen boundaries
    if (x1 < 0) x1 = 0;
    if (x1 >= SCREEN_WIDTH) x1 = SCREEN_WIDTH - 1;
    if (y1 < 0) y1 = 0;
    if (y1 >= SCREEN_HEIGHT) y1 = SCREEN_HEIGHT - 1;


    int x0 = dc_pool[hdc].current_x, y0 = dc_pool[hdc].current_y; // Starting point is current position
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; // error value e_xy

    while (true)
    {
        // Draw the pixel at (x0, y0)
        if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT)
        {
            unsigned char *video_memory = phys_to_virt(VIDEO_MEMORY);
            video_memory[y0 * SCREEN_WIDTH + x0] = dc_pool[hdc].current_pen;
        }
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }

    // Update the current graphics position
    dc_pool[hdc].current_x = x1;
    dc_pool[hdc].current_y = y1;

    return 0; // Success
}


int sys_beginpaint(void) {
    int hwnd;

    if (argint(0, &hwnd) < 0)
        return -1;

         // Extract the hwnd argument
    for (int i = 0; i < MAX_DC; i++) {
        if (!dc_in_use[i]) {
            dc_in_use[i] = true;
            dc_pool[i].current_x = 0;
            dc_pool[i].current_y = 0;
            dc_pool[i].current_pen = WHITE;
            // Initialize other fields as necessary
            return i;
        }
    }
    return -1; // No available device context
}

int sys_endpaint(void) {
    int hdc;

    if (argint(0, &hdc) < 0) // Extract the hdc argument
        return -1; 

    if (hdc >= 0 && hdc < MAX_DC && dc_in_use[hdc]) {
        // release the handle to the device context
        dc_pool[hdc].current_x = 0;
        dc_pool[hdc].current_y = 0;
        dc_pool[hdc].current_pen = WHITE;
        dc_in_use[hdc] = false;        
        return 0; // Success
    }
    return -1; // Invalid device context handle
}


int sys_setpencolour(void)
{
    int index, r, g, b;

    // Extract arguments
    if (argint(0, &index) < 0)
        return -1;

    if (argint(1, &r) < 0)
        return -1;

    if (argint(2, &g) < 0)
        return -1;

    if (argint(3, &b) < 0)
        return -1;

    // Validate the index and clip RGB values
    if (index < 16 || index > 255)
        return -1;
    // Clip RGB values
    if (r < 0) r = 0;
    if (r > 63) r = 63;
    if (g < 0) g = 0;
    if (g > 63) g = 63;
    if (b < 0) b = 0;
    if (b > 63) b = 63;

    // Set the color in the palette
    outb(0x3C8, index);
    outb(0x3C9, r);
    outb(0x3C9, g);
    outb(0x3C9, b);

    return 0;
}

int sys_selectpen(void)
{
    int hdc, index;

    if (argint(0, &hdc) < 0)
        return -1; 
    if (argint(1, &index) < 0)
        return -1;

    // Validate the index
    if (index < 16 || index > 255)
        return -1;

    dc_pool[hdc].current_pen = index;

    return 0;
}

int sys_fillrect(void) {
    int hdc;
    struct rect *r;

    // Extract arguments
    if (argint(0, &hdc) < 0)
        return -1;

    if (argptr(1, (void *)&r, sizeof(r)) < 0)
        return -1;

        // Clip the rectangle coordinates to the screen boundaries
    if (r->left < 0) r->left = 0;
    if (r->right >= SCREEN_WIDTH) r->right = SCREEN_WIDTH - 1;
    if (r->top < 0) r->top = 0;
    if (r->bottom >= SCREEN_HEIGHT) r->bottom = SCREEN_HEIGHT - 1;

    // Validate the rectangle dimensions
    if (r->left > r->right || r->top > r->bottom)
        return -1; // Invalid rectangle

    uchar* videomemory = phys_to_virt(VIDEO_MEMORY);

    // Fill the rectangle
    for (int y = r->top; y <= r->bottom; y++) {
        for (int x = r->left; x <= r->right; x++) {
            videomemory[y * SCREEN_WIDTH + x] = dc_pool[hdc].current_pen;
        }
    }

    return 0; // Success
}
