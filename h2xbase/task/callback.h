#ifndef H2XBASE_TASK_CALLBACK__H
#define H2XBASE_TASK_CALLBACK__H

#include <string>
#include <memory>
#include <functional>
#include "h2xbase/h2x_base_export.h"

namespace h2x {

// 标准线程任务函数
typedef std::function<void(void)> StdClosure;

// 标准中间件next函数，参数为错误代码和错误消息，如果错误代码为0，则表明没有错误，会继续执行下一个中间件，
// 如果错误代码不为0，则表明发生了错误，会把错误信息一直传递下去，直到最后或传递给错误处理中间件为止
typedef std::function<void(const size_t& errcode, const std::string& errmsg)> StdNextClosure;

} // end namespace h2x

#endif // !H2XBASE_TASK_CALLBACK__H
