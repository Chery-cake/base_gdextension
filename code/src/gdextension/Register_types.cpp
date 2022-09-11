#include "Register_types.h"

#include <godot/gdnative_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "AutoRegister.hpp"

using namespace godot;

void initialize_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	AutoRegister::register_initialize_classes();

	AutoRegister::register_initialize_module();

}

void uninitialize_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	AutoRegister::register_uninitialize_classes();
}

extern "C" {

// Initialization.

	GDNativeBool GDN_EXPORT library_init(const GDNativeInterface *p_interface,
			const GDNativeExtensionClassLibraryPtr p_library,
			GDNativeInitialization *r_initialization) {
		godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library,
				r_initialization);

		init_obj.register_initializer(initialize_module);
		init_obj.register_terminator(uninitialize_module);

		init_obj.set_minimum_library_initialization_level(
				MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
