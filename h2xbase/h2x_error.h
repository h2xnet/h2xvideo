#ifndef H2XBASE_H2X_ERROR__H
#define H2XBASE_H2X_ERROR__H

#include <memory>
#include <stdint.h>

#include "h2xbase/h2x_base_export.h"

namespace h2x {

enum ErrorCode {
    ERROR_CODE_SUCCESS = 0, // 成功
    ERROR_CODE_FAIL = 1, // 失败
};

/*
* ClassName: Error 
* Desc: 错误信息类
* Author: zfs
* Date: 2021-05-27 22:15
*/
class H2XBASE_EXPORT Error {
public:
    Error() : data_size_(0) {

    }

    Error(int code, const char* errmsg, size_t errmsgSize) : code_(code) {

    }

    ~Error() {
        data_size_ = 0;
        if (data_ptr_.get()) {
            data_ptr_.release();
        }
    }

    void SetError(int code, const char* errmsg, size_t errmsgSize) {
        code_ = code;
        data_size_ = 0;
        if (errmsg && errmsgSize > 0) {
            data_ptr_.reset(new char[errmsgSize * sizeof(char)] {0});
            if (data_ptr_.get()) {
                data_size_ = errmsgSize;
                memcpy(data_ptr_.get(), errmsg, data_size_ * sizeof(char));
            }
        }
        else {
            data_ptr_.reset(NULL);
        }
    }

    void SetErrmsg(const char* errmsg, size_t errmsgSize = -1) {
        data_size_ = 0;

        if (errmsgSize < 0) {
            if (errmsg) {
                errmsgSize = strlen(errmsg);
            }
            else {
                errmsgSize = 0;
            }
        }
        if (errmsg && errmsgSize > 0) {
            data_ptr_.reset(new char[errmsgSize * sizeof(char)]{ 0 });
            if (data_ptr_.get()) {
                data_size_ = errmsgSize;
                memcpy(data_ptr_.get(), errmsg, data_size_ * sizeof(char));
            }
        }
        else {
            data_ptr_.reset(NULL);
        }
    }

    void SetCode(int code) {
        code_ = code;
    }

    int GetCode() const {
        return code_;
    }

    const char* GetErrmsg() const {
        return data_ptr_.get();
    }

    const size_t GetErrmsgSize() const {
        return data_size_;
    }

private:
    // 错误代码
    int code_;

    // 错误信息
    std::unique_ptr<char[]> data_ptr_;
    size_t data_size_;
};

} // end namespace h2x

#endif // ! H2XBASE_H2X_ERROR__H
