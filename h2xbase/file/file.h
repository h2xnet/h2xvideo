#ifndef H2XBASE_FILE_FILE__H
#define H2XBASE_FILE_FILE__H

#include "build/build_config.h"
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/file/file_path.h"

#ifdef OS_WIN
#include <Windows.h>
#endif // OS_WIN


namespace h2x {

/*
 * ClassName: File
 * Desc: 文件处理类
 * Author: zfs
 * Date: 2021-05-16 10:25
 */
class H2XBASE_EXPORT File {
public:
	File();
	virtual ~File();

#ifdef OS_WIN
    /*
     * FunctionName: OpenFileW
     * Desc: 打开文件，如果存在则追加模式打开，不存在则创建
     * Author: zfs
     * Date: 2021-05-16 10:20
     */
    static HANDLE OpenFileW(const h2x::PathWString& file);

    /*
     * FunctionName: WriteFileData
     * Desc: 写文件数据
     * Author: zfs
     * Date: 2021-05-16 10:30
     */
    static int WriteFileData(const HANDLE h, const char* data, size_t dataSize);

    /*
     * FunctionName: CloseFile
     * Desc: 关闭文件
     * Author: zfs
     * Date: 2021-05-16 10:31
     */
    static void CloseFile(HANDLE h);
#endif // OS_WIN

};

} // end namespace h2x

#endif // !H2XBASE_FILE_FILE__H
