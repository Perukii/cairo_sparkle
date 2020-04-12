
void casp_init(int _argc, char **_argv) { gtk_init(&_argc, &_argv); }
void casp_main();
void casp_draw();

#define casp_auto DBL_MAX
#define casp_translate_norm_w 0
#define casp_translate_norm_h 1

#define casp_rgb_null casp_rgb(0, 0, 0, 0)
#define casp_rgb_black casp_rgb(0, 0, 0, 1)
#define casp_rgb_red casp_rgb(1, 0, 0, 1)
#define casp_rgb_green casp_rgb(0, 1, 0, 1)
#define casp_rgb_blue casp_rgb(0, 0, 1, 1)
#define casp_rgb_yellow casp_rgb(1, 1, 0, 1)
#define casp_rgb_sky casp_rgb(0, 1, 1, 1)
#define casp_rgb_pink casp_rgb(1, 0, 1, 1)
#define casp_rgb_white casp_rgb(1, 1, 1, 1)

#define casp_rgb_adv_naturalGreen casp_rgb(0.60, 0.96, 0.52)
#define casp_rgb_adv_skyBlue casp_rgb(0.56, 0.88, 1.00)
#define casp_rgb_adv_autumnRed casp_rgb(1.00, 0.60, 0.46)

#include "fundament/fundamental_math.hpp"
#include "objects/surface.hpp"

casp_surface *casp_default_surface_target = NULL;

void casp_default_surface(casp_surface *_surface) {
    casp_default_surface_target = _surface;
}

#include "objects/functions.hpp"
#include "objects/object.hpp"

#include "objects/options/stroke.hpp"

#include "objects/rect.hpp"
#include "objects/text.hpp"
#include "objects/image.hpp"
#include "objects/line.hpp"
#include "objects/circle.hpp"

#include "host/casp_host.hpp"
#include "host/casp_host_debug.hpp"