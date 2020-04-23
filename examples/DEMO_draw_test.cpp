
#include "src/cairo_sparkle.cpp"

casp_host host;
casp_rect rect, rect2;
casp_line line;
casp_image image;

void main_loop(){
    rect.xywh.x+=0.01;
    line.path[0].xy = host.mouse_pos;
    rect.draw_rect();
    
    rect2.draw_rect();
    line.draw_line();
    image.draw_image();
    
    host.debug_QWEASD(0);

    if(host.get_key_press(32))
       host.write_png("test.png");
}

int main() {
    host.setup_host({500, 500});
    host.set_titlebar("THANKS");
    host.set_background(casp_rgb(1.0, 1.0, 1.0, 1.0));
    rect.setup_rect({0.0, 0.0, 3.0, 3.0}, casp_rgb_adv_skyBlue);
    rect.rect_stroke.setup_stroke(0.1, casp_rgb_adv_autumnRed);
    rect2.setup_rect({0.0, 0.0, 3.0, 3.0}, casp_rgb_adv_naturalGreen);
    line.setup_line({0.0, 0.0}, 0.1, casp_rgb_black);
    line.add_line({3.2,1.5});
    line.switch_color(casp_rgb_adv_autumnRed);
    line.add_line({-1.2,4.5});
    line.switch_width(0.5);
    line.close_path();
    image.setup_image("/home/tada/Pictures/kusokora.png",{-3.0, -3.0, casp_auto, 6.0},{-0.5,1});
    image.setup_fill_color(casp_rgb(1,0,0,0.5));
    host.run(main_loop);
}

