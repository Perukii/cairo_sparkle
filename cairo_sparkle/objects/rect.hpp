


class casp_rect : public casp_object{
public:
     
     casp_xy  <double> pivot;
     
     casp_rgb color;

     casp_rect(double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          xywh.x=_x;
          xywh.y=_y;
          xywh.w=_w;
          xywh.h=_h;
          color =_color;

          pivot.x=_pivx;
          pivot.y=_pivy;
     }

     void draw(casp_surface * _casf){
          cairo_set_source_rgba(_casf->cr, color.r, color.g, color.b, color.a);
          casp_xywh<double> d_xywh = _casf->make(xywh);
          cairo_rectangle(_casf->cr, d_xywh.x-d_xywh.w*pivot.x, d_xywh.y-d_xywh.h*pivot.y,
                              d_xywh.w, d_xywh.h);
          cairo_fill(_casf->cr);
     }

};