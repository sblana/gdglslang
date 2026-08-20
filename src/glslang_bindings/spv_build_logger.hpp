#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/SPIRV/Logger.h>

namespace gdglslang {

	class gSpvBuildLogger;
	using gdglslangSpvBuildLogger = gSpvBuildLogger;
	class gSpvBuildLogger : public godot::RefCounted {
		GDCLASS(gdglslangSpvBuildLogger, godot::RefCounted)
		private:
			spv::SpvBuildLogger *data;

		protected:
			static void _bind_methods();

		#pragma region Exposed to godot
		public:
			gSpvBuildLogger();
			~gSpvBuildLogger();

			godot::String get_all_messages() const;

		#pragma endregion
	};
}
