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

    bool Open(const PathWChar* fileName, const PathWChar* mode = L"a+");

    void Close();

    /*
     * FunctionName: Read
     * Desc: 读取文件内容
     * Author: zhaofushou
     * Date: 2021-05-29 16:21
     * @buff: 存放读取数据的缓冲区
     * @buffSize: 缓冲区大小
     * @readDataSize: 实际读取的数据长度
     * 返回值：读出的字节数，如果小于0，则代表错误
     */
    int Read(byte* buff, size_t buffSize, int& readDataSize);

    //
    // Write : 字入文件内容
    //
    int Write(const char* data, size_t dataSize);

    //
    // Print : 格式化写入文件内容
    //
    int Print(const char* format, ...);

    int Print(const char* format, const va_list& ap);

    //
    // PrintW : 格式化写入文件内容（unicode模式，主要用于包含中文内容输出）
    //
    int PrintW(const wchar_t* format, ...);

    int PrintW(const wchar_t* format, const va_list& ap);

private:
    FILE* ff_;

};

} // end namespace h2x

#endif // !H2XBASE_FILE_FILE__H
