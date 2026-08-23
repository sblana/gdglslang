extends Node

func _ready() -> void:
	compile()

func compile() -> PackedByteArray:
	gdglslangGlobalSpace.initialize_process()

	var shader: gdglslangTShader = gdglslangTShader.create_new(gdglslangGlobalSpace.gEShLanguage.EShLangCompute)
	shader.set_strings([FileAccess.open("res://example.comp", FileAccess.READ).get_as_text()])

	shader.set_env_input(gdglslangGlobalSpace.EShSourceGlsl, gdglslangGlobalSpace.EShLangCompute, gdglslangGlobalSpace.EShClientVulkan, 100)
	shader.set_env_client(gdglslangGlobalSpace.EShClientVulkan, gdglslangGlobalSpace.EShTargetVulkan_1_4)
	shader.set_env_target(gdglslangGlobalSpace.EShTargetSpv, gdglslangGlobalSpace.EShTargetSpv_1_6)

	var messages: int = gdglslangGlobalSpace.EShMsgDefault | gdglslangGlobalSpace.EShMsgSpvRules | gdglslangGlobalSpace.EShMsgVulkanRules | gdglslangGlobalSpace.EShMsgDebugInfo
	var success: bool = shader.parse_2(gdglslangGlobalSpace.get_default_resources(), 460, true, messages)

	if not success:
		print("shader.parse() failed")
		print(shader.get_info_log())
		gdglslangGlobalSpace.finalize_process()
		return []

	var program: gdglslangTProgram = gdglslangTProgram.new()
	program.add_shader(shader)
	success = program.link(messages)

	if not success:
		print("program.link() failed")
		print(program.get_info_log())
		gdglslangGlobalSpace.finalize_process()
		return []

	var spirv_data: PackedByteArray = gdglslangGlobalSpace.glslang_to_spv_1(program.get_intermediate(shader.get_stage()), gdglslangSpvOptions.new())
	gdglslangGlobalSpace.finalize_process()
	return spirv_data
