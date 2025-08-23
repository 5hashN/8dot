#include "../include/common.h"
#include "../include/atedot.h"

int main(void) {
    setlocale(LC_ALL, ""); // for unicode output

    int px_w = 160;  // ~ x1/2 braille columns
    int px_h = 120;  // ~ x1/4 braille rows
    Canvas plot = plot_make(px_w, px_h);
    plot_clear(&plot);

    // axes
    plot_line(&plot,      0, px_h/2, px_w-1, px_h/2, 0x000000); // white
    plot_line(&plot, px_w/2,      0, px_w/2, px_h-1, 0x000000);

    // box
    plot_line(&plot,      8,      8, px_w-9,      8, 0x000000);
    plot_line(&plot, px_w-9,      8, px_w-9, px_h-9, 0x000000);
    plot_line(&plot, px_w-9, px_h-9,      8, px_h-9, 0x000000);
    plot_line(&plot,      8, px_h-9,      8,      8, 0x000000);

    // color lines
    plot_line(&plot, 0, 0, px_w-1, px_h-1, 0xFF0000);   // red
    plot_line(&plot, 0, px_h-1, px_w-1, 0, 0x00FF00);   // green

    // sine wave
    for (int x = 0; x < px_w; ++x) {
        double t = (double)x / (double)px_w * 2.0 * M_PI * 2.0;
        int y = (int)(px_h/2 - sin(t) * (px_h*0.4));
        plot_set(&plot, x, y, 0x0000FF);    // blue
    }

    plot_to_stdout_color(&plot);
    plot_free(&plot);
    return 0;
}

