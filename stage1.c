#include "types.h"
#include "user.h"
#include "rect.h"

int main(int argc, char* argv[])
{
    int hdc = beginpaint(0);
    setpencolour(16, 99, 3, 48);
    selectpen(hdc, 16);

    setvideomode(0x13);
    moveto(hdc, 100, 50);
    lineto(hdc, 200, 50);
    lineto(hdc, 200, 150);
    lineto(hdc, 100, 150);
    lineto(hdc, 100, 50);
    getch();
    setvideomode(0x03);
    exit();
}
