#include "t_shader.hpp"
#include <glslang/glslang/Public/ShaderLang.h>
#include <godot_cpp/core/memory.hpp>
#include "includer/includer_impl.hpp"

namespace gdglslang {

	void gTShader::_bind_methods() {
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("create_new", "p_language"), &gTShader::create_new);

		godot::ClassDB::bind_method(godot::D_METHOD("setup", "p_language"), &gTShader::setup);
		godot::ClassDB::bind_method(godot::D_METHOD("is_setup"), &gTShader::is_setup);

		godot::ClassDB::bind_method(godot::D_METHOD("set_strings",                        "p_strings"),                         &gTShader::set_strings);
		godot::ClassDB::bind_method(godot::D_METHOD("set_strings_with_lengths",           "p_strings", "p_lengths"),            &gTShader::set_strings_with_lengths);
		godot::ClassDB::bind_method(godot::D_METHOD("set_strings_with_lengths_and_names", "p_strings", "p_lengths", "p_names"), &gTShader::set_strings_with_lengths_and_names);

		godot::ClassDB::bind_method(godot::D_METHOD("set_preamble", "p_preamble"), &gTShader::set_preamble);

		godot::ClassDB::bind_method(godot::D_METHOD("set_env_input", "p_lang", "p_env_stage", "p_client", "p_version"), &gTShader::set_env_input);
		godot::ClassDB::bind_method(godot::D_METHOD("set_env_client", "p_client", "p_version"), &gTShader::set_env_client);
		godot::ClassDB::bind_method(godot::D_METHOD("set_env_target", "p_lang", "p_version"), &gTShader::set_env_target);

		godot::ClassDB::bind_method(godot::D_METHOD("parse",   "p_built_in_resource", "p_default_version", "p_default_profile", "p_force_default_version_and_profile", "p_forward_compatible", "p_messages", "p_includer"), &gTShader::parse);
		godot::ClassDB::bind_method(godot::D_METHOD("parse_1", "p_built_in_resource", "p_default_version", "p_default_profile", "p_force_default_version_and_profile", "p_forward_compatible", "p_messages"), &gTShader::parse_1);
		godot::ClassDB::bind_method(godot::D_METHOD("parse_2", "p_built_in_resource", "p_default_version", "p_forward_compatible", "p_messages"), &gTShader::parse_2);
		godot::ClassDB::bind_method(godot::D_METHOD("parse_3", "p_built_in_resource", "p_default_version", "p_forward_compatible", "p_messages", "p_includer"), &gTShader::parse_3);

