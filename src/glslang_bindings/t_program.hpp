#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include "t_shader.hpp"
#include "t_intermediate.hpp"

namespace gdglslang {

	class gTProgram;
	using gdglslangTProgram = gTProgram;
	class gTProgram : public godot::RefCounted {
		GDCLASS(gdglslangTProgram, godot::RefCounted)
		private:
			glslang::TProgram *data;

		protected:
			static void _bind_methods();

		#pragma region Exposed to godot
		public:
			gTProgram();
			~gTProgram();

			void add_shader(godot::Ref<gTShader> p_shader);

			bool link(gGlobalSpace::EShMessages p_messages);

			godot::String get_info_log();
			godot::String get_info_debug_log();

			godot::Ref<gTIntermediate> get_intermediate(gGlobalSpace::EShLanguage p_stage) const;
		#pragma endregion
	};
}
