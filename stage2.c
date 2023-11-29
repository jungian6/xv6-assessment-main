#include "types.h"
#include "user.h"
#include "rect.h"

int main(int argc, char* argv[]) {
    setvideomode(0x13);

    int hdc = beginpaint(0);
    setpencolour(16, 0, 255, 0);
    selectpen(hdc, 16);

    struct rect r;

    r.top = 10;
    r.left = 10;
    r.bottom = 50;
    r.right = 50;

    fillrect(hdc, &r);
    
    endpaint(hdc);
    getch();

    setvideomode(0x03);
    exit();
}