		godot::ClassDB::bind_method(godot::D_METHOD("get_info_log"), &gTShader::get_info_log);
		godot::ClassDB::bind_method(godot::D_METHOD("get_info_debug_log"), &gTShader::get_info_debug_log);
		godot::ClassDB::bind_method(godot::D_METHOD("get_stage"), &gTShader::get_stage);
		godot::ClassDB::bind_method(godot::D_METHOD("get_intermediate"), &gTShader::get_intermediate);
	}

	void gTShader::_setup_strings(godot::PackedStringArray p_strings) {
		strings_ptr.resize(p_strings.size());
		strings.resize(p_strings.size());
		for (size_t i = 0; i < p_strings.size(); ++i) {
			strings[i] = p_strings[i].utf8();
			strings_ptr[i] = strings[i].ptr();
		}
	}

	void gTShader::_setup_names(godot::PackedStringArray p_names) {
		names_ptr.resize(p_names.size());
		names.resize(p_names.size());
		for (size_t i = 0; i < p_names.size(); ++i) {
			names[i] = p_names[i].utf8();
			names_ptr[i] = names[i].ptr();
		}
	}

	void gTShader::_setup_lengths(godot::PackedInt32Array p_lengths) {
		lengths = p_lengths;
	}

	gTShader::gTShader() {}

	gTShader::~gTShader() {
		delete data;
	}

	godot::Ref<gTShader> gTShader::create_new(gGlobalSpace::gEShLanguage p_language) {
		godot::Ref<gTShader> ret = memnew(gTShader);
		ret->setup(p_language);
		return ret;
	}

	void gTShader::setup(gGlobalSpace::gEShLanguage p_language) {
		delete data;
		data = new glslang::TShader(gGlobalSpace::convert_to_glslang_enum(p_language));
	}

	bool gTShader::is_setup() const {
		return data != nullptr;
	}

	void gTShader::set_strings(godot::PackedStringArray p_strings) {
		ERR_FAIL_COND_MSG(!is_setup(), "gdglslangTShader::setup(...) must be called before this function.");
		_setup_strings(p_strings);
		data->setStrings(strings_ptr.data(), strings.size());
	}

	void gTShader::set_strings_with_lengths(godot::PackedStringArray p_strings, godot::PackedInt32Array p_lengths) {
		ERR_FAIL_COND_MSG(!is_setup(), "gdglslangTShader::setup(...) must be called before this function.");
		_setup_strings(p_strings);
		_setup_lengths(p_lengths);
		data->setStringsWithLengths(strings_ptr.data(), lengths.ptr(), strings.size());
	}

	void gTShader::set_strings_with_lengths_and_names(godot::PackedStringArray p_strings, godot::PackedInt32Array p_lengths, godot::PackedStringArray p_names) {
		ERR_FAIL_COND_MSG(!is_setup(), "gdglslangTShader::setup(...) must be called before this function.");
		_setup_strings(p_strings);
		_setup_lengths(p_lengths);
		_setup_names(p_names);
		data->setStringsWithLengthsAndNames(strings_ptr.data(), lengths.ptr(), names_ptr.data(), strings.size());
	}

	void gTShader::set_preamble(godot::String p_preamble) {
		ERR_FAIL_COND_MSG(!is_setup(), "gdglslangTShader::setup(...) must be called before this function.");
		preamble = p_preamble.utf8();
		data->setPreamble(preamble.ptr());
	}

	void gTShader::set_env_input(gGlobalSpace::gEShSource p_lang, gGlobalSpace::gEShLanguage p_env_stage, gGlobalSpace::gEShClient p_client, int p_version) {
		ERR_FAIL_COND_MSG(!is_setup(), "gdglslangTShader::setup(...) must be called before this function.");
		data->setEnvInput(gGlobalSpace::convert_to_glslang_enum(p_lang), gGlobalSpace::convert_to_glslang_enum(p_env_stage), gGlobalSpace::convert_to_glslang_enum(p_client), p_version);
	}

	void gTShader::set_env_client(gGlobalSpace::gEShClient p_client, gGlobalSpace::gEShTargetClientVersion p_version) {
		ERR_FAIL_COND_MSG(!is_setup(), "gdglslangTShader::setup(...) must be called before this function.");
		data->setEnvClient(gGlobalSpace::convert_to_glslang_enum(p_client), gGlobalSpace::convert_to_glslang_enum(p_version));
	}

	void gTShader::set_env_target(gGlobalSpace::gEShTargetLanguage p_lang, gGlobalSpace::gEShTargetLanguageVersion p_version) {
		ERR_FAIL_COND_MSG(!is_setup(), "gdglslangTShader::setup(...) must be called before this function.");
		data->setEnvTarget(gGlobalSpace::convert_to_glslang_enum(p_lang), gGlobalSpace::convert_to_glslang_enum(p_version));
	}

	bool gTShader::parse(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, gGlobalSpace::gEProfile p_default_profile, bool p_force_default_version_and_profile, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages, godot::Ref<gIncluderInterface> p_includer) {
		ERR_FAIL_COND_V_MSG(!is_setup(), false, "gdglslangTShader::setup(...) must be called before this function.");
		return data->parse(&p_built_in_resource->data, p_default_version, gGlobalSpace::convert_to_glslang_enum(p_default_profile), p_force_default_version_and_profile, p_forward_compatible, gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShMessages(int64_t(p_messages))), *p_includer->impl);
	}

	// forbid includer
	bool gTShader::parse_1(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, gGlobalSpace::gEProfile p_default_profile, bool p_force_default_version_and_profile, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages) {
		ERR_FAIL_COND_V_MSG(!is_setup(), false, "gdglslangTShader::setup(...) must be called before this function.");
		return data->parse(&p_built_in_resource->data, p_default_version, gGlobalSpace::convert_to_glslang_enum(p_default_profile), p_force_default_version_and_profile, p_forward_compatible, gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShMessages(int64_t(p_messages))));
	}

	// forbid includer
	bool gTShader::parse_2(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages) {
		ERR_FAIL_COND_V_MSG(!is_setup(), false, "gdglslangTShader::setup(...) must be called before this function.");
		return data->parse(&p_built_in_resource->data, p_default_version, p_forward_compatible, gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShMessages(int64_t(p_messages))));
	}

	bool gTShader::parse_3(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages, godot::Ref<gIncluderInterface> p_includer) {
		ERR_FAIL_COND_V_MSG(!is_setup(), false, "gdglslangTShader::setup(...) must be called before this function.");
		return data->parse(&p_built_in_resource->data, p_default_version, p_forward_compatible, gGlobalSpace::convert_to_glslang_enum(gGlobalSpace::gEShMessages(int64_t(p_messages))), *p_includer->impl);
	}

	godot::String gTShader::get_info_log() {
		ERR_FAIL_COND_V_MSG(!is_setup(), "", "gdglslangTShader::setup(...) must be called before this function.");
		return godot::String(data->getInfoLog());
	}

	godot::String gTShader::get_info_debug_log() {
		ERR_FAIL_COND_V_MSG(!is_setup(), "", "gdglslangTShader::setup(...) must be called before this function.");
		return godot::String(data->getInfoDebugLog());
	}

	gGlobalSpace::gEShLanguage gTShader::get_stage() const {
		ERR_FAIL_COND_V_MSG(!is_setup(), gGlobalSpace::gEShLanguage::EShLangVertex, "gdglslangTShader::setup(...) must be called before this function.");
		return gGlobalSpace::convert_to_gdglslang_enum(data->getStage());
	}

	godot::Ref<gTIntermediate> gTShader::get_intermediate() const {
		ERR_FAIL_COND_V_MSG(!is_setup(), godot::Ref<gTIntermediate>(), "gdglslangTShader::setup(...) must be called before this function.");
		godot::Ref<gTIntermediate> ret = memnew(gTIntermediate);
		ret->data = data->getIntermediate();
		return ret;
	}
}
