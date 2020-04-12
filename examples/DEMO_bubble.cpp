
#include "src/cairo_sparkle.cpp"

casp_host host;
casp_circle circle, subcic;

int main(int _argc, char **_argv) {

    casp_init(_argc, _argv);
    host.setup_host(500, 500, casp_translate_norm_w);
    host.set_surface(5);
    host.set_titlebar("BUBBLE");
    circle.setup_circle(0.0, 0.0, 1.0, casp_rgb_black);
    circle.set_surface(&host.surface[0]);
    subcic.setup_circle(2.0, 2.0, 2.0, casp_rgb_white);
    subcic.setup_stroke(0.1, casp_rgb_black);
    subcic.set_surface(&host.surface[1]);
    host.run();
}

void casp_main(){
    host.debug_QWEASD(0);
}

void casp_draw(){
    host.surface[0].fill();
    circle.draw_circle();
    subcic.draw_circle();
    
}
