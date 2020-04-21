
#define c_permission_debug
//#define c_permission_key_events
//#define c_permission_mouse_button_events
//#define c_permission_mouse_notify_events


#include "definition.hpp"
#include "default_signal.hpp"

#ifdef c_permission_key_events
    #include "key.hpp"
#endif

#ifdef c_permission_mouse_button_events
    #include "mouse_button.hpp"
#endif

#ifdef c_permission_mouse_notify_events
    #include "mouse_notify.hpp"
#endif
