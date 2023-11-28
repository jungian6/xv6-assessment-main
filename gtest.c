#include "types.h"
#include "user.h"  

int main(int argc, char *argv[]) {
    setvideomode(0x13);


    // Test moveto and lineto
    moveto(0, 50, 50);     // Move to position (50, 50)
    lineto(0, 100, 100);   // Draw line from (50, 50) to (100, 100)

    getch();
    setvideomode(0x03);
    exit();
}
