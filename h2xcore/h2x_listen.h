#ifndef H2XCORE_H2X_LISTEN__H
#define H2XCORE_H2X_LISTEN__H

#include <string>
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Option;

/*
* ClassName: Listen
* Desc:¼àÌýÀà
* Author: zhaofushou
* Date: 2021-06-03 22:51
*/
class H2XCORE_EXPORT Listen {
public:
    Listen();
    virtual ~Listen();

    /*
     * FunctionName: getName
     * Desc: ·µ»Ø¼àÌýÆ÷Ãû³Æ
     * Author: zfs
     * Date: 2021-06-06 08:24
     */
    virtual std::string getName() = 0;

    virtual bool init(const Option* opt) = 0;

    virtual bool open() = 0;

    virtual void close() = 0;

    virtual int send(const char* data, size_t size) = 0;

    virtual int recv(unsigned char* buffer, size_t bufferSize) = 0;

    virtual void error(int errno, const std::string& errmsg) = 0;

    virtual bool isOpen() = 0;

};

} // end namespace h2x

#endif // !H2XCORE_H2X_LISTEN__H
