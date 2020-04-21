
void c_host::write_png(const char * _file) {

    image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                        surface->resolution.x, surface->resolution.y);
    
    draw_event(window, cairo_create(image), this);

    cairo_surface_flush(image);
    cairo_surface_write_to_png(image, _file);
    std::cout << "Wrote : " << _file << std::endl;
}