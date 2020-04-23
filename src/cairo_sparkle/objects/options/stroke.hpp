
class c_stroke {

private:
    bool stroke_enable = false;

public:
    
    double stroke_w;
    casp_rgb color_stroke;

    template<class... Args> c_stroke(Args...);
    void setup_stroke(double, casp_rgb);

    void enable_stroke();
    void disable_stroke();
    bool is_enabled_stroke();

    void draw_stroke(c_surface *);

};

template<class... Args> c_stroke::c_stroke(Args... args){ setup_stroke(args...); }

void c_stroke::setup_stroke(double _stroke_w = 0,
                  casp_rgb _color_stroke = casp_rgb_null) {
    enable_stroke();
    stroke_w = _stroke_w;
    color_stroke = _color_stroke;
}

void c_stroke::enable_stroke(){
    stroke_enable = true;
}

void c_stroke::disable_stroke(){
    stroke_enable = false;
}

bool c_stroke::is_enabled_stroke(){
    return stroke_enable;
}

void c_stroke::draw_stroke(c_surface * _surface) {

    
    _surface->set_color(stroke_enable ? color_stroke:casp_rgb_null);

    double d_stroke_w = _surface->transform_w(stroke_w);

    cairo_set_line_width(_surface->cr, d_stroke_w);
    
    cairo_stroke(_surface->cr);
}
