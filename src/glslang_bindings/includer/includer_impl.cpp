#include "includer_impl.hpp"

namespace gdglslang {

	namespace detail {

		bool gIncluderImpl::has_owner() const {
			if (owner->get_ref().get_type() == godot::Variant::Type::NIL) {
				return false;
			}
			godot::Object *obj = owner->get_ref();
			godot::Ref<gIncluderInterface> ref = godot::Object::cast_to<gIncluderInterface>(obj);
			return ref.is_valid();
		}

		godot::Ref<gIncluderInterface> gIncluderImpl::get_owner() const {
			if (has_owner()) {
				godot::Object *obj = owner->get_ref();
				return godot::Object::cast_to<gIncluderInterface>(obj);
			}
			// error or something
			return nullptr;
		}

		gIncluderImpl::IncludeResult *gIncluderImpl::includeSystem(char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) {
			if (has_owner()) {
				return get_owner()->on_include_system(p_header_name, p_includer_name, p_inclusion_depth);
			}
			// error or something
			return nullptr;
		}

		gIncluderImpl::IncludeResult *gIncluderImpl::includeLocal (char const *p_header_name, char const *p_includer_name, std::size_t p_inclusion_depth) {
			if (has_owner()) {
				return get_owner()->on_include_local(p_header_name, p_includer_name, p_inclusion_depth);
			}
			// error or something
			return nullptr;
		}

		void gIncluderImpl::releaseInclude(gIncluderImpl::IncludeResult *p_result) {
			if (has_owner()) {
				get_owner()->on_release_include(p_result);
				return;
			}
			// error or something
			return;
		}

		gIncluderImpl::gIncluderImpl(godot::Ref<gIncluderInterface> p_owner) {
			owner = godot::UtilityFunctions::weakref(p_owner);
		}

	}
}
