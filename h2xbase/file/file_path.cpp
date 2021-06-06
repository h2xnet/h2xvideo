#include "file_path.h"

namespace h2x {

FilePath::FilePath() {

}

FilePath::~FilePath() {

}


bool FilePath::GetModulePath(PathChar* dataBuf, size_t dataBufSize, int& dataSize) {
    dataSize = 0;
    PathChar buff[MAX_PATH] = { '\0' };
    DWORD dwRet = ::GetModuleFileNameA(NULL, buff, MAX_PATH);
    if (dwRet < 1) {
        return false;
    }
    int i = 0;
    for (i = dwRet - 1; i >= 0; i--) {
        if (buff[i] == '\\') {
            break;
        }
    }
    if (i > 0) {
        dataSize = i;
        if (dataBuf && dataBufSize > i) {
            memcpy(dataBuf, buff, i * sizeof(char));
            buff[i] = '\0';
        }
        return true;
    }
    else {
        return false;
    }
}

bool FilePath::GetModulePathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize) {
    dataSize = 0;
#ifdef OS_WIN
    PathWChar szTempPath[2 * MAX_PATH] = { 0 };
    int status = GetModuleFileNameW(NULL, szTempPath, 2 * MAX_PATH);
    if (status < 1) {
        return false;
    }

    PathWChar* lpStr1 = szTempPath;
    PathWChar *lpStr2 = wcsrchr(lpStr1, L'\\');
    if (lpStr2) {
        dataSize = (lpStr2 - lpStr1);
        if (dataBuf && dataBufSize > dataSize) {
            memcpy(dataBuf, lpStr1, dataSize * sizeof(PathWChar));
            dataBuf[dataSize * sizeof(PathWChar)] = 0;
            dataBuf[dataSize * sizeof(PathWChar) + 1] = 0;
        }
        return true;
    }

#endif // OS_WIN
    return false;
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

bool FilePath::CheckFileIsExist(const PathString& filePath, bool isDirectory) {
    if (filePath.empty()) {
        return false;
    }
#ifdef  OS_WIN
    const DWORD file_attr = ::GetFileAttributesA(filePath.c_str());
    if (file_attr != INVALID_FILE_ATTRIBUTES)
    {
        if (isDirectory)
            return (file_attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
        else
            return true;
    }
#endif
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


bool FilePath::CreatePath(const PathString& path) {
    if (path.empty()) {
        return false;
    }

    // 如果已经存在，则直接返回true
    if (FilePath::CheckFileIsExist(path, true)) {
        return true;
    }

    // 创建目录
    if (!CreateDirectoryA(path.c_str(), NULL)) {
        return false;
    }

    return true;
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


bool FilePath::FileDelete(const PathString& fileName) {
    if (fileName.empty()) {
        return false;
    }
    int status = -1;
    try {
        status = ::DeleteFileA(fileName.c_str());
    }
    catch (...) {
        return false;
    }
    return status ? true : false;
}

bool FilePath::FileDeleteW(const PathWString& fileName) {
    if (fileName.empty()) {
        return false;
    }
    int status = -1;
    try {
        status = ::DeleteFileW(fileName.c_str());
    }
    catch (...) {
        return false;
    }
    return status ? true : false;
}

bool FilePath::GetFileSize(const PathString& fileName, int64_t& fileSize) {
    fileSize = 0;
    if (fileName.empty()) {
        return false;
    }
#ifdef  OS_WIN
    // 判断文件是否存在
    const DWORD file_attr = ::GetFileAttributesA(fileName.c_str());
    if (file_attr != INVALID_FILE_ATTRIBUTES) {
        HANDLE hFile = CreateFileA(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            LARGE_INTEGER lSize;
            BOOL bRet = ::GetFileSizeEx(hFile, &lSize);

            CloseHandle(hFile);
            hFile = NULL;

            if (bRet) {
                fileSize = lSize.QuadPart;
            }

            return (bRet ? true : false);
        }
    }
#endif
    return false;
}

bool FilePath::GetFileSizeW(const PathWString& fileName, int64_t& fileSize) {
    fileSize = 0;
    if (fileName.empty()) {
        return false;
    }
#ifdef  OS_WIN
    // 判断文件是否存在
    const DWORD file_attr = ::GetFileAttributesW(fileName.c_str());
    if (file_attr != INVALID_FILE_ATTRIBUTES) {
        HANDLE hFile = CreateFileW(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != INVALID_HANDLE_VALUE) {
            LARGE_INTEGER lSize;
            BOOL bRet = ::GetFileSizeEx(hFile, &lSize);

            CloseHandle(hFile);
            hFile = NULL;

            if (bRet) {
                fileSize = lSize.QuadPart;
            }

            return (bRet ? true : false);
        }
    }
#endif
    return false;
}

} // end namespace h2x