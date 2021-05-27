#include "h2xcore/h2x_application.h"

#include "h2xcore/h2x_config.h"

#include <assert.h>

namespace h2x {

Application::Application(const Config* cfg) : cfg_((Config*)cfg) {
	assert(cfg_);
}

Application::~Application() {

}

} // end namespace h2x