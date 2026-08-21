#include "spv_build_logger.hpp"

namespace gdglslang {

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
