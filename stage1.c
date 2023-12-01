#include "types.h"
#include "user.h"
#include "rect.h"

int main(int argc, char* argv[])
{
    int hdc = beginpaint(0);
    int pid = fork();
    setvideomode(0x13);

    if (pid == 0)
    {
        setpencolour(16, 99, 3, 48);
        selectpen(hdc, 16);
        moveto(hdc, 100, 50);
        lineto(hdc, 200, 150);
        lineto(hdc, 300, 50);
        lineto(hdc, 400, 150);
        lineto(hdc, 500, 50);
        exit();
    } else if (pid > 0)
    {
        setpencolour(16, 99, 3, 48);
        selectpen(hdc, 16);
        moveto(hdc, 100, 50);
        lineto(hdc, 200, 150);
        
    }
    
    getch();
    setvideomode(0x03);
    exit();
}
