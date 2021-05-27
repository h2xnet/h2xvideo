#ifndef H2XBASE_STRING_STRING_UTIL__H
#define H2XBASE_STRING_STRING_UTIL__H

#include <string>
#include <memory>

#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
* ClassName: StringResult
* Desc: 字符串处理结果类，用于保存字符串处理后结果字符串（通于用于字符串转换）
* Author: zfs
* Date: 2021-05-19 23:13
*/
class H2XBASE_EXPORT StringResult {
public:
    StringResult() : data_size_(0) {

    }

    virtual ~StringResult() {
        if (data_ptr_.get()) {
            data_ptr_.release();
        }
    }

    /*
     * FunctionName: SetData
     * Desc: 设置字符串结果数据
     * Author: zfs
     * Date: 2021-05-19 23:18
     * @data: 要设置的字符串指针
     * @dataSize: 设置的字符串大小
     */
    void SetData(const char* data, size_t dataSize) {
        data_size_ = 0;
        if (data && dataSize) {
            data_ptr_.reset(new char[dataSize + 1]{ '\0' });
            if (data_ptr_.get()) {
                memcpy(data_ptr_.get(), data, dataSize);
                *(data_ptr_.get() + dataSize) = '\0';
                data_size_ = dataSize;
            }
        }
        else {
            data_ptr_.reset(NULL);
        }
    }

    const char* GetData() {
        return data_ptr_.get();
    }

    size_t GetDataSize() const {
        return data_size_;
    }

private:
    std::unique_ptr<char[]> data_ptr_;
    size_t data_size_;
};

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
};

};

#endif // !H2XBASE_STRING_STRING_UTIL__H
