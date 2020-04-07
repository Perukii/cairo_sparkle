

class casp_object {
  public:
    casp_surface *surface;
    bool locked, d_set;

    casp_object() {
        locked = false;
        d_set = false;
    }

    void lock() { locked = true; }

    void unlock() { locked = false; }

    void setup_surface(casp_surface *_surface = casp_default_surface_target) {
        surface = _surface;
    }

    bool translate_allowed() { return !(locked and d_set); }
};
