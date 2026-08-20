#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/glslang/Public/ShaderLang.h>

namespace gdglslang {

	// class just for passing around an opaque glslang::TIntermediate *
	class gTIntermediate;
	using gdglslangTIntermediate = gTIntermediate;
	class gTIntermediate : public godot::RefCounted {
		GDCLASS(gdglslangTIntermediate, godot::RefCounted)
		private:
			glslang::TIntermediate *data;

		protected:
			static void _bind_methods() {}

		public:
			glslang::TIntermediate *get_data() const { return data; }
			void set_data(glslang::TIntermediate *p_ptr) { data = p_ptr; }

		#pragma region Exposed to godot
		public:
			gTIntermediate() {};
			~gTIntermediate() {};

		#pragma endregion
	};
}
