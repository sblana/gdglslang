#pragma once
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/callable.hpp>
#include "include_result.hpp"

namespace gdglslang {

	namespace detail {
		class gIncluderImpl;
	}

	class gIncluderInterface;
	using GlslangIncluderInterface = gIncluderInterface;
	class gIncluderInterface : public godot::RefCounted {
		GDCLASS(GlslangIncluderInterface, godot::RefCounted)
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
			godot::Ref<godot::RefCounted> user_data;

			// f(p_header_name: String, p_includer_name: String, p_inclusion_depth: int, p_user_data: RefCounted) -> bool
			// returns bool whether this should be included
			// if callback_should_include_xx is set, then the corresponding callback_include_xx should also be set
			godot::Callable callback_should_include_system;
			godot::Callable callback_should_include_local;

			// f(p_header_name: String, p_includer_name: String, p_inclusion_depth: int, p_user_data: RefCounted) -> GlslangIncludeResult
			// only called if should_include_XXX returns true.
			godot::Callable callback_include_system;
			godot::Callable callback_include_local;

			// f(p_result: GlslangIncludeResult, p_user_data: RefCounted) -> void
			// user doesn't control the release of p_result; this is called before p_result is released
			godot::Callable callback_pre_release_include;

			gIncluderInterface();
			~gIncluderInterface();

			void set_user_data(godot::Ref<godot::RefCounted> p_user_data) { user_data = p_user_data; }
			godot::Ref<godot::RefCounted> get_user_data() const { return user_data; }

			void set_callback_should_include_system(godot::Callable p_callback) { callback_should_include_system = p_callback; }
			godot::Callable get_callback_should_include_system() const { return callback_should_include_system; }

			void set_callback_should_include_local(godot::Callable p_callback) { callback_should_include_local = p_callback; }
			godot::Callable get_callback_should_include_local() const { return callback_should_include_local; }

			void set_callback_include_system(godot::Callable p_callback) { callback_include_system = p_callback; }
			godot::Callable get_callback_include_system() const { return callback_include_system; }

			void set_callback_include_local(godot::Callable p_callback) { callback_include_local = p_callback; }
			godot::Callable get_callback_include_local() const { return callback_include_local; }

			void set_callback_pre_release_include(godot::Callable p_callback) { callback_pre_release_include = p_callback; }
			godot::Callable get_callback_pre_release_include() const { return callback_pre_release_include; }
		#pragma endregion
	};
}
