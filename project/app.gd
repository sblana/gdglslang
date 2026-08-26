extends Node

func _ready() -> void:
	var source_file_path: String = "res://example.comp"

	var spirv_data: PackedByteArray = compile(source_file_path)
	if spirv_data:
		print("compiled %s" % source_file_path)


func compile(p_source_file_path: String) -> PackedByteArray:
	GlslangGlobalScope.initialize_process()

	var shader: GlslangTShader = GlslangTShader.create_new(GlslangGlobalScope.gEShLanguage.EShLangCompute)
	shader.set_strings([FileAccess.open(p_source_file_path, FileAccess.READ).get_as_text()])

	shader.set_env_input(GlslangGlobalScope.EShSourceGlsl, GlslangGlobalScope.EShLangCompute, GlslangGlobalScope.EShClientVulkan, 100)
	shader.set_env_client(GlslangGlobalScope.EShClientVulkan, GlslangGlobalScope.EShTargetVulkan_1_4)
	shader.set_env_target(GlslangGlobalScope.EShTargetSpv, GlslangGlobalScope.EShTargetSpv_1_6)

	var includer: StandardIncluder = StandardIncluder.new()
	includer.add_search_dirs([p_source_file_path.get_base_dir()])

	var messages: int = GlslangGlobalScope.EShMsgDefault | GlslangGlobalScope.EShMsgSpvRules | GlslangGlobalScope.EShMsgVulkanRules | GlslangGlobalScope.EShMsgDebugInfo
	var success: bool = shader.parse_3(GlslangGlobalScope.get_default_resources(), 460, true, messages, includer)

	if not success:
		print("shader.parse() failed")
		print(shader.get_info_log())
		GlslangGlobalScope.finalize_process()
		return []

	var program: GlslangTProgram = GlslangTProgram.new()
	program.add_shader(shader)
	success = program.link(messages)

	if not success:
		print("program.link() failed")
		print(program.get_info_log())
		GlslangGlobalScope.finalize_process()
		return []

	var spirv_data: PackedByteArray = GlslangGlobalScope.glslang_to_spv_1(program.get_intermediate(shader.get_stage()), GlslangSpvOptions.new())
	GlslangGlobalScope.finalize_process()
	return spirv_data
