#include "ogl.h"
#include "config.h"
#include "gui.h"
#include "framebuffer.h"
#include "shader.h"

FrameBuffer *main_buffer;
GLFWwindow *window;
unsigned int VAO;
unsigned int VBO;

int screen_w = 0;
int screen_h = 0;

Shader *fbo_shader;

void init_g_object() {
    float quad[] = { 
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), &quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void g_draw_g_object() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int g_init(int screenW, int screenH, const char *title) {
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(screenW, screenH, title, NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit();
    init_gui(window);
    init_g_object();

    main_buffer = new FrameBuffer(screenW,screenH);

    screen_w = screenW;
    screen_h = screenH;

    fbo_shader = new Shader("shaders/fbo_vertex.glsl","shaders/fbo_fragment.glsl");

    return 0;
}

void g_clear() {

    delete main_buffer;
    delete fbo_shader;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    main_buffer->clear();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

bool g_main_loop() {
    if(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        return true;
    }
    return false;
}

void g_swap_buffer() {

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    #if GUI  == 1 
        draw_gui();
    #else
        fbo_shader->use();
        glActiveTexture(GL_TEXTURE0+main_buffer->texture);
        fbo_shader->send_int_uniform("fbo_buffer",main_buffer->texture);        
        glBindTexture(GL_TEXTURE_2D, main_buffer->texture);
        g_draw_g_object();
    #endif

    glfwSwapBuffers(window);
}

void g_clear_color(float r, float g, float b) {
    glBindFramebuffer(GL_FRAMEBUFFER, main_buffer->id);
    glClearColor(r,g,b,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

FrameBuffer* g_get_main_buffer() {
    return main_buffer;
}

int g_get_screen_w() {
    return screen_w;
}

int g_get_screen_h() {
    return screen_h;
}

GLFWwindow *g_get_window() {
    return window;
}

