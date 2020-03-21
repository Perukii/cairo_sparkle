


class casp_rect : public casp_object{
public:
     casp_xy  <double> pivot;
     casp_rgb color_rect;

     // stroke
     bool stroke=false;
     double stroke_w=0;
     casp_rgb color_stroke=casp_rgb_null;

     casp_rect(double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color_rect=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          setup_rect(_x, _y, _w, _h, _color_rect, _pivx, _pivy);
     }

     void setup_rect(double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color_rect=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          xywh.x=_x;
          xywh.y=_y;
          xywh.w=_w;
          xywh.h=_h;
          color_rect =_color_rect;

          pivot.x=_pivx;
          pivot.y=_pivy;
     }

     void setup_stroke(bool _stroke, double _stroke_w, casp_rgb _color_stroke=casp_rgb_null){
          stroke      =_stroke;
          stroke_w    =_stroke_w;
          color_stroke=_color_stroke;
     }

     void draw_rect(casp_surface * _casf, bool strokein = false){
          casp_rgb color = strokein ? color_stroke:color_rect;
          cairo_set_source_rgba(_casf->cr, color.r, color.g, color.b, color.a);

          casp_xywh<double> d_xywh = _casf->make(xywh);
          

          cairo_rectangle(_casf->cr, d_xywh.x-d_xywh.w*pivot.x, d_xywh.y-d_xywh.h*pivot.y,
                              d_xywh.w, d_xywh.h);
          if(strokein){
               double d_stroke_w =_casf->make_w(stroke_w);
               cairo_set_line_width(_casf->cr, d_stroke_w);
               cairo_stroke(_casf->cr);
          }
          else{
               cairo_fill(_casf->cr);
               if(stroke) draw_rect(_casf, true);
          }
          
     }
};
