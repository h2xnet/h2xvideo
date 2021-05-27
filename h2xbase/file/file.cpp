#include "file.h"

namespace h2x {

File::File() {

}

File::~File() {

}

#ifdef OS_WIN

HANDLE File::OpenFileW(const h2x::PathWString& file) {
    if (file.empty()) {
        return NULL;
    }

    HANDLE h = CreateFileW(file.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    return h;
}

void File::CloseFile(HANDLE h) {
    if (h != INVALID_HANDLE_VALUE) {
        CloseHandle(h);
    }
}

#endif // OS_WIN


} // end namespace h2x