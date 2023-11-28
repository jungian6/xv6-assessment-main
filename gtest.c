#include "types.h"
#include "user.h"  

int main(int argc, char *argv[]) {

    setvideomode(0x13);

    setpixel(100, 100, 15);
    setpixel(101, 100, 15);
    setpixel(102, 100, 15);
    getch();

    setvideomode(0x03);

    exit();
    
}

