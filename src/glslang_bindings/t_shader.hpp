#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include "global_space.hpp"
#include "includer/includer_interface.hpp"
#include "t_intermediate.hpp"

namespace gdglslang {

	class gTShader;
	using gdglslangTShader = gTShader;
	class gTShader : public godot::RefCounted {
		GDCLASS(gdglslangTShader, godot::RefCounted)
		private:
			glslang::TShader *data;

		protected:
			static void _bind_methods();

		#pragma region Exposed to godot
		public:
			// Dummy constructor. Need to call init(...) or create_new(...)
			gTShader();
			~gTShader();
			void init(gGlobalSpace::EShLanguage p_e_sh_language);
			static godot::Ref<gTShader> create_new(gGlobalSpace::EShLanguage p_e_sh_language);

			void set_strings(godot::PackedStringArray p_strings);
			// setStringsWithLengths(...)
			void set_preamble(godot::String p_preamble);
			// ...

			void set_env_input(gGlobalSpace::EShSource p_lang, gGlobalSpace::EShLanguage p_env_stage, gGlobalSpace::EShClient p_client, int p_version);
			void set_env_client(gGlobalSpace::EShClient p_client, gGlobalSpace::EShTargetClientVersion p_version);
			void set_env_target(gGlobalSpace::EShTargetLanguage p_lang, gGlobalSpace::EShTargetLanguageVersion p_version);

			bool parse(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, gGlobalSpace::EProfile p_default_profile, bool p_force_default_version_and_profile, bool p_forward_compatible, gGlobalSpace::EShMessages p_messages, godot::Ref<gIncluderInterface> p_includer);
			// forbid includer
			bool parse_1(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, gGlobalSpace::EProfile p_default_profile, bool p_force_default_version_and_profile, bool p_forward_compatible, gGlobalSpace::EShMessages p_messages);
			// forbid includer
			bool parse_2(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, bool p_forward_compatible, gGlobalSpace::EShMessages p_messages);
			bool parse_3(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, bool p_forward_compatible, gGlobalSpace::EShMessages p_messages, godot::Ref<gIncluderInterface> p_includer);

			godot::String get_info_log();
			godot::String get_info_debug_log();

			gGlobalSpace::EShLanguage get_stage() const;

			godot::Ref<gTIntermediate> get_intermediate() const;

		#pragma endregion
	};
}
