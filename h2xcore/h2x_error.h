#ifndef H2XCORE_H2X_ERROR__H
#define H2XCORE_H2X_ERROR__H

#include <memory>
#include "h2xbase/string/string_result.h"
#include "h2xbase/h2x_error_code.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: Error
* Desc: 错误信息类
* Author: zfs
* Date: 2021-06-05 10:18
*/
class H2XCORE_EXPORT Error {
public:
    Error();
    virtual ~Error();

public:
    // 请求状态，0为成功，其它为错误代码
    int status_;

    // 数据错误代码，0为正确，其它为错误代码
    int code_;

    // 错误消息
    StringResult<char> msg_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_ERROR__H
