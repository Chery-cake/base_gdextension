#include "example2.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void ExampleUnused::_bind_methods(){

}

ExampleUnused::ExampleUnused(){

}

ExampleUnused::~ExampleUnused(){

}

void ExampleUnused::_initialize_module(){
	UtilityFunctions::print("initialization");
}

void ExampleUnused::_uninitialize_module(){
	UtilityFunctions::print("unitialization");
}
