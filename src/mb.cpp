#include "mb.h"
#include "framebuffer.h"
#include "ogl.h"

MB::MB() {
    buffer = new FrameBuffer(g_get_screen_w(),g_get_screen_h());

    r = 9;
    g = 15;
    b = 8;

    iter = 100;
    offset_x = 0;
    offset_y = 0;
    zoom = 100;
    type = 0;
}

MB::~MB() {
}

void MB::clear() {
    buffer->clear();
    delete buffer;
}



void MB::update() {
    if(type == 0 )
        gpu();
    else if(type == 1) {
        omp();
    }
    else {
        mpi();
    }
}

void MB::gpu() {
    g_get_mb_shader()->use();
    g_get_mb_shader()->send_int_uniform("screen_w", g_get_screen_w())   ;
    g_get_mb_shader()->send_int_uniform("screen_h", g_get_screen_h());
    g_get_mb_shader()->send_float_uniform("zoom",this->get_zoom());
    g_get_mb_shader()->send_float_uniform("offset_x",this->get_offset_x());
    g_get_mb_shader()->send_float_uniform("offset_y",this->get_offset_y());
    g_get_mb_shader()->send_int_uniform("color_r", get_r());
    g_get_mb_shader()->send_int_uniform("color_g", get_g());
    g_get_mb_shader()->send_int_uniform("color_b", get_b());
    g_get_mb_shader()->send_int_uniform("iteracie", get_iter());

    g_draw_g_object();
}

void MB::omp() {}
void MB::mpi() {}

void MB::reset() {
    r = 9;
    g = 15;
    b = 8;
    iter = 100;
    offset_x = 0;
    offset_y = 0;
    zoom = 100;
}

void MB::set_type(int i) {
    this->type = i;
}

int MB::get_type() {
    return this->type;
}

void MB::set_r(int i) {
   this->r = i;
}

void MB::set_g(int i) {
   this->g = i;
}

void MB::set_b(int i) {
   this->b = i;
}

void MB::set_iter(int i) {
    this->iter = i;
}

void MB::set_zoom(float i) {
    this->zoom = i;
}

void MB::set_offset_x(float i) {
    this->offset_x = i;
}

void MB::set_offset_y(float i) {
    this->offset_y = i;
}


int MB::get_r() {
    return this->r;
}

int MB::get_g() {
    return this->g;
}

int MB::get_b() {
    return this->b;
}

int MB::get_iter() {
    return this->iter;
}

float MB::get_zoom() {
    return this->zoom;
}

float MB::get_offset_x() {
    return this->offset_x;
}

float MB::get_offset_y() {
    return this->offset_y;
}

FrameBuffer* MB::get_buffer() {
    return this->buffer;
}


