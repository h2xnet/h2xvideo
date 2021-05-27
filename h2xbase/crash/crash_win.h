#ifndef H2XBASE_CRASH_CRASH_WIN__H
#define H2XBASE_CRASH_CRASH_WIN__H

#include "build/build_config.h"
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/crash/crash_handler.h"

#ifdef  OS_WIN
#include <Windows.h>
#endif //  OS_WIN

namespace h2x {

/*
 * ClassName: CrashWin
 * Description: Windows崩溃处理类
 * Author: zfs
 * Date: 2021-05-16 09:02
 */
class H2XBASE_EXPORT CrashWin {
public:
    /*
     * ExceptionLevel: 异常处理级别
     * info: 只弹出消息
     * normal: 不弹出消息，只记录DUMP文件
     * error: 即弹出消息，又记录DUMP文件
     */
    enum ExceptionLevel {
        info, // 信息
        normal, // 常规
        error, // 错误
    };

#ifdef OS_WIN
    // 异常注册处理函数
    static LONG CALLBACK ExceptionHandler(PEXCEPTION_POINTERS exception);
    static BOOL PreventSetUnhandledExceptionFilter();
    static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI ExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
#endif // OS_WIN


    explicit CrashWin(const CrashHandler* handler);
    virtual ~CrashWin();

    /*
     * FunctionName: Regist
     * Description: 注册崩溃处理级别
     * Author: zfs
     * Date: 2021-05-16 09:18
     */
    bool Regist(const ExceptionLevel& el);

    CrashHandler* getHandler() const {
        return handler_;
    }

    bool getInited() const {
        return inited_;
    }

protected:
    // 通知回调句柄
    CrashHandler* handler_;

    // 异常处理级别
    ExceptionLevel exception_level_;

    // 回调函数已经注册标志
    bool inited_;
};

} // end namespace h2x

#endif // !H2XBASE_CRASH_CRASH_WIN__H
