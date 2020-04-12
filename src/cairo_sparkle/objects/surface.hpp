

class casp_surface {

  public:
    casp_xy<double> xy, scale, scale_range;
    double range, zoom = 1;
    cairo_t *cr;

    bool translate_norm = casp_translate_norm_w;

    casp_surface(double _x = 0, double _y = 0, double _w = 0, double _h = 0,
                 double _range = 20.0) {
        xy.x = _x;
        xy.y = _y;
        range = _range;
        set_scale({_w, _h});
    }

    void set_scale(casp_xy<double> _tar) {
        scale = _tar;
        scale_range.x = (translate_norm == casp_translate_norm_w)
                            ? range
                            : range / scale.y * scale.x;
        scale_range.y = (translate_norm == casp_translate_norm_h)
                            ? range
                            : range / scale.x * scale.y;
    }

    void fill_white() {
        cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);
        cairo_rectangle(cr, 0, 0, scale.x + 1, scale.y + 1);
        cairo_fill(cr);
    }

    casp_xywh<double> translate_xywh(casp_xywh<double> _xywh) {
        casp_xywh<double> result;
        result.x = translate_x(_xywh.x);
        result.y = translate_y(_xywh.y);
        result.w = translate_w(_xywh.w);
        result.h = translate_h(_xywh.h);
        return result;
    }

    double translate_x(double _tar) {
        return (_tar - xy.x) *
                   (translate_norm == casp_translate_norm_w ? scale.x
                                                            : scale.y) /
                   range * zoom +
               scale.x * 0.5;
    }

    double retranslate_x(double _tar) {
        return range * (_tar - scale.x * 0.5) /
                   (translate_norm == casp_translate_norm_w ? scale.x
                                                            : scale.y) / zoom + xy.x;
    }

    double retranslate_y(double _tar) {
        return range * (_tar - scale.y * 0.5) /
                   (translate_norm == casp_translate_norm_w ? scale.x
                                                            : scale.y) / zoom + xy.y;
    }

    double translate_y(double _tar) {

        return (_tar - xy.y) *
                   (translate_norm == casp_translate_norm_w ? scale.x
                                                            : scale.y) /
                   range * zoom +
               scale.y * 0.5;
    }

    double translate_w(double _tar) {
        return _tar *
               (translate_norm == casp_translate_norm_w ? scale.x : scale.y) /
               range * zoom;
    }

    double translate_h(double _tar) {
        return _tar *
               (translate_norm == casp_translate_norm_w ? scale.x : scale.y) /
               range * zoom;
    }
};
