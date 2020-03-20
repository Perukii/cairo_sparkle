
class casp_surface{
public:
     casp_xy<double> xy, resolution;
     double range;
     cairo_t * cr;

     casp_surface(double _x=0, double _y=0,
                    double _range=10){
          xy.x=_x;
          xy.y=_y;
          range =_range;
     }

     casp_xywh<double> make(casp_xywh<double> _obj){
          casp_xywh<double> result;
          result.x = (_obj.x-xy.x+range*0.5)*resolution.x/range;
          result.y = (_obj.y-xy.y+range*0.5)*resolution.x/range;
          result.w = _obj.w                 *resolution.x/range;
          result.h = _obj.h                 *resolution.x/range;
          return result;
     }
};