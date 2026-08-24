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
			std::vector<godot::CharString> strings;
			std::vector<godot::CharString> names;
			std::vector<char const *> strings_ptr;
			std::vector<char const *> names_ptr;
			godot::PackedInt32Array lengths;

			godot::CharString preamble;

			void _setup_strings(godot::PackedStringArray p_strings);
			void _setup_names(godot::PackedStringArray p_names);
			void _setup_lengths(godot::PackedInt32Array p_lengths);

		protected:
			static void _bind_methods();

		public:
			glslang::TShader *data = nullptr;

		#pragma region Exposed to godot
		public:
			// Dummy constructor. Need to call setup(...) or create_new(...)
			gTShader();
			~gTShader();

			static godot::Ref<gTShader> create_new(gGlobalSpace::gEShLanguage p_language);

			void setup(gGlobalSpace::gEShLanguage p_language);
			bool is_setup() const;

			void set_strings(godot::PackedStringArray p_strings);
			void set_strings_with_lengths(godot::PackedStringArray p_strings, godot::PackedInt32Array p_lengths);
			void set_strings_with_lengths_and_names(godot::PackedStringArray p_strings, godot::PackedInt32Array p_lengths, godot::PackedStringArray p_names);
			void set_preamble(godot::String p_preamble);
			// ...

			void set_env_input(gGlobalSpace::gEShSource p_lang, gGlobalSpace::gEShLanguage p_env_stage, gGlobalSpace::gEShClient p_client, int p_version);
			void set_env_client(gGlobalSpace::gEShClient p_client, gGlobalSpace::gEShTargetClientVersion p_version);
			void set_env_target(gGlobalSpace::gEShTargetLanguage p_lang, gGlobalSpace::gEShTargetLanguageVersion p_version);

			bool parse(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, gGlobalSpace::gEProfile p_default_profile, bool p_force_default_version_and_profile, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages, godot::Ref<gIncluderInterface> p_includer);
			// forbid includer
			bool parse_1(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, gGlobalSpace::gEProfile p_default_profile, bool p_force_default_version_and_profile, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages);
			// forbid includer
			bool parse_2(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages);
			bool parse_3(godot::Ref<gTBuiltInResource> p_built_in_resource, int p_default_version, bool p_forward_compatible, godot::BitField<gGlobalSpace::gEShMessages> p_messages, godot::Ref<gIncluderInterface> p_includer);

			godot::String get_info_log();
			godot::String get_info_debug_log();
			gGlobalSpace::gEShLanguage get_stage() const;
			godot::Ref<gTIntermediate> get_intermediate() const;
		#pragma endregion
	};
}
