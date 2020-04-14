
class casp_line : public casp_object {
  private:
    class casp_line_path {
      public:
        casp_xy<double> xy;
        uint property;
    };

    class casp_line_property {
      public:
        double w;
        casp_rgb color_line;

        void activate(casp_surface * _surface){
            cairo_set_line_width(_surface->cr, _surface->translate_w(w));
            cairo_set_source_rgba(_surface->cr, color_line.r, color_line.g,
                                  color_line.b, color_line.a);
        }
    };

  public:
    std::vector<casp_line_path> path;
    std::vector<casp_line_property> property;

    void setup_line(double _w = 0, double _x = 0, double _y = 0,
                     casp_rgb _color_line = casp_rgb_null){
        path.clear();
        property.clear();
        
        switch_property(_w, _color_line);
        set_path(_x, _y);

        set_surface();
    }

    void add_line(double _x = 0, double _y = 0){
        set_path(_x, _y);
    }

    void draw_line(){
        casp_line_path d_path, d_b_path;

        for(int i = 0; i<path.size(); i++){

            if(i > 0 and path[i-1].property != path[i].property){
                cairo_stroke(surface->cr);
                property[path[i].property].activate(surface);
                cairo_move_to(surface->cr, d_path.xy.x, d_path.xy.y);
            }

            d_path.xy.x = surface->translate_x(path[i].xy.x);
            d_path.xy.y = surface->translate_y(path[i].xy.y);
            
            if(i > 0){
                cairo_line_to(surface->cr, d_path.xy.x, d_path.xy.y);
            }
            else{
                property[path[i].property].activate(surface);
                cairo_move_to(surface->cr, d_path.xy.x, d_path.xy.y);
            }
        }
        cairo_stroke(surface->cr);
    }

    void switch_width(double _w){
        switch_property(_w, property.back().color_line);
    }

    void switch_color(casp_rgb _color_line){
        switch_property(property.back().w, _color_line);
    }

    void switch_property(double _w, casp_rgb _color_line){

        casp_line_property tar;
        tar.w = _w;
        tar.color_line = _color_line;

        property.push_back(tar);

    }

  private:
    void set_path(double _x, double _y){

        casp_line_path tar;
        tar.xy = casp_xy<double>(_x, _y);
        tar.property = property.size()-1;

        path.push_back(tar);

    }

};