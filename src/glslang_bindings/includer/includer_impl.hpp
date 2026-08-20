#pragma once
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/weak_ref.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <glslang/glslang/Public/ShaderLang.h>
#include "includer_interface.hpp"

namespace gdglslang {

	namespace detail {

		class gIncluderImpl : public glslang::TShader::Includer {
			private:
				// gIncluderInterface
				godot::Ref<godot::WeakRef> owner;

				bool has_owner() const;

				godot::Ref<gIncluderInterface> get_owner() const;

			public:
				virtual IncludeResult *includeSystem(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) override;
				virtual IncludeResult *includeLocal (char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) override;
				virtual void releaseInclude(IncludeResult *p_result) override;

				gIncluderImpl(godot::Ref<gIncluderInterface> p_owner);
				virtual ~gIncluderImpl() override {}
		};
	}
}
