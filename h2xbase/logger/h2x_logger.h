#ifndef H2XBASE_LOGGER_H2X_LOGGER__H
#define H2XBASE_LOGGER_H2X_LOGGER__H

#include <memory>
#include <mutex>
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/file/file.h"
#include "h2xbase/string/string_result.h"

namespace h2x {

/*
* ClassName: Logger
* Desc: 日志类
* Author: zfs
* Date: 2021-05-16 17:25
*/
class H2XBASE_EXPORT Logger {
public:
    // 日志文件类型，不同类型对应不同日志文件名
    enum LoggerType {
        Default, // 默认类型，对应当前日期文件
        Frame // 框架日志
    };

    // 日志内容类型
    enum ContentType {
        OFF = 0, //关闭日志
        Debug, // 调试
        Info, // 信息
        Warn, // 告警
        Error, // 错误
        Fatal // 严重错误
    };
    
    Logger();
    virtual ~Logger();

    virtual int debug(const char* format, ...);
    virtual int debugw(const wchar_t* format, ...);

    virtual int info(const char* format, ...);
    virtual int infow(const wchar_t* format, ...);

    virtual int warn(const char* format, ...);
    virtual int warnw(const wchar_t* format, ...);

    virtual int error(const char* format, ...);
    virtual int errorw(const wchar_t* format, ...);
    
    virtual int fatal(const char* format, ...);
    virtual int fatalw(const wchar_t* format, ...);

    /*
     * FunctionName: PrintLog / PrintLogW
     * Desc: 格式化打印日志
     * Author: zhaofushou
     * Date: 2021-05-29 16:39
     * 返回值：返回实际打印的日志字节数，不包含带回额外追加的信息
     */
    int PrintLog(ContentType contentType, const char* format, ...);
    int PrintLogW(ContentType contentType, const wchar_t* format, ...);

    /*
     * FunctionName: GetPrefix
     * Desc: 获取日志文件前缀名
     * Author: zhaofushou
     * Date: 2021-05-29 15:36
     */
    virtual bool GetPrefix(StringResult<PathWChar>& result);

    /*
     * FunctionName: SetLoggerType
     * Desc: 设置日志文件类型
     * Author: zhaofushou
     * Date: 2021-05-29 15:14
     */
    void SetLoggerType(LoggerType type) {
        log_type_ = type;
    }

    LoggerType GetLoggerType() const {
        return log_type_;
    }

    /*
     * FunctionName: GetContentType
     * Desc: 获取日志内容类型
     * Author: zhaofushou
     * Date: 2021-05-29 16:02
     */
    ContentType GetContentType() const {
        return content_type_;
    }

protected:

    size_t GetModulePathSize() const {
        return module_path_size_;
    }

private://
    // OnOpenFile : 打开文件
    //
    bool OnOpenFile();

    //
    // OnCloseFile : 关闭文件
    //
    void OnCloseFile();

    //
    // OnShouldSave : 判断是否需要保存
    //
    bool OnShouldSave(const ContentType& contentType);

    // 日志文件类型
    LoggerType log_type_;

    // 日志内容类型
    ContentType content_type_;

    // 模块路径
    PathWChar module_path_[2 * MAX_PATH];
    size_t module_path_size_;

    // 线程同步锁
    std::mutex mutex_;
    //std::unique_lock<std::mutex> lock_;

    // 日志文件变量
    h2x::File file_;
};

} // end namespace h2x

#endif // !H2XBASE_LOGGER_H2X_LOGGER__H
