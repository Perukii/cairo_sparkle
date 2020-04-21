

// === signals ===

gboolean c_host::mouse_button_press_event(GtkWidget *_widget, GdkEventButton *_event,
                                   gpointer _data) {
    c_host *_host = (c_host *)_data;
    if (_host->get_mouse_button_retain(_event->button) == false) {
        _host->button_sig = _event->button;
        _host->buttons.insert(_event->button);
    }
    return true;
}

gboolean c_host::mouse_button_release_event(GtkWidget *_widget, GdkEventButton *_event,
                                     gpointer _data) {
    c_host *_host = (c_host *)_data;
    _host->buttons.erase(_event->button);
    return true;
}

gboolean c_host::mouse_scroll_event(GtkWidget *_widget, GdkEventScroll *_event,
                             gpointer _data) {
    c_host *_host = (c_host *)_data;
    switch (_event->direction) {
    case GDK_SCROLL_UP:
        _host->scroll = -1;
        break;
    case GDK_SCROLL_DOWN:
        _host->scroll = 1;
        break;
    case GDK_SCROLL_LEFT:
        _host->scroll = 2;
        break;
    case GDK_SCROLL_RIGHT:
        _host->scroll = -2;
        break;
    default:
        break;
    }
    return true;
}

bool c_host::get_mouse_button_press(int _value) {
    return button_sig == _value;
}

bool c_host::get_mouse_button_retain(int _value) {
    return buttons.find(_value) != buttons.end();
}

// === debug ===

#ifdef c_permission_debug

void c_host::debug_mouse_button() {
    if  (buttons.size() > 0)
        std::cout << "mouse_button_code : ";

    for (auto button : buttons) 
        std::cout << button << " ";
    
    if  (scroll != 0)
        std::cout << "scroll : " << scroll;

    if  (buttons.size() > 0 or scroll != 0)
        std::cout << std::endl;
}

#endif
