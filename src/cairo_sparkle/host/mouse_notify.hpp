
gboolean c_host::motion_notify_event(GtkWidget *_widget, GdkEventMotion *_event,
                                    gpointer _data) {
    c_host *_host = (c_host *)_data;
    c_surface *_surface = &_host->surface[0];
    _host->mouse_pos.x = _surface->re_transform_x(_event->x);
    _host->mouse_pos.y = _surface->re_transform_y(_event->y);
    return true;
}
