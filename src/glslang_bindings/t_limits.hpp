#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/glslang/Public/ShaderLang.h>

namespace gdglslang {

	class gTLimits;
	using GlslangTLimits = gTLimits;
	class gTLimits : public godot::RefCounted {
		GDCLASS(GlslangTLimits, godot::RefCounted)
		protected:
			static void _bind_methods() {}

		public:
			TLimits data;

		#pragma region Exposed to godot
		public:
			gTLimits() {}
			~gTLimits() {}
		#pragma endregion
	};
}
