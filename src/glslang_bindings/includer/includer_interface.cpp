#include "includer_interface.hpp"
#include "includer_impl.hpp"
#include <godot_cpp/core/memory.hpp>

namespace gdglslang {

	void gIncluderInterface::_bind_methods() {
		godot::ClassDB::bind_method(godot::D_METHOD("set_user_data", "p_user_data"), &gIncluderInterface::set_user_data);
		godot::ClassDB::bind_method(godot::D_METHOD("get_user_data"), &gIncluderInterface::get_user_data);

		godot::ClassDB::bind_method(godot::D_METHOD("set_callback_should_include_system", "p_callback"), &gIncluderInterface::set_callback_should_include_system);
		godot::ClassDB::bind_method(godot::D_METHOD("get_callback_should_include_system"), &gIncluderInterface::get_callback_should_include_system);

		godot::ClassDB::bind_method(godot::D_METHOD("set_callback_should_include_local", "p_callback"), &gIncluderInterface::set_callback_should_include_local);
		godot::ClassDB::bind_method(godot::D_METHOD("get_callback_should_include_local"), &gIncluderInterface::get_callback_should_include_local);

		godot::ClassDB::bind_method(godot::D_METHOD("set_callback_include_system", "p_callback"), &gIncluderInterface::set_callback_include_system);
		godot::ClassDB::bind_method(godot::D_METHOD("get_callback_include_system"), &gIncluderInterface::get_callback_include_system);

		godot::ClassDB::bind_method(godot::D_METHOD("set_callback_include_local", "p_callback"), &gIncluderInterface::set_callback_include_local);
		godot::ClassDB::bind_method(godot::D_METHOD("get_callback_include_local"), &gIncluderInterface::get_callback_include_local);

		godot::ClassDB::bind_method(godot::D_METHOD("set_callback_pre_release_include", "p_callback"), &gIncluderInterface::set_callback_pre_release_include);
		godot::ClassDB::bind_method(godot::D_METHOD("get_callback_pre_release_include"), &gIncluderInterface::get_callback_pre_release_include);

		ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "user_data"), "set_user_data", "get_user_data");
		ADD_PROPERTY(godot::PropertyInfo(godot::Variant::CALLABLE, "callback_should_include_system"), "set_callback_should_include_system", "get_callback_should_include_system");
		ADD_PROPERTY(godot::PropertyInfo(godot::Variant::CALLABLE, "callback_should_include_local"), "set_callback_should_include_local", "get_callback_should_include_local");
		ADD_PROPERTY(godot::PropertyInfo(godot::Variant::CALLABLE, "callback_include_system"), "set_callback_include_system", "get_callback_include_system");
		ADD_PROPERTY(godot::PropertyInfo(godot::Variant::CALLABLE, "callback_include_local"), "set_callback_include_local", "get_callback_include_local");
		ADD_PROPERTY(godot::PropertyInfo(godot::Variant::CALLABLE, "callback_pre_release_include"), "set_callback_pre_release_include", "get_callback_pre_release_include");
	}

	void gIncluderInterface::add_include_result(godot::Ref<gIncludeResult> p_result) {
		include_results.insert(p_result);
	}

	void gIncluderInterface::remove_include_result(godot::Ref<gIncludeResult> p_result) {
		include_results.erase(p_result);
	}

	glslang::TShader::Includer::IncludeResult *gIncluderInterface::on_include_system(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) {
		godot::String header_name = godot::String(p_header_name);
		godot::String includer_name = godot::String(p_includer_name);

		bool should_include = false;
		if (callback_should_include_system.is_valid() && callback_include_system.is_valid()) {
			should_include = callback_should_include_system.call(header_name, includer_name, p_inclusion_depth, user_data);
		}

		if (!should_include) {
			return nullptr;
		}

		godot::Ref<gIncludeResult> g_include_result = callback_include_system.call(header_name, includer_name, p_inclusion_depth, user_data);
		add_include_result(g_include_result);

		return &g_include_result->data;
	}

	glslang::TShader::Includer::IncludeResult *gIncluderInterface::on_include_local(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) {
		godot::String header_name = godot::String(p_header_name);
		godot::String includer_name = godot::String(p_includer_name);

		bool should_include = false;
		if (callback_should_include_local.is_valid() && callback_include_local.is_valid()) {
			should_include = callback_should_include_local.call(header_name, includer_name, p_inclusion_depth, user_data);
		}

		if (!should_include) {
			return nullptr;
		}

		godot::Ref<gIncludeResult> g_include_result = callback_include_local.call(header_name, includer_name, p_inclusion_depth, user_data);
		add_include_result(g_include_result);

		return &g_include_result->data;
	}

	void gIncluderInterface::on_release_include(glslang::TShader::Includer::IncludeResult *p_result) {
		if (p_result == nullptr) {
			return;
		}

		godot::Ref<gIncludeResult> g_include_result = gIncludeResult::get_owner(p_result);

		if (callback_pre_release_include.is_valid()) {
			callback_pre_release_include.call(g_include_result, user_data);
		}

		remove_include_result(g_include_result);
	}

	gIncluderInterface::gIncluderInterface() {
		impl = new detail::gIncluderImpl(this);
	}

	gIncluderInterface::~gIncluderInterface() {
		delete impl;
	}
}
