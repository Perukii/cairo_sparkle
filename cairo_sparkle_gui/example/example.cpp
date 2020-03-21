
/* how to build */

/*
 [g++]     : g++ -o [executable-file] [cpp-file] $(pkg-config --cflags --libs gtk+-3.0)
                  -I [PATH to cairo_sparkle]
 [clang++] : clang++ -o [executable-file] [cpp-file] $(pkg-config --cflags --libs gtk+-3.0)
                  -I [PATH to cairo_sparkle]
*/

// <example> //

// g++ -o output example.cpp $(pkg-config --cflags --libs gtk+-3.0) -I home/documents/cairo_sparkle


// ===================

#include "cairo_sparkle/include.hpp"
// contains - <set>

#include "cairo_sparkle_gui/include.hpp"


casp_gui_host host;                 // casp_gui_host : manage GUI-widgets


int main(int _argc, char ** _argv){
     casp_gui_init(_argc, _argv);   // casp_gui_init : initialize gtk3 & casp_gui

     host.setup(900,900);           // setup casp_gui_host automatically
                                    //       (900,900):scale(resolution) of window

     // host.window_scale(900,900); // you can use "host.window_scale(x,y)" if you want to 
                                    //       vary the scale of window

     host.run();                    // mainloop
}

casp_rect recta(-0.5,-0.5,2.0,1.5,casp_rgb_adv_autumnRed);
   // casp_rect( x  , y  , w , h , color)

casp_rect rectb( 0.5, 0.5,2.0,1.5,casp_rgb_adv_skyBlue);


// mainloop

void casp_gui_main(){

     // draw
     recta.draw(&host.surface);
     rectb.draw(&host.surface);

     for(auto key:host.surface.keys){ // recognize pressed-keys
          switch(key){
               case 113: // q
                    host.surface.zoom/=1.05;
                    break;
               case 119: // w
                    host.surface.xy.y-=0.1;
                    break;
               case 101: // e
                    host.surface.zoom*=1.05;
                    break;
               case 97 : // a
                    host.surface.xy.x-=0.1;
                    break;
               case 115: // s
                    host.surface.xy.y+=0.1;
                    break;
               case 100: // d
                    host.surface.xy.x+=0.1;
                    break;
          }
     }
}

/*

definition of default-colors 

     #define casp_rgb_null   casp_rgb(0,0,0,0)
     #define casp_rgb_black  casp_rgb(0,0,0,1)
     #define casp_rgb_red    casp_rgb(1,0,0,1)
     #define casp_rgb_green  casp_rgb(0,1,0,1)
     #define casp_rgb_blue   casp_rgb(0,0,1,1)
     #define casp_rgb_yellow casp_rgb(1,1,0,1)
     #define casp_rgb_sky    casp_rgb(0,1,1,1)
     #define casp_rgb_pink   casp_rgb(1,0,1,1)
     #define casp_rgb_white  casp_rgb(1,1,1,1)

     #define casp_rgb_adv_naturalGreen casp_rgb(0.60,0.96,0.52)
     #define casp_rgb_adv_skyBlue      casp_rgb(0.56,0.88,1.00)
     #define casp_rgb_adv_autumnRed    casp_rgb(1.00,0.60,0.46)

*/