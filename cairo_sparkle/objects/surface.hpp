
class casp_surface{

public:
     casp_xy<double> xy, resolution;
     double range, zoom = 1;
     cairo_t * cr;
     std::set<uint> keys;
     
     casp_surface(double _x=0, double _y=0,
                    double _range=10){
          xy.x=_x;
          xy.y=_y;
          range =_range;
          keys.clear();
     }

     casp_xywh<double> make(casp_xywh<double> _obj){
          casp_xywh<double> result;
          result.x = (_obj.x-xy.x)*resolution.x/range*zoom+resolution.x*0.5;
          result.y = (_obj.y-xy.y)*resolution.x/range*zoom+resolution.x*0.5;
          result.w = _obj.w       *resolution.x/range*zoom;
          result.h = _obj.h       *resolution.x/range*zoom;
          return result;
     }

     double make_w(double _tar){
          double result;
          result = _tar*resolution.x/range*zoom;
          return result;
     }
};