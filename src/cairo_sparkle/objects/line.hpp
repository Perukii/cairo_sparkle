
class casp_line : public casp_object {
  public:
    casp_xy<double> start, end, d_start, d_end;
    double w, d_w;
    casp_rgb color_line;

    void setup_line(double _w = 0, double _sx = 0, double _sy = 0, double _ex = 0, double _ey = 0,
                    casp_rgb _color_line = casp_rgb_null) {
        w = _w;
        start = casp_xy<double>(_sx, _sy);
        end   = casp_xy<double>(_ex, _ey);
        color_line = _color_line;

        setup_surface();
    }

    void draw_line() {
        cairo_set_source_rgba(surface->cr, color_line.r, color_line.g,
                              color_line.b, color_line.a);

        d_w = surface->translate_w(w);
        d_start.x = surface->translate_x(start.x);
        d_start.y = surface->translate_y(start.y);
        d_end  .x = surface->translate_x(end  .x);
        d_end  .y = surface->translate_y(end  .y);

        cairo_set_line_width(surface->cr, d_w);

        cairo_move_to(surface->cr, d_start.x, d_start.y);
        cairo_line_to(surface->cr, d_end  .x, d_end  .y);
        cairo_stroke(surface->cr);
    }
};