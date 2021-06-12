#include "h2xcore/h2x_application.h"

#include "h2xcore/h2x_config.h"
#include "h2xcore/h2x_context.h"
#include "h2xcore/h2x_listen_table.h"
#include "h2xcore/h2x_middleware.h"
#include "h2xcore/h2x_router.h"

#include <assert.h>

namespace h2x {

Application::Application(int argc, char *argv[], const Config* cfg) : argc_(argc), argv_(argv), cfg_((Config*)cfg) {
	if (!cfg_) {
        cfg_ = new Config();
    }
    assert(cfg_);
}

Application::~Application() {

}
bool Application::exec() {

    this->beforeStart();

    // 加载配置文件

    this->onStarted();

    return true;
}

void Application::beforeStart() {

}

void Application::onStarted() {
    //
    // onStarted : 服务启动完成后框加调用的回调函数
    // 此函数会遍历用 once 注册的回调函数，发送通知
    //
}

bool Application::once(const std::string& name) {
    return true;
}

bool Application::on(const std::string& name) {
    return true;
}

} // end namespace h2x