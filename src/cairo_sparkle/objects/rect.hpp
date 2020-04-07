
class casp_rect : public casp_object, public casp_stroke {
  public:
    casp_xy<double> pivot;
    casp_xywh<double> xywh;
    casp_xywh<double> d_xywh;

    bool rect = false;
    casp_rgb color_rect;

    casp_rect(double _x = 0, double _y = 0, double _w = 0, double _h = 0,
              casp_rgb _color_rect = casp_rgb_null, double _pivx = 0.5,
              double _pivy = 0.5) {
        setup_rect(_x, _y, _w, _h, _color_rect, _pivx, _pivy);
    }

    void setup_rect(casp_rgb _color_rect = casp_rgb_null) {
        color_rect = _color_rect;
    }

    void setup_rect(double _x = 0, double _y = 0, double _w = 0, double _h = 0,
                    casp_rgb _color_rect = casp_rgb_null, double _pivx = 0.5,
                    double _pivy = 0.5) {
        rect = true;
        xywh.x = _x;
        xywh.y = _y;
        xywh.w = _w;
        xywh.h = _h;
        color_rect = _color_rect;

        pivot.x = _pivx;
        pivot.y = _pivy;
        setup_surface();
    }

    void form_style() {
        cairo_rectangle(surface->cr, d_xywh.x - d_xywh.w * pivot.x,
                        d_xywh.y - d_xywh.h * pivot.y, d_xywh.w, d_xywh.h);
    }

    void draw_rect() {
        cairo_set_source_rgba(surface->cr, color_rect.r, color_rect.g,
                              color_rect.b, color_rect.a);

        if (translate_allowed())
            d_xywh = surface->translate_xywh(xywh);
        form_style();

        cairo_fill(surface->cr);
        if (stroke)
            draw_stroke();

        d_set = true;
    }

    void draw_stroke(){
        form_style();
        draw_stroke_pre(this);
    }

    bool on_point(casp_xy<double> _tar) {
        return (_tar.x >= xywh.x - xywh.w * pivot.x and
                _tar.x <= xywh.x + xywh.w * (1 - pivot.x)) and
               (_tar.y >= xywh.y - xywh.h * pivot.y and
                _tar.y <= xywh.y + xywh.h * (1 - pivot.y));
    }

    
};
