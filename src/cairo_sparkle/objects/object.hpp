

class c_object {
protected:
    c_surface * surface;

public:
    void set_color(casp_rgb);
    void set_surface(c_surface *);

};

void c_object::set_color(casp_rgb _color){
    cairo_set_source_rgba(surface->cr, _color.r, _color.g, _color.b, _color.a);
}

void c_object::set_surface(c_surface * _surface = c_default_surface_target){
    surface = _surface;
}
