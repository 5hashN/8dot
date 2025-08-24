#include "../../include/common.h"
#include "../../include/atedot.h"

int plot_from_csv(Canvas *surf, const char *filename, int col_x, int col_y, uint32_t color) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        return -1;
    }

    char line[512];
    double x_min = 1e308, x_max = -1e308;
    double y_min = 1e308, y_max = -1e308;

    // find minmax for scaling
    int n_points = 0;
    while (fgets(line, sizeof(line), f)) {
        char *token;
        int idx = 0;
        double x = 0, y = 0;
        token = strtok(line, ",");
        while (token) {
            if (idx == col_x) x = atof(token);
            if (idx == col_y) y = atof(token);
            token = strtok(NULL, ",");
            idx++;
        }
        if (idx <= col_x || idx <= col_y) continue; // skip invalid line

        if (x < x_min) x_min = x;
        if (x > x_max) x_max = x;
        if (y < y_min) y_min = y;
        if (y > y_max) y_max = y;

        n_points++;
    }

    if (n_points == 0) {
        fclose(f);
        return -1;
    }

    // Determine axis positions in pixel coordinates
    int y0 = -1; // x axis
    if (y_min <= 0 && y_max >= 0) {
        y0 = (int)((y_max - 0) / (y_max - y_min) * (surf->px_h - 1));
    }

    int x0 = -1; // y axis
    if (x_min <= 0 && x_max >= 0) {
        x0 = (int)((0 - x_min) / (x_max - x_min) * (surf->px_w - 1));
    }

    rewind(f);

    // plot points
    while (fgets(line, sizeof(line), f)) {
        char *token;
        int idx = 0;
        double x = 0, y = 0;
        token = strtok(line, ",");
        while (token) {
            if (idx == col_x) x = atof(token);
            if (idx == col_y) y = atof(token);
            token = strtok(NULL, ",");
            idx++;
        }
        if (idx <= col_x || idx <= col_y) continue;

        int px = (int)((x - x_min) / (x_max - x_min) * (surf->px_w - 1));
        int py = (int)((y_max - y) / (y_max - y_min) * (surf->px_h - 1)); // flip y

        plot_set(surf, px, py, color);
    }

    // draw axes
    if (y0 >= 0) plot_line(surf, 0, y0, surf->px_w - 1, y0, 0x000000);
    if (x0 >= 0) plot_line(surf, x0, 0, x0, surf->px_h - 1, 0x000000);

    // axis ticks
    // plot_ax_ticks_numbers(surf, x_min, x_max, y_min, y_max, x0, y0);

    fclose(f);
    return 0;
}
