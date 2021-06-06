#include "http_client_listen_plugin.h"


namespace h2x {

HttpClientListenPlugin::HttpClientListenPlugin() {
}

HttpClientListenPlugin::~HttpClientListenPlugin() {

}

std::string HttpClientListenPlugin::getName() {
    return std::string("http_client_listen_plugin");
}

bool HttpClientListenPlugin::init(const Option* opt) {
    return true;
}

bool HttpClientListenPlugin::open() {
    return true;
}

void HttpClientListenPlugin::close() {

}

void HttpClientListenPlugin::error(int errorno, const std::string& errormsg) {

}

bool HttpClientListenPlugin::isOpen() {
    return false;
}

int HttpClientListenPlugin::send(const char* data, size_t size) {
    return 0;
}

int HttpClientListenPlugin::recv(unsigned char* buffer, size_t bufferSize) {
    return 0;
}

bool HttpClientListenPlugin::isRunning() {
    return false;
}

void HttpClientListenPlugin::working() {

}

} // end namespace h2x {