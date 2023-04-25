#include "ogl.h"
#include "config.h"
#include "gui.h"
#include "framebuffer.h"

FrameBuffer *main_buffer;
GLFWwindow *window;
unsigned int VAO;
unsigned int VBO;


int screen_w = 0;
int screen_h = 0;

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

    return 0;
}

void g_clear() {
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

    draw_gui();

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
