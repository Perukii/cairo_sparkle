#include <iostream>
///usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf
#include "cairo_sparkle/include.hpp"
#include "cairo_sparkle_image/include.hpp"

casp_rect recta, rectb;
casp_text texta;
casp_img_host host;

int main(int _argc, char ** _argv){
     casp_img_init(_argc, _argv);

     host.setup(1200,900);
     casp_default_surface(&host.surface);

     recta.setup_rect(-0.5,-0.5,2.0,1.5,casp_rgb_adv_autumnRed);
     rectb.setup_rect(0, 0,1.0,1.0);
     rectb.setup_stroke(true, 0.05, casp_rgb_adv_skyBlue);
     texta.setup_text("132132", 0,0,casp_auto,1.0,casp_rgb_adv_naturalGreen,0,0);
     
     host.write();
     
}

void casp_main(){
     
     host.surface.fill_white();
     recta.draw_rect();
     rectb.draw_rect();
     texta.draw_text();
     
}

