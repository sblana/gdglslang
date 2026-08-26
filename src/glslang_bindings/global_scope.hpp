#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <glslang/glslang/Public/ShaderLang.h>
#include <cstdint>
#include "t_built_in_resource.hpp"
#include "t_intermediate.hpp"
#include "spv_options.hpp"
#include "spv_build_logger.hpp"

namespace gdglslang {

	class gGlobalScope;
	using GlslangGlobalScope = gGlobalScope;
	class gGlobalScope : public godot::Object {
		GDCLASS(GlslangGlobalScope, godot::Object)
		#pragma region Exposed to godot
		public:
			enum Language : std::uint32_t {
				LANGUAGE_VERTEX,
				LANGUAGE_TESS_CONTROL,
				LANGUAGE_TESS_EVALUATION,
				LANGUAGE_GEOMETRY,
				LANGUAGE_FRAGMENT,
				LANGUAGE_COMPUTE,
				LANGUAGE_RAY_GEN,
				LANGUAGE_RAY_GEN_NV = LANGUAGE_RAY_GEN,
				LANGUAGE_INTERSECT,
				LANGUAGE_INTERSECT_NV = LANGUAGE_INTERSECT,
				LANGUAGE_ANY_HIT,
				LANGUAGE_ANY_HIT_NV = LANGUAGE_ANY_HIT,
				LANGUAGE_CLOSEST_HIT,
				LANGUAGE_CLOSEST_HIT_NV = LANGUAGE_CLOSEST_HIT,
				LANGUAGE_MISS,
				LANGUAGE_MISS_NV = LANGUAGE_MISS,
				LANGUAGE_CALLABLE,
				LANGUAGE_CALLABLE_NV = LANGUAGE_CALLABLE,
				LANGUAGE_TASK,
				LANGUAGE_TASK_NV = LANGUAGE_TASK,
				LANGUAGE_MESH,
				LANGUAGE_MESH_NV = LANGUAGE_MESH,
				LANGUAGE_MAX
			};

			// enum gEShLanguageMask : std::uint32_t {};

			enum Source : std::uint32_t {
				SOURCE_NONE,
				SOURCE_GLSL,
				SOURCE_HLSL,
			};

			enum Client : std::uint32_t {
				CLIENT_NONE,
				CLIENT_VULKAN,
				CLIENT_OPEN_GL,
			};

			enum TargetLanguage : std::uint32_t {
				TARGET_LANGUAGE_NONE,
				TARGET_LANGUAGE_SPV,
			};

			enum TargetClientVersion : std::uint32_t {
				TARGET_CLIENT_VERSION_VULKAN_1_0  = (1 << 22),
				TARGET_CLIENT_VERSION_VULKAN_1_1  = (1 << 22) | (1 << 12),
				TARGET_CLIENT_VERSION_VULKAN_1_2  = (1 << 22) | (2 << 12),
				TARGET_CLIENT_VERSION_VULKAN_1_3  = (1 << 22) | (3 << 12),
				TARGET_CLIENT_VERSION_VULKAN_1_4  = (1 << 22) | (4 << 12),
				TARGET_CLIENT_VERSION_OPEN_GL_450 = 450,
			};

			enum TargetLanguageVersion : std::uint32_t {
				TARGET_LANGUAGE_VERSION_SPV_1_0 = (1 << 16),
				TARGET_LANGUAGE_VERSION_SPV_1_1 = (1 << 16) | (1 << 8),
				TARGET_LANGUAGE_VERSION_SPV_1_2 = (1 << 16) | (2 << 8),
				TARGET_LANGUAGE_VERSION_SPV_1_3 = (1 << 16) | (3 << 8),
				TARGET_LANGUAGE_VERSION_SPV_1_4 = (1 << 16) | (4 << 8),
				TARGET_LANGUAGE_VERSION_SPV_1_5 = (1 << 16) | (5 << 8),
				TARGET_LANGUAGE_VERSION_SPV_1_6 = (1 << 16) | (6 << 8),
			};

			enum Profile : std::uint32_t {
				PROFILE_BAD_PROFILE           = 0,
				PROFILE_NO_PROFILE            = (1 << 0),
				PROFILE_CORE_PROFILE          = (1 << 1),
				PROFILE_COMPATIBILITY_PROFILE = (1 << 2),
				PROFILE_ES_PROFILE            = (1 << 3),
			};

