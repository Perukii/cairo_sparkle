
gboolean casp_host::motion_notify_event(GtkWidget *_widget, GdkEventMotion *_event,
                                    gpointer _data) {
    casp_host *_host = (casp_host *)_data;
    casp_surface *_surface = &_host->surface[0];
    _host->mouse_pos.x = _surface->re_transform_x(_event->x);
    _host->mouse_pos.y = _surface->re_transform_y(_event->y);
    return true;
}
