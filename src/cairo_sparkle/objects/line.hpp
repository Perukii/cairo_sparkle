
class c_line : public c_object {
private:
    class c_line_path;
    class c_line_property;

public:

    std::vector<c_line_path> path;
    std::vector<c_line_property> property;

    void setup_line(casp_xy<double>, double, casp_rgb);
    void add_line(casp_xy<double>);
    void switch_width(double);
    void switch_color(casp_rgb);
    void switch_property(double, casp_rgb);
    void close_path();
    void draw_line();

private:
    void set_path(casp_xy<double>);
};

class c_line::c_line_path {
public:
    casp_xy<double> xy;
    uint property;
};

class c_line::c_line_property {
public:
    double w;
    casp_rgb color_line;

    void activate(c_surface * _surface){
        cairo_set_line_width(_surface->cr, _surface->transform_w(w));
        _surface->set_color(color_line);
    }
};

void c_line::setup_line(casp_xy<double> _xy, double _w = 0,
                    casp_rgb _color_line = casp_rgb_null){
    path.clear();
    property.clear();
    
    switch_property(_w, _color_line);
    set_path(_xy);

    set_surface();
}

void c_line::add_line(casp_xy<double> _xy){
    set_path(_xy);
}


void c_line::switch_width(double _w){
    switch_property(_w, property.back().color_line);
}

void c_line::switch_color(casp_rgb _color_line){
    switch_property(property.back().w, _color_line);
}

void c_line::switch_property(double _w, casp_rgb _color_line){

    c_line_property tar;
    tar.w = _w;
    tar.color_line = _color_line;

    property.push_back(tar);

}

void c_line::set_path(casp_xy<double> _xy){

    c_line_path tar;
    tar.xy = casp_xy<double>(_xy);
    tar.property = property.size()-1;

    path.push_back(tar);

}

void c_line::close_path(){
    set_path(path[0].xy);
}

void c_line::draw_line(){

    if(surface == NULL) return;

    c_line_path d_path, d_b_path;

    for(int i = 0; i<path.size(); i++){

        if(i > 0 and path[i-1].property != path[i].property){
            cairo_stroke(surface->cr);
            property[path[i].property].activate(surface);
            cairo_move_to(surface->cr, d_path.xy.x, d_path.xy.y);
        }

        d_path.xy.x = surface->transform_x(path[i].xy.x);
        d_path.xy.y = surface->transform_y(path[i].xy.y);
        
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
