extends Node

func _ready() -> void:
	var source_file_path: String = "res://example.comp"

	var spirv_data: PackedByteArray = compile(source_file_path)
	if spirv_data:
		print("compiled %s" % source_file_path)


func compile(p_source_file_path: String) -> PackedByteArray:
	gdglslangGlobalScope.initialize_process()

	var shader: gdglslangTShader = gdglslangTShader.create_new(gdglslangGlobalScope.gEShLanguage.EShLangCompute)
	shader.set_strings([FileAccess.open(p_source_file_path, FileAccess.READ).get_as_text()])

	shader.set_env_input(gdglslangGlobalScope.EShSourceGlsl, gdglslangGlobalScope.EShLangCompute, gdglslangGlobalScope.EShClientVulkan, 100)
	shader.set_env_client(gdglslangGlobalScope.EShClientVulkan, gdglslangGlobalScope.EShTargetVulkan_1_4)
	shader.set_env_target(gdglslangGlobalScope.EShTargetSpv, gdglslangGlobalScope.EShTargetSpv_1_6)

	var includer: StandardIncluder = StandardIncluder.new()
	includer.add_search_dirs([p_source_file_path.get_base_dir()])

	var messages: int = gdglslangGlobalScope.EShMsgDefault | gdglslangGlobalScope.EShMsgSpvRules | gdglslangGlobalScope.EShMsgVulkanRules | gdglslangGlobalScope.EShMsgDebugInfo
	var success: bool = shader.parse_3(gdglslangGlobalScope.get_default_resources(), 460, true, messages, includer.create_new_includer_interface())

	if not success:
		print("shader.parse() failed")
		print(shader.get_info_log())
		gdglslangGlobalScope.finalize_process()
		return []

	var program: gdglslangTProgram = gdglslangTProgram.new()
	program.add_shader(shader)
	success = program.link(messages)

	if not success:
		print("program.link() failed")
		print(program.get_info_log())
		gdglslangGlobalScope.finalize_process()
		return []

	var spirv_data: PackedByteArray = gdglslangGlobalScope.glslang_to_spv_1(program.get_intermediate(shader.get_stage()), gdglslangSpvOptions.new())
	gdglslangGlobalScope.finalize_process()
	return spirv_data
