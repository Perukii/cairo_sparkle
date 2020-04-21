

// === signals ===

gboolean c_host::key_press_event(GtkWidget *_widget, GdkEventKey *_event,
                                gpointer _data) {
    c_host *_host = (c_host *)_data;
    if (_host->get_key_retain(_event->keyval) == false) {
        _host->key_sig = _event->keyval;
        _host->keys.insert(_event->keyval);
    }
    return true;
}

gboolean c_host::key_release_event(GtkWidget *_widget, GdkEventKey *_event,
                                  gpointer _data) {
    c_host *_host = (c_host *)_data;
    _host->keys.erase(_event->keyval);
    return true;
}

// === functions ===

bool c_host::get_key_press(int _value) {
    return key_sig == _value;
}

bool c_host::get_key_retain(int _value) {
    return keys.find(_value) != keys.end();
}

// === debug ===

#ifdef c_permission_debug

void c_host::debug_key() {
    for (auto key : keys) {
        std::cout << key << " ";
    }
    if (keys.size() > 0)
        std::cout << std::endl;
}


void c_host::debug_QWEASD(uint _layer){
    for (auto key : keys) {
        switch (key) {
        case 113: // q
            surface[_layer].scale /= 1.05;
            break;
        case 119: // w
            surface[_layer].xywh.y -= 0.2;
            break;
        case 101: // e
            surface[_layer].scale *= 1.05;
            break;
        case 97: // a
            surface[_layer].xywh.x -= 0.2;
            break;
        case 115: // s
            surface[_layer].xywh.y += 0.2;
            break;
        case 100: // d
            surface[_layer].xywh.x += 0.2;
            break;
        }
    }
}

#endif
