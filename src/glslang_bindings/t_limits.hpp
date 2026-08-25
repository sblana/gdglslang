#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <glslang/glslang/Public/ShaderLang.h>
#include "binding_macros.hpp"

namespace gdglslang {

	class gTLimits;
	using GlslangTLimits = gTLimits;
	class gTLimits : public godot::RefCounted {
		GDCLASS(GlslangTLimits, godot::RefCounted)
		protected:
			static void _bind_methods();

		public:
			TLimits data;

		#pragma region Exposed to godot
		public:
			gTLimits();
			~gTLimits() {}

			L_DEF_SET_GET(bool, non_inductive_for_loops, data.nonInductiveForLoops)
			L_DEF_SET_GET(bool, while_loops, data.whileLoops)
			L_DEF_SET_GET(bool, do_while_loops, data.doWhileLoops)
			L_DEF_SET_GET(bool, generalUniformIndexing, data.generalUniformIndexing)
			L_DEF_SET_GET(bool, generalAttributeMatrixVectorIndexing, data.generalAttributeMatrixVectorIndexing)
			L_DEF_SET_GET(bool, generalVaryingIndexing, data.generalVaryingIndexing)
			L_DEF_SET_GET(bool, generalSamplerIndexing, data.generalSamplerIndexing)
			L_DEF_SET_GET(bool, generalVariableIndexing, data.generalVariableIndexing)
			L_DEF_SET_GET(bool, generalConstantMatrixVectorIndexing, data.generalConstantMatrixVectorIndexing)
		#pragma endregion
	};
}
