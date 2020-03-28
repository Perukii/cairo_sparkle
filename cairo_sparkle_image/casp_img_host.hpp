
void casp_img_init(int _argc, char ** _argv){
     gtk_init(&_argc, &_argv);
}

class casp_img_host{
public :
     casp_surface surface;
     std::string file_write;
     cairo_surface_t * image;

     ~casp_img_host(){
          cairo_surface_destroy (image);
     }

     void image_scale(int _w=-1, int _h=-1){
          casp_xy<double> _scale = surface.scale;
          
          if(_w!=-1) _scale.x = _w;
          if(_h!=-1) _scale.y = _h;

          surface.scale = _scale;
          
     }

     void setup(int _w=-1, int _h=-1){
          image_scale(_w,_h);
          image = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, surface.scale.x, surface.scale.y);
          surface.cr = cairo_create(image);
          
     }

     void write(){
          casp_main();
          cairo_surface_flush(image);
          cairo_surface_write_to_png(image,"/home/tada/Documents/Codes/CASP/cairo_sparkle/test.png");
     }


};