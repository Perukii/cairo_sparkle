
casp_surface * casp_default_surface_target = NULL;

class casp_object{
public:
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
      
/*
protected:
     void make_xywh(){
          if(!locked or d_set){
               d_xywh = surface->make(xywh);
          }
     }
*/
};

void casp_default_surface(casp_surface * _surface){
     casp_default_surface_target = _surface;
}