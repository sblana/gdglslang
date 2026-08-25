@abstract
class_name BaseIncluder
extends RefCounted


func create_new_includer_interface() -> GlslangIncluderInterface:
	var ret: GlslangIncluderInterface = GlslangIncluderInterface.new()

	ret.callback_should_include_system = _should_include_system
	ret.callback_should_include_local = _should_include_local
	ret.callback_include_system = _include_system
	ret.callback_include_local = _include_local
	ret.callback_pre_release_include = _pre_release_include

	return ret


@abstract
func _should_include_system(p_header_name: String, p_includer_name: String, p_inclusion_depth: int, p_user_data: RefCounted) -> bool

@abstract
func _should_include_local(p_header_name: String, p_includer_name: String, p_inclusion_depth: int, p_user_data: RefCounted) -> bool

@abstract
func _include_system(p_header_name: String, p_includer_name: String, p_inclusion_depth: int, p_user_data: RefCounted) -> GlslangIncludeResult

@abstract
func _include_local(p_header_name: String, p_includer_name: String, p_inclusion_depth: int, p_user_data: RefCounted) -> GlslangIncludeResult

@abstract
func _pre_release_include(p_result: GlslangIncludeResult, p_user_data: RefCounted) -> void
