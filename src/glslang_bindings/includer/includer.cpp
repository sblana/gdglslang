#include "includer.hpp"
#include "includer_impl.hpp"
#include <godot_cpp/core/memory.hpp>

namespace gdglslang {

	void gIncluder::_bind_methods() {
		GDVIRTUAL_BIND(_should_include_system, "p_header_name", "p_includer_name", "p_inclusion_depth");
		GDVIRTUAL_BIND(_should_include_local, "p_header_name", "p_includer_name", "p_inclusion_depth");

		GDVIRTUAL_BIND(_include_system, "p_header_name", "p_includer_name", "p_inclusion_depth");
		GDVIRTUAL_BIND(_include_local, "p_header_name", "p_includer_name", "p_inclusion_depth");

		GDVIRTUAL_BIND(_pre_release_include, "p_include_result");
	}

	void gIncluder::add_include_result(godot::Ref<gIncludeResult> p_result) {
		include_results.insert(p_result);
	}

	void gIncluder::remove_include_result(godot::Ref<gIncludeResult> p_result) {
		include_results.erase(p_result);
	}

	glslang::TShader::Includer::IncludeResult *gIncluder::on_include_system(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) {
		godot::String header_name = godot::String(p_header_name);
		godot::String includer_name = godot::String(p_includer_name);

		bool should_include = false;
		if (GDVIRTUAL_IS_OVERRIDDEN(_should_include_system) && GDVIRTUAL_IS_OVERRIDDEN(_include_system)) {
			GDVIRTUAL_CALL(_should_include_system, header_name, includer_name, p_inclusion_depth, should_include);
		}

		if (!should_include) {
			return nullptr;
		}

		godot::Ref<gIncludeResult> g_include_result;
		GDVIRTUAL_CALL(_include_system, header_name, includer_name, p_inclusion_depth, g_include_result);
		add_include_result(g_include_result);

		return &g_include_result->data;
	}

	glslang::TShader::Includer::IncludeResult *gIncluder::on_include_local(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) {
		godot::String header_name = godot::String(p_header_name);
		godot::String includer_name = godot::String(p_includer_name);

		bool should_include = false;
		if (GDVIRTUAL_IS_OVERRIDDEN(_should_include_local) && GDVIRTUAL_IS_OVERRIDDEN(_include_local)) {
			GDVIRTUAL_CALL(_should_include_local, header_name, includer_name, p_inclusion_depth, should_include);
		}

		if (!should_include) {
			return nullptr;
		}

		godot::Ref<gIncludeResult> g_include_result;
		GDVIRTUAL_CALL(_include_local, header_name, includer_name, p_inclusion_depth, g_include_result);
		add_include_result(g_include_result);

		return &g_include_result->data;
	}

	void gIncluder::on_release_include(glslang::TShader::Includer::IncludeResult *p_result) {
		if (p_result == nullptr) {
			return;
		}

		godot::Ref<gIncludeResult> g_include_result = gIncludeResult::get_owner(p_result);
		GDVIRTUAL_CALL(_pre_release_include, g_include_result);
		remove_include_result(g_include_result);
	}

	gIncluder::gIncluder() {
		impl = new detail::gIncluderImpl(this);
	}

	gIncluder::~gIncluder() {
		delete impl;
	}
}
