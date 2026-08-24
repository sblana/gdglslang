#include "register_types.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "glslang_bindings/t_limits.hpp"
#include "glslang_bindings/t_built_in_resource.hpp"
#include "glslang_bindings/t_intermediate.hpp"
#include "glslang_bindings/spv_build_logger.hpp"
#include "glslang_bindings/spv_options.hpp"
#include "glslang_bindings/global_space.hpp"
#include "glslang_bindings/t_shader.hpp"
#include "glslang_bindings/t_program.hpp"
#include "glslang_bindings/includer/include_result.hpp"
#include "glslang_bindings/includer/includer_interface.hpp"


void initialize_gdglslang(godot::ModuleInitializationLevel p_level) {
	if (p_level == godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) {
		GDREGISTER_CLASS(gdglslang::gTLimits);
		GDREGISTER_CLASS(gdglslang::gTBuiltInResource);
		GDREGISTER_CLASS(gdglslang::gTIntermediate);
		GDREGISTER_CLASS(gdglslang::gSpvBuildLogger);
		GDREGISTER_CLASS(gdglslang::gSpvOptions);
		GDREGISTER_CLASS(gdglslang::gGlobalSpace);
		GDREGISTER_CLASS(gdglslang::gTShader);
		GDREGISTER_CLASS(gdglslang::gTProgram);
		GDREGISTER_CLASS(gdglslang::gIncludeResult);
		GDREGISTER_CLASS(gdglslang::gIncluderInterface);
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
