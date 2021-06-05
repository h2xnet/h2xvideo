#include "h2xcore/h2x_schedule.h"

#include "h2xcore/h2x_context.h"

#include <assert.h>

namespace h2x {

Schedule::Schedule(Context* ctx) : ctx_(ctx) {
    assert(ctx_);
}

Schedule::~Schedule() {
    ctx_ = NULL;
}

} // end namespace h2x