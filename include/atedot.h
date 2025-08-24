#pragma once
#include <stdint.h>

typedef struct {
    int px_w, px_h;         // pixel-space size
    int cell_w, cell_h;     // braille character grid
    uint8_t *cells;         // bits map to braille dots
    uint32_t *colors;       // color per pixel
} Canvas;

Canvas plot_make(int px_w, int px_h); // (col, row)
void plot_resize(Canvas *surf, int new_w, int new_h);
void plot_free(Canvas *surf);
void plot_clear(Canvas *surf);

void plot_set(Canvas *surf, int x, int y, uint32_t color); // single pixel (x, y)
void plot_unset(Canvas *surf, int x, int y);

int plot_line(Canvas *surf, int x0, int y0, int x1, int y1, uint32_t color); // bresenham line
int plot_ax_ticks_numbers(Canvas *surf, double x_min, double x_max, double y_min, double y_max,
                           int x0, int y0);
int plot_from_csv(Canvas *surf, const char *path, int xcol, int ycol, uint32_t color);

void plot_to_stdout(const Canvas *surf);
void plot_to_stdout_color(const Canvas *surf);
