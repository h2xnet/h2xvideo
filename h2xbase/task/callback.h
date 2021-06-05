#ifndef H2XBASE_TASK_CALLBACK__H
#define H2XBASE_TASK_CALLBACK__H

#include <string>
#include <memory>
#include <functional>
#include "h2xbase/h2x_base_export.h"

namespace h2x {

// ��׼�߳�������
typedef std::function<void(void)> StdClosure;

// ��׼�м��next����������Ϊ�������ʹ�����Ϣ������������Ϊ0�������û�д��󣬻����ִ����һ���м����
// ���������벻Ϊ0������������˴��󣬻�Ѵ�����Ϣһֱ������ȥ��ֱ�����򴫵ݸ��������м��Ϊֹ
typedef std::function<void(const size_t& errcode, const std::string& errmsg)> StdNextClosure;

} // end namespace h2x

#endif // !H2XBASE_TASK_CALLBACK__H
