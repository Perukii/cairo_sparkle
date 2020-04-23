

void casp_host::write_png(const char * _file) {

    if(output_mode == true)return;
    
    cairo_surface_t * image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                        resolution.x, resolution.y) ;

    cairo_t * created_image = cairo_create(image);

    output_mode = true;
    draw_event(window, created_image, this);
    output_mode = false;

    cairo_surface_flush(image);
    cairo_surface_write_to_png(image, _file);
    std::cout << "written to : " << _file << std::endl;
    cairo_destroy(created_image);
    cairo_surface_destroy(image);
}
