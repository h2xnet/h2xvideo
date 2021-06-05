#ifndef H2XCORE_H2X_CONFIG__H
#define H2XCORE_H2X_CONFIG__H

#include <string>
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Middleware;

/*
    * ClassName: Config
    * Desc: 配置类，配置最终生成的是一个JSON字符串，会根据配置文件进行合并处理
    * 输出到app_config.json，和agent_config.json文件中
    * Author: zfs
    * Date: 2021-05-16 17:17
    */
class H2XCORE_EXPORT Config {
public:
    Config();
    virtual ~Config();

public:
    // 服务运行环境，生产环境为prod，单元测试环境为unittest，本地开发环境为local或空
    // 不同的环境会对应config目录下不同的配置文件
    std::string env_;

    // 此处配置的是全局中间件，局部中间件直接在路由中配置
    // 框架层中间件
    Middleware* core_middleware_;

    // 应用层中间件
    Middleware* app_middleware_;

};

} // end namespace h2x

#endif // !H2XCORE_H2X_CONFIG__H
