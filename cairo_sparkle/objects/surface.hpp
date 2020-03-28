

class casp_surface{

public:
     casp_xy<double> xy, scale;
     double range, zoom = 1;
     cairo_t * cr;
     bool make_norm = casp_make_norm_w;
     std::set<uint> keys;
     
     casp_surface(double _x=0, double _y=0, double _w=0, double _h=0,
                    double _range=10){
          xy.x=_x;
          xy.y=_y;
          scale.x = _w;
          scale.y = _h;
          range =_range;
          keys.clear();
     }

     void fill_white(){
          cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);

          cairo_rectangle(cr, 0, 0, scale.x+1, scale.y+1);
          cairo_fill(cr);
     }

     casp_xywh<double> make_xywh(casp_xywh<double> _xywh){
          casp_xywh<double> result;
          result.x = make_x(_xywh.x);
          result.y = make_y(_xywh.y);
          result.w = make_w(_xywh.w);
          result.h = make_h(_xywh.h);
          return result;
     }

     double make_x(double _tar){
          double result;
          result = (_tar-xy.x)*
                         (make_norm == casp_make_norm_w ? scale.x:scale.y)/range*zoom+scale.x*0.5;
          return result;
     }

     double make_y(double _tar){
          double result;
          result = (_tar-xy.y)*
                         (make_norm == casp_make_norm_w ? scale.x:scale.y)/range*zoom+scale.y*0.5;
          return result;
     }

     double make_w(double _tar){
          double result;
          result = _tar*
                    (make_norm == casp_make_norm_w ? scale.x:scale.y)/range*zoom;
          return result;
     }

     double make_h(double _tar){
          double result;
          result = _tar*
                    (make_norm == casp_make_norm_w ? scale.x:scale.y)/range*zoom;
          return result;
     }


};

