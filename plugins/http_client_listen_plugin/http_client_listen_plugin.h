#ifndef PLUGINS_HTTP_CLIENT_LISTEN_PLUGIN__H
#define PLUGINS_HTTP_CLIENT_LISTEN_PLUGIN__H

#include "h2xcore/h2x_listen.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: HttpClientListenPlugin
* Desc: http客户端请求插件，接收用户http请求事件，并进行网络请求，再将请求结果进行应答
* Author: zfs
* Date: 2021-06-06 17:07
*/
class H2XCORE_EXPORT HttpClientListenPlugin : public Listen
{
public:
    HttpClientListenPlugin();
    virtual ~HttpClientListenPlugin();

    //
    // Plugin
    //
    virtual std::string getName() override;
    virtual bool init(const Option* opt) override;
    virtual bool open() override;
    virtual void close() override;
    virtual void error(int errorno, const std::string& errormsg) override;
    virtual bool isOpen() override;

    //
    // Listen
    // 
    virtual int send(const char* data, size_t size) override;
    virtual int recv(unsigned char* buffer, size_t bufferSize) override;
    virtual bool isRunning() override;
    virtual void working() override;
};

} // end namespace h2x

#endif // PLUGINS_HTTP_CLIENT_LISTEN_PLUGIN__H
