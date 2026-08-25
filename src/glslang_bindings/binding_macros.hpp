#pragma once

#define L_DEF_SET_GET(m_type, m_property_name, m_property_access) \
	void set_##m_property_name(m_type p_value) { m_property_access = p_value; } \
	m_type get_##m_property_name() const { return m_property_access; }

#define L_BIND_SET_GET(m_class, m_property_name) \
	::godot::ClassDB::bind_method(::godot::D_METHOD("get_"#m_property_name), &m_class::get_##m_property_name); \
	::godot::ClassDB::bind_method(::godot::D_METHOD("set_"#m_property_name, "p_value"), &m_class::set_##m_property_name);

#define L_BIND_PROPERTY(m_type, m_property_name) \
	ADD_PROPERTY(::godot::PropertyInfo(m_type, #m_property_name), "set_"#m_property_name, "get_"#m_property_name);
