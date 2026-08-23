#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/glslang/Public/ShaderLang.h>

namespace gdglslang {

	// class just for passing around an opaque glslang::TIntermediate *
	class gTIntermediate;
	using gdglslangTIntermediate = gTIntermediate;
	class gTIntermediate : public godot::RefCounted {
		GDCLASS(gdglslangTIntermediate, godot::RefCounted)
		protected:
			static void _bind_methods() {}

		public:
			glslang::TIntermediate *data = nullptr;

		#pragma region Exposed to godot
		public:
			gTIntermediate() {}
			~gTIntermediate() {}
		#pragma endregion
	};
}
