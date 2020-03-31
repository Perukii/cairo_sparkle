
void casp_func_linear(double & _targ, double _goal, double _weigh){
     if(abs(_targ-_goal)<_weigh) _targ = _goal;
     else if(_targ>_goal){
          _targ -= _weigh;
     }
     else _targ += _weigh;
}

void casp_func_linear(casp_xy<double> & _targ, casp_xy<double> _goal, double _weigh){
     casp_func_linear(_targ.x,_goal.x,_weigh);
     casp_func_linear(_targ.y,_goal.y,_weigh);
}

void casp_func_linear(casp_xywh<double> & _targ, casp_xywh<double> _goal, double _weigh){
     casp_func_linear(_targ.x,_goal.x,_weigh);
     casp_func_linear(_targ.y,_goal.y,_weigh);
     casp_func_linear(_targ.w,_goal.w,_weigh);
     casp_func_linear(_targ.h,_goal.h,_weigh);
}

void casp_func_linear(casp_rgb & _targ, casp_rgb _goal, double _weigh){
     casp_func_linear(_targ.r,_goal.r,_weigh);
     casp_func_linear(_targ.g,_goal.g,_weigh);
     casp_func_linear(_targ.b,_goal.b,_weigh);
     casp_func_linear(_targ.a,_goal.a,_weigh);
}


void casp_func_quadra(double & _targ, double _goal, double _weigh){
     _targ += (_goal-_targ)*_weigh;
}

void casp_func_quadra(casp_xy<double> & _targ, casp_xy<double> _goal, double _weigh){
     casp_func_quadra(_targ.x,_goal.x,_weigh);
     casp_func_quadra(_targ.y,_goal.y,_weigh);
}

void casp_func_quadra(casp_xywh<double> & _targ, casp_xywh<double> _goal, double _weigh){
     casp_func_quadra(_targ.x,_goal.x,_weigh);
     casp_func_quadra(_targ.y,_goal.y,_weigh);
     casp_func_quadra(_targ.w,_goal.w,_weigh);
     casp_func_quadra(_targ.h,_goal.h,_weigh);
}

void casp_func_quadra(casp_rgb & _targ, casp_rgb _goal, double _weigh){
     casp_func_quadra(_targ.r,_goal.r,_weigh);
     casp_func_quadra(_targ.g,_goal.g,_weigh);
     casp_func_quadra(_targ.b,_goal.b,_weigh);
     casp_func_quadra(_targ.a,_goal.a,_weigh);
}




