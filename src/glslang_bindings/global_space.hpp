#pragma oncee

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/object.hpp>
#include <cstdint>
#include "t_built_in_resource.hpp"
#include "t_intermediate.hpp"
#include "spv_options.hpp"
#include "spv_build_logger.hpp"

namespace gdglslang {

	class gGlobalSpace;
	using gdglslangGlobalSpace = gGlobalSpace;
	class gGlobalSpace : public godot::Object {
		GDCLASS(gdglslangGlobalSpace, godot::Object)
		protected:
			static void _bind_methods();

		#pragma region Exposed to godot
		public:
			enum EShLanguage : std::uint32_t {
				EShLangVertex,
				EShLangTessControl,
				EShLangTessEvaluation,
				EShLangGeometry,
				EShLangFragment,
				EShLangCompute,
				EShLangRayGen,
				EShLangRayGenNV = EShLangRayGen,
				EShLangIntersect,
				EShLangIntersectNV = EShLangIntersect,
				EShLangAnyHit,
				EShLangAnyHitNV = EShLangAnyHit,
				EShLangClosestHit,
				EShLangClosestHitNV = EShLangClosestHit,
				EShLangMiss,
				EShLangMissNV = EShLangMiss,
				EShLangCallable,
				EShLangCallableNV = EShLangCallable,
				EShLangTask,
				EShLangTaskNV = EShLangTask,
				EShLangMesh,
				EShLangMeshNV = EShLangMesh,
			};

			// enum EShLanguageMask : std::uint32_t {};

			enum EShSource : std::uint32_t {
				EShSourceNone,
				EShSourceGlsl,
				EShSourceHlsl,
			};

			enum EShClient : std::uint32_t {
				EShClientNone,
				EShClientVulkan,
				EShClientOpenGL,
			};

			enum EShTargetLanguage : std::uint32_t {
				EShTargetNone,
				EShTargetSpv,
			};

			enum EShTargetClientVersion : std::uint32_t {
				EShTargetVulkan_1_0 = (1 << 22),
				EShTargetVulkan_1_1 = (1 << 22) | (1 << 12),
				EShTargetVulkan_1_2 = (1 << 22) | (2 << 12),
				EShTargetVulkan_1_3 = (1 << 22) | (3 << 12),
				EShTargetVulkan_1_4 = (1 << 22) | (4 << 12),
				EShTargetOpenGL_450 = 450,
			};

			enum EShTargetLanguageVersion : std::uint32_t {
				EShTargetSpv_1_0 = (1 << 16),
				EShTargetSpv_1_1 = (1 << 16) | (1 << 8),
				EShTargetSpv_1_2 = (1 << 16) | (2 << 8),
				EShTargetSpv_1_3 = (1 << 16) | (3 << 8),
				EShTargetSpv_1_4 = (1 << 16) | (4 << 8),
				EShTargetSpv_1_5 = (1 << 16) | (5 << 8),
				EShTargetSpv_1_6 = (1 << 16) | (6 << 8),
			};

			enum EProfile : std::uint32_t {
				EBadProfile           = 0,
				ENoProfile            = (1 << 0),
				ECoreProfile          = (1 << 1),
				ECompatibilityProfile = (1 << 2),
				EEsProfile            = (1 << 3),
			};

			enum EShMessages : std::uint32_t {
				EShMsgDefault               = 0,
				EShMsgRelaxedErrors         = (1 << 0),
				EShMsgSuppressWarnings      = (1 << 1),
				EShMsgAST                   = (1 << 2),
				EShMsgSpvRules              = (1 << 3),
				EShMsgVulkanRules           = (1 << 4),
				EShMsgOnlyPreprocessor      = (1 << 5),
				EShMsgReadHlsl              = (1 << 6),
				EShMsgCascadingErrors       = (1 << 7),
				EShMsgKeepUncalled          = (1 << 8),
				EShMsgHlslOffsets           = (1 << 9),
				EShMsgDebugInfo             = (1 << 10),
				EShMsgHlslEnable16BitTypes  = (1 << 11),
				EShMsgHlslLegalization      = (1 << 12),
				EShMsgHlslDX9Compatible     = (1 << 13),
				EShMsgBuiltinSymbolTable    = (1 << 14),
				EShMsgEnhanced              = (1 << 15),
				EShMsgAbsolutePath          = (1 << 16),
				EShMsgDisplayErrorColumn    = (1 << 17),
				EShMsgLinkTimeOptimization  = (1 << 18),
				EShMsgValidateCrossStageIO  = (1 << 19),
				EShMsgRelaxSetBindingLimits = (1 << 20),
			};

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

VARIANT_ENUM_CAST(gdglslang::gGlobalSpace::EShLanguage);
