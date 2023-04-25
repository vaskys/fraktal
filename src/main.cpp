#include <iostream>
#include "config.h"
#include "ogl.h"
#include "shader.h"

using namespace std;

int main(int argc, char** argv) {
    g_init(1280, 720, "fraktal");

    Shader main("shaders/fbo_vertex.glsl","shaders/fbo_fragment.glsl");

    while (g_main_loop()) {

        g_clear_color(1, 1, 1);
        g_swap_buffer();
    }

    g_clear();
    return 0;
}
