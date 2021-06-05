#include "h2xcore/h2x_router.h"

#include "h2xcore/h2x_application.h"

#include <assert.h>

namespace h2x {

Router::Router(Application* app) : app_(app) {
    assert(app_);
}

Router::~Router() {
    app_ = NULL;
}

} // end namespace h2x