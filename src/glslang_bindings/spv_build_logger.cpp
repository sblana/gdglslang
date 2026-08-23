#include "spv_build_logger.hpp"
#include <godot_cpp/core/class_db.hpp>

namespace gdglslang {

	void gSpvBuildLogger::_bind_methods() {
		godot::ClassDB::bind_method(godot::D_METHOD("get_all_messages"), &gSpvBuildLogger::get_all_messages);
	}

	gSpvBuildLogger::gSpvBuildLogger() {
		data = new spv::SpvBuildLogger;
	}

	gSpvBuildLogger::~gSpvBuildLogger() {
		delete data;
	}

	godot::String gSpvBuildLogger::get_all_messages() const {
		return godot::String(data->getAllMessages().c_str());
	}
}
