
#define casp_permission_debug
#define casp_permission_key_events
#define casp_permission_mouse_button_events
#define casp_permission_mouse_notify_events
#define casp_output_png

#include "definition.hpp"
#include "default_signal.hpp"

#ifdef casp_permission_key_events
    #include "key.hpp"
#endif

#ifdef casp_permission_mouse_button_events
    #include "mouse_button.hpp"
#endif

#ifdef casp_permission_mouse_notify_events
    #include "mouse_notify.hpp"
#endif

#ifdef casp_output_png
    #include "output/png.hpp"
#endif