

class casp_rect : public casp_object {
protected:
    bool rect_enable;
    casp_xywh<double> d_xywh;

public:
    casp_xywh<double> xywh;
    casp_xy<double> draw_pivot;
    casp_rgb color_rect;
    casp_stroke rect_stroke;
    

    template<class... Args> casp_rect(Args...);

    void setup_rect(casp_xywh<double>, casp_rgb, casp_xy<double>);

    void enable_rect();
    void disable_rect();

    void draw_rect(bool);

};

template<class... Args> casp_rect::casp_rect(Args... args){ setup_rect(args...); }

void casp_rect::setup_rect(casp_xywh<double> _xywh = {0.0, 0.0, 0.0, 0.0},
                        casp_rgb _color_rect = casp_rgb_null,
                        casp_xy<double> _draw_pivot = {0.0, 0.0}){

    enable_rect();
    xywh = _xywh;
    draw_pivot = _draw_pivot;
    color_rect = _color_rect; 
    set_surface();
    
}

void casp_rect::enable_rect() { rect_enable = true; }
void casp_rect::disable_rect() { rect_enable = false; }

void casp_rect::draw_rect(bool transform_xywh = true) {

    if(transform_xywh) d_xywh = surface->transform_xywh(xywh);

    cairo_rectangle(surface->cr,
                    d_xywh.x - d_xywh.w * (draw_pivot.x + 1.0) * 0.5,
                    d_xywh.y - d_xywh.h * (draw_pivot.y + 1.0) * 0.5,
                    d_xywh.w, d_xywh.h);

    surface->set_color(rect_enable ? color_rect:casp_rgb_null);
    
    cairo_fill_preserve(surface->cr);
    rect_stroke.draw_stroke(surface);

}
