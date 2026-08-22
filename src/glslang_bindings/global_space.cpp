#include "global_space.hpp"
#include <glslang/glslang/Public/ShaderLang.h>
#include <glslang/glslang/Public/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/core/memory.hpp>

namespace gdglslang {

	EShLanguage gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShLanguage p_value) {
		return EShLanguage(p_value);
	}

	glslang::EShSource gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShSource p_value) {
		return glslang::EShSource(p_value);
	}

	glslang::EShClient gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShClient p_value) {
		return glslang::EShClient(p_value);
	}

	glslang::EShTargetLanguage gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShTargetLanguage p_value) {
		return glslang::EShTargetLanguage(p_value);
	}

	glslang::EShTargetClientVersion gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShTargetClientVersion p_value) {
		return glslang::EShTargetClientVersion(p_value);
	}

	glslang::EShTargetLanguageVersion gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShTargetLanguageVersion p_value) {
		return glslang::EShTargetLanguageVersion(p_value);
	}

	EProfile gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEProfile p_value) {
		return EProfile(p_value);
	}

	EShMessages gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShMessages p_value) {
		return EShMessages(p_value);
	}


	gGlobalSpace::gEShLanguage gGlobalSpace::convert_to_gdglslang_enum(EShLanguage p_value) {
		return gGlobalSpace::gEShLanguage(p_value);
	}


	bool gGlobalSpace::initialize_process() {
		return glslang::InitializeProcess();
	}

	void gGlobalSpace::finalize_process() {
		glslang::FinalizeProcess();
	}

	godot::Ref<gTBuiltInResource> gGlobalSpace::get_default_resources() {
		godot::Ref<gTBuiltInResource> ret = memnew(gTBuiltInResource);
		ret->data = *GetDefaultResources();
		return ret;
	}

	godot::String gGlobalSpace::get_spirv_version() {
		std::string version;
		glslang::GetSpirvVersion(version);

		return godot::String(version.c_str());
	}

	int gGlobalSpace::get_spirv_generator_version() {
		return glslang::GetSpirvGeneratorVersion();
	}

	godot::PackedByteArray gGlobalSpace::glslang_to_spv(godot::Ref<gTIntermediate> p_intermediate, godot::Ref<gSpvBuildLogger> p_logger, godot::Ref<gSpvOptions> p_options) {
		std::vector<unsigned int> spirv;
		glslang::GlslangToSpv(*p_intermediate->data, spirv, p_logger->data, &p_options->data);
		godot::PackedByteArray ret;

		ret.resize(spirv.size() * sizeof(unsigned int));
		uint8_t *w = ret.ptrw();
		memcpy(w, &spirv[0], spirv.size() * sizeof(unsigned int));

		return ret;
	}

	godot::PackedByteArray gGlobalSpace::glslang_to_spv_1(godot::Ref<gTIntermediate> p_intermediate, godot::Ref<gSpvOptions> p_options) {
		return glslang_to_spv(p_intermediate, godot::Ref<gSpvBuildLogger>(memnew(gSpvBuildLogger)), p_options);
	}
}
