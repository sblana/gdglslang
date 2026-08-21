#include "includer_interface.hpp"
#include "includer_impl.hpp"
#include <godot_cpp/core/memory.hpp>

namespace gdglslang {

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
