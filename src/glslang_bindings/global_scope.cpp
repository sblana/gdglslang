#include "global_scope.hpp"
#include <glslang/glslang/Public/ShaderLang.h>
#include <glslang/glslang/Public/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/core/memory.hpp>

namespace gdglslang {

	void gGlobalScope::_bind_methods() {
		#pragma region Enums
			BIND_ENUM_CONSTANT(EShLangVertex)
			BIND_ENUM_CONSTANT(EShLangTessControl)
			BIND_ENUM_CONSTANT(EShLangTessEvaluation)
			BIND_ENUM_CONSTANT(EShLangGeometry)
			BIND_ENUM_CONSTANT(EShLangFragment)
			BIND_ENUM_CONSTANT(EShLangCompute)
			BIND_ENUM_CONSTANT(EShLangRayGen)
			BIND_ENUM_CONSTANT(EShLangRayGenNV)
			BIND_ENUM_CONSTANT(EShLangIntersect)
			BIND_ENUM_CONSTANT(EShLangIntersectNV)
			BIND_ENUM_CONSTANT(EShLangAnyHit)
			BIND_ENUM_CONSTANT(EShLangAnyHitNV)
			BIND_ENUM_CONSTANT(EShLangClosestHit)
			BIND_ENUM_CONSTANT(EShLangClosestHitNV)
			BIND_ENUM_CONSTANT(EShLangMiss)
			BIND_ENUM_CONSTANT(EShLangMissNV)
			BIND_ENUM_CONSTANT(EShLangCallable)
			BIND_ENUM_CONSTANT(EShLangCallableNV)
			BIND_ENUM_CONSTANT(EShLangTask)
			BIND_ENUM_CONSTANT(EShLangTaskNV)
			BIND_ENUM_CONSTANT(EShLangMesh)
			BIND_ENUM_CONSTANT(EShLangMeshNV)

			BIND_ENUM_CONSTANT(EShSourceNone)
			BIND_ENUM_CONSTANT(EShSourceGlsl)
			BIND_ENUM_CONSTANT(EShSourceHlsl)

			BIND_ENUM_CONSTANT(EShClientNone)
			BIND_ENUM_CONSTANT(EShClientVulkan)
			BIND_ENUM_CONSTANT(EShClientOpenGL)

			BIND_ENUM_CONSTANT(EShTargetNone)
			BIND_ENUM_CONSTANT(EShTargetSpv)

			BIND_ENUM_CONSTANT(EShTargetVulkan_1_0)
			BIND_ENUM_CONSTANT(EShTargetVulkan_1_1)
			BIND_ENUM_CONSTANT(EShTargetVulkan_1_2)
			BIND_ENUM_CONSTANT(EShTargetVulkan_1_3)
			BIND_ENUM_CONSTANT(EShTargetVulkan_1_4)
			BIND_ENUM_CONSTANT(EShTargetOpenGL_450)

			BIND_ENUM_CONSTANT(EShTargetSpv_1_0)
			BIND_ENUM_CONSTANT(EShTargetSpv_1_1)
			BIND_ENUM_CONSTANT(EShTargetSpv_1_2)
			BIND_ENUM_CONSTANT(EShTargetSpv_1_3)
			BIND_ENUM_CONSTANT(EShTargetSpv_1_4)
			BIND_ENUM_CONSTANT(EShTargetSpv_1_5)
			BIND_ENUM_CONSTANT(EShTargetSpv_1_6)

			BIND_ENUM_CONSTANT(EBadProfile)
			BIND_ENUM_CONSTANT(ENoProfile)
			BIND_ENUM_CONSTANT(ECoreProfile)
			BIND_ENUM_CONSTANT(ECompatibilityProfile)
			BIND_ENUM_CONSTANT(EEsProfile)

			BIND_BITFIELD_FLAG(EShMsgDefault)
			BIND_BITFIELD_FLAG(EShMsgRelaxedErrors)
			BIND_BITFIELD_FLAG(EShMsgSuppressWarnings)
			BIND_BITFIELD_FLAG(EShMsgAST)
			BIND_BITFIELD_FLAG(EShMsgSpvRules)
			BIND_BITFIELD_FLAG(EShMsgVulkanRules)
			BIND_BITFIELD_FLAG(EShMsgOnlyPreprocessor)
			BIND_BITFIELD_FLAG(EShMsgReadHlsl)
			BIND_BITFIELD_FLAG(EShMsgCascadingErrors)
			BIND_BITFIELD_FLAG(EShMsgKeepUncalled)
			BIND_BITFIELD_FLAG(EShMsgHlslOffsets)
			BIND_BITFIELD_FLAG(EShMsgDebugInfo)
			BIND_BITFIELD_FLAG(EShMsgHlslEnable16BitTypes)
			BIND_BITFIELD_FLAG(EShMsgHlslLegalization)
			BIND_BITFIELD_FLAG(EShMsgHlslDX9Compatible)
			BIND_BITFIELD_FLAG(EShMsgBuiltinSymbolTable)
			BIND_BITFIELD_FLAG(EShMsgEnhanced)
			BIND_BITFIELD_FLAG(EShMsgAbsolutePath)
			BIND_BITFIELD_FLAG(EShMsgDisplayErrorColumn)
			BIND_BITFIELD_FLAG(EShMsgLinkTimeOptimization)
			BIND_BITFIELD_FLAG(EShMsgValidateCrossStageIO)
			BIND_BITFIELD_FLAG(EShMsgRelaxSetBindingLimits)
		#pragma endregion

		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("initialize_process"), &gGlobalScope::initialize_process);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("finalize_process"), &gGlobalScope::finalize_process);

		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("get_default_resources"), &gGlobalScope::get_default_resources);

		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("get_spirv_version"), &gGlobalScope::get_spirv_version);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("get_spirv_generator_version"), &gGlobalScope::get_spirv_generator_version);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("glslang_to_spv", "p_intermediate", "p_logger", "p_options"), &gGlobalScope::glslang_to_spv);
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("glslang_to_spv_1", "p_intermediate", "p_options"), &gGlobalScope::glslang_to_spv_1);
	}

	EShLanguage gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEShLanguage p_value) {
		return EShLanguage(p_value);
	}

	glslang::EShSource gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEShSource p_value) {
		return glslang::EShSource(p_value);
	}

	glslang::EShClient gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEShClient p_value) {
		return glslang::EShClient(p_value);
	}

	glslang::EShTargetLanguage gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEShTargetLanguage p_value) {
		return glslang::EShTargetLanguage(p_value);
	}

	glslang::EShTargetClientVersion gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEShTargetClientVersion p_value) {
		return glslang::EShTargetClientVersion(p_value);
	}

	glslang::EShTargetLanguageVersion gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEShTargetLanguageVersion p_value) {
		return glslang::EShTargetLanguageVersion(p_value);
	}

	EProfile gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEProfile p_value) {
		return EProfile(p_value);
	}

	EShMessages gGlobalScope::convert_to_glslang_enum(gGlobalScope::gEShMessages p_value) {
		return EShMessages(p_value);
	}


	gGlobalScope::gEShLanguage gGlobalScope::convert_to_gdglslang_enum(EShLanguage p_value) {
		return gGlobalScope::gEShLanguage(p_value);
	}


	bool gGlobalScope::initialize_process() {
		return glslang::InitializeProcess();
	}

	void gGlobalScope::finalize_process() {
		glslang::FinalizeProcess();
	}

	godot::Ref<gTBuiltInResource> gGlobalScope::get_default_resources() {
		godot::Ref<gTBuiltInResource> ret = memnew(gTBuiltInResource);
		ret->data = *GetDefaultResources();
		return ret;
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
