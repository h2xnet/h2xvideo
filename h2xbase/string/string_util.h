#ifndef H2XBASE_STRING_STRING_UTIL__H
#define H2XBASE_STRING_STRING_UTIL__H

#include <string>
#include <memory>

#include "h2xbase/btype.h"
#include "h2xbase/string/string_result.h"
#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
* ClassName: StringUtil
* Desc: 字符串综合处理类
* Author: zfs
* Date: 2021-05-19 23:19
*/
class H2XBASE_EXPORT StringUtil {
public:
    StringUtil();
    virtual ~StringUtil();

    /*
     * Function: StringPrintf
     * Desc: 字符串格式化输出
     * Author: zhaofushou
     * Date: 2021-05-18 14:24
     * @result: 返回格式化后的字符串
     * @format: 格式字符串
     * 返回值：成功返回true，失败返回false
     */
    static bool StringPrintf(StringResult<PathChar>& result, const char *format, ...);

    /*
     * Function: StringPrintfW
     * Desc: 字符串格式化输出
     * Author: zhaofushou
     * Date: 2021-05-18 16:05
     * @result: 返回格式化后的字符串
     * @format: 格式字符串
     * 返回值：成功返回true，失败返回false
     */
    static bool StringPrintfW(StringResult<PathWChar>& result, const wchar_t *format, ...);

    /*
     * FunctionName: GetNowDateString
     * Desc: 获取当前日期字符串，比如2021-05-29
     * Author: zhaofushou
     * Date: 2021-05-29 14:12
     * @result: 返回的日期字符串
     * 返回值：成功返回true，失败返回false
     */
    static bool GetNowDateString(StringResult<PathChar>& result);

    /*
     * FunctionName: GetNowDateStringW
     * Desc: 获取当前日期字符串，比如2021-05-29
     * Author: zhaofushou
     * Date: 2021-05-29 14:12
     * @result: 返回的日期字符串
     * 返回值：成功返回true，失败返回false
     */
    static bool GetNowDateStringW(StringResult<PathWChar>& result);

    /*
     * FunctionName: GetNowDatetimeString
     * Desc: 获取当前日期时间字符串，比如2021-05-29 14:48:23.323
     * Author: zhaofushou
     * Date: 2021-05-29 14:12
     * @result: 返回的日期字符串
     * 返回值：成功返回true，失败返回false
     */
    static bool GetNowDatetimeString(StringResult<PathChar>& result);
    static bool GetNowDatetimeStringW(StringResult<PathWChar>& result);

    /*
     * FunctionName: GetDateLoggerFileNameW
     * Desc: 获取日期日志文件名称，扩展名为log
     * Author: zhaofushou
     * Date: 2021-05-29 14:55
     * @prefix: 文件名前缀，返回的文件名会把前缀和文件名用下划线连接
     * @result: 返回的日期字符串
     * 返回值：成功返回true，失败返回false
     */
    static bool GetDateLoggerFileNameW(const PathWString& prefix, StringResult<PathWChar>& result);

};

};

#endif // !H2XBASE_STRING_STRING_UTIL__H
