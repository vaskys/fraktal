#ifndef OGL_H
#define OGL_H

#include "framebuffer.h"
#include "config.h"

int g_init(int screenW,int screenH,const char* title);
void g_clear();

bool g_main_loop();
void g_clear_color(float r,float g,float b);
void g_swap_buffer();
void g_draw_g_object();
FrameBuffer* g_get_main_buffer();

int g_get_screen_w();
int g_get_screen_h();

int g_get_d_screen_w();
int g_get_d_screen_h();

int g_get_mouse_x();
int g_get_mouse_y();

float g_get_zoom();

GLFWwindow *g_get_window();


float g_get_center_x();
float g_get_center_y();


#endif
