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
     * FunctionName: GetModulePath
     * Desc: 获取当前EXE模块路径，多字节版本
     * Author: zhaofushou
     * Date: 2021-05-17 15:20
     * @dataBuf: 接收返回值缓冲
     * @dataBufSize: 缓冲区大小
     * @dataSize: 实际返回的数据大小
     * 返回值：成功返回true,失败返回false
     */
    static bool GetModulePath(PathChar* dataBuf, size_t dataBufSize, int& dataSize);

    /*
     * FunctionName: GetModulePathW
     * Desc: 获取当前EXE模块路径
     * Author: zhaofushou
     * Date: 2021-05-17 15:20
     * @dataBuf: 接收返回值缓冲
     * @dataBufSize: 缓冲区大小
     * @dataSize: 实际返回的数据大小
     * 返回值：成功返回true,失败返回false
     */
    static bool GetModulePathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize);

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
     * FuntionName: CheckFileIsExist
     * Desc: 检测文件或目录是否存在，多字节版本
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @filePath: 要检测的路径
     * @isDirectory: 为true代表检测的是目录，否则检测的是文件
     * 返回值：成功返回true,失败返回false
     */
    static bool CheckFileIsExist(const PathString& filePath, bool isDirectory);

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
     * FuntionName: CreatePath
     * Desc: 创建目录（不会递归创建，因此需要自己处理递归创建问题）
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @path: 要创建的目录
     * 返回值：成功返回true,失败返回false
     */
    static bool CreatePath(const PathString& path);

    /*
     * FuntionName: CreatePathW
     * Desc: 创建目录（不会递归创建，因此需要自己处理递归创建问题）
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @path: 要创建的目录
     * 返回值：成功返回true,失败返回false
     */
    static bool CreatePathW(const PathWString& path);

    /*
     * FunctionName: FileDelete
     * Desc: 删除文件
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: 要删除的文件名
     * 返回值：成功返回true,失败返回false
     */
    static bool FileDelete(const PathString& fileName);

    /*
     * FunctionName: FileDeleteW
     * Desc: 删除文件
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: 要删除的文件名
     * 返回值：成功返回true,失败返回false
     */
    static bool FileDeleteW(const PathWString& fileName);

    /*
     * FunctionName: GetFileSize
     * Desc: 获取文件大小
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: 文件名
     * @fileSize: 返回的文件大小
     * 返回值：成功返回true,失败返回false
     */
    static bool GetFileSize(const PathString& fileName, int64_t& fileSize);

    /*
     * FunctionName: GetFileSizeW
     * Desc: 获取文件大小
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: 文件名
     * @fileSize: 返回的文件大小
     * 返回值：成功返回true,失败返回false
     */
    static bool GetFileSizeW(const PathWString& fileName, int64_t& fileSize);

};

} // end namespace h2x

#endif // !H2XBASE_FILE_FILE_PATH__H