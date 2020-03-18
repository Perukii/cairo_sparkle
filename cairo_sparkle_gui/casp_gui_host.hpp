
void casp_gui_main(cairo_t * );

static gboolean
keyEvent(GtkWidget * _widget, GdkEventKey * _event, gpointer _user_data){
     //std::cout<<event->keyval<<std::endl;
     return true;
}

static gboolean
drawEvent(GtkWidget * _widget, cairo_t * _cr, gpointer _data){
     casp_gui_main(_cr);
     return true;
}


class casp_gui_host{

private:
     GtkWidget * window;
     GtkWidget * canvas;
public :
     int w = 100, h = 100;

     void window_scale(int _w=-1, int _h=-1){
          if(_w!=-1) w = _w;
          if(_h!=-1) h = _h;
          gtk_window_set_default_size((GtkWindow *)window, w, h);
     }

     casp_gui_host(){

          // ~~~ definition ~~~

          window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
          canvas = gtk_drawing_area_new();

          gtk_widget_set_app_paintable(canvas, true);
          gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

          // ~~~ signals ~~~
          
          g_signal_connect(window, "key-press-event"    , G_CALLBACK(keyEvent) , NULL);
          g_signal_connect(canvas, "draw"               , G_CALLBACK(drawEvent), NULL);
          g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit),NULL);
          
          // ~~~ CSS setting ~~~
          
          GtkCssProvider * provider = gtk_css_provider_new ();
          GdkDisplay *     display;
          GdkScreen *      screen;

          display = gdk_display_get_default ();
          screen = gdk_display_get_default_screen (display);
          gtk_style_context_add_provider_for_screen (screen,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

          gsize bytes_written, bytes_read;
          const gchar * home = "/home/tada/Documents/Codes/CASP/cairo_sparkle/cairo_sparkle_gui/casp_gui_style.css";
          GError * error = 0;

          gtk_css_provider_load_from_path (provider,g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),NULL);
          g_object_unref (provider);

          // ---

          gtk_container_add(GTK_CONTAINER(window), canvas);
     }

     void run(){
          window_scale();
          gtk_widget_show_all(window);
          gtk_main();
     }
};
