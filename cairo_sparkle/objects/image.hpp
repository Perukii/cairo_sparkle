
class casp_image : public casp_object{

public:
     cairo_surface_t * image;
     casp_xy<double> resolution;

     casp_image(std::string _file = "", double _x=0, double _y=0, double _w=0, double _h=0,
                    double _pivx=0.5, double _pivy=0.5){
          setup_image(_file, _x, _y, _w, _h, _pivx, _pivy);
     }

     ~casp_image(){ cairo_surface_destroy (image); }

     void setup_image(std::string _file = "", double _x=0, double _y=0, double _w=0, double _h=0,
                    double _pivx=0.5, double _pivy=0.5){
          xywh.x = _x;
          xywh.y = _y;

          if(_file!="") image_register(_file); 

          xywh.w = (_w != casp_auto ? _w:_h/resolution.y*resolution.x);
          xywh.h = (_h != casp_auto ? _h:_w/resolution.x*resolution.y);

          pivot.x = _pivx;
          pivot.y = _pivy;
          setup_surface();
     }

     void image_register(std::string _file){
          image = cairo_image_surface_create_from_png(_file.c_str());
          resolution.x = cairo_image_surface_get_width (image);
          resolution.y = cairo_image_surface_get_height(image);
     }

     void draw_image(){
          if(make_allowed()) d_xywh = surface->make_xywh(xywh);
          d_xywh.w /= resolution.x;
          d_xywh.h /= resolution.y;
               
          cairo_scale(surface->cr, d_xywh.w, d_xywh.h);
          
          cairo_set_source_surface(surface->cr, image, 
                    d_xywh.x/d_xywh.w-resolution.x*pivot.x,
                    d_xywh.y/d_xywh.h-resolution.y*pivot.y);
          
          cairo_paint(surface->cr);
     }

};