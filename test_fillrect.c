#include "types.h"
#include "user.h"
#include "deviceContext.h"

int main(int argc, char* argv[]) {
    setvideomode(0x13);

    int hdc = beginpaint(0);
    setpencolour(16, 30, 50, 60);
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