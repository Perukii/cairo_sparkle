
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

    void setup_rect(double _x = 0, double _y = 0, double _w = 0, double _h = 0,
                    casp_rgb _color_rect = casp_rgb_null, double _pivx = 0.5,
                    double _pivy = 0.5) {
        rect = true;
        xywh = casp_xywh<double>(_x, _y, _w, _h);
        color_rect = _color_rect;

        pivot.x = _pivx;
        pivot.y = _pivy;
        set_surface();
    }

    void draw_rect() {
        
        d_xywh = surface->translate_xywh(xywh);
        
        cairo_rectangle(surface->cr, d_xywh.x - d_xywh.w * pivot.x,
                        d_xywh.y - d_xywh.h * pivot.y, d_xywh.w, d_xywh.h);
        set_color(color_rect);

        if (stroke){
            cairo_fill_preserve(surface->cr);
            draw_stroke(this);
        }
        else if (rect)
            cairo_fill(surface->cr);
    }

    bool on_point(casp_xy<double> _tar) {
        return (_tar.x >= xywh.x - xywh.w * pivot.x and
                _tar.x <= xywh.x + xywh.w * (1 - pivot.x)) and
               (_tar.y >= xywh.y - xywh.h * pivot.y and
                _tar.y <= xywh.y + xywh.h * (1 - pivot.y));
    }

    
};
