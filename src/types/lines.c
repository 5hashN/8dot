#include "../../include/common.h"
#include "../../include/atedot.h"

// bresenham line generation in pixel space
int plot_line(Canvas *surf, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    for(;;) {
        canvas_pixel_set(surf, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
    return 0;
}
\

int plot_trig(Canvas *surf, const char *line, uint32_t color) {
    int is_sin = strstr(line, "sin") != NULL;
    int is_cos = strstr(line, "cos") != NULL;

    if (!is_sin && !is_cos) return -1;

    double a = 1.0, b = 0.0, n = 1.0;

    // parse "sin(ax+b)*n" from the line
    const char *expr = strchr(line, ' ');
    if (expr) expr = strchr(expr+1, ' '); // skip "plot " and "sin/cos"

    if (expr) {
        // expects form "a*x+b *n")
        sscanf(expr, "%lf*x%lf *%lf", &a, &b, &n);
    }

    for (int x = 0; x < surf->px_w; ++x) {
        double t = (double)x / surf->px_w * 2 * M_PI * 2; // 0..4π
        double yval = n * (is_sin ? sin(a * t + b) : cos(a * t + b));
        int y = surf->px_h/2 - (int)(yval * (surf->px_h * 0.4));
        canvas_pixel_set(surf, x, y, color);
    }

    return 0;
}
