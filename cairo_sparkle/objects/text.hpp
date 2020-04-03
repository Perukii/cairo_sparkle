



class casp_text : public casp_rect{
public:
     std::string text;
     casp_rgb color_text;

     casp_text(std::string _text="", double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color_text=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          setup_text(_text, _x, _y, _w, _h, _color_text, _pivx, _pivy);
     }
     
     void setup_text(std::string _text="", double _x=0, double _y=0, double _w=0, double _h=0,
                    casp_rgb _color_text=casp_rgb_null,
                    double _pivx=0.5, double _pivy=0.5){
          text = _text;
          xywh.x=_x;
          xywh.y=_y;
          xywh.w=_w;
          xywh.h=_h;
          color_text =_color_text;
          pivot.x=_pivx;
          pivot.y=_pivy;
          setup_surface();
     }

     void draw_text(){

          if(rect) draw_rect();
          
          cairo_set_source_rgba(surface->cr, color_text.r, color_text.g, color_text.b, color_text.a);

          cairo_select_font_face(surface->cr, "Sans",
               CAIRO_FONT_SLANT_NORMAL,
               CAIRO_FONT_WEIGHT_NORMAL);

          cairo_text_extents_t extents;

          cairo_text_extents (surface->cr, text.c_str(), &extents);

          double d_extent, d_font;
          
          d_extent = (double)extents.width
                         /(double)extents.height;

          if(xywh.h==casp_auto){
               xywh.h = xywh.w/d_extent;
          }
          
          if(xywh.w==casp_auto){
               xywh.w = xywh.h*d_extent;
          }

          if(make_allowed()){
               d_xywh = surface->make_xywh(xywh);
          }

          d_font   = d_xywh.h;

          cairo_set_font_size(surface->cr,d_font);
          cairo_move_to(surface->cr, d_xywh.x-d_font*d_extent*pivot.x,
                         d_xywh.y+d_font*(1-pivot.y));
          cairo_show_text(surface->cr, text.c_str());

          if(stroke)draw_stroke();
     }



};