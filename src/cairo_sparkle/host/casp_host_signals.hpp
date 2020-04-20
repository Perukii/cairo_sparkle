
static gboolean key_press_event(GtkWidget *_widget, GdkEventKey *_event,
                                gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    if (_host->get_key_retain(_event->keyval) == false) {
        _host->skey = _event->keyval;
        _host->keys.insert(_event->keyval);
    }
    return true;
}

static gboolean key_release_event(GtkWidget *_widget, GdkEventKey *_event,
                                  gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    _host->keys.erase(_event->keyval);
    return true;
}

static gboolean draw_event(GtkWidget *_widget, cairo_t *_cr, gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    for(int i=0;i<_host->layer_size;i++){
        _host->surface[i].cr = _cr;
    }

    casp_draw();
    _host->reset_vals();
    return true;
}

static gboolean window_resize_event(GtkWidget *_widget,
                                    GdkRectangle *_allocation, gpointer _data) {
    int w, h;
    gtk_window_get_size((GtkWindow *)_widget, &w, &h);
    casp_host *_host = (casp_host *)_data;
    _host->def_scale = casp_xy<int>(w,h);
    _host->window_scale();
    return true;
}

static gboolean button_press_event(GtkWidget *_widget, GdkEventButton *_event,
                                   gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    if (_host->get_button_retain(_event->button) == false) {
        _host->sbutton = _event->button;
        _host->buttons.insert(_event->button);
    }
    return true;
}

static gboolean button_release_event(GtkWidget *_widget, GdkEventButton *_event,
                                     gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    _host->buttons.erase(_event->button);
    return true;
}

static gboolean motion_notify_event(GtkWidget *_widget, GdkEventMotion *_event,
                                    gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    casp_surface *_surface = &_host->surface[0];
    _host->mouse_pos.x = _surface->retranslate_x(_event->x);
    _host->mouse_pos.y = _surface->retranslate_y(_event->y);
    return true;
}

static gboolean enter_notify_event(GtkWidget *_widget, GdkEventCrossing *_event,
                                   gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    _host->mouse_pos.x = _event->x;
    _host->mouse_pos.y = _event->y;
    return true;
}

static gboolean scroll_event(GtkWidget *_widget, GdkEventScroll *_event,
                             gpointer _data) {
    casp_host *_host = (casp_host *)_data;
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

static gboolean window_state_event(GtkWidget *_widget, GdkEventWindowState *_event,
                                    gpointer _data){
    casp_host *_host = (casp_host *)_data;
    _host->set_fullscreen_signal();
    return true;
}