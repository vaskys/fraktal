#ifndef OGL_H
#define OGL_H

int g_init(int screenW,int screenH,const char* title);
void g_clear();

bool g_main_loop();
void g_clear_color(float r,float g,float b);
void g_swap_buffer();

#endif
