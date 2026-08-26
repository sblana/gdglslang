#pragma once
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include "include_result.hpp"

namespace gdglslang {

	namespace detail {
		class gIncluderImpl;
	}

	class gIncluder;
	using GlslangIncluder = gIncluder;
	class gIncluder : public godot::RefCounted {
		GDCLASS(GlslangIncluder, godot::RefCounted)
		private:
			godot::HashSet<godot::Ref<gIncludeResult>> include_results;

		protected:
			static void _bind_methods();

		public:
			// public so that gTShader can get this
			detail::gIncluderImpl *impl;

			void add_include_result(godot::Ref<gIncludeResult> p_result);
			void remove_include_result(godot::Ref<gIncludeResult> p_result);

			// called by impl. call callbacks here and create resources
			glslang::TShader::Includer::IncludeResult *on_include_system(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth);
			glslang::TShader::Includer::IncludeResult *on_include_local (char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth);
			void on_release_include(glslang::TShader::Includer::IncludeResult *p_result);

		#pragma region Exposed to godot
		public:
			// returns bool whether this should be included
			// if _should_include_xx is defined, then the corresponding _include_xx should also be defined
			GDVIRTUAL3R(bool, _should_include_system, godot::String, godot::String, int)
			GDVIRTUAL3R(bool, _should_include_local, godot::String, godot::String, int)

			// only called if _should_include_XXX returns true.
			GDVIRTUAL3R(godot::Ref<gIncludeResult>, _include_system, godot::String, godot::String, int)
			GDVIRTUAL3R(godot::Ref<gIncludeResult>, _include_local, godot::String, godot::String, int)

			// user doesn't control the release of p_include_result; this is called before p_include_result is released
			GDVIRTUAL1(_pre_release_include, godot::Ref<gIncludeResult>)

			gIncluder();
			~gIncluder();
		#pragma endregion
	};
}
