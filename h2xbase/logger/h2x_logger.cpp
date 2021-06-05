#include "h2xbase/logger/h2x_logger.h"

namespace h2x {

Logger::Logger() : log_type_(LOG_WARN){

}

Logger::~Logger() {

}

int Logger::debug(const char* format, ...) {
    return 0;
}

int Logger::debugw(const wchar_t* format, ...) {
    return 0;
}

int Logger::info(const char* format, ...) {
    return 0;
}

int Logger::infow(const wchar_t* format, ...) {
    return 0;
}

int Logger::warn(const char* format, ...) {
    return 0;
}

int Logger::warnw(const wchar_t* format, ...) {
    return 0;
}

int Logger::error(const char* format, ...) {
    return 0;
}

int Logger::errorw(const wchar_t* format, ...) {
    return 0;
}

int Logger::fatal(const char* format, ...) {
    return 0;
}

int Logger::fatalw(const wchar_t* format, ...) {
    return 0;
}

} // end namespace h2x