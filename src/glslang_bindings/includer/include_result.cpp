#include "include_result.hpp"
#include <string>

namespace gdglslang {

	void gIncludeResult::_bind_methods() {
		godot::ClassDB::bind_static_method(get_class_static(), godot::D_METHOD("create_new", "p_header_name", "p_header_data", "p_user_data"), &gIncludeResult::create_new);

		godot::ClassDB::bind_method(godot::D_METHOD("get_header_name"), &gIncludeResult::get_header_name);
		godot::ClassDB::bind_method(godot::D_METHOD("get_header_data"), &gIncludeResult::get_header_data);
		godot::ClassDB::bind_method(godot::D_METHOD("get_user_data"), &gIncludeResult::get_user_data);
	}

	godot::Ref<gIncludeResult> gIncludeResult::get_owner(glslang::TShader::Includer::IncludeResult *p_ptr) {
		godot::ObjectID id = godot::ObjectID(reinterpret_cast<uint64_t>(p_ptr->userData));
		return godot::Ref(godot::Object::cast_to<gIncludeResult>(godot::ObjectDB::get_instance(id)));
	}

	godot::Ref<gIncludeResult> gIncludeResult::create_new(godot::String p_header_name, godot::String p_header_data, godot::Ref<godot::RefCounted> p_user_data) {
		godot::Ref<gIncludeResult> ret = memnew(gIncludeResult(p_header_name, p_header_data, p_user_data));
		return ret;
	}

	godot::String gIncludeResult::get_header_name() const {
		return data.headerName.c_str();
	}

	godot::String gIncludeResult::get_header_data() const {
		return godot::String(data.headerData);
	}

	godot::Ref<godot::RefCounted> gIncludeResult::get_user_data() const {
		return user_data;
	}
}
