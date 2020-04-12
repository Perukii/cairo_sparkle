
class casp_circle : public casp_object, public casp_stroke {
public:
    casp_xy<double> center, d_center;
    double rx, ry, d_rx, d_ry;
    casp_rgb color_circle;
    bool circle = false;
    
    void setup_circle(double _x = 0, double _y = 0, double _r = 0,
                    casp_rgb _color_circle = casp_rgb_null){

        circle = true;
        center = casp_xy<double>(_x, _y);
        rx = _r;
        ry = _r;
        color_circle = _color_circle;
        set_surface();
    }

    //void setup_circle_advance(); //随時実装予定

    void draw_circle(){
        
        d_rx = surface->translate_w(rx);
        d_ry = surface->translate_h(ry);
        d_center.x = surface->translate_x(center.x);
        d_center.y = surface->translate_y(center.y);
        
        set_color(color_circle);

        cairo_arc(surface->cr, d_center.x, d_center.y, d_rx, 0.0, G_PI * 2.0);

        if (stroke){
            cairo_fill_preserve(surface->cr);
            draw_stroke(this);
        }
        else if (circle)
            cairo_fill(surface->cr);

    }

};