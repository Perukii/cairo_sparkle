
class casp_image : public casp_subrect {
private:
    cairo_surface_t *image;
    casp_xy<double> resolution;
    cairo_filter_t filter;
    double alpha = 1;
    bool image_enable;

public:

    ~casp_image();

    void setup_image(const char *, casp_xywh<double>, casp_xy<double>);
    void image_register(const char *);

    void enable_image();
    void disable_image();

    void set_alpha(double);
    double get_alpha();

    void set_cairo_filter(cairo_filter_t);

    void draw_image();
};


casp_image::~casp_image() { cairo_surface_destroy(image); }

void casp_image::setup_image(const char * _file = "",
                casp_xywh<double> _xywh = {0.0, 0.0, 0.0, 0.0},
                casp_xy<double> _draw_pivot = {0.0, 0.0}) {

    enable_image();
    xywh = _xywh;

    if (_file != "")
        image_register(_file);

    draw_pivot = _draw_pivot;

    set_surface();
    set_cairo_filter(casp_def_image_filter);
    set_alpha(1.0);
}

void casp_image::image_register(const char * _file) {
    image = cairo_image_surface_create_from_png(_file);

    resolution.x = cairo_image_surface_get_width(image);
    resolution.y = cairo_image_surface_get_height(image);
}

void casp_image::enable_image(){
    image_enable = true;
}
void casp_image::disable_image(){
    image_enable = false;
}

void casp_image::set_alpha(double _alpha){
    alpha = _alpha;
}
double casp_image::get_alpha(){
    return alpha;
}

void casp_image::set_cairo_filter(cairo_filter_t _filter){
    filter = _filter;
}

void casp_image::draw_image() {

    casp_xywh<double> d_b_xywh;

    d_b_xywh.x = xywh.x;
    d_b_xywh.y = xywh.y;
    
    d_b_xywh.w = (abs(xywh.w) != casp_auto ?
            xywh.w :
            xywh.h / resolution.y * resolution.x * (xywh.w > 0 ? 1:-1) );

    d_b_xywh.h = (abs(xywh.h) != casp_auto ?
            xywh.h :
            xywh.w / resolution.x * resolution.y * (xywh.h > 0 ? 1:-1) );

    d_xywh = surface->transform_xywh(d_b_xywh);

    if(image_enable){

        cairo_save(surface->cr);

        casp_xywh<double> d_a_xywh = d_xywh;

        d_a_xywh.w /= resolution.x;
        d_a_xywh.h /= resolution.y;

        cairo_scale(surface->cr, d_a_xywh.w, d_a_xywh.h);

        cairo_set_source_surface(surface->cr, image,
                                    d_a_xywh.x / d_a_xywh.w - resolution.x * (draw_pivot.x + 1.0) * 0.5,
                                    d_a_xywh.y / d_a_xywh.h - resolution.y * (draw_pivot.y + 1.0) * 0.5);

        cairo_pattern_set_filter (cairo_get_source (surface->cr), filter);

        cairo_scale(surface->cr, 1 / d_a_xywh.w, 1 / d_a_xywh.h);
        
        cairo_paint_with_alpha(surface->cr, alpha);

        cairo_restore(surface->cr);
        
    }

    if (rect_enable)
        draw_rect(false);
}
