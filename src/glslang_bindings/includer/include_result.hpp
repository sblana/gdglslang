#pragma once
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/glslang/Public/ShaderLang.h>

namespace gdglslang {

	class gIncludeResult;
	using gdglslangIncludeResult = gIncludeResult;
	class gIncludeResult : public godot::RefCounted {
		GDCLASS(gdglslangIncludeResult, godot::RefCounted)
		private:
			godot::CharString header_name_string;
			godot::CharString header_data_string;
			godot::Ref<godot::RefCounted> user_data;

		protected:
			static void _bind_methods();

		public:
			glslang::TShader::Includer::IncludeResult data{"", "", 0, nullptr};

			gIncludeResult(godot::String p_header_name, godot::String p_header_data, godot::Ref<godot::RefCounted> p_user_data) :
				header_name_string(p_header_name.utf8()),
				header_data_string(p_header_data.utf8()),
				user_data(p_user_data),
				data(header_name_string.ptr(), header_data_string.ptr(), header_data_string.length(), reinterpret_cast<void *>(get_instance_id()))
			{}

			static godot::Ref<gIncludeResult> get_owner(glslang::TShader::Includer::IncludeResult *p_ptr);

		#pragma region Exposed to godot
		public:
			gIncludeResult() {}
			~gIncludeResult() {}

			static godot::Ref<gIncludeResult> create_new(godot::String p_header_name, godot::String p_header_data, godot::Ref<godot::RefCounted> p_user_data);

			godot::String get_header_name() const;
			godot::String get_header_data() const;
			godot::Ref<godot::RefCounted> get_user_data() const;
		#pragma endregion
	};
}
