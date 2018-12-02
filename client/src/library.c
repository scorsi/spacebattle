#include "client.hpp"

#include <core/Godot.hpp>
#include <gdnative/gdnative.h>

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    //godot::Godot::gdnative_init(o);
}

void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    //godot::Godot::gdnative_terminate(o);
}

void GDN_EXPORT godot_nativescript_init(void *handle) {
    //godot::Godot::nativescript_init(handle);

    //godot::register_class<godot::client>();
}
