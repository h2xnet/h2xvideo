#include "h2xcore/h2x_middleware.h"

#include "h2xcore/h2x_context.h"

namespace h2x {

Middleware::Middleware(Context* ctx) : ctx_(ctx) {

}

Middleware::~Middleware() {

}

} // end namespace h2x