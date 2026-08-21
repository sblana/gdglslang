#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/glslang/Public/ShaderLang.h>
#include "t_limits.hpp"

namespace gdglslang {

	class gTBuiltInResource;
	using gdglslangTBuiltInResource = gTBuiltInResource;
	class gTBuiltInResource : public godot::RefCounted {
		GDCLASS(gdglslangTBuiltInResource, godot::RefCounted)
		protected:
			static void _bind_methods();

		public:
			TBuiltInResource data;

		#pragma region Exposed to godot
		public:
			godot::Ref<gTLimits> limits;

			gTBuiltInResource() { limits = memnew(gTLimits); }
			~gTBuiltInResource() {}
		#pragma endregion
	};
}
