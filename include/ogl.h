#ifndef OGL_H
#define OGL_H

#include "framebuffer.h"

int g_init(int screenW,int screenH,const char* title);
void g_clear();

bool g_main_loop();
void g_clear_color(float r,float g,float b);
void g_swap_buffer();
FrameBuffer* g_get_main_buffer();


int g_get_screen_w();
int g_get_screen_h();

#endif
