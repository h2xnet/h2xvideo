#include "h2xcore/h2x_listen_table.h"

#include "h2xcore/h2x_listen.h"

namespace h2x {

ListenTable::ListenTable() {

}

ListenTable::~ListenTable() {

}

bool ListenTable::regist(const std::string& name, const Listen* value, bool replace, bool isDelete) {
    if (name.empty() || !value) {
        return false;
    }
    const Listen* node = (const Listen*)list_.set(name, value, replace, isDelete);
    return (node ? true : false);
}

void ListenTable::unregist(const std::string& name, bool isDelete) {
    if (name.empty()) {
        return;
    }

    list_.remove(name, isDelete);
}

Listen* ListenTable::get(const std::string& name) {
    if (name.empty()) {
        return NULL;
    }
    return (Listen*)list_.get(name);
}

} // end namespace h2x