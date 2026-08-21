#include "t_program.hpp"

namespace gdglslang {

	gTProgram::gTProgram() {
		data = new glslang::TProgram;
	}

	gTProgram::~gTProgram() {
		delete data;
	}

	void gTProgram::add_shader(godot::Ref<gTShader> p_shader) {
		ERR_FAIL_COND(!p_shader->is_setup());
		shaders.append(p_shader);
		data->addShader(p_shader->data);
	}

	bool gTProgram::link(gGlobalSpace::gEShMessages p_messages) {
		data->link(gGlobalSpace::convert_to_glslang_enum(p_messages));
	}

	godot::String gTProgram::get_info_log() {
		return godot::String(data->getInfoLog());
	}

	godot::String gTProgram::get_info_debug_log() {
		return godot::String(data->getInfoDebugLog());
	}

	godot::Ref<gTIntermediate> gTProgram::get_intermediate(gGlobalSpace::gEShLanguage p_stage) const {
		godot::Ref<gTIntermediate> ret = memnew(gTIntermediate);
		ret->data = data->getIntermediate(gGlobalSpace::convert_to_glslang_enum(p_stage));
		return ret;
	}
}
