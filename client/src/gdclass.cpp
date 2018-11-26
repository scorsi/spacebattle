#include "gdclass.hpp"

using namespace godot;

namespace godot {

void gdclass::_register_methods() {
    register_method((char *) "_process", &gdclass::_process);
}

gdclass::gdclass(){
}

gdclass::~gdclass() {
}

void gdclass::_process() {
}

}
