#ifndef H2XBASE_H2X_ERROR_CODE__H
#define H2XBASE_H2X_ERROR_CODE__H

#include <memory>
#include <stdint.h>

namespace h2x {

//
// ErrorCode : 错误信息 code 代码
//
enum ErrorCode {
    ERROR_CODE_SUCCESS = 0, // 成功
    ERROR_CODE_FAIL = 1, // 失败
};

//
// 错误信息 status 代码
//
#define ERROR_STATUS_SUCCESS    0   // 成功
#define ERROR_STATUS_FAIL       -1  // 失败

} // end namespace h2x

#endif // ! H2XBASE_H2X_ERROR_CODE__H
