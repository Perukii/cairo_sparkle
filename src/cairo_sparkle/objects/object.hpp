

class casp_object {
  public:
    casp_surface *surface;

    casp_object() {
    }

    void set_color(casp_rgb _color){
        cairo_set_source_rgba(surface->cr, _color.r, _color.g,
                    _color.b, _color.a);
    }

    void setup_surface(casp_surface *_surface = casp_default_surface_target) {
        surface = _surface;
    }

};
