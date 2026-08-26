#include "t_program.hpp"

namespace gdglslang {

	void gTProgram::_bind_methods() {
		godot::ClassDB::bind_method(godot::D_METHOD("add_shader", "p_shader"), &gTProgram::add_shader);
		godot::ClassDB::bind_method(godot::D_METHOD("link", "p_messages"), &gTProgram::link);
		godot::ClassDB::bind_method(godot::D_METHOD("get_info_log"), &gTProgram::get_info_log);
		godot::ClassDB::bind_method(godot::D_METHOD("get_info_debug_log"), &gTProgram::get_info_debug_log);
		godot::ClassDB::bind_method(godot::D_METHOD("get_intermediate", "p_stage"), &gTProgram::get_intermediate);
	}

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

	bool gTProgram::link(godot::BitField<gGlobalScope::Messages> p_messages) {
		return data->link(gGlobalScope::convert_to_glslang_enum(gGlobalScope::Messages(int64_t(p_messages))));
	}

	godot::String gTProgram::get_info_log() {
		return godot::String(data->getInfoLog());
	}

	godot::String gTProgram::get_info_debug_log() {
		return godot::String(data->getInfoDebugLog());
	}

	godot::Ref<gTIntermediate> gTProgram::get_intermediate(gGlobalScope::Language p_stage) const {
		godot::Ref<gTIntermediate> ret = memnew(gTIntermediate);
		ret->data = data->getIntermediate(gGlobalScope::convert_to_glslang_enum(p_stage));
		return ret;
	}
}
