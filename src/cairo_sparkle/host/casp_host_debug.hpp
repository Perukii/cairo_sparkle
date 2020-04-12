
void casp_host::debug_QWEASD(casp_surface * _surface) {
    for (auto key : keys) {
        switch (key) {
        case 113: // q
            _surface->zoom /= 1.05;
            break;
        case 119: // w
            _surface->xy.y -= 0.2;
            break;
        case 101: // e
            _surface->zoom *= 1.05;
            break;
        case 97: // a
            _surface->xy.x -= 0.2;
            break;
        case 115: // s
            _surface->xy.y += 0.2;
            break;
        case 100: // d
            _surface->xy.x += 0.2;
            break;
        }
    }
}

void casp_host::debug_QWEASD(int _layer){
    debug_QWEASD(&surface[_layer]);
}