

class casp_img_host{
public :
     casp_surface * surface;
     cairo_surface_t * image;

     ~casp_img_host(){
          cairo_surface_destroy (image);
     }

     void image_scale(int _w=-1, int _h=-1){
          casp_xy<double> _scale = surface -> scale;
          
          if(_w!=-1) _scale.x = _w;
          if(_h!=-1) _scale.y = _h;

          surface -> scale = _scale;
          
     }

     void setup(casp_surface * _surface, int _w=-1, int _h=-1){
          surface = _surface;
          image_scale(_w,_h);
          image = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, surface -> scale.x, surface -> scale.y);
          surface -> cr = cairo_create(image);
     }

     void write_png(std::string _file){
          cairo_surface_flush(image);
          cairo_surface_write_to_png(image, _file.c_str());
          std::cout<<"Wrote to png : "<<_file<<std::endl;
     }


};