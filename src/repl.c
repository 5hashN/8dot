#include <termios.h>
#include <unistd.h>
#include "../include/common.h"
#include "../include/atedot.h"

#define MAX_HISTORY 100
#define MAX_LINE 256

static struct termios orig_termios;

static void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

static void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO); // no canonical, no echo
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// read one line with editing & history
static int readline(char *out, size_t out_size, char **history, int *history_len, int *history_index) {
    char buf[MAX_LINE] = {0};
    int len = 0, cursor = 0;

    while (1) {
        char c;
        if (read(STDIN_FILENO, &c, 1) <= 0) continue;

        if (c == '\n') {
            buf[len] = '\0';
            printf("\n");
            strncpy(out, buf, out_size);
            out[out_size-1] = '\0';
            if (len > 0 && *history_len < MAX_HISTORY) {
                history[*history_len] = strdup(buf);
                (*history_len)++;
            }
            *history_index = *history_len;
            return len;
        }
        else if (c == 127) { // backspace
            if (cursor > 0) {
                memmove(buf + cursor - 1, buf + cursor, len - cursor);
                len--;
                cursor--;
            }
        }
        else if (c == 27) { // escape seq
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 0) continue;
            if (read(STDIN_FILENO, &seq[1], 1) == 0) continue;
            if (seq[0] == '[') {
                if (seq[1] == 'A') { // up
                    if (*history_index > 0) {
                        (*history_index)--;
                        strncpy(buf, history[*history_index], MAX_LINE);
                        len = strlen(buf);
                        cursor = len;
                    }
                } else if (seq[1] == 'B') { // down
                    if (*history_index < *history_len - 1) {
                        (*history_index)++;
                        strncpy(buf, history[*history_index], MAX_LINE);
                        len = strlen(buf);
                        cursor = len;
                    } else {
                        len = cursor = 0;
                        buf[0] = '\0';
                    }
                } else if (seq[1] == 'C') { // right
                    if (cursor < len) cursor++;
                } else if (seq[1] == 'D') { // left
                    if (cursor > 0) cursor--;
                }
            }
        }
        else if (c >= 32 && c <= 126) { // printable
            if (len < MAX_LINE - 1) {
                memmove(buf + cursor + 1, buf + cursor, len - cursor);
                buf[cursor] = c;
                len++;
                cursor++;
            }
        }

        // redraw line in place
        printf("\r > %s", buf);
        // clear to end of line (avoid leftovers if shorter)
        printf("\033[K");
        // move cursor to correct spot
        int prompt_len = 3; // " > "
        printf("\r\033[%dC", prompt_len + cursor);
        fflush(stdout);

        printf("\r > ");         // move to start + print prompt
        printf("%s", buf);           // print current buffer
        printf(" ");                 // overwrite leftover char if buffer shrank
        printf("\r\033[%dC", 3 + cursor); // move cursor to correct spot
        fflush(stdout);
    }
}

void repl(Canvas *surf) {
    char line[MAX_LINE];
    int x_ticks = 5, y_ticks = 5;

    char *history[MAX_HISTORY];
    int history_len = 0, history_index = 0;

    enable_raw_mode();

    printf(" > ");
    fflush(stdout);

    while (readline(line, sizeof(line), history, &history_len, &history_index) > 0) {
        if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) break;

        if (strcmp(line, "clear") == 0) canvas_clear(surf);

        else if (strncmp(line, "size ", 5) == 0) {
            int w, h;
            if (sscanf(line + 5, "%d %d", &w, &h) == 2) {
                canvas_resize(surf, w, h);
                printf("Resized plot to %dx%d\n", w, h);
            } else {
                printf("Usage: size <width> <height>\n");
            }
        }

        else if (strncmp(line, "ticks", 5) == 0) {
            int xt, yt;
            if (sscanf(line + 5, "%d %d", &xt, &yt) == 2) {
                if (xt > 1) x_ticks = xt;
                if (yt > 1) y_ticks = yt;
                printf("Set ticks: x=%d, y=%d\n", x_ticks, y_ticks);
            } else {
                printf("Usage: ticks <x_ticks> <y_ticks>\n");
            }
        }

        else if (strncmp(line, "plot ", 5) == 0) {
            if (strstr(line, "sin") || strstr(line, "cos")) {
                plot_trig(surf, line, 0x00FF00);

                printf("\n");
                render_full(surf, true);
                printf("\n");
            }

            else {
                char filename[128]; int xcol, ycol;
                const char *p = line + 5; while (*p == ' ') p++;
                if (*p == '"' || *p == '\'') {
                    char quote = *p++; const char *start = p; const char *end = strchr(start, quote);
                    if (end) {
                        size_t len = end - start;
                        if (len >= sizeof(filename)) len = sizeof(filename)-1;
                        strncpy(filename, start, len); filename[len] = '\0'; p = end + 1;
                    } else { printf("Unterminated quoted filename\n"); continue; }
                } else { printf("Filename must be quoted with ' or \"\n"); continue; }

                if (sscanf(p, " %d %d", &xcol, &ycol) == 2) {
                    double xmin, xmax, ymin, ymax;
                    if (plot_from_csv(surf, filename, xcol, ycol, 0x00FFFF,
                        &xmin, &xmax, &ymin, &ymax) == 0) {

                        printf("\n");
                        render_full_w_axes(surf, xmin, xmax, ymin, ymax, x_ticks, y_ticks, true);
                        printf("\n");

                    } else printf("Failed to plot CSV %s\n", filename);
                } else printf("Usage: plot \"filename.csv\" <xcol> <ycol>\n");
            }

        } else {
            printf("Unknown command.\n");
        }
        printf(" > ");
        fflush(stdout);
    }

    disable_raw_mode();
}
