#include "../../include/common.h"
#include "../../include/atedot.h"

int plot_ax_ticks_numbers(Canvas *surf, double x_min, double x_max, double y_min, double y_max,
                           int x0, int y0) {

    int cell_w = surf->cell_w;
    int cell_h = surf->cell_h;

    // X-axis ticks (horizontal, every 5 braille cells)
    if (y0 >= 0) {
        int step_cells = 12;
        int step_px = step_cells * 2;
        for (int px = 0; px < surf->px_w; px += step_px) {
            double val = x_min + (x_max - x_min) * px / (surf->px_w - 1);
            char buf[16];
            snprintf(buf, sizeof(buf), "%.0f", val);

            int cy = y0 / 4;
            int cx = px / 2;
            for (size_t i = 0; i < strlen(buf); i++) {
                if ((size_t)(cx + i) < (size_t)cell_w)
                    surf->cells[cy * cell_w + cx + i] = buf[i];
            }
        }
    }

    // Y-axis ticks (vertical, every 2 braille cells)
    if (x0 >= 0) {
        int step_cells = 6;
        int step_px = step_cells * 4;
        for (int py = 0; py < surf->px_h; py += step_px) {
            double val = y_max - (y_max - y_min) * py / (surf->px_h - 1);
            char buf[16];
            snprintf(buf, sizeof(buf), "%.0f", val);

            int cy = py / 4;
            int cx = x0 / 2;
            for (size_t i = 0; i < strlen(buf); i++) {
                if ((size_t)(cy + i) < (size_t)cell_h)
                    surf->cells[(cy + i) * cell_w + cx] = buf[i];
            }
        }
    }
    return 0;
}
