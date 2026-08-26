#include "global_scope.hpp"
#include <glslang/glslang/Public/ShaderLang.h>
#include <glslang/glslang/Public/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/core/memory.hpp>

namespace gdglslang {

	void gGlobalScope::_bind_methods() {
		#pragma region Enums
			BIND_ENUM_CONSTANT(LANGUAGE_VERTEX)
			BIND_ENUM_CONSTANT(LANGUAGE_TESS_CONTROL)
			BIND_ENUM_CONSTANT(LANGUAGE_TESS_EVALUATION)
			BIND_ENUM_CONSTANT(LANGUAGE_GEOMETRY)
			BIND_ENUM_CONSTANT(LANGUAGE_FRAGMENT)
			BIND_ENUM_CONSTANT(LANGUAGE_COMPUTE)
			BIND_ENUM_CONSTANT(LANGUAGE_RAY_GEN)
			BIND_ENUM_CONSTANT(LANGUAGE_RAY_GEN_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_INTERSECT)
			BIND_ENUM_CONSTANT(LANGUAGE_INTERSECT_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_ANY_HIT)
			BIND_ENUM_CONSTANT(LANGUAGE_ANY_HIT_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_CLOSEST_HIT)
			BIND_ENUM_CONSTANT(LANGUAGE_CLOSEST_HIT_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_MISS)
			BIND_ENUM_CONSTANT(LANGUAGE_MISS_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_CALLABLE)
			BIND_ENUM_CONSTANT(LANGUAGE_CALLABLE_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_TASK)
			BIND_ENUM_CONSTANT(LANGUAGE_TASK_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_MESH)
			BIND_ENUM_CONSTANT(LANGUAGE_MESH_NV)
			BIND_ENUM_CONSTANT(LANGUAGE_MAX)

			BIND_ENUM_CONSTANT(SOURCE_NONE)
			BIND_ENUM_CONSTANT(SOURCE_GLSL)
			BIND_ENUM_CONSTANT(SOURCE_HLSL)

			BIND_ENUM_CONSTANT(CLIENT_NONE)
			BIND_ENUM_CONSTANT(CLIENT_VULKAN)
			BIND_ENUM_CONSTANT(CLIENT_OPEN_GL)

			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_NONE)
			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_SPV)

			BIND_ENUM_CONSTANT(TARGET_CLIENT_VERSION_VULKAN_1_0)
			BIND_ENUM_CONSTANT(TARGET_CLIENT_VERSION_VULKAN_1_1)
			BIND_ENUM_CONSTANT(TARGET_CLIENT_VERSION_VULKAN_1_2)
			BIND_ENUM_CONSTANT(TARGET_CLIENT_VERSION_VULKAN_1_3)
			BIND_ENUM_CONSTANT(TARGET_CLIENT_VERSION_VULKAN_1_4)
			BIND_ENUM_CONSTANT(TARGET_CLIENT_VERSION_OPEN_GL_450)

			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_VERSION_SPV_1_0)
			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_VERSION_SPV_1_1)
			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_VERSION_SPV_1_2)
			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_VERSION_SPV_1_3)
			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_VERSION_SPV_1_4)
			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_VERSION_SPV_1_5)
			BIND_ENUM_CONSTANT(TARGET_LANGUAGE_VERSION_SPV_1_6)

			BIND_ENUM_CONSTANT(PROFILE_BAD_PROFILE)
			BIND_ENUM_CONSTANT(PROFILE_NO_PROFILE)
			BIND_ENUM_CONSTANT(PROFILE_CORE_PROFILE)
			BIND_ENUM_CONSTANT(PROFILE_COMPATIBILITY_PROFILE)
			BIND_ENUM_CONSTANT(PROFILE_ES_PROFILE)

			BIND_BITFIELD_FLAG(MESSAGE_DEFAULT)
			BIND_BITFIELD_FLAG(MESSAGE_RELAXED_ERRORS)
			BIND_BITFIELD_FLAG(MESSAGE_SUPPRESS_WARNINGS)
			BIND_BITFIELD_FLAG(MESSAGE_AST)
			BIND_BITFIELD_FLAG(MESSAGE_SPV_RULES)
			BIND_BITFIELD_FLAG(MESSAGE_VULKAN_RULES)
			BIND_BITFIELD_FLAG(MESSAGE_ONLY_PREPROCESSOR)
			BIND_BITFIELD_FLAG(MESSAGE_READ_HLSL)
			BIND_BITFIELD_FLAG(MESSAGE_CASCADING_ERRORS)
			BIND_BITFIELD_FLAG(MESSAGE_KEEP_UNCALLED)
			BIND_BITFIELD_FLAG(MESSAGE_HLSL_OFFSETS)
			BIND_BITFIELD_FLAG(MESSAGE_DEBUG_INFO)
			BIND_BITFIELD_FLAG(MESSAGE_HLSL_ENABLE16_BIT_TYPES)
			BIND_BITFIELD_FLAG(MESSAGE_HLSL_LEGALIZATION)
			BIND_BITFIELD_FLAG(MESSAGE_HLSL_DX9_COMPATIBLE)
			BIND_BITFIELD_FLAG(MESSAGE_BUILTIN_SYMBOL_TABLE)
			BIND_BITFIELD_FLAG(MESSAGE_ENHANCED)
			BIND_BITFIELD_FLAG(MESSAGE_ABSOLUTE_PATH)
			BIND_BITFIELD_FLAG(MESSAGE_DISPLAY_ERROR_COLUMN)
			BIND_BITFIELD_FLAG(MESSAGE_LINK_TIME_OPTIMIZATION)
			BIND_BITFIELD_FLAG(MESSAGE_VALIDATE_CROSS_STAGE_IO)
			BIND_BITFIELD_FLAG(MESSAGE_RELAX_SET_BINDING_LIMITS)
		#pragma endregion

		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("initialize_process"), &gGlobalScope::initialize_process);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("finalize_process"), &gGlobalScope::finalize_process);

		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("get_default_resources"), &gGlobalScope::get_default_resources);

		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("get_spirv_version"), &gGlobalScope::get_spirv_version);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("get_spirv_generator_version"), &gGlobalScope::get_spirv_generator_version);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("glslang_to_spv", "p_intermediate", "p_logger", "p_options"), &gGlobalScope::glslang_to_spv);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("glslang_to_spv_1", "p_intermediate", "p_options"), &gGlobalScope::glslang_to_spv_1);
	}

	EShLanguage gGlobalScope::convert_to_glslang_enum(gGlobalScope::Language p_value) {
		return EShLanguage(p_value);
	}

	glslang::EShSource gGlobalScope::convert_to_glslang_enum(gGlobalScope::Source p_value) {
		return glslang::EShSource(p_value);
	}

	glslang::EShClient gGlobalScope::convert_to_glslang_enum(gGlobalScope::Client p_value) {
		return glslang::EShClient(p_value);
	}

	glslang::EShTargetLanguage gGlobalScope::convert_to_glslang_enum(gGlobalScope::TargetLanguage p_value) {
		return glslang::EShTargetLanguage(p_value);
	}

	glslang::EShTargetClientVersion gGlobalScope::convert_to_glslang_enum(gGlobalScope::TargetClientVersion p_value) {
		return glslang::EShTargetClientVersion(p_value);
	}

	glslang::EShTargetLanguageVersion gGlobalScope::convert_to_glslang_enum(gGlobalScope::TargetLanguageVersion p_value) {
		return glslang::EShTargetLanguageVersion(p_value);
	}

	EProfile gGlobalScope::convert_to_glslang_enum(gGlobalScope::Profile p_value) {
		return EProfile(p_value);
	}

	EShMessages gGlobalScope::convert_to_glslang_enum(gGlobalScope::Messages p_value) {
		return EShMessages(p_value);
	}


	gGlobalScope::Language gGlobalScope::convert_to_gdglslang_enum(EShLanguage p_value) {
		return gGlobalScope::Language(p_value);
	}


	bool gGlobalScope::initialize_process() {
		return glslang::InitializeProcess();
	}

	void gGlobalScope::finalize_process() {
		glslang::FinalizeProcess();
	}

	godot::Ref<gTBuiltInResource> gGlobalScope::get_default_resources() {
		// gTBuiltInResource should init to GetDefaultResources
		return memnew(gTBuiltInResource);
	}

	godot::String gGlobalScope::get_spirv_version() {
		std::string version;
		glslang::GetSpirvVersion(version);

		return godot::String(version.c_str());
	}

	int gGlobalScope::get_spirv_generator_version() {
		return glslang::GetSpirvGeneratorVersion();
	}

	godot::PackedByteArray gGlobalScope::glslang_to_spv(godot::Ref<gTIntermediate> p_intermediate, godot::Ref<gSpvBuildLogger> p_logger, godot::Ref<gSpvOptions> p_options) {
		godot::PackedByteArray ret;
		ERR_FAIL_COND_V(p_intermediate.is_null(), ret);
		ERR_FAIL_NULL_V(p_intermediate->data, ret);

		std::vector<unsigned int> spirv;
		glslang::GlslangToSpv(*p_intermediate->data, spirv, p_logger->data, &p_options->data);

		ret.resize(spirv.size() * sizeof(unsigned int));
		uint8_t *w = ret.ptrw();
		memcpy(w, &spirv[0], spirv.size() * sizeof(unsigned int));

		return ret;
	}

	godot::PackedByteArray gGlobalScope::glslang_to_spv_1(godot::Ref<gTIntermediate> p_intermediate, godot::Ref<gSpvOptions> p_options) {
		return glslang_to_spv(p_intermediate, godot::Ref<gSpvBuildLogger>(memnew(gSpvBuildLogger)), p_options);
	}
}
