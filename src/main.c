#include "../include/common.h"
#include "../include/atedot.h"
#include "../include/repl.h"

int main() {
    setlocale(LC_ALL, "");

    Canvas surf = plot_make(80, 24);    // 80x24 terminal pixels

    repl(&surf);    // interactive REPL

    plot_free(&surf);
    return 0;
}
