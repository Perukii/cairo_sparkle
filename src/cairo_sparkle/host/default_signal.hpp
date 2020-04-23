
gboolean casp_host::loop_event(GtkWidget *widget) {
    gtk_widget_queue_draw(widget);
    return true;
}

gboolean casp_host::draw_event(GtkWidget *_widget, cairo_t *_cr, gpointer _data) {

    casp_host *_host = (casp_host *)_data;

    for(int i=0;i<_host->layer_size;i++){
        _host->surface[i].cr = _cr;
    }

    if(_host->background_color != casp_rgb_null)
        _host->surface[0].draw_background(_host->background_color);

    _host->main_loop();

    _host->reset_value();

    return true;//_host->output_mode == false;
}

gboolean casp_host::window_resize_event(GtkWidget *_widget,
                                    GdkRectangle *_allocation, gpointer _data) {
    int w, h;
    gtk_window_get_size((GtkWindow *)_widget, &w, &h);
    casp_host *_host = (casp_host *)_data;
    _host->window_scale(casp_xy<double>(w, h));
    return true;
}

gboolean casp_host::window_state_event(GtkWidget *_widget,
                                    GdkEventWindowState *_event, gpointer _data){
    casp_host *_host = (casp_host *)_data;
    if(_host->fullscreen)gtk_window_fullscreen  ( (GtkWindow *)_host->window);
    return true;
}