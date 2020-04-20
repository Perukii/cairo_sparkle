


static gboolean key_press_event(GtkWidget *, GdkEventKey *, gpointer);

static gboolean key_release_event(GtkWidget *, GdkEventKey *, gpointer);

static gboolean draw_event(GtkWidget *, cairo_t *, gpointer);

static gboolean window_resize_event(GtkWidget *, GdkRectangle *, gpointer);

static gboolean button_press_event(GtkWidget *, GdkEventButton *, gpointer);

static gboolean button_release_event(GtkWidget *, GdkEventButton *, gpointer);

static gint motion_notify_event(GtkWidget *, GdkEventMotion *, gpointer);

static gboolean enter_notify_event(GtkWidget *, GdkEventCrossing *, gpointer);

static gboolean scroll_event(GtkWidget *, GdkEventScroll *, gpointer);

static gboolean window_state_event(GtkWidget *, GdkEventWindowState *, gpointer);


static gboolean loop_event(GtkWidget *);

class c_host {
private:
    GtkWidget *window;
    GtkWidget *canvas;
    uint layer_size;
    
public:

    c_surface *surface;

    void setup_host(casp_xy<int>);
    void run();
    void set_surface(uint);

};

void c_host::setup_host(casp_xy<int> _resolution){

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    canvas = gtk_drawing_area_new();

    gtk_widget_set_app_paintable(canvas, true);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_decorated( (GtkWindow *)window, false);
    gtk_window_set_default_size((GtkWindow *)window, _resolution.x,
                                        _resolution.y);

    g_timeout_add(1, (GSourceFunc)loop_event, canvas);
    gtk_container_add(GTK_CONTAINER(window), canvas);

    set_surface(1);
}

void c_host::run() {
    gtk_widget_show_all(window);
    gtk_main();
}

void c_host::set_surface(uint _layer_size){
    layer_size = _layer_size;
    surface = new c_surface[layer_size];
}



static gboolean loop_event(GtkWidget *widget) {
    c_main();
    gtk_widget_queue_draw(widget);
    return true;
}


/*




class casp_host {

  private:
    GtkWidget *window;
    GtkWidget *canvas;

  public:
    casp_surface *surface;
    uint skey, sbutton;
    int scroll, layer_size, def_translate_norm, draw_time;

    std::set<uint> keys, buttons;
    casp_xy<double> mouse_pos, def_scale;

    bool fullscreen_f, unfullscreen_f;

    cairo_surface_t *image;

    //casp_host_audio.hpp
    casp_audio audio;

    casp_host() { keys.clear(); }

    ~casp_host() { cairo_surface_destroy(image); }

    //casp_host_debug.hpp
    void debug_QWEASD(casp_surface *);
    void debug_QWEASD(int);



    void window_scale() {
        for(int i=0;i<layer_size;i++){
            casp_xy<double> _scale = surface[i].scale;

            if (def_scale.x != -1)
                _scale.x = def_scale.x;
            if (def_scale.y != -1)
                _scale.y = def_scale.y;

            surface[i].set_scale(_scale);
            surface[i].translate_norm = def_translate_norm;
            gtk_window_set_default_size((GtkWindow *)window, surface[i].scale.x,
                                        surface[i].scale.y);
        }

    }

    void setup_host(int _w = -1, int _h = -1,
               int _translate_norm = casp_translate_norm_w) {

        reset_vals();
        def_scale = casp_xy<double>(_w,_h);
        def_translate_norm = _translate_norm;

        // ~~~ definition ~~~

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        canvas = gtk_drawing_area_new();

        gtk_widget_set_app_paintable(canvas, true);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_window_set_decorated( (GtkWindow *)window, false);

        // ~~~ signals ~~~

        g_signal_connect(window, "key_press_event", G_CALLBACK(key_press_event),
                         this);
        g_signal_connect(window, "key_release_event",
                         G_CALLBACK(key_release_event), this);
        g_signal_connect(window, "draw",
                         G_CALLBACK(draw_event), this);
        g_signal_connect(window, "size_allocate",
                         G_CALLBACK(window_resize_event), this);
        g_signal_connect(window, "button_press_event",
                         G_CALLBACK(button_press_event), this);
        g_signal_connect(window, "button_release_event",
                         G_CALLBACK(button_release_event), this);
        g_signal_connect(window, "motion_notify_event",
                         G_CALLBACK(motion_notify_event), this);
        g_signal_connect(window, "enter_notify_event",
                         G_CALLBACK(enter_notify_event), this);
        g_signal_connect(window, "scroll_event",
                         G_CALLBACK(scroll_event), this);
        g_signal_connect(window, "window_state_event",
                         G_CALLBACK(window_state_event), this);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        g_timeout_add(draw_time, (GSourceFunc)loop_event, canvas);

        gtk_widget_set_events(
            canvas, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
                        GDK_POINTER_MOTION_MASK | GDK_ENTER_NOTIFY_MASK |
                        GDK_LEAVE_NOTIFY_MASK | GDK_SCROLL_MASK);

        gtk_container_add(GTK_CONTAINER(window), canvas);

        set_surface(1);
        casp_default_surface(&surface[0]);
        window_scale();

    }

    void set_surface(uint _layer_size){
        layer_size = _layer_size;
        surface = new casp_surface[layer_size];
        window_scale();
    }

    void reset_vals() {
        skey = 0;
        sbutton = 0;
        scroll = 0;
        fullscreen_f = false;
        unfullscreen_f = false;
        draw_time = 20;
    }

    void write_png(std::string _file) {
        image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                           surface->scale.x, surface->scale.y);

        for(int i=0;i<layer_size;i++){
            surface[i].cr = cairo_create(image);
        }
        
        casp_draw();

        cairo_surface_flush(image);
        cairo_surface_write_to_png(image, _file.c_str());
        std::cout << "Wrote : " << _file << std::endl;
    }

    void run() {
        gtk_widget_show_all(window);
        gtk_main();
    }

    bool get_key_retain(int value) { return keys.find(value) != keys.end(); }

    bool get_button_retain(int value) {
        return buttons.find(value) != buttons.end();
    }

    bool get_key_press(int value) { return skey == value; }

    bool get_button_press(int value) { return sbutton == value; }

    void key_debug() {
        for (auto key : keys) {
            std::cout << key << " ";
        }
        if (keys.size())
            std::cout << std::endl;
    }

    void button_debug() {
        for (auto button : buttons) {
            std::cout << button << " ";
        }
        if (buttons.size())
            std::cout << std::endl;
    }

    void set_titlebar(const char * title){
        gtk_window_set_decorated( (GtkWindow *)window, true);
        gtk_window_set_title ( (GtkWindow *)window, title);
    }

    void fullscreen()  {
        fullscreen_f = true;
        window_state_event(window, NULL, this);
    }

    void unfullscreen(){
        unfullscreen_f = true;
        window_state_event(window, NULL, this);
    }

    void set_fullscreen_signal(){
        if(fullscreen_f == true){
            gtk_window_fullscreen  ( (GtkWindow *)window);
            fullscreen_f = false;
            return;
        }
        
        if(unfullscreen_f == true){
            gtk_window_unfullscreen( (GtkWindow *)window);
            unfullscreen_f = false;
            return;
        }
    }

    void end_process() { gtk_main_quit(); }

};

*/