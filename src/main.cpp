#include <iostream>
#include "config.h"
#include "ogl.h"

using namespace std;

int main(int argc, char** argv) {
    g_init(1280, 720, "fraktal");

    while (g_main_loop(1, 1, 1)) {
        g_draw_gui();
        g_swap_buffer();
    }

    g_clear();
    return 0;
}
