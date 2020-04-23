
class casp_subrect : public casp_rect {
public:
    void setup_fill_color(casp_rgb);

    void enable_fill_color();
    void disable_fill_color();
};

void casp_subrect::setup_fill_color(casp_rgb _color_rect = casp_rgb_null){

    enable_rect();
    color_rect = _color_rect; 
    set_surface();
    
}

void casp_subrect::enable_fill_color() { enable_rect(); };
void casp_subrect::disable_fill_color() { disable_rect(); };