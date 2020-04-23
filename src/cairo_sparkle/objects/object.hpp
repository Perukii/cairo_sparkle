

class casp_object {
protected:
    casp_surface * surface;

public:
    void set_surface(casp_surface *);

};

void casp_object::set_surface(casp_surface * _surface = casp_default_surface_target){
    surface = _surface;
}
