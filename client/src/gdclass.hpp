#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>

namespace godot {

class gdclass : public godot::GodotScript<Node> {
GODOT_CLASS(gdclass)

public:
    static void _register_methods();

    gdclass();

    ~gdclass();

    void _process();
};

}