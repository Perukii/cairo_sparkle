

#include "surface.hpp"

casp_surface *casp_default_surface_target = NULL;
cairo_filter_t casp_def_image_filter = CAIRO_FILTER_GOOD;

void casp_default_surface(casp_surface *_surface){
    casp_default_surface_target = _surface;
}

#include "options/stroke.hpp"

#include "functions.hpp"
#include "object.hpp"

#include "line.hpp"
#include "rect.hpp"
#include "subrect.hpp"
#include "image.hpp"



/*
#include "objects/text.hpp"
#include "objects/image.hpp"
#include "objects/line.hpp"
#include "objects/circle.hpp"
*/


