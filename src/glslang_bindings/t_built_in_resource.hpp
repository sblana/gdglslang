#pragma once
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <glslang/glslang/Public/ShaderLang.h>
#include "t_limits.hpp"
#include "binding_macros.hpp"

namespace gdglslang {

	class gTBuiltInResource;
	using GlslangTBuiltInResource = gTBuiltInResource;
	class gTBuiltInResource : public godot::RefCounted {
		GDCLASS(GlslangTBuiltInResource, godot::RefCounted)
		protected:
			static void _bind_methods();

		public:
			TBuiltInResource data;

		#pragma region Exposed to godot
		public:
			godot::Ref<gTLimits> limits;

			gTBuiltInResource();
			~gTBuiltInResource() {}

			// TODO: implement:
			// void set_limits(godot::Ref<gTLimits> p_value);
			// godot::Ref<gTLimits> get_limits() const;

			L_DEF_SET_GET(int, max_lights, data.maxLights)
			L_DEF_SET_GET(int, max_clip_planes, data.maxClipPlanes)
			L_DEF_SET_GET(int, max_texture_units, data.maxTextureUnits)
			L_DEF_SET_GET(int, max_texture_coords, data.maxTextureCoords)
			L_DEF_SET_GET(int, max_vertex_attribs, data.maxVertexAttribs)
			L_DEF_SET_GET(int, max_vertex_uniform_components, data.maxVertexUniformComponents)
			L_DEF_SET_GET(int, max_varying_floats, data.maxVaryingFloats)
			L_DEF_SET_GET(int, max_vertex_texture_image_units, data.maxVertexTextureImageUnits)
			L_DEF_SET_GET(int, max_combined_texture_image_units, data.maxCombinedTextureImageUnits)
			L_DEF_SET_GET(int, max_texture_image_units, data.maxTextureImageUnits)
			L_DEF_SET_GET(int, max_fragment_uniform_components, data.maxFragmentUniformComponents)
			L_DEF_SET_GET(int, max_draw_buffers, data.maxDrawBuffers)
			L_DEF_SET_GET(int, max_vertex_uniform_vectors, data.maxVertexUniformVectors)
			L_DEF_SET_GET(int, max_varying_vectors, data.maxVaryingVectors)
			L_DEF_SET_GET(int, max_fragment_uniform_vectors, data.maxFragmentUniformVectors)
			L_DEF_SET_GET(int, max_vertex_output_vectors, data.maxVertexOutputVectors)
			L_DEF_SET_GET(int, max_fragment_input_vectors, data.maxFragmentInputVectors)
			L_DEF_SET_GET(int, min_program_texel_offset, data.minProgramTexelOffset)
			L_DEF_SET_GET(int, max_program_texel_offset, data.maxProgramTexelOffset)
			L_DEF_SET_GET(int, max_clip_distances, data.maxClipDistances)
			L_DEF_SET_GET(int, max_compute_work_group_count_x, data.maxComputeWorkGroupCountX)
			L_DEF_SET_GET(int, max_compute_work_group_count_y, data.maxComputeWorkGroupCountY)
			L_DEF_SET_GET(int, max_compute_work_group_count_z, data.maxComputeWorkGroupCountZ)
			L_DEF_SET_GET(int, max_compute_work_group_size_x, data.maxComputeWorkGroupSizeX)
			L_DEF_SET_GET(int, max_compute_work_group_size_y, data.maxComputeWorkGroupSizeY)
			L_DEF_SET_GET(int, max_compute_work_group_size_z, data.maxComputeWorkGroupSizeZ)
			L_DEF_SET_GET(int, max_compute_uniform_components, data.maxComputeUniformComponents)
			L_DEF_SET_GET(int, max_compute_texture_image_units, data.maxComputeTextureImageUnits)
			L_DEF_SET_GET(int, max_compute_image_uniforms, data.maxComputeImageUniforms)
			L_DEF_SET_GET(int, max_compute_atomic_counters, data.maxComputeAtomicCounters)
			L_DEF_SET_GET(int, max_compute_atomic_counter_buffers, data.maxComputeAtomicCounterBuffers)
			L_DEF_SET_GET(int, max_varying_components, data.maxVaryingComponents)
			L_DEF_SET_GET(int, max_vertex_output_components, data.maxVertexOutputComponents)
			L_DEF_SET_GET(int, max_geometry_input_components, data.maxGeometryInputComponents)
			L_DEF_SET_GET(int, max_geometry_output_components, data.maxGeometryOutputComponents)
			L_DEF_SET_GET(int, max_fragment_input_components, data.maxFragmentInputComponents)
			L_DEF_SET_GET(int, max_image_units, data.maxImageUnits)
			L_DEF_SET_GET(int, max_combined_image_units_and_fragment_outputs, data.maxCombinedImageUnitsAndFragmentOutputs)
			L_DEF_SET_GET(int, max_combined_shader_output_resources, data.maxCombinedShaderOutputResources)
			L_DEF_SET_GET(int, max_image_samples, data.maxImageSamples)
			L_DEF_SET_GET(int, max_vertex_image_uniforms, data.maxVertexImageUniforms)
			L_DEF_SET_GET(int, max_tess_control_image_uniforms, data.maxTessControlImageUniforms)
			L_DEF_SET_GET(int, max_tess_evaluation_image_uniforms, data.maxTessEvaluationImageUniforms)
			L_DEF_SET_GET(int, max_geometry_image_uniforms, data.maxGeometryImageUniforms)
			L_DEF_SET_GET(int, max_fragment_image_uniforms, data.maxFragmentImageUniforms)
			L_DEF_SET_GET(int, max_combined_image_uniforms, data.maxCombinedImageUniforms)
			L_DEF_SET_GET(int, max_geometry_texture_image_units, data.maxGeometryTextureImageUnits)
			L_DEF_SET_GET(int, max_geometry_output_vertices, data.maxGeometryOutputVertices)
			L_DEF_SET_GET(int, max_geometry_total_output_components, data.maxGeometryTotalOutputComponents)
			L_DEF_SET_GET(int, max_geometry_uniform_components, data.maxGeometryUniformComponents)
			L_DEF_SET_GET(int, max_geometry_varying_components, data.maxGeometryVaryingComponents)
			L_DEF_SET_GET(int, max_tess_control_input_components, data.maxTessControlInputComponents)
			L_DEF_SET_GET(int, max_tess_control_output_components, data.maxTessControlOutputComponents)
			L_DEF_SET_GET(int, max_tess_control_texture_image_units, data.maxTessControlTextureImageUnits)
			L_DEF_SET_GET(int, max_tess_control_uniform_components, data.maxTessControlUniformComponents)
			L_DEF_SET_GET(int, max_tess_control_total_output_components, data.maxTessControlTotalOutputComponents)
			L_DEF_SET_GET(int, max_tess_evaluation_input_components, data.maxTessEvaluationInputComponents)
			L_DEF_SET_GET(int, max_tess_evaluation_output_components, data.maxTessEvaluationOutputComponents)
			L_DEF_SET_GET(int, max_tess_evaluation_texture_image_units, data.maxTessEvaluationTextureImageUnits)
			L_DEF_SET_GET(int, max_tess_evaluation_uniform_components, data.maxTessEvaluationUniformComponents)
			L_DEF_SET_GET(int, max_tess_patch_components, data.maxTessPatchComponents)
			L_DEF_SET_GET(int, max_patch_vertices, data.maxPatchVertices)
			L_DEF_SET_GET(int, max_tess_gen_level, data.maxTessGenLevel)
			L_DEF_SET_GET(int, max_viewports, data.maxViewports)
			L_DEF_SET_GET(int, max_vertex_atomic_counters, data.maxVertexAtomicCounters)
			L_DEF_SET_GET(int, max_tess_control_atomic_counters, data.maxTessControlAtomicCounters)
			L_DEF_SET_GET(int, max_tess_evaluation_atomic_counters, data.maxTessEvaluationAtomicCounters)
			L_DEF_SET_GET(int, max_geometry_atomic_counters, data.maxGeometryAtomicCounters)
			L_DEF_SET_GET(int, max_fragment_atomic_counters, data.maxFragmentAtomicCounters)
			L_DEF_SET_GET(int, max_combined_atomic_counters, data.maxCombinedAtomicCounters)
			L_DEF_SET_GET(int, max_atomic_counter_bindings, data.maxAtomicCounterBindings)
			L_DEF_SET_GET(int, max_vertex_atomic_counter_buffers, data.maxVertexAtomicCounterBuffers)
			L_DEF_SET_GET(int, max_tess_control_atomic_counter_buffers, data.maxTessControlAtomicCounterBuffers)
			L_DEF_SET_GET(int, max_tess_evaluation_atomic_counter_buffers, data.maxTessEvaluationAtomicCounterBuffers)
			L_DEF_SET_GET(int, max_geometry_atomic_counter_buffers, data.maxGeometryAtomicCounterBuffers)
			L_DEF_SET_GET(int, max_fragment_atomic_counter_buffers, data.maxFragmentAtomicCounterBuffers)
			L_DEF_SET_GET(int, max_combined_atomic_counter_buffers, data.maxCombinedAtomicCounterBuffers)
			L_DEF_SET_GET(int, max_atomic_counter_buffer_size, data.maxAtomicCounterBufferSize)
			L_DEF_SET_GET(int, max_transform_feedback_buffers, data.maxTransformFeedbackBuffers)
			L_DEF_SET_GET(int, max_transform_feedback_interleaved_components, data.maxTransformFeedbackInterleavedComponents)
			L_DEF_SET_GET(int, max_cull_distances, data.maxCullDistances)
			L_DEF_SET_GET(int, max_combined_clip_and_cull_distances, data.maxCombinedClipAndCullDistances)
			L_DEF_SET_GET(int, max_samples, data.maxSamples)
			L_DEF_SET_GET(int, max_mesh_output_vertices_nv, data.maxMeshOutputVerticesNV)
			L_DEF_SET_GET(int, max_mesh_output_primitives_nv, data.maxMeshOutputPrimitivesNV)
			L_DEF_SET_GET(int, max_mesh_work_group_size_x_nv, data.maxMeshWorkGroupSizeX_NV)
			L_DEF_SET_GET(int, max_mesh_work_group_size_y_nv, data.maxMeshWorkGroupSizeY_NV)
			L_DEF_SET_GET(int, max_mesh_work_group_size_z_nv, data.maxMeshWorkGroupSizeZ_NV)
			L_DEF_SET_GET(int, max_task_work_group_size_x_nv, data.maxTaskWorkGroupSizeX_NV)
			L_DEF_SET_GET(int, max_task_work_group_size_y_nv, data.maxTaskWorkGroupSizeY_NV)
			L_DEF_SET_GET(int, max_task_work_group_size_z_nv, data.maxTaskWorkGroupSizeZ_NV)
			L_DEF_SET_GET(int, max_mesh_view_count_nv, data.maxMeshViewCountNV)
			L_DEF_SET_GET(int, max_mesh_output_vertices_ext, data.maxMeshOutputVerticesEXT)
			L_DEF_SET_GET(int, max_mesh_output_primitives_ext, data.maxMeshOutputPrimitivesEXT)
			L_DEF_SET_GET(int, max_mesh_work_group_size_x_ext, data.maxMeshWorkGroupSizeX_EXT)
			L_DEF_SET_GET(int, max_mesh_work_group_size_y_ext, data.maxMeshWorkGroupSizeY_EXT)
			L_DEF_SET_GET(int, max_mesh_work_group_size_z_ext, data.maxMeshWorkGroupSizeZ_EXT)
			L_DEF_SET_GET(int, max_task_work_group_size_x_ext, data.maxTaskWorkGroupSizeX_EXT)
			L_DEF_SET_GET(int, max_task_work_group_size_y_ext, data.maxTaskWorkGroupSizeY_EXT)
			L_DEF_SET_GET(int, max_task_work_group_size_z_ext, data.maxTaskWorkGroupSizeZ_EXT)
			L_DEF_SET_GET(int, max_mesh_view_count_ext, data.maxMeshViewCountEXT)
			L_DEF_SET_GET(int, max_dual_source_draw_buffers_ext, data.maxDualSourceDrawBuffersEXT)
		#pragma endregion
	};
}
