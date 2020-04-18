
void casp_func_linear(double &_targ, double _goal, double _weigh) {
    if (abs(_targ - _goal) < _weigh)
        _targ = _goal;
    else if (_targ > _goal) {
        _targ -= _weigh;
    } else
        _targ += _weigh;
}

void casp_func_linear(casp_xy<double> &_targ, casp_xy<double> _goal,
                      double _weigh) {
    casp_func_linear(_targ.x, _goal.x, _weigh);
    casp_func_linear(_targ.y, _goal.y, _weigh);
}

void casp_func_linear(casp_xywh<double> &_targ, casp_xywh<double> _goal,
                      double _weigh) {
    casp_func_linear(_targ.x, _goal.x, _weigh);
    casp_func_linear(_targ.y, _goal.y, _weigh);
    casp_func_linear(_targ.w, _goal.w, _weigh);
    casp_func_linear(_targ.h, _goal.h, _weigh);
}

void casp_func_linear(casp_rgb &_targ, casp_rgb _goal, double _weigh) {
    casp_func_linear(_targ.r, _goal.r, _weigh);
    casp_func_linear(_targ.g, _goal.g, _weigh);
    casp_func_linear(_targ.b, _goal.b, _weigh);
    casp_func_linear(_targ.a, _goal.a, _weigh);
}

void casp_func_quadra(double &_targ, double _goal, double _weigh) {
    _targ += (_goal - _targ) * _weigh;
}

void casp_func_quadra(casp_xy<double> &_targ, casp_xy<double> _goal,
                      double _weigh) {
    casp_func_quadra(_targ.x, _goal.x, _weigh);
    casp_func_quadra(_targ.y, _goal.y, _weigh);
}

void casp_func_quadra(casp_xywh<double> &_targ, casp_xywh<double> _goal,
                      double _weigh) {
    casp_func_quadra(_targ.x, _goal.x, _weigh);
    casp_func_quadra(_targ.y, _goal.y, _weigh);
    casp_func_quadra(_targ.w, _goal.w, _weigh);
    casp_func_quadra(_targ.h, _goal.h, _weigh);
}

void casp_func_quadra(casp_rgb &_targ, casp_rgb _goal, double _weigh) {
    casp_func_quadra(_targ.r, _goal.r, _weigh);
    casp_func_quadra(_targ.g, _goal.g, _weigh);
    casp_func_quadra(_targ.b, _goal.b, _weigh);
    casp_func_quadra(_targ.a, _goal.a, _weigh);
}

bool casp_func_point_on_rect(casp_xy<double> _xy, casp_xywh<double> _xywh,
                                casp_xy<double> _pivot = casp_xy<double>(0.5, 0.5)) {
    return (_xy.x >= _xywh.x -_xywh.w * _pivot.x  and
            _xy.x <= _xywh.x +_xywh.w * (1.0 - _pivot.x) ) and
           (_xy.y >= _xywh.y -_xywh.h * _pivot.y  and
            _xy.y <= _xywh.y +_xywh.h * (1.0 - _pivot.y) );
}

uint casp_func_rect_on_rect(casp_xywh<double> _xywha, casp_xywh<double> _xywhb,
                            casp_xy<double> _pivota = casp_xy<double>(0.5, 0.5),
                            casp_xy<double> _pivotb = casp_xy<double>(0.5, 0.5)) {
    return casp_func_point_on_rect(
                casp_xy<double>(_xywha.x -_xywha.w * _pivota.x, 
                                _xywha.y -_xywha.h * _pivota.y)
                , _xywhb, _pivotb)
         + casp_func_point_on_rect(
                casp_xy<double>(_xywha.x +_xywha.w * (1.0 - _pivota.x), 
                                _xywha.y -_xywha.h * _pivota.y)
                , _xywhb, _pivotb)
         + casp_func_point_on_rect(
                casp_xy<double>(_xywha.x +_xywha.w * (1.0 - _pivota.x), 
                                _xywha.y +_xywha.h * (1.0 - _pivota.y))
                , _xywhb, _pivotb)
         + casp_func_point_on_rect(
                casp_xy<double>(_xywha.x -_xywha.w * _pivota.x, 
                                _xywha.y +_xywha.h * (1.0 - _pivota.y))
                , _xywhb, _pivotb);
}