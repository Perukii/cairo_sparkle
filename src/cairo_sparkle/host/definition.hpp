
class casp_host {
private:
    GtkWidget *window;
    GtkWidget *canvas;
    casp_surface *surface;
    
    casp_rgb background_color;
    uint layer_size;
    bool fullscreen = false;
    
    casp_xy<int> resolution;
    

    static gboolean draw_event(GtkWidget *, cairo_t *, gpointer);
    static gboolean loop_event(GtkWidget *);
    static gboolean window_resize_event(GtkWidget *, GdkRectangle *, gpointer);
    static gboolean window_state_event(GtkWidget *, GdkEventWindowState *, gpointer);
    

public: 

    void(*main_loop)();

    void setup_host(casp_xy<int>);
    void run(void(*)());
    void set_layer(uint);
    void switch_layer(uint);
    void window_scale(casp_xy<int>);
    void set_titlebar(const char *);
    void set_background(casp_rgb);
    void set_fullscreen(bool);
    void fullscreen_signal();
    void quit();
    void reset_value();
    
    // === Key Events ===

    #ifdef casp_permission_key_events

    private:
        std::set<uint> keys;
        uint key_sig;
        static gboolean key_press_event(GtkWidget *, GdkEventKey *, gpointer);
        static gboolean key_release_event(GtkWidget *, GdkEventKey *, gpointer);

    public:
        bool get_key_retain(int);
        bool get_key_press (int);

        #ifdef casp_permission_debug

        public:
            void debug_key();
            void debug_QWEASD(uint);

        #endif

    #endif

    #ifdef casp_permission_mouse_button_events

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

        #ifdef casp_permission_debug

        public:
            void debug_mouse_button();

        #endif

    #endif

    #ifdef casp_permission_mouse_notify_events
    private:
        static gboolean motion_notify_event(GtkWidget *, GdkEventMotion *, gpointer);
    public:
        casp_xy<double> mouse_pos; 

    #endif

    #ifdef casp_output_png
    private:
        bool output_mode;
    public:
        void write_png(const char * _file);
    #endif

};

void casp_host::setup_host(casp_xy<int> _resolution = {500, 500}){

    gtk_init(NULL, NULL);

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

    #ifdef casp_permission_key_events

        g_signal_connect(window, "key_press_event",
                        G_CALLBACK(key_press_event),this);
        g_signal_connect(window, "key_release_event",
                        G_CALLBACK(key_release_event), this);

    #endif

    #ifdef casp_permission_mouse_button_events

        g_signal_connect(window, "button_press_event",
                        G_CALLBACK(mouse_button_press_event), this);
        g_signal_connect(window, "button_release_event",
                        G_CALLBACK(mouse_button_release_event), this);
        g_signal_connect(window, "scroll_event",
                        G_CALLBACK(mouse_scroll_event), this);
        
        gtk_widget_set_events(canvas,
            GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_SCROLL_MASK);
        
    #endif

    #ifdef casp_permission_mouse_notify_events

        g_signal_connect(window, "motion_notify_event",
                        G_CALLBACK(motion_notify_event), this);
        gtk_widget_set_events(canvas, GDK_POINTER_MOTION_MASK);

    #endif

    g_timeout_add(1, (GSourceFunc)loop_event, canvas);
    
    gtk_container_add(GTK_CONTAINER(window), canvas);

    resolution = _resolution;
    set_layer(1);
    switch_layer(0);

    window_scale(_resolution);
}

void casp_host::run(void (*_main_loop )()) {
    main_loop = _main_loop;
    gtk_widget_show_all(window);
    gtk_main();
}

void casp_host::set_layer(uint _layer_size){
    layer_size = _layer_size;
    surface = new casp_surface[layer_size];
}

void casp_host::switch_layer(uint _layer){
    casp_default_surface(&surface[_layer]);
}

void casp_host::window_scale(casp_xy<int> _resolution){

    for(int i=0;i<layer_size;i++){
        surface[i].resolution = _resolution;
        surface[i].set_wh();
    }

    gtk_window_set_default_size((GtkWindow *)window, _resolution.x, _resolution.y);
}

void casp_host::set_titlebar(const char * _title){
    gtk_window_set_decorated( (GtkWindow *)window, true);
    gtk_window_set_title ( (GtkWindow *)window, _title);
}

void casp_host::set_background(casp_rgb _background_color){
    background_color = _background_color;
}

void casp_host::set_fullscreen(bool _flag){
    fullscreen = true;
    window_state_event(window, NULL, this);
}

void casp_host::quit(){
    gtk_main_quit();
}

void casp_host::reset_value(){
    #ifdef casp_permission_key_events
        key_sig = 0;
    #endif

    #ifdef casp_permission_mouse_button_events
        button_sig = 0;
        scroll = 0;
    #endif
}
