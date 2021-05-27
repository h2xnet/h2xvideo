#ifndef H2XBASE_LOGGER_H2X_LOGGER__H
#define H2XBASE_LOGGER_H2X_LOGGER__H

#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
* ClassName: Logger
* Desc: ��־��
* Author: zfs
* Date: 2021-05-16 17:25
*/
class H2XBASE_EXPORT Logger {
public:
    enum LOG_TYPE {
        LOG_DEBUG, // ����
        LOG_INFO, // ��Ϣ
        LOG_WARNING, // ����
        LOG_ERROR, // ����
        LOG_FATAL // ���ش���
    };
    
    Logger();
    virtual ~Logger();

    void SetLogType(LOG_TYPE type) {
        log_type_ = type;
    }

    int GetLogType() const {
        return log_type_;
    }

private:
    // ������־��������
    int log_type_;
};

} // end namespace h2x

#endif // !H2XBASE_LOGGER_H2X_LOGGER__H
