
class c_host {
private:
    GtkWidget *window;
    GtkWidget *canvas;
    c_surface *surface;
    casp_rgb background_color;
    uint layer_size;
    bool fullscreen = false;
      
    casp_xy<int> resolution;

    static gboolean draw_event(GtkWidget *, cairo_t *, gpointer);
    static gboolean loop_event(GtkWidget *);
    static gboolean window_resize_event(GtkWidget *, GdkRectangle *, gpointer);
    static gboolean window_state_event(GtkWidget *, GdkEventWindowState *, gpointer);

public: 

    void setup_host(casp_xy<int>);
    void run();
    void set_surface(uint);
    void window_scale(casp_xy<int>);
    void set_titlebar(const char *);
    void set_background(casp_rgb);
    void set_fullscreen(bool);
    void fullscreen_signal();
    void quit();

    // === Key Events ===

    #ifdef c_permission_key_events

    private:
        std::set<uint> keys;
        uint key_sig;
        static gboolean key_press_event(GtkWidget *, GdkEventKey *, gpointer);
        static gboolean key_release_event(GtkWidget *, GdkEventKey *, gpointer);

    public:
        bool get_key_retain(int);
        bool get_key_press (int);

        #ifdef c_permission_debug

        public:
            void debug_key();
            void debug_QWEASD(uint);

        #endif

    #endif

    #ifdef c_permission_mouse_button_events

    private:
        std::set<uint> buttons;
        uint button_sig;
        int scroll;
        static gboolean mouse_button_press_event(GtkWidget *, GdkEventButton *, gpointer);
        static gboolean mouse_button_release_event(GtkWidget *, GdkEventButton *, gpointer);
        static gboolean mouse_scroll_event(GtkWidget *, GdkEventScroll *, gpointer);

    public:
        bool get_mouse_button_retain(int);
        bool get_mouse_button_press (int);

        #ifdef c_permission_debug

        public:
            void debug_mouse_button();

        #endif

    #endif

    #ifdef c_permission_mouse_notify_events
    private:
        static gboolean motion_notify_event(GtkWidget *, GdkEventMotion *, gpointer);
    public:
        casp_xy<double> mouse_pos; 

    #endif

};



void c_host::setup_host(casp_xy<int> _resolution){

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    canvas = gtk_drawing_area_new();

    gtk_widget_set_app_paintable(canvas, true);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_decorated( (GtkWindow *)window, false);

    g_signal_connect(window, "draw",
                        G_CALLBACK(draw_event), this);
    g_signal_connect(window, "size_allocate",
                        G_CALLBACK(window_resize_event), this);
    g_signal_connect(window, "window_state_event",
                        G_CALLBACK(window_state_event), this);
    g_signal_connect(window, "destroy",
                        G_CALLBACK(gtk_main_quit), NULL);

    #ifdef c_permission_key_events

        g_signal_connect(window, "key_press_event",
                        G_CALLBACK(key_press_event),this);
        g_signal_connect(window, "key_release_event",
                        G_CALLBACK(key_release_event), this);

    #endif

    #ifdef c_permission_mouse_button_events

        g_signal_connect(window, "button_press_event",
                        G_CALLBACK(mouse_button_press_event), this);
        g_signal_connect(window, "button_release_event",
                        G_CALLBACK(mouse_button_release_event), this);
        g_signal_connect(window, "scroll_event",
                        G_CALLBACK(mouse_scroll_event), this);
        
        gtk_widget_set_events(canvas,
            GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_SCROLL_MASK);
        
    #endif

    #ifdef c_permission_mouse_notify_events

        g_signal_connect(window, "motion_notify_event",
                        G_CALLBACK(motion_notify_event), this);
        gtk_widget_set_events(canvas, GDK_POINTER_MOTION_MASK);

    #endif

    g_timeout_add(1, (GSourceFunc)loop_event, canvas);
    gtk_container_add(GTK_CONTAINER(window), canvas);

    resolution = _resolution;

    set_surface(1);
    c_default_surface(&surface[0]);

    window_scale(_resolution);
}

void c_host::run() {
    gtk_widget_show_all(window);
    gtk_main();
}

void c_host::set_surface(uint _layer_size){
    layer_size = _layer_size;
    surface = new c_surface[layer_size];
}

void c_host::window_scale(casp_xy<int> _resolution){

    for(int i=0;i<layer_size;i++){
        surface[i].resolution = _resolution;
        surface[i].set_wh();
    }

    gtk_window_set_default_size((GtkWindow *)window, _resolution.x, _resolution.y);
}

void c_host::set_titlebar(const char * _title){
    gtk_window_set_decorated( (GtkWindow *)window, true);
    gtk_window_set_title ( (GtkWindow *)window, _title);
}

void c_host::set_background(casp_rgb _background_color){
    background_color = _background_color;
}

void c_host::set_fullscreen(bool _flag){
    fullscreen = true;
    window_state_event(window, NULL, this);
}

void c_host::quit(){
    gtk_main_quit();
}


/*
    cairo_surface_t *image;

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
*/