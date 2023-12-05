#include "types.h"
#include "user.h"
#include "rect.h"

#include "types.h"
#include "user.h"

int main(int argc, char* argv[])
{
    setvideomode(0x13);

    int hdc = beginpaint(0);
    setpixel(hdc, 100, 100);
    setpixel(hdc, 101, 100);
    setpixel(hdc, 102, 100);
    setpixel(hdc, 103, 100);
    setpixel(hdc, 104, 100);
    setpixel(hdc, 105, 100);

    setpixel(hdc, 100, 101);
    getch();
    setvideomode(0x03);
    exit();
}

