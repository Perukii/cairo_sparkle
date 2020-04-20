

class c_surface{
protected:
    
    bool transform_basis = c_transform_basis_w;

public:

    casp_xywh<double> xywh;
    casp_xy<double> resolution;
    double scale = 20.0;
    cairo_t *cr;

    template<class... Args> c_surface(Args...);

    void setup_surface(casp_xy<double>, casp_xy<double>);

    void set_wh(casp_xy<double>);
    void set_background(casp_rgb);

    double transform_x(double);
    double transform_y(double);
    double transform_w(double);
    double transform_h(double);

    double re_transform_x(double);
    double re_transform_y(double);

    casp_xy<double>   transform_xy  (casp_xy<double>);
    casp_xy<double>   transform_wh  (casp_xy<double>);
    casp_xywh<double> transform_xywh(casp_xywh<double>);

};

template<class... Args> c_surface::c_surface(Args... args){ setup_surface(args...); }

void c_surface::setup_surface
        (casp_xy<double> _xy = {0,0},
         casp_xy<double> _resolution = {0,0}){
    
    xywh.x = _xy.x;
    xywh.y = _xy.y;

    resolution = _resolution;
}

void c_surface::set_wh(casp_xy<double> _wh) {
    xywh.w = (transform_basis == c_transform_basis_w)
                ? scale
                : scale / resolution.y * resolution.x;

    xywh.h = (transform_basis == c_transform_basis_h)
                ? scale
                : scale / resolution.x * resolution.y;
}

void c_surface::set_background(casp_rgb _color = casp_rgb_white) {
    cairo_set_source_rgba(cr, _color.r, _color.g, _color.b, _color.a);
    cairo_rectangle(cr, 0, 0, resolution.x + 1, resolution.y + 1);
    cairo_fill(cr);
}

double c_surface::transform_x(double _tar_x) {
    return (_tar_x - xywh.x) *
           (transform_basis == c_transform_basis_w ? resolution.x : resolution.y)
           / scale + resolution.x * 0.5;
}

double c_surface::transform_y(double _tar_y) {
    return (_tar_y - xywh.y) *
           (transform_basis == c_transform_basis_w ? resolution.x : resolution.y)
           / scale + resolution.y * 0.5;
}

double c_surface::transform_w(double _tar_w) {
    return _tar_w *
            (transform_basis == c_transform_basis_w ? resolution.x : resolution.y)
            / scale;
}

double c_surface::transform_h(double _tar_h) {
    return _tar_h *
            (transform_basis == c_transform_basis_w ? resolution.x : resolution.y)
            / scale;
}

casp_xy<double> c_surface::transform_xy(casp_xy<double> _tar_xy){
    casp_xy<double> result;
    result.x = transform_x(_tar_xy.x);
    result.y = transform_y(_tar_xy.y);
    return result;
}

casp_xy<double> c_surface::transform_wh(casp_xy<double> _tar_wh){
    casp_xy<double> result;
    result.x = transform_w(_tar_wh.x);
    result.y = transform_h(_tar_wh.y);
    return result;
}

casp_xywh<double> c_surface::transform_xywh(casp_xywh<double> _tar_xywh){
    casp_xywh<double> result;
    result.x = transform_x(_tar_xywh.x);
    result.y = transform_y(_tar_xywh.y);
    result.w = transform_w(_tar_xywh.w);
    result.h = transform_h(_tar_xywh.h);
    return result;
}








/*


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

    void fill(casp_rgb _color = casp_rgb_white) {
        cairo_set_source_rgba(cr, _color.r, _color.g, _color.b, _color.a);
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

    casp_xywh<double> for_xywh(){
        return casp_xywh<double>(xy, scale_range);
    }
};


*/