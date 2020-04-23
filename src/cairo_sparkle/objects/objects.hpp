

#include "surface.hpp"

c_surface *c_default_surface_target = NULL;
cairo_filter_t c_def_image_filter = CAIRO_FILTER_GOOD;

void c_default_surface(c_surface *_surface){
    c_default_surface_target = _surface;
}

#include "options/stroke.hpp"

#include "functions.hpp"
#include "object.hpp"
#include "rect.hpp"
#include "line.hpp"



/*
#include "objects/text.hpp"
#include "objects/image.hpp"
#include "objects/line.hpp"
#include "objects/circle.hpp"
*/


