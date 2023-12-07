#include "types.h"
#include "user.h"

int main(int argc, char* argv[])
{
    setvideomode(0x13);
    setpixel(0, 100, 100);
    setpixel(0, 101, 100);
    setpixel(0, 102, 100);
    setpixel(0, 103, 100);
    setpixel(0, 104, 100);
    setpixel(0, 105, 100);
    setpixel(0, 100, 101);
    getch();
    setvideomode(0x03);
    exit();
}

