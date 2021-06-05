#ifndef H2XCORE_H2X_CONTEXT__H
#define H2XCORE_H2X_CONTEXT__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Application;
class Helper;
class Model;
class Request;
class Response;
class Service;

/*
* ClassName: Context
* Desc: 上下文请求对象类，每次请求，框架都会实例化一个Context对象
* Author: zfs
* Date: 2021-05-16 17:20
*/
class H2XCORE_EXPORT Context {
public:
    Context();
    virtual ~Context();

private:
    // 应用对象
    Application* app_;

    // 服务对象数组
    Service* services_;

    // 数据模型对象数组
    Model* models_;

    // 请求对象
    Request* req_;

    // 应答对象
    Response* res_;

    // 帮类对象
    Helper* helper_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_CONTEXT__H
