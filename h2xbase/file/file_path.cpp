#include "file_path.h"

namespace h2x {

FilePath::FilePath() {

}

FilePath::~FilePath() {

}

bool FilePath::GetAppDataPathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize) {
    dataSize = 0;
#ifdef  OS_WIN
    // WINDOWSϵͳ
    PathWChar tempBuf[_MAX_PATH * 2] = { 0 };

    if (!SHGetSpecialFolderPathW(NULL, tempBuf, CSIDL_APPDATA, FALSE)) {
        return false;
    }

    // ��ȡ����
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

    // ����Ѿ����ڣ���ֱ�ӷ���true
    if (FilePath::CheckFileIsExistW(path, true)) {
        return true;
    }

    // ����Ŀ¼
    if (!CreateDirectoryW(path.c_str(), NULL)) {
        return false;
    }

    return true;
}

} // end namespace h2x