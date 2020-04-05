
static gboolean
key_press_event (GtkWidget *, GdkEventKey *, gpointer);

static gboolean
key_release_event (GtkWidget *, GdkEventKey *, gpointer);

static gboolean
draw_event (GtkWidget *, cairo_t *, gpointer);

static gboolean
window_resize_event (GtkWidget *, GdkRectangle *, gpointer);

static gboolean
button_press_event (GtkWidget *, GdkEventButton *, gpointer);

static gboolean
button_release_event (GtkWidget *, GdkEventButton *, gpointer);

static gint
motion_notify_event (GtkWidget *, GdkEventMotion *, gpointer);

static gboolean
enter_notify_event (GtkWidget *, GdkEventCrossing *, gpointer);

static gboolean 
scroll_event (GtkWidget *, GdkEventScroll *, gpointer);

static gboolean
loop_event (GtkWidget * widget){
     gtk_widget_queue_draw(widget);
     return true;
}

class casp_gui_host {

private:
     GtkWidget * window;
     GtkWidget * canvas;
     
public :
     casp_surface *  surface; 
     uint            skey, sbutton;
     int             scroll;
     std::set<uint>  keys, buttons;
     casp_xy<double> mouse_pos;

     casp_gui_host(){
          keys.clear();
     }
     
     void window_scale(int _w=-1, int _h=-1){
          casp_xy<double> _scale = surface -> scale;
          
          if(_w!=-1) _scale.x = _w;
          if(_h!=-1) _scale.y = _h;
          
          surface -> set_scale(_scale);
          gtk_window_set_default_size((GtkWindow *)window, surface -> scale.x, surface -> scale.y);
     }

     void setup(casp_surface * _surface ,int _w=-1, int _h=-1, int _norm=casp_translate_norm_w){
          
          surface = _surface;

          // ~~~ definition ~~~

          window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
          canvas = gtk_drawing_area_new();

          gtk_widget_set_app_paintable(canvas, true);
          gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

          // ~~~ signals ~~~
          
          g_signal_connect(window, "key_press_event",     G_CALLBACK(key_press_event),     this);
          g_signal_connect(window, "key_release_event",   G_CALLBACK(key_release_event),   this);
          g_signal_connect(window, "draw",                G_CALLBACK(draw_event),          this);
          g_signal_connect(window, "size_allocate"     ,  G_CALLBACK(window_resize_event), this);
          g_signal_connect(window, "button_press_event",  G_CALLBACK(button_press_event),  this);
          g_signal_connect(window, "button_release_event",G_CALLBACK(button_release_event),this);
          g_signal_connect(window, "motion_notify_event", G_CALLBACK(motion_notify_event), this);
          g_signal_connect(window, "enter_notify_event",  G_CALLBACK(enter_notify_event),  this);
          g_signal_connect(window, "scroll_event",        G_CALLBACK(scroll_event),        this);
          g_signal_connect(window, "destroy",             G_CALLBACK(gtk_main_quit),       NULL);

          g_timeout_add(15, (GSourceFunc)loop_event, canvas);

          gtk_widget_set_events(canvas,
                    GDK_BUTTON_PRESS_MASK |
                    GDK_BUTTON_RELEASE_MASK |
                    GDK_POINTER_MOTION_MASK |
                    GDK_ENTER_NOTIFY_MASK |
                    GDK_LEAVE_NOTIFY_MASK | 
                    GDK_SCROLL_MASK
          );

          gtk_container_add(GTK_CONTAINER(window), canvas);
          surface -> translate_norm = casp_translate_norm_h;
          window_scale(_w,_h);
     }

     void run(){
          gtk_widget_show_all(window);
          gtk_main();
     }

     bool get_key_retain(int value){ return keys.find(value)!=keys.end(); }

     bool get_button_retain(int value){ return buttons.find(value)!=buttons.end(); }

     bool get_key_press(int value){ return skey == value; }

     bool get_button_press(int value){ return sbutton == value; }

     void key_debug(){
          for(auto key:keys){ std::cout<<key<<" "; }
          if(keys.size()) std::cout<<std::endl;
     }

     void button_debug(){
          for(auto button:buttons){ std::cout<<button<<" "; }
          if(buttons.size()) std::cout<<std::endl;
     }

     void debug_QWEASD(){
          for(auto key:keys){
               switch(key){
                    case 113: // q
                         surface -> zoom/=1.05;
                         break;
                    case 119: // w
                         surface -> xy.y-=0.1;
                         break;
                    case 101: // e
                         surface -> zoom*=1.05;
                         break;
                    case 97 : // a
                         surface -> xy.x-=0.1;
                         break;
                    case 115: // s
                         surface -> xy.y+=0.1;
                         break;
                    case 100: // d
                         surface -> xy.x+=0.1;
                         break;
               }
          }
     }
};

static gboolean
key_press_event(GtkWidget * _widget, GdkEventKey * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     if(_host -> get_key_retain(_event->keyval) == false){
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
     casp_surface * _surface = _host->surface;
     _surface -> cr = _cr;
     casp_main();
     _host -> skey    = 0;
     _host -> sbutton = 0;
     _host -> scroll  = 0;
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

static gboolean
button_press_event (GtkWidget * _widget, GdkEventButton * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     if(_host -> get_button_retain(_event->button) == false){
          _host -> sbutton = _event->button;
          _host -> buttons.insert(_event->button);
     }
     return true;
}

static gboolean
button_release_event (GtkWidget * _widget, GdkEventButton * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     _host -> buttons.erase(_event->button);
     return true;
}

static gboolean
motion_notify_event (GtkWidget * _widget, GdkEventMotion * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     casp_surface * _surface = _host -> surface;
     _host -> mouse_pos.x = _surface -> retranslate_x(_event -> x);
     _host -> mouse_pos.y = _event -> y;
     return true;
}

static gboolean
enter_notify_event (GtkWidget * _widget, GdkEventCrossing * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     _host -> mouse_pos.x = _event -> x;
     _host -> mouse_pos.y = _event -> y;
     return true;
}

static gboolean 
scroll_event(GtkWidget * _widget, GdkEventScroll * _event, gpointer _data){
     casp_gui_host * _host = (casp_gui_host * )_data;
     switch(_event -> direction){
     case GDK_SCROLL_UP:
               _host -> scroll = -1;
               break;
     case GDK_SCROLL_DOWN:
               _host -> scroll = 1 ;
               break;
     case GDK_SCROLL_LEFT:
               _host -> scroll = 2 ;
               break;
     case GDK_SCROLL_RIGHT:
               _host -> scroll = -2;
               break;
     default:
               break;
     }
     return true;
}