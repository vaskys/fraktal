#include <iostream>
#include "config.h"
#include "ogl.h"
#include "shader.h"


int main(int argc, char** argv) {
    g_init(1280, 720, "fraktal");

    Shader mb_shader("shaders/mb_vertex.glsl","shaders/mv_fragment.glsl");

    while (g_main_loop()) {
        g_clear_color(1, 0, 0);
        mb_shader.use();
        g_draw_g_object();
        g_swap_buffer();
    }

    g_clear();
    return 0;
}
