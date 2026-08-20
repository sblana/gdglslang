#include "global_space.hpp"
#include <glslang/glslang/Public/ShaderLang.h>
#include <glslang/glslang/Public/ResourceLimits.h>
#include <glslang/SPIRV/GlslangToSpv.h>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/core/memory.hpp>
#include "spv_options.hpp"

namespace gdglslang {

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

	godot::PackedByteArray gGlobalSpace::glslang_to_spv1(godot::Ref<gTIntermediate> p_intermediate, godot::Ref<gSpvOptions> p_options) {
		return glslang_to_spv(p_intermediate, godot::Ref<gSpvBuildLogger>(memnew(gSpvBuildLogger)), p_options);
	}
}
