#pragma once
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <unordered_map>
#include "include_result.hpp"

namespace gdglslang {

	namespace detail {
		class gIncluderImpl;
	}

	class gIncluderInterface;
	using gdglslangIncluderInterface = gIncluderInterface;
	class gIncluderInterface : public godot::RefCounted {
		GDCLASS(gdglslangIncluderInterface, godot::RefCounted)
		private:
			std::unordered_map<glslang::TShader::Includer::IncludeResult *, godot::ObjectID> glslang_include_result_to_owner_map;

		protected:
			static void _bind_methods();

		public:
			// public so that gTShader can get this
			detail::gIncluderImpl *impl;

			gIncludeResult *create_g_include_result();
			// p_id and p_ptr should be the same object
			void cleanup_g_include_result(godot::ObjectID p_id, gIncludeResult *p_ptr);
			gIncludeResult *get_owner(glslang::TShader::Includer::IncludeResult *p_ptr) const;

			// called by impl. call callbacks here and create resources
			glslang::TShader::Includer::IncludeResult *on_include_system(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth);
			glslang::TShader::Includer::IncludeResult *on_include_local (char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth);
			void on_release_include(glslang::TShader::Includer::IncludeResult *p_result);

		#pragma region Exposed to godot
		public:
			godot::Ref<godot::RefCounted> user_data;

			// f(p_header_name: String, p_includer_name String, p_inclusion_depth int, p_user_data: RefCounted) -> bool
			// returns bool whether this should be included
			// if callback_should_include_xx is set, then the corresponding callback_include_xx should also be set
			godot::Callable callback_should_include_system;
			godot::Callable callback_should_include_local;

			// f(p_header_name: String, p_includer_name String, p_inclusion_depth int, p_result: gdglslangIncludeResult, p_user_data: RefCounted) -> void
			// only called if should_include_XXX returns true.
			// note that user doesn't create gdglslangIncludeResult: user has the ability to modify p_result.
			godot::Callable callback_include_system;
			godot::Callable callback_include_local;

			// f(p_result: gdglslangIncludeResult, p_user_data: RefCounted) -> void
			// user doesn't control the release of p_result; this is called before p_result is released
			godot::Callable callback_pre_release_include;

			gIncluderInterface();
			~gIncluderInterface();

		#pragma endregion
	};
}
