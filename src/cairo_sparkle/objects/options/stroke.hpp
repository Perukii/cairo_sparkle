
class casp_stroke {

private:
    bool stroke_enable = false;

public:
    
    double stroke_w;
    casp_rgb color_stroke;

    template<class... Args> casp_stroke(Args...);
    void setup_stroke(double, casp_rgb);

    void enable_stroke();
    void disable_stroke();
    bool is_enabled_stroke();

    void draw_stroke(casp_surface *);

};

template<class... Args> casp_stroke::casp_stroke(Args... args){ setup_stroke(args...); }

void casp_stroke::setup_stroke(double _stroke_w = 0,
                  casp_rgb _color_stroke = casp_rgb_null) {
    enable_stroke();
    stroke_w = _stroke_w;
    color_stroke = _color_stroke;
}

void casp_stroke::enable_stroke(){
    stroke_enable = true;
}

void casp_stroke::disable_stroke(){
    stroke_enable = false;
}

bool casp_stroke::is_enabled_stroke(){
    return stroke_enable;
}

void casp_stroke::draw_stroke(casp_surface * _surface) {

    
    _surface->set_color(stroke_enable ? color_stroke:casp_rgb_null);

    double d_stroke_w = _surface->transform_w(stroke_w);

    cairo_set_line_width(_surface->cr, d_stroke_w);
    
    cairo_stroke(_surface->cr);
}
