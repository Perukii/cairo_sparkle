

class c_object {
protected:
    c_surface * surface;

public:
    void set_surface(c_surface *);

};

void c_object::set_surface(c_surface * _surface = c_default_surface_target){
    surface = _surface;
}
