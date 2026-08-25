#include "t_limits.hpp"
#include <glslang/glslang/Public/ResourceLimits.h>

namespace gdglslang {

	void gTLimits::_bind_methods() {
		L_BIND_SET_GET(gTLimits, non_inductive_for_loops)
		L_BIND_SET_GET(gTLimits, while_loops)
		L_BIND_SET_GET(gTLimits, do_while_loops)
		L_BIND_SET_GET(gTLimits, generalUniformIndexing)
		L_BIND_SET_GET(gTLimits, generalAttributeMatrixVectorIndexing)
		L_BIND_SET_GET(gTLimits, generalVaryingIndexing)
		L_BIND_SET_GET(gTLimits, generalSamplerIndexing)
		L_BIND_SET_GET(gTLimits, generalVariableIndexing)
		L_BIND_SET_GET(gTLimits, generalConstantMatrixVectorIndexing)

		L_BIND_PROPERTY(godot::Variant::BOOL, non_inductive_for_loops)
		L_BIND_PROPERTY(godot::Variant::BOOL, while_loops)
		L_BIND_PROPERTY(godot::Variant::BOOL, do_while_loops)
		L_BIND_PROPERTY(godot::Variant::BOOL, generalUniformIndexing)
		L_BIND_PROPERTY(godot::Variant::BOOL, generalAttributeMatrixVectorIndexing)
		L_BIND_PROPERTY(godot::Variant::BOOL, generalVaryingIndexing)
		L_BIND_PROPERTY(godot::Variant::BOOL, generalSamplerIndexing)
		L_BIND_PROPERTY(godot::Variant::BOOL, generalVariableIndexing)
		L_BIND_PROPERTY(godot::Variant::BOOL, generalConstantMatrixVectorIndexing)
	}

	gTLimits::gTLimits() {
		data = GetDefaultResources()->limits;
	}
}
