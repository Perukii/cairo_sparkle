
class casp_image : public casp_rect {

  public:
    cairo_surface_t *image;
    casp_xy<double> resolution;
    bool xflip, yflip;

    ~casp_image() { cairo_surface_destroy(image); }

    void setup_image(std::string _file = "", double _x = 0, double _y = 0,
                     double _w = 0, double _h = 0, double _pivx = 0.5,
                     double _pivy = 0.5) {
        xywh.x = _x;
        xywh.y = _y;

        if (_file != "")
            image_register(_file);

        xywh.w = (_w != casp_auto ? _w : _h / resolution.y * resolution.x);
        xywh.h = (_h != casp_auto ? _h : _w / resolution.x * resolution.y);

        pivot.x = _pivx;
        pivot.y = _pivy;

        xflip = false;
        yflip = false;

        set_surface();
    }

    void image_register(std::string _file) {
        image = cairo_image_surface_create_from_png(_file.c_str());

        resolution.x = cairo_image_surface_get_width(image);
        resolution.y = cairo_image_surface_get_height(image);
    }

    void set_cairo_filter(cairo_filter_t _filter){
        // CAIRO_FILTER_NEAREST
        cairo_pattern_set_filter (cairo_get_source (surface->cr), _filter);
    }

    void draw_image() {

        d_xywh = surface->translate_xywh(xywh);
        d_xywh.w /= resolution.x;
        d_xywh.h /= resolution.y;
        
        cairo_save(surface->cr);

        cairo_scale(surface->cr, d_xywh.w, d_xywh.h);

        if(xflip or yflip){
            cairo_matrix_t reflection_matrix; 
            cairo_matrix_init_identity(&reflection_matrix);
            if(xflip){
                reflection_matrix.xx = -1.0;
                d_xywh.x *= -1.0;
            }
            if(yflip){
                reflection_matrix.yy = -1.0;
                d_xywh.y *= -1.0;
            }

            cairo_transform(surface->cr, &reflection_matrix);
        }


        cairo_set_source_surface(surface->cr, image,
                                 d_xywh.x / d_xywh.w - resolution.x * pivot.x,
                                 d_xywh.y / d_xywh.h - resolution.y * pivot.y);
        set_cairo_filter(casp_def_image_filter);

        cairo_scale(surface->cr, 1 / d_xywh.w, 1 / d_xywh.h);
        
        cairo_paint(surface->cr);


        cairo_restore(surface->cr);

        
        if (rect)
            draw_rect();
        if (stroke)
            draw_stroke(this);
    }
};