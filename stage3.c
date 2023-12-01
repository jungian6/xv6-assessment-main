#include "types.h"
#include "user.h"
#include "rect.h"

int main(int argc, char* argv[]) {
    setvideomode(0x13);
    int pid = fork();

    if (pid == 0) {
        // Child process
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
    } else if (pid > 0) {
        // Parent process
        int hdc = beginpaint(0);
        setpencolour(17, 255, 0, 0);
        selectpen(hdc, 17);

        // draw a line
        moveto(hdc, 100, 50);
        lineto(hdc, 200, 150);
        endpaint(hdc);

        getch();
        setvideomode(0x03);

        wait(); // Wait for child process to finish
        exit();
    }

    return 0;
}
