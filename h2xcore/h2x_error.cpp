#include "h2xcore/h2x_error.h"

namespace h2x {

Error::Error() : status_(0), code_(0){

}

Error::~Error() {
}

} // end namespace h2x