

static gboolean
key_press_event(GtkWidget * _widget, GdkEventKey * _event, gpointer _data);

static gboolean
key_release_event(GtkWidget * _widget, GdkEventKey * _event, gpointer _data);

static gboolean
draw_event(GtkWidget * _widget, cairo_t * _cr, gpointer _data);

static gboolean
window_resize_event(GtkWidget * _widget, GdkRectangle * _allocation, gpointer _data);


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
     uint skey;
     std::set<uint> keys;

     casp_gui_host(){
          keys.clear();
     }
     
     void window_scale(int _w=-1, int _h=-1){
          casp_xy<double> _scale = surface.scale;
          
          if(_w!=-1) _scale.x = _w;
          if(_h!=-1) _scale.y = _h;
          
          surface.scale=_scale;
          gtk_window_set_default_size((GtkWindow *)window, surface.scale.x, surface.scale.y);
          
     }

     void setup(int _w=-1, int _h=-1){
          
          // ~~~ definition ~~~

          window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
          canvas = gtk_drawing_area_new();

          gtk_widget_set_app_paintable(canvas, true);
          gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

          // ~~~ signals ~~~
          
          g_signal_connect(window, "key-press-event",     G_CALLBACK(key_press_event),     this);
          g_signal_connect(window, "key-release-event",   G_CALLBACK(key_release_event),   this);
          g_signal_connect(window, "draw",                G_CALLBACK(draw_event),          this);
          g_signal_connect(window, "size_allocate"     ,  G_CALLBACK(window_resize_event), this);
          g_signal_connect(window, "destroy",             G_CALLBACK(gtk_main_quit),       NULL);

          g_timeout_add(1, (GSourceFunc)loop_event, canvas);
          
          gtk_container_add(GTK_CONTAINER(window), canvas);
          
          window_scale(_w,_h);
     }

     void run(){
          gtk_widget_show_all(window);
          gtk_main();
     }

     bool key_retain(int value){
          return keys.find(value)!=keys.end();
     }

     bool key_press(int value){
          bool result = ( skey == value );
          skey = 0;
          return result;
     }

     void key_debug(){
          for(auto key:keys){
               std::cout<<key<<" ";
          }
          if(keys.size()) std::cout<<std::endl;
     }

     void debug_QWEASD(){
          for(auto key:keys){
               switch(key){
                    case 113: // q
                         surface.zoom/=1.05;
                         break;
                    case 119: // w
                         surface.xy.y-=0.1;
                         break;
                    case 101: // e
                         surface.zoom*=1.05;
                         break;
                    case 97 : // a
                         surface.xy.x-=0.1;
                         break;
                    case 115: // s
                         surface.xy.y+=0.1;
                         break;
                    case 100: // d
                         surface.xy.x+=0.1;
                         break;
               }
          }
     }
};

static gboolean
key_press_event(GtkWidget * _widget, GdkEventKey * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     if(_host -> key_retain(_event->keyval) == false){
          _host -> skey = _event->keyval;
          _host -> keys.insert(_event->keyval);
     }
     return true;
}

static gboolean
key_release_event(GtkWidget * _widget, GdkEventKey * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     _host -> keys.erase(_event->keyval);
     return true;
}


static gboolean
draw_event(GtkWidget * _widget, cairo_t * _cr, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     casp_surface * _surface = &_host->surface;
     _surface -> cr = _cr;
     casp_main();

     return true;
}


static gboolean
window_resize_event(GtkWidget * _widget, GdkRectangle * _allocation, gpointer _data){
     int w,h;
     gtk_window_get_size((GtkWindow*)_widget, &w, &h);
     casp_gui_host * _host = (casp_gui_host * )_data;
     _host -> window_scale(w,h);
     return true;
}

