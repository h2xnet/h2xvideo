#ifndef H2XBASE_STRING_STRING_RESULT__H
#define H2XBASE_STRING_STRING_RESULT__H

#include <memory>
#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
* ClassName: StringResult
* Desc: 字符串处理结果类，用于保存字符串处理后结果字符串（通于用于字符串转换）
* Author: zfs
* Date: 2021-05-19 23:13
*/

template <class T>
class H2XBASE_EXPORT StringResult {
public:
    StringResult() : data_size_(0) {

    }

    virtual ~StringResult() {
        if (data_ptr_.get()) {
            data_ptr_.release();
        }
    }

    void SetData(const T* data, size_t dataSize) {
        data_size_ = 0;
        if (data && dataSize > 0) {
            data_ptr_.reset(new T[dataSize]{ 0 });
            if (data_ptr_.get()) {
                memcpy(data_ptr_.get(), data, dataSize * sizeof(T));
                data_size_ = dataSize;
            }
        }
        else {
            data_ptr_.reset(NULL);
        }
    }

    T* GetData() {
        return data_ptr_.get();
    }

    size_t GetDataSize() const {
        return data_size_;
    }

private:
    std::unique_ptr<T[]> data_ptr_;
    size_t data_size_;
};

} // end namespace h2x

#endif // !H2XBASE_STRING_STRING_RESULT__H
