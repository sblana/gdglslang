class_name StandardIncluder
extends BaseIncluder


var search_dir_stack: Array[String] = []
var num_base_dirs: int = 0


func add_search_dirs(p_search_dirs: Array[String]) -> void:
	search_dir_stack.append_array(p_search_dirs)
	num_base_dirs += p_search_dirs.size()


func _get_include_full_path_if_valid(p_header_name: String, p_inclusion_depth: int) -> String:
	var full_path: String = p_header_name

	if p_header_name.is_relative_path():
		var num_relevant_dirs: int = mini(num_base_dirs + p_inclusion_depth - 1, search_dir_stack.size())

		for i: int in range(num_relevant_dirs - 1, -1, -1):
			var candidate: String = search_dir_stack[i].path_join(p_header_name)
			if FileAccess.file_exists(candidate):
				full_path = candidate
				break

	if FileAccess.file_exists(full_path):
		return full_path

	return ""


func _should_include_system(p_header_name: String, _p_includer_name: String, p_inclusion_depth: int, _p_user_data: RefCounted) -> bool:
	var full_path: String = _get_include_full_path_if_valid(p_header_name, p_inclusion_depth)
	return FileAccess.file_exists(full_path)

func _should_include_local(_p_header_name: String, _p_includer_name: String, _p_inclusion_depth: int, _p_user_data: RefCounted) -> bool:
	# for a local-style include, glslang first requests a local include and, if that fails, then requests a system include
	return false

func _include_system(p_header_name: String, _p_includer_name: String, p_inclusion_depth: int, _p_user_data: RefCounted) -> GlslangIncludeResult:
	var full_path: String = _get_include_full_path_if_valid(p_header_name, p_inclusion_depth)
	if FileAccess.file_exists(full_path):
		search_dir_stack.resize(num_base_dirs + p_inclusion_depth - 1)
		search_dir_stack.append(full_path.get_base_dir())

		var file: FileAccess = FileAccess.open(full_path, FileAccess.READ)
		return GlslangIncludeResult.create_new(p_header_name, file.get_as_text(), null)

	return null

func _include_local(_p_header_name: String, _p_includer_name: String, _p_inclusion_depth: int, _p_user_data: RefCounted) -> GlslangIncludeResult:
	return null

func _pre_release_include(_p_result: GlslangIncludeResult, _p_user_data: RefCounted) -> void:
	return