			enum Messages : std::uint32_t {
				MESSAGE_DEFAULT                  = 0,
				MESSAGE_RELAXED_ERRORS           = (1 << 0),
				MESSAGE_SUPPRESS_WARNINGS        = (1 << 1),
				MESSAGE_AST                      = (1 << 2),
				MESSAGE_SPV_RULES                = (1 << 3),
				MESSAGE_VULKAN_RULES             = (1 << 4),
				MESSAGE_ONLY_PREPROCESSOR        = (1 << 5),
				MESSAGE_READ_HLSL                = (1 << 6),
				MESSAGE_CASCADING_ERRORS         = (1 << 7),
				MESSAGE_KEEP_UNCALLED            = (1 << 8),
				MESSAGE_HLSL_OFFSETS             = (1 << 9),
				MESSAGE_DEBUG_INFO               = (1 << 10),
				MESSAGE_HLSL_ENABLE16_BIT_TYPES  = (1 << 11),
				MESSAGE_HLSL_LEGALIZATION        = (1 << 12),
				MESSAGE_HLSL_DX9_COMPATIBLE      = (1 << 13),
				MESSAGE_BUILTIN_SYMBOL_TABLE     = (1 << 14),
				MESSAGE_ENHANCED                 = (1 << 15),
				MESSAGE_ABSOLUTE_PATH            = (1 << 16),
				MESSAGE_DISPLAY_ERROR_COLUMN     = (1 << 17),
				MESSAGE_LINK_TIME_OPTIMIZATION   = (1 << 18),
				MESSAGE_VALIDATE_CROSS_STAGE_IO  = (1 << 19),
				MESSAGE_RELAX_SET_BINDING_LIMITS = (1 << 20),
			};
		#pragma endregion

		protected:
			static void _bind_methods();

		public:
			static EShLanguage                       convert_to_glslang_enum(Language              p_value);
			static glslang::EShSource                convert_to_glslang_enum(Source                p_value);
			static glslang::EShClient                convert_to_glslang_enum(Client                p_value);
			static glslang::EShTargetLanguage        convert_to_glslang_enum(TargetLanguage        p_value);
			static glslang::EShTargetClientVersion   convert_to_glslang_enum(TargetClientVersion   p_value);
			static glslang::EShTargetLanguageVersion convert_to_glslang_enum(TargetLanguageVersion p_value);
			static EProfile                          convert_to_glslang_enum(Profile                 p_value);
			static EShMessages                       convert_to_glslang_enum(Messages              p_value);

			static Language              convert_to_gdglslang_enum(EShLanguage                       p_value);
			// static Source                convert_to_gdglslang_enum(glslang::EShSource                p_value);
			// static Client                convert_to_gdglslang_enum(glslang::EShClient                p_value);
			// static TargetLanguage        convert_to_gdglslang_enum(glslang::EShTargetLanguage        p_value);
			// static TargetClientVersion   convert_to_gdglslang_enum(glslang::EShTargetClientVersion   p_value);
			// static TargetLanguageVersion convert_to_gdglslang_enum(glslang::EShTargetLanguageVersion p_value);
			// static Profile                 convert_to_gdglslang_enum(EProfile                          p_value);
			// static Messages              convert_to_gdglslang_enum(EShMessages                       p_value);

		#pragma region Exposed to godot
		public:
			// ShaderLang.h functions
			static bool initialize_process();
			static void finalize_process();

			// ResourceLimits.h functions
			static godot::Ref<gTBuiltInResource> get_default_resources();

			// GlslangToSpv.h functions
			static godot::String get_spirv_version();
			static int get_spirv_generator_version();
			static godot::PackedByteArray glslang_to_spv(godot::Ref<gTIntermediate> p_intermediate, godot::Ref<gSpvBuildLogger> p_logger, godot::Ref<gSpvOptions> p_options);
			static godot::PackedByteArray glslang_to_spv_1(godot::Ref<gTIntermediate> p_intermediate, godot::Ref<gSpvOptions> p_options);
		#pragma endregion
	};
}

VARIANT_ENUM_CAST(gdglslang::GlslangGlobalScope::Language);
VARIANT_ENUM_CAST(gdglslang::GlslangGlobalScope::Source);
VARIANT_ENUM_CAST(gdglslang::GlslangGlobalScope::Client);
VARIANT_ENUM_CAST(gdglslang::GlslangGlobalScope::TargetLanguage);
VARIANT_ENUM_CAST(gdglslang::GlslangGlobalScope::TargetClientVersion);
VARIANT_ENUM_CAST(gdglslang::GlslangGlobalScope::TargetLanguageVersion);
VARIANT_ENUM_CAST(gdglslang::GlslangGlobalScope::Profile);
VARIANT_BITFIELD_CAST(gdglslang::GlslangGlobalScope::Messages);
