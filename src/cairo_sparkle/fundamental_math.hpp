
template <class MAIN> class casp_xy {

  public:
    MAIN x, y;

    casp_xy(MAIN _x = 0, MAIN _y = 0) {
        x = _x;
        y = _y;
    }

    template <class TARG> casp_xy(casp_xy<TARG> _p) {
        x = _p.x;
        y = _p.y;
    }

    casp_xy operator+(casp_xy _p) { return casp_xy(x + _p.x, y + _p.y); }
    casp_xy operator-(casp_xy _p) { return casp_xy(x - _p.x, y - _p.y); }
    casp_xy operator*(casp_xy _p) { return casp_xy(x * _p.x, y * _p.y); }
    casp_xy operator/(casp_xy _p) { return casp_xy(x / _p.x, y / _p.y); }

    casp_xy operator+=(casp_xy _p) {
        x += _p.x;
        y += _p.y;
        return *this;
    }
    casp_xy operator-=(casp_xy _p) {
        x -= _p.x;
        y -= _p.y;
        return *this;
    }
    casp_xy operator*=(casp_xy _p) {
        x *= _p.x;
        y *= _p.y;
        return *this;
    }
    casp_xy operator/=(casp_xy _p) {
        x /= _p.x;
        y /= _p.y;
        return *this;
    }

    bool operator==(casp_xy _p) { return x == _p.x and y == _p.y; }
    bool operator!=(casp_xy _p) { return x != _p.x or y != _p.y; }

    friend std::ostream &operator<<(std::ostream &opt, casp_xy _p) {
        return opt << '[' << _p.x << ':' << _p.y << ']';
    }
};

template <class MAIN> class casp_xywh : public casp_xy<MAIN> {
  public:
    MAIN w, h;

    casp_xywh(MAIN _x = 0, MAIN _y = 0, MAIN _w = 0, MAIN _h = 0) {
        this->x = _x;
        this->y = _y;
        w = _w;
        h = _h;
    }

    casp_xywh operator+(casp_xywh _p) {
        return casp_xywh(this->x + _p.x, this->y + _p.y, w + _p.w, h + _p.h);
    }
    casp_xywh operator-(casp_xywh _p) {
        return casp_xywh(this->x - _p.x, this->y - _p.y, w - _p.w, h - _p.h);
    }
    casp_xywh operator*(casp_xywh _p) {
        return casp_xywh(this->x * _p.x, this->y * _p.y, w * _p.w, h * _p.h);
    }
    casp_xywh operator/(casp_xywh _p) {
        return casp_xywh(this->x / _p.x, this->y / _p.y, w / _p.w, h / _p.h);
    }

    casp_xywh operator+=(casp_xywh _p) {
        this->x += _p.x;
        this->y += _p.y;
        w += _p.w;
        h += _p.h;
        return *this;
    }
    casp_xywh operator-=(casp_xywh _p) {
        this->x -= _p.x;
        this->y -= _p.y;
        w -= _p.w;
        h -= _p.h;
        return *this;
    }
    casp_xywh operator*=(casp_xywh _p) {
        this->x *= _p.x;
        this->y *= _p.y;
        w *= _p.w;
        h *= _p.h;
        return *this;
    }
    casp_xywh operator/=(casp_xywh _p) {
        this->x /= _p.x;
        this->y /= _p.y;
        w /= _p.w;
        h /= _p.h;
        return *this;
    }

    bool operator==(casp_xywh _p) {
        return this->x == _p.x and this->y == _p.y and w == _p.w and h == _p.h;
    }
    bool operator!=(casp_xywh _p) {
        return this->x != _p.x or this->y != _p.y or w != _p.w or h != _p.h;
    }

    operator casp_xy<MAIN>() const { return casp_xy<MAIN>(this->x, this->y); }

    friend std::ostream &operator<<(std::ostream &opt, casp_xywh _p) {
        return opt << '[' << _p.x << ':' << _p.y << ':' << _p.w << ':' << _p.h
                   << ']';
    }
};

class casp_rgb {
  public:
    double r, g, b, a;

    casp_rgb(double _r = 0, double _g = 0, double _b = 0, double _a = 1) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    casp_rgb operator+(casp_rgb _p) {
        return casp_rgb(r + _p.r, g + _p.g, b + _p.b, a + _p.a);
    }
    casp_rgb operator-(casp_rgb _p) {
        return casp_rgb(r - _p.r, g - _p.g, b - _p.b, a - _p.a);
    }
    casp_rgb operator*(casp_rgb _p) {
        return casp_rgb(r * _p.r, g * _p.g, b * _p.b, a * _p.a);
    }
    casp_rgb operator/(casp_rgb _p) {
        return casp_rgb(r / _p.r, g / _p.g, b / _p.b, a / _p.a);
    }

    casp_rgb operator+=(casp_rgb _p) {
        r += _p.r;
        g += _p.g;
        b += _p.b;
        a += _p.a;
        return *this;
    }
    casp_rgb operator-=(casp_rgb _p) {
        r -= _p.r;
        g -= _p.g;
        b -= _p.b;
        a -= _p.a;
        return *this;
    }
    casp_rgb operator*=(casp_rgb _p) {
        r *= _p.r;
        g *= _p.g;
        b *= _p.b;
        a *= _p.a;
        return *this;
    }
    casp_rgb operator/=(casp_rgb _p) {
        r /= _p.r;
        g /= _p.g;
        b /= _p.b;
        a /= _p.a;
        return *this;
    }

    bool operator==(casp_rgb _p) {
        return r == _p.r and g == _p.g and b == _p.b and a == _p.a;
    }
    bool operator!=(casp_rgb _p) {
        return r != _p.r or g != _p.g or b != _p.b or a != _p.a;
    }

    friend std::ostream &operator<<(std::ostream &opt, casp_rgb _p) {
        return opt << '[' << _p.r << ':' << _p.g << ':' << _p.b << ':' << _p.a
                   << ']';
    }
};
