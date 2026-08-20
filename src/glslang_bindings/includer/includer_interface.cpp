#include "includer_interface.hpp"
#include "glslang_includer_impl.hpp"
#include <godot_cpp/core/memory.hpp>

namespace gdglslang {

	gIncludeResult *gIncluderInterface::create_g_include_result() {
		gIncludeResult *ret = memnew(gIncludeResult);
		glslang_include_result_to_owner_map.insert({ &ret->data, godot::ObjectID(ret->get_instance_id()) });
		return ret;
	}

	void gIncluderInterface::cleanup_g_include_result(godot::ObjectID p_id, gIncludeResult *p_ptr) {
		ERR_FAIL_NULL(p_ptr);

		if (godot::ObjectDB::get_instance(p_id) != nullptr) {
			ERR_FAIL_COND(godot::ObjectDB::get_instance(p_id) != p_ptr);
			godot::memdelete(p_ptr);
		}

		glslang::TShader::Includer::IncludeResult *key = &p_ptr->data;
		ERR_FAIL_COND_EDMSG(glslang_include_result_to_owner_map.count(key) == 0, "p_ptr is not registered in this gIncluderInterface.");

		godot::ObjectID value = glslang_include_result_to_owner_map.at(key);
		ERR_FAIL_COND_EDMSG(value != p_id, "p_id mismatch with the registered id.");

		glslang_include_result_to_owner_map.erase(key);
	}

	gIncludeResult *gIncluderInterface::get_owner(glslang::TShader::Includer::IncludeResult *p_ptr) const {
		if (glslang_include_result_to_owner_map.count(p_ptr) == 0) {
			return nullptr;
		}

		godot::Object *value = godot::ObjectDB::get_instance(glslang_include_result_to_owner_map.at(p_ptr));
		ERR_FAIL_NULL_V(value, nullptr);

		return godot::Object::cast_to<gIncludeResult>(value);
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

		gIncludeResult *g_include_result = create_g_include_result();
		godot::ObjectID g_include_result_object_id = godot::ObjectID(g_include_result->get_instance_id());
		callback_include_system.call(header_name, includer_name, p_inclusion_depth, g_include_result, user_data);
		bool was_freed_during_callback = godot::ObjectDB::get_instance(g_include_result_object_id) == nullptr;

		if (was_freed_during_callback) {
			cleanup_g_include_result(g_include_result_object_id, g_include_result);
			ERR_FAIL_V_EDMSG(nullptr, "`p_result: gdglslangIncludeResult` was freed in callback_include_system.");
		}

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

		gIncludeResult *g_include_result = create_g_include_result();
		godot::ObjectID g_include_result_object_id = godot::ObjectID(g_include_result->get_instance_id());
		callback_include_local.call(header_name, includer_name, p_inclusion_depth, g_include_result, user_data);
		bool was_freed_during_callback = godot::ObjectDB::get_instance(g_include_result_object_id) == nullptr;

		if (was_freed_during_callback) {
			cleanup_g_include_result(g_include_result_object_id, g_include_result);
			ERR_FAIL_V_EDMSG(nullptr, "`p_result: gdglslangIncludeResult` was freed in callback_include_local.");
		}

		return &g_include_result->data;
	}

	void gIncluderInterface::on_release_include(glslang::TShader::Includer::IncludeResult *p_result) {
		if (p_result == nullptr) {
			return;
		}

		gIncludeResult *g_include_result = get_owner(p_result);
		godot::ObjectID g_include_result_object_id = godot::ObjectID(g_include_result->get_instance_id());

		if (callback_pre_release_include.is_valid()) {
			callback_pre_release_include.call(g_include_result, user_data);
		}

		bool was_freed_during_callback = godot::ObjectDB::get_instance(g_include_result_object_id) == nullptr;

		cleanup_g_include_result(g_include_result_object_id, g_include_result);

		ERR_FAIL_COND_EDMSG(was_freed_during_callback, "`p_result: gdglslangIncludeResult` was freed in callback_pre_release_include.");
	}

	gIncluderInterface::gIncluderInterface() {
		impl = new detail::gIncluderImpl(this);
	}

	gIncluderInterface::~gIncluderInterface() {
		delete impl;
	}
}
