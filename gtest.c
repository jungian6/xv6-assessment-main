#include "types.h"
#include "user.h"
#include "rect.h" // Include this if struct rect is in a separate header

int main(int argc, char* argv[]) {
    setvideomode(0x13);

    int hdc = beginpaint(0);
    setpencolour(16, 0, 63, 0);
    for (int i = 20; i <= 160; i+=20)
    {
        selectpen(hdc, 16);
        moveto(hdc, i, i);
        lineto(hdc, i, i+20);
        lineto(hdc, i+20, i+20);
        lineto(hdc, i+20, i);
        lineto(hdc, i, i);
        
    }

    hdc = beginpaint(0);
    setpencolour(17, 63, 0, 0);
    for (int i = 20; i <= 160; i+=20)
    {
        selectpen(hdc, 17);
        moveto(hdc, i, i);
        lineto(hdc, i, i+20);
        lineto(hdc, i+20, i+20);
        lineto(hdc, i+20, i);
        lineto(hdc, i, i);
        
    }
    endpaint(hdc);
    getch();

    setvideomode(0x03);
    exit();

    
}
