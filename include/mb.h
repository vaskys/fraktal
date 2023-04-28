#ifndef MB_H
#define MB_H


#include "config.h"
#include "framebuffer.h"

class MB {
public:
    MB();
    ~MB();

    void update();

    void set_type(int i);
    int get_type();

    void set_r(int i);
    void set_g(int i);
    void set_b(int i);

    void set_iter(int i);
    void set_zoom(float i);
    void set_offset_x(float i);
    void set_offset_y(float i);


    int get_r();
    int get_g();
    int get_b();


    int get_iter();
    float get_zoom();
    float get_offset_x();
    float get_offset_y();


    FrameBuffer *get_buffer();

    void reset();
    void clear();


    void set_omp_threads(int i);
    int get_omp_threads();

    double cas;

private:
    int r;
    int g;
    int b;

    int iter;
    float zoom;
    float offset_x;
    float offset_y;

    FrameBuffer *buffer;

    void gpu();
    void omp();
    void mpi();

    int n_omp_threads;

    int type;
};


#endif




