
#include "src/cairo_sparkle.cpp"

casp_window_host host;
casp_surface surface;
casp_line line;
casp_text text;

int main(int _argc, char **_argv) {

    casp_init(_argc, _argv);
    host.setup(&surface, 500, 500, casp_translate_norm_w);
    host.set_titlebar("HELLO");
    casp_default_surface(&surface);

    line.setup_line(0.3,
                    -7.0, 1.0,
                    7.0 , 1.0,
                    casp_rgb_adv_autumnRed);
    
    text.setup_text("Hello,world",-6.5, 1.0,
                    14.0, casp_auto,
                    casp_rgb_black, 0.0, 1.0);
                    
    text.set_font("Arial", true, true);

    host.run();
}

void casp_main(){

}

void casp_draw(){
    host.surface->fill_white();
    line.draw_line();
    text.draw_text();
}
