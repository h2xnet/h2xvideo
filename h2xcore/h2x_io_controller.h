#ifndef H2XCORE_H2X_IO_CONTROLLER__H
#define H2XCORE_H2X_IO_CONTROLLER__H

#include "h2xcore/h2x_core_export.h"
#include "h2xcore/h2x_controller.h"

namespace h2x {

    /*
    * ClassName: IOController
    * Desc: IO控制器类，负责提供高IO任务类型处理
    * 与CPU控制器的区别是，所有IO控制器任务都在同一个线程中进行运行，适合处理高IO，低时延的任务
    * 而不同的CPU控制器对象则会在不同的线程中运行（每个CPU控制器任务由单独的线程负责处理），适合处理占CPU时间长，IO不频繁的任务
    * Author: zfs
    * Date: 2021-05-27 21:50
    */
    class H2XCORE_EXPORT IOController : public Controller {
    public:
        IOController(Application* app, Context* ctx);
        virtual ~IOController();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_IO_CONTROLLER__H
