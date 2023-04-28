#include <iostream>
#include "config.h"
#include "ogl.h"
#include "shader.h"


int main(int argc, char** argv) {
    g_init(1280, 720, "fraktal");

    while (g_main_loop()) {
        g_clear_color(1, 0, 0);
        g_swap_buffer();

    }
    g_clear();
    return 0;
}
