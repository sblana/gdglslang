#pragma once
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/object.hpp>
#include <glslang/glslang/Public/ShaderLang.h>

namespace gdglslang {

	class gIncludeResult;
	using gdglslangIncludeResult = gIncludeResult;
	class gIncludeResult : public godot::Object {
		GDCLASS(gdglslangIncludeResult, godot::Object)
		protected:
			static void _bind_methods();

		public:
			glslang::TShader::Includer::IncludeResult data;

		#pragma region Exposed to godot
		public:
			gIncludeResult();
			~gIncludeResult();

			godot::String get_header_name() const;
			godot::PackedByteArray get_header_data() const;
			godot::Ref<godot::RefCounted> get_user_data() const;

			void set_header_name(godot::String const p_name);
			void set_header_data(godot::PackedByteArray const p_data);
			void set_user_data(godot::Ref<godot::RefCounted> const p_data);

		#pragma endregion
	};
}
