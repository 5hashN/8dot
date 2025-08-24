#include "../include/common.h"

typedef struct {
    int px_w, px_h;         // pixel-space size
    int cell_w, cell_h;     // braille character grid
    uint8_t *cells;         // bits map to braille dots
    uint32_t *colors;       // color per pixel
} Canvas;

// map (col, row) in a 2x4 cell to braille bit index
static inline int braille_bit(int col, int row) {
    static const int left [4] = {0, 1, 2, 6}; // dots 1, 2, 3, 7
    static const int right[4] = {3, 4, 5, 7}; // dots 4, 5, 6, 8
    return col ? right[row] : left[row];
}

static inline uint32_t braille_cp(uint8_t mask) {
    return 0x2800u + (uint32_t)mask;
}

// encode one unicode codepoint to UTF-8 into out[4], return bytes written
static int utf8_encode(uint32_t cp, char out[4]) {
    if (cp < 0x80) {
        out[0] = (char)cp; return 1;
    } else if (cp < 0x800) {
        out[0] = 0xC0 | (cp >> 6);
        out[1] = 0x80 | (cp & 0x3F);
        return 2;
    } else if (cp < 0x10000) {
        out[0] = 0xE0 | (cp >> 12);
        out[1] = 0x80 | ((cp >> 6) & 0x3F);
        out[2] = 0x80 | (cp & 0x3F);
        return 3;
    } else {
        out[0] = 0xF0 | (cp >> 18);
        out[1] = 0x80 | ((cp >> 12) & 0x3F);
        out[2] = 0x80 | ((cp >> 6) & 0x3F);
        out[3] = 0x80 | (cp & 0x3F);
        return 4;
    }
}

Canvas plot_make(int px_w, int px_h) {
    Canvas surf;
    surf.px_w = px_w;
    surf.px_h = px_h;

    surf.cell_w = (px_w + 1) / 2;  // ceil(px_w / 2)
    surf.cell_h = (px_h + 3) / 4;  // ceil(px_h / 4)

    size_t n = (size_t)surf.cell_w * (size_t)surf.cell_h;

    surf.cells = (uint8_t*)calloc(n, 1);
    surf.colors = (uint32_t*)calloc((size_t)px_w * (size_t)px_h, sizeof(uint32_t));
    return surf;
}

void plot_resize(Canvas *surf, int new_w, int new_h) {
    free(surf->cells);
    free(surf->colors);

    surf->px_w = new_w;
    surf->px_h = new_h;
    surf->cell_w = (new_w + 1) / 2;
    surf->cell_h = (new_h + 3) / 4;

    surf->cells = (uint8_t*)calloc((size_t)(surf->cell_w * surf->cell_h), sizeof(uint8_t));
    surf->colors = (uint32_t*)calloc((size_t)(surf->px_w * surf->px_h), sizeof(uint32_t));
}

void plot_free(Canvas *surf) {
    free(surf->cells); surf->cells = NULL;
    free(surf->colors); surf->colors = NULL;
}

void plot_clear(Canvas *surf) {
    memset(surf->cells, 0, (size_t)surf->cell_w * (size_t)surf->cell_h);
}

// set a single pixel (x, y) in pixel space
void plot_set(Canvas *surf, int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x >= surf->px_w || y >= surf->px_h) return;
    int cx = x / 2; int cy = y / 4;
    int col = x % 2; int row = y % 4;
    int bit = braille_bit(col, row);

    surf->cells[cy * surf->cell_w + cx] |= (1u << bit);
    surf->colors[y * surf->px_w + x] = color;
}

// unset pixel
void plot_unset(Canvas *surf, int x, int y) {
    if (x < 0 || y < 0 || x >= surf->px_w || y >= surf->px_h) return;
    int cx = x / 2; int cy = y / 4;
    int col = x % 2; int  row = y % 4;
    int bit = braille_bit(col, row);

    surf->cells[cy * surf->cell_w + cx] &= ~(1u << bit);
    surf->colors[y * surf->px_w + x] = 0;
}

// dump to stdout with utf-8 braille and space for the rest
void plot_to_stdout(const Canvas *surf) {
    for (int y = 0; y < surf->cell_h; ++y) {
        for (int x = 0; x < surf->cell_w; ++x) {
            uint8_t mask = surf->cells[y * surf->cell_w + x];
            if (mask == 0) {
                putchar(' ');
            } else {
                uint32_t cp = braille_cp(mask);
                char buf[4];
                int n = utf8_encode(cp, buf);
                fwrite(buf, 1, (size_t)n, stdout);
            }
        }
        putchar('\n');
    }
}

void plot_to_stdout_color(const Canvas *surf) {
    for (int y = 0; y < surf->cell_h; ++y) {
        for (int x = 0; x < surf->cell_w; ++x) {
            uint8_t mask = surf->cells[y * surf->cell_w + x];
            if (mask == 0) {
                putchar(' '); continue;
            }

            // find a color in this cell
            uint32_t color = 0xFFFFFF; // default white
            for (int dy = 0; dy < 4; ++dy) {
                for (int dx = 0; dx < 2; ++dx) {
                    int px = x*2 + dx, py = y*4 + dy;
                    if (px < surf->px_w && py < surf->px_h) {
                        int bit = braille_bit(dx, dy);
                        if (mask & (1u << bit)) {
                            color = surf->colors[py * surf->px_w + px];
                            goto found_color;
                        }
                    }
                }
            }
        found_color:;

            uint32_t cp = braille_cp(mask);
            char buf[4];
            int n = utf8_encode(cp, buf);

            int r = (color >> 16) & 0xFF;
            int g = (color >> 8) & 0xFF;
            int bcol = color & 0xFF;

            printf("\x1b[38;2;%d;%d;%dm", r, g, bcol); // set fg color
            fwrite(buf, 1, (size_t)n, stdout);
            printf("\x1b[0m"); // reset
        }
        putchar('\n');
    }
}
