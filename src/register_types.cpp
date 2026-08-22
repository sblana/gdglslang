#include "register_types.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "glslang_bindings/t_limits.hpp"
#include "glslang_bindings/t_built_in_resource.hpp"
#include "glslang_bindings/spv_options.hpp"


void initialize_gdglslang(godot::ModuleInitializationLevel p_level) {
	if (p_level == godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) {
		GDREGISTER_CLASS(gdglslang::gTLimits);
		GDREGISTER_CLASS(gdglslang::gTBuiltInResource);
		GDREGISTER_CLASS(gdglslang::gSpvOptions);
	}
}

void uninitialize_gdglslang(godot::ModuleInitializationLevel p_level) {}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT gdglslang_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_gdglslang);
	init_obj.register_terminator(uninitialize_gdglslang);
	init_obj.set_minimum_library_initialization_level(godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
