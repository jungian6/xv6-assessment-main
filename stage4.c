#include "types.h"
#include "user.h"

int main(int argc, char* argv[])
{
    setvideomode(0x13);

    int pid = fork();

    if (pid == -1) {
        // Handle error: fork failed
        exit();
    }

    int hdc;
    int hdc2;
    
    if (pid > 0) {
        // Child
        hdc = beginpaint(0);
        setpencolour(16, 0, 0, 63); // Blue
        for (int i = 20; i <= 160; i += 20) {
            selectpen(hdc, 16);
            moveto(hdc, i, i + 20);
            lineto(hdc, i, i + 40);
            lineto(hdc, i + 20, i + 40);
            lineto(hdc, i + 20, i + 20);
            lineto(hdc, i, i + 20);
        }
        endpaint(hdc);
        wait(); // Wait for parent process
        getch();
        setvideomode(0x03);
        exit();
    } else if (pid == 0){
        // Parent
        hdc2 = beginpaint(0);
        setpencolour(17, 0, 63, 0); // Green
        for (int i = 20; i <= 160; i += 20) {
            selectpen(hdc2, 17);
            moveto(hdc2, i, i);
            lineto(hdc2, i, i + 20);
            lineto(hdc2, i + 20, i + 20);
            lineto(hdc2, i + 20, i);
            lineto(hdc2, i, i);
        }
        endpaint(hdc2);
        exit();
    }

    return 0;
}
