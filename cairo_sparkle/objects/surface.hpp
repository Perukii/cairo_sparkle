

class casp_surface{

public:
     casp_xy<double> xy, scale, scale_ratio;
     double range, zoom = 1;
     cairo_t * cr;
     std::set<uint> keys;
     
     casp_surface(double _x=0, double _y=0,
                    double _range=10){
          xy.x=_x;
          xy.y=_y;
          range =_range;
          keys.clear();
          set_scale_ratio();
     }

     void set_scale_ratio(double _x = 1, double _y = 1){
          scale_ratio.x = _x;
          scale_ratio.y = _y;
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
          result = (_tar-xy.x)*scale.x/range*zoom+scale.x*0.5;
          return result;
     }

     double make_y(double _tar){
          double result;
          result = (_tar-xy.y)*scale.y/range*zoom+scale.y*0.5;
          return result;
     }

     double make_w(double _tar){
          double result;
          result = _tar*scale.x/range*zoom/scale_ratio.x*scale_ratio.y;
          return result;
     }

     double make_h(double _tar){
          double result;
          result = _tar*scale.y/range*zoom;
          return result;
     }


};

