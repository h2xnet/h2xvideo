#include "file_path.h"

namespace h2x {

FilePath::FilePath() {

}

FilePath::~FilePath() {

}

bool FilePath::GetAppDataPathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize) {
    dataSize = 0;
#ifdef  OS_WIN
    // WINDOWS系统
    PathWChar tempBuf[_MAX_PATH * 2] = { 0 };

    if (!SHGetSpecialFolderPathW(NULL, tempBuf, CSIDL_APPDATA, FALSE)) {
        return false;
    }

    // 获取长度
    dataSize = wcslen(tempBuf);

    if (dataBuf && dataBufSize >= dataSize && dataSize > 0) {
        memcpy(dataBuf, tempBuf, dataSize * sizeof(PathWChar));
    }

    return true;

#endif //  OS_WIN
    return false;
}

bool FilePath::CheckFileIsExistW(const PathWString& filePath, bool isDirectory) {
    if (filePath.empty()) {
        return false;
    }
    const DWORD file_attr = ::GetFileAttributesW(filePath.c_str());
    if (file_attr != INVALID_FILE_ATTRIBUTES)
    {
        if (isDirectory)
            return (file_attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
        else
            return true;
    }
    return false;
}

bool FilePath::CreatePathW(const PathWString& path) {
    if (path.empty()) {
        return false;
    }

    // 如果已经存在，则直接返回true
    if (FilePath::CheckFileIsExistW(path, true)) {
        return true;
    }

    // 创建目录
    if (!CreateDirectoryW(path.c_str(), NULL)) {
        return false;
    }

    return true;
}

} // end namespace h2x