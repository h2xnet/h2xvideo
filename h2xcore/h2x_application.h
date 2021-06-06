#ifndef H2XCORE_H2X_APPLICATION__H
#define H2XCORE_H2X_APPLICATION__H

#include <string>
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Cache;
class Config;
class Context;
class Middleware;
class Router;

// 各种日志类型
class AppLogger;
class AppCoreLogger;
class ContextLogger;
class ContextCoreLogger;
class ControllerLogger;
class Listen;
class ListenTable;
class ServiceLogger;

/*
 * ClassName: Application
 * Desc: 应用类，一个应用只允许有一个实例
 * Author: zfs
 * Date: 2021-05-16 17:12
 */
class H2XCORE_EXPORT Application {
public:
    Application(const Config* cfg);
    virtual ~Application();

    /*
     * FunctionName: beforeStart
     * Desc: 当应用服务启动前，会调用此函数回调通知，一个应用只会通知一次
     * Author: zfs
     * Date: 2021-06-05 09:38
     */
    virtual void beforeStart();

    /*
     * FunctionName: onStarted
     * Desc: 当应用服务启动完成后，会调用此函数回调通知，一个应用只会通知一次
     * Author: zfs
     * Date: 2021-06-05 09:38
     */
    virtual void onStarted();
    virtual bool once(const std::string& name);

    /*
     * FunctionName: on
     * Desc: 注册事件监听函数，此函数注册的事件，每次发生都会通知
     * Author: zfs
     * Date: 2021-06-05 09:38
     * @name: 事件名称，主要有比如error事件,request事件，response事件等
     */
    virtual bool on(const std::string& name);

    /*
     * FunctionName: createAnonymousContext
     * Desc: 创建一个匿名的上下文对象
     */
    Context* createAnonymousContext();

	/*
	 * setName : 设置应用名称
	 * Author: zfs
	 * Date: 2021-05-17 12:38
	 */
	void setName(const char* name, size_t nameSize) {
		if (name && nameSize > 0) {
			name_ = std::string(name, nameSize);
		}
		else {
			name_ = "h2xapp";
		}
	}

	/*
	 * getName: 获取应用名称
	 * Author: zfs
	 * Date: 2021-05-17 12:38
	*/
	const char* getName() {
		return name_.c_str();
	}

	/*
	 * FunctionName: getConfig
	 * Desc: 获取配置指针
	 * Author: zhaofushou
	 * Date: 2021-05-17 12:40
	 */
	Config* getConfig() const {
		return cfg_;
	}

private:
	// 应用名称
	std::string name_;

    // 配置对象
	Config* cfg_;

    // 缓存对象
    Cache* cache_;

    // 监听对象
    ListenTable* listens_;

    // 中间件对象
    Middleware* middlewares_;

    // 路由对象
    Router* router_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_APPLICATION__H
