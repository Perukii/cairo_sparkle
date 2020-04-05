
class casp_rect : public casp_object{

public:

     // stroke
     bool rect = false,stroke = false;
     double stroke_w = 0, d_stroke_w;
     casp_rgb color_stroke = casp_rgb_null;
     casp_rgb color_rect;

     casp_rect(double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color_rect=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          setup_rect(_x, _y, _w, _h, _color_rect, _pivx, _pivy);
     }

     void setup_rect(casp_rgb _color_rect=casp_rgb_null){
          color_rect = _color_rect;
     }

     void setup_rect(double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color_rect=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          rect = true;
          xywh.x=_x;
          xywh.y=_y;
          xywh.w=_w;
          xywh.h=_h;
          color_rect =_color_rect;

          pivot.x=_pivx;
          pivot.y=_pivy;
          setup_surface();
     }


     void setup_stroke(double _stroke_w, casp_rgb _color_stroke=casp_rgb_null){
          stroke      = true;
          stroke_w    = _stroke_w;
          color_stroke= _color_stroke;
     }

private:
     void rectangle(){
          cairo_rectangle(surface->cr, d_xywh.x-d_xywh.w*pivot.x, d_xywh.y-d_xywh.h*pivot.y,
                                        d_xywh.w, d_xywh.h);
     }

public:
     void draw_rect(){
          cairo_set_source_rgba(surface->cr, color_rect.r, color_rect.g, color_rect.b, color_rect.a);

          if(translate_allowed()) d_xywh = surface->translate_xywh(xywh);
          rectangle();
          
          cairo_fill(surface->cr);
          if(stroke) draw_stroke();

          d_set = true;
          
     }
     
     void draw_stroke(){
          cairo_set_source_rgba(surface->cr,
                    color_stroke.r, color_stroke.g, color_stroke.b, color_stroke.a);
          rectangle();
          if(translate_allowed()) d_stroke_w = surface->translate_w(stroke_w);
          cairo_set_line_width(surface->cr, d_stroke_w);
          cairo_stroke(surface->cr);
     }

     bool on_point(casp_xy<double> _tar){
          return (_tar.x >= xywh.x-xywh.w*pivot.x and _tar.x <= xywh.x+xywh.w*(1-pivot.x) )
             and (_tar.y >= xywh.y-xywh.h*pivot.y and _tar.y <= xywh.y+xywh.h*(1-pivot.y) );
     }

};
