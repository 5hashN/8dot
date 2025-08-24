#include "../include/common.h"
#include "../include/atedot.h"

void repl(Canvas *surf) {
    char line[256];

    printf("plot> ");
    while (fgets(line, sizeof(line), stdin)) {
        // remove trailing newline
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0) break;
        if (strcmp(line, "quit") == 0) break;

        if (strcmp(line, "clear") == 0) plot_clear(surf);

        else if (strncmp(line, "size ", 5) == 0) {
            int w, h;
            if (sscanf(line + 5, "%d %d", &w, &h) == 2) {
                plot_resize(surf, w, h);
                printf("Resized plot to %dx%d\n", w, h);
            } else {
                printf("Usage: size <width> <height>\n");
            }
        }
        else if (strncmp(line, "plot ", 5) == 0) {
            plot_clear(surf);

            if (strstr(line, "sin") || strstr(line, "cos")) {
                int is_sin = strstr(line, "sin") != NULL;
                // int is_cos = strstr(line, "cos") != NULL;

                for (int x = 0; x < surf->px_w; ++x) {
                    double t = (double)x / surf->px_w * 4 * M_PI; // 2 periods
                    int y = surf->px_h/2 - (int)((is_sin ? sin(t) : cos(t)) * (surf->px_h * 0.4));
                    plot_set(surf, x, y, 0x00FF00); // green
                }
            } else {
                char filename[128];
                int xcol, ycol;
                if (sscanf(line + 5, "%127[^ ] %d %d", filename, &xcol, &ycol) == 3) {
                    if (plot_from_csv(surf, filename, xcol, ycol, 0x00FFFF) != 0) {
                        printf("Failed to plot CSV %s\n", filename);
                    }
                } else {
                    printf("Unknown function or usage: sin, cos, or plot <file> <xcol> <ycol>\n");
                }
            }
            plot_to_stdout_color(surf);
        } else {
            printf("Unknown command.\n");
        }
        printf("plot> ");
    }
}
