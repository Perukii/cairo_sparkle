
void casp_gui_main();

void casp_gui_init(int _argc, char ** _argv){
     gtk_init(&_argc, &_argv);
}


static gboolean
key_press_event(GtkWidget * _widget, GdkEventKey * _event, gpointer _data){
     casp_surface * _surface = (casp_surface * )_data;
     //_surface -> key = _event->keyval;
     _surface -> keys.insert(_event->keyval);

     return true;
}

static gboolean
key_release_event(GtkWidget * _widget, GdkEventKey * _event, gpointer _data){
     casp_surface * _surface = (casp_surface * )_data;
     //_surface -> key = _event->keyval;
     _surface -> keys.erase(_event->keyval);
     return true;
}

static gboolean
draw_event(GtkWidget * _widget, cairo_t * _cr, gpointer _data){
     casp_surface * _surface = (casp_surface * )_data;
     _surface -> cr = _cr;
     casp_gui_main();
     return true;
}

static gboolean
loop_event(GtkWidget * widget){
     
     gtk_widget_queue_draw(widget);
     return true;
}

class casp_gui_host{

private:
     GtkWidget * window;
     GtkWidget * canvas;

public :
     casp_surface surface;

     void window_scale(int _w=-1, int _h=-1){
          
          if(_w!=-1) surface.resolution.x = _w;
          if(_h!=-1) surface.resolution.y = _h;
          gtk_window_set_default_size((GtkWindow *)window, surface.resolution.x, surface.resolution.y);

     }

     void setup(int _w=-1, int _h=-1){
          
          // ~~~ definition ~~~

          window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
          canvas = gtk_drawing_area_new();

          gtk_widget_set_app_paintable(canvas, true);
          gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

          // ~~~ signals ~~~
          
          g_signal_connect(window, "key-press-event",     G_CALLBACK(key_press_event),     &surface);
          g_signal_connect(window, "key-release-event",   G_CALLBACK(key_release_event),   &surface);
          g_signal_connect(canvas, "draw",                G_CALLBACK(draw_event),          &surface);
          g_signal_connect(window, "destroy",             G_CALLBACK(gtk_main_quit),       NULL);

          g_timeout_add(1, (GSourceFunc)loop_event, canvas);
          
          // ~~~ CSS setting ~~~
          
          GtkCssProvider * provider = gtk_css_provider_new ();
          GdkDisplay *     display;
          GdkScreen *      screen;

          display = gdk_display_get_default ();
          screen = gdk_display_get_default_screen (display);
          gtk_style_context_add_provider_for_screen (screen,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

          gsize bytes_written, bytes_read;
          const gchar * home = "cairo_sparkle_gui/casp_gui_style.css";
          GError * error = 0;

          gtk_css_provider_load_from_path (provider,g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),NULL);
          g_object_unref (provider);

          // ---

          gtk_container_add(GTK_CONTAINER(window), canvas);

          window_scale(_w,_h);
     }

     void run(){
          
          gtk_widget_show_all(window);
          gtk_main();
     }
};
