
casp_surface * casp_default_surface_target = NULL;

class casp_object{

public:
     casp_xy  <double> pivot;
     casp_rgb color;
     casp_xywh<double> xywh;

protected:
     casp_surface * surface;
     casp_xywh<double> d_xywh;
     bool locked, d_set;

public:
     casp_object(){
          locked = false;
          d_set = false;
     }
     
     void lock(){ locked = true; }

     void unlock(){ locked = false; }

     void setup_surface(casp_surface * _surface = casp_default_surface_target){
          surface = _surface;
     }

protected:
     bool make_allowed(){
          return !(locked and d_set);
     }

public:
     
};

void casp_default_surface(casp_surface * _surface){
     casp_default_surface_target = _surface;
}