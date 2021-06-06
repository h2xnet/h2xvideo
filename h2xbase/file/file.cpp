#include "file.h"

namespace h2x {

File::File() : ff_(NULL){
    setlocale(LC_CTYPE, ""); // ÖÐÎÄ
}

File::~File() {
    this->Close();
}

bool File::Open(const PathWChar* fileName, const PathWChar* mode) {
    if (!fileName) {
        false;
    }

    this->Close();

    int status = -1;
    if (mode) {
        status = _wfopen_s(&ff_, fileName, mode);
    }
    else {
        status = _wfopen_s(&ff_, fileName, L"a+");
    }

    return (status == 0 ? true : false);
}

void File::Close() {
    if (ff_) {
        fclose(ff_);
        ff_ = NULL;
    }
}

int File::Read(byte* buff, size_t bufSize, int& readDataSize) {
    readDataSize = 0;
    if (!ff_ || !buff || !bufSize) {
        return -1;
    }
    readDataSize = fread(buff, 1, bufSize, ff_);
    return readDataSize;
}

int File::Write(const char* data, size_t dataSize) {
    if (!ff_) {
        return -1;
    }
    if (!data || !dataSize) {
        return 0;
    }
    int status = fwrite((char*)data, sizeof(char), dataSize, ff_);
    return status;
}

int File::Print(const char* format, ...) {
    if (!ff_ || !format) {
        return -1;
    }

    int status = -1;
    va_list ap;
    va_start(ap, format);
    status = vfprintf_s(ff_, format, ap);
    va_end(ap);

    return status;
}

int File::Print(const char* format, const va_list& ap) {
    if (!ff_ || !format) {
        return -1;
    }
    int status = -1;
    status = vfprintf_s(ff_, format, ap);
    return status;
}

int File::PrintW(const wchar_t* format, ...) {
    if (!ff_ || !format) {
        return -1;
    }

    int status = -1;
    va_list ap;
    va_start(ap, format);
    status = vfwprintf_s(ff_, format, ap);
    va_end(ap);

    return status;
}

int File::PrintW(const wchar_t* format, const va_list& ap) {
    if (!ff_ || !format) {
        return -1;
    }

    int status = -1;
    status = vfwprintf_s(ff_, format, ap);
    return status;
}


} // end namespace h2x