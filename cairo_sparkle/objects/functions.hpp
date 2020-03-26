
void casp_func_linear(double & _targ, double _goal, double _weigh){
     if(abs(_targ-_goal)<_weigh) _targ = _goal;
     else if(_targ>_goal){
          _targ -= _weigh;
     }
     else _targ += _weigh;
}

void casp_func_quadra(double & _targ, double _goal, double _weigh){
     _targ += (_goal-_targ)*_weigh;
}


