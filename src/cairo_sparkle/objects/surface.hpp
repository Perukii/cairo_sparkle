
class c_surface{

private:
    bool transform_basis = c_transform_basis_w;

public:

    casp_xywh<double> xywh;
    casp_xy<double> resolution;
    
    double scale = 20.0;
    cairo_t *cr;

    template<class... Args> c_surface(Args...);

    ~c_surface();

    void setup_surface(casp_xy<double>, casp_xy<double>);

    void set_wh();

    void draw_background(casp_rgb);

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

c_surface::~c_surface(){
    cairo_destroy(cr);
}

void c_surface::setup_surface
        (casp_xy<double> _xy = {0,0},
         casp_xy<double> _resolution = {0,0}){
    
    xywh.x = _xy.x;
    xywh.y = _xy.y;

    resolution = _resolution;
}

void c_surface::set_wh() {
    xywh.w = (transform_basis == c_transform_basis_w)
                ? scale
                : scale / resolution.y * resolution.x;

    xywh.h = (transform_basis == c_transform_basis_h)
                ? scale
                : scale / resolution.x * resolution.y;
}

void c_surface::draw_background(casp_rgb _color) {
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

double c_surface::re_transform_x(double _tar_x){
    return scale * (_tar_x - resolution.x * 0.5) /
                (transform_basis == c_transform_basis_w ? resolution.x : resolution.y)
                 + xywh.x;
}

double c_surface::re_transform_y(double _tar_y){
    return scale * (_tar_y - resolution.y * 0.5) /
                (transform_basis == c_transform_basis_w ? resolution.x : resolution.y)
                 + xywh.y;
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
