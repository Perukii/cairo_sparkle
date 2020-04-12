
class casp_stroke {
  public:
    bool stroke = false;
    double stroke_w = 0, d_stroke_w;
    casp_rgb color_stroke = casp_rgb_null;

    void setup_stroke(double _stroke_w,
                      casp_rgb _color_stroke = casp_rgb_null) {
        stroke = true;
        stroke_w = _stroke_w;
        color_stroke = _color_stroke;
    }

    void draw_stroke(casp_object * _obj) {
      
        _obj->set_color(color_stroke);
        d_stroke_w = _obj->surface->translate_w(stroke_w);
        cairo_set_line_width(_obj->surface->cr, d_stroke_w);
        if(stroke)
          cairo_stroke(_obj->surface->cr);
    }

  
};