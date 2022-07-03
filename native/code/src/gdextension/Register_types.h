#ifndef SRC_GDEXTENSION_REGISTER_TYPES_H_
#define SRC_GDEXTENSION_REGISTER_TYPES_H_

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_module(ModuleInitializationLevel p_level);
void uninitialize_module(ModuleInitializationLevel p_level);

#endif /* SRC_GDEXTENSION_REGISTER_TYPES_H_ */

