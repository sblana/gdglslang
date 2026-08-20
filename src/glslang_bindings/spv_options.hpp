#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/SPIRV/GlslangToSpv.h>

namespace gdglslang {

	class gSpvOptions;
	using gdglslangSpvOptions = gSpvOptions;
	class gSpvOptions : public godot::RefCounted {
		GDCLASS(gdglslangSpvOptions, godot::RefCounted)
		protected:
			static void _bind_methods();

		public:
			glslang::SpvOptions data;

		#pragma region Exposed to godot
		public:
			gSpvOptions();
			~gSpvOptions();

		#pragma endregion
	};
}
