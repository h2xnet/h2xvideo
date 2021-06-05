#include "h2xcore/h2x_controller.h"

#include "h2xcore/h2x_application.h"
#include "h2xcore/h2x_context.h"

#include <assert.h>

namespace h2x {

Controller::Controller(Application* app, Context* ctx) : app_(app), ctx_(ctx) {
    assert(app_);
    assert(ctx_);
}

Controller::~Controller() {
    app_ = NULL;
    ctx_ = NULL;
}

} // end namespace h2x