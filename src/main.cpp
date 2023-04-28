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
        mb_shader.send_int_uniform("screen_w", g_get_screen_w());
        mb_shader.send_int_uniform("screen_h",g_get_screen_h());
        mb_shader.send_float_uniform("zoom", g_get_zoom());
        mb_shader.send_float_uniform("mouse_x",g_get_center_x());
        mb_shader.send_float_uniform("mouse_y",g_get_center_y());

        g_draw_g_object();
        g_swap_buffer();

    }

    g_clear();
    return 0;
}
