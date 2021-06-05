#include "h2xcore/h2x_application.h"

#include "h2xcore/h2x_config.h"
#include "h2xcore/h2x_context.h"
#include "h2xcore/h2x_middleware.h"
#include "h2xcore/h2x_router.h"

#include <assert.h>

namespace h2x {

Application::Application(const Config* cfg) : cfg_((Config*)cfg) {
	assert(cfg_);
}

Application::~Application() {

}

void Application::beforeStart() {

}

void Application::onStarted() {
    //
    // onStarted : ����������ɺ��ӵ��õĻص�����
    // �˺���������� once ע��Ļص�����������֪ͨ
    //
}

bool Application::once(const std::string& name) {
    return true;
}

bool Application::on(const std::string& name) {
    return true;
}

} // end namespace h2x