#ifndef H2XBASE_LOGGER_H2X_LOGGER__H
#define H2XBASE_LOGGER_H2X_LOGGER__H

#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
* ClassName: Logger
* Desc: 日志类
* Author: zfs
* Date: 2021-05-16 17:25
*/
class H2XBASE_EXPORT Logger {
public:
    enum LOG_TYPE {
        LOG_DEBUG, // 调试
        LOG_INFO, // 信息
        LOG_WARN, // 警告
        LOG_ERROR, // 错误
        LOG_FATAL // 严重错误
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

    void SetLogType(LOG_TYPE type) {
        log_type_ = type;
    }

    int GetLogType() const {
        return log_type_;
    }

protected:

private:
    // 错误日志保存类型
    int log_type_;
};

} // end namespace h2x

#endif // !H2XBASE_LOGGER_H2X_LOGGER__H
