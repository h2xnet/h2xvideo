#ifndef H2XBASE_FILE_FILE_PATH__H
#define H2XBASE_FILE_FILE_PATH__H

#include <string>
#include "build/build_config.h"
#include "../h2x_base_export.h"

#ifdef OS_WIN
#include <shlobj.h>
#endif // OS_WIN


namespace h2x {

#if defined(OS_POSIX)
    typedef std::string PathString;
#elif defined(OS_WIN)
    typedef std::string PathString;
    typedef std::wstring PathWString;
#endif

typedef PathString::value_type PathChar;
typedef PathWString::value_type PathWChar;

/*
 * ClassName: FilePath
 * Desc: 文件路径处理类
 */
class H2XBASE_EXPORT FilePath {
public:
	FilePath();
	virtual ~FilePath();

    /*
     * FunctionName: GetAppDataPathW
     * Description: 获取系统默认AppData目录
     * Author: zfs
     * Date: 2021-05-16 09:58
     * @dataBuf: 接收数据的缓冲区
     * @dataBufSize: 缓冲区大小
     * @dataSize: 实际需要数据大小，如果缓冲区为空，也会返回真实数据大小
     * 返回值：成功返回true,失败返回false
     */
    static bool GetAppDataPathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize);

    /*
     * FuntionName: CheckFileIsExistW
     * Desc: 检测文件或目录是否存在
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @filePath: 要检测的路径
     * @isDirectory: 为true代表检测的是目录，否则检测的是文件
     * 返回值：成功返回true,失败返回false
     */
    static bool CheckFileIsExistW(const PathWString& filePath, bool isDirectory);

    /*
     * FuntionName: CreatePathW
     * Desc: 创建目录（不会递归创建，因此需要自己处理递归创建问题）
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @path: 要创建的目录
     * 返回值：成功返回true,失败返回false
     */
    static bool CreatePathW(const PathWString& path);
};

} // end namespace h2x

#endif // !H2XBASE_FILE_FILE_PATH__H