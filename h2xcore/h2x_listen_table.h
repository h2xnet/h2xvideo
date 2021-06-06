#ifndef H2XCORE_H2X_LISTEN_TABLE__H
#define H2XCORE_H2X_LISTEN_TABLE__H

#include "h2xbase/h2x_map_table.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Listen;

/*
* ClassName: ListenTable
* Desc: 监听器注册表
* Author: zfs
* Date: 2021-06-06 09:43
*/
class H2XCORE_EXPORT ListenTable {
public:
    ListenTable();
    virtual ~ListenTable();

    /*
     * FunctionName: regist
     * Desc: 注册一个监听器
     * Author: zfs
     * Date: 2021-06-06 09:50
     * @name: 监听器名称
     * @value: 监听器指针
     * @replace: 如果已经存在，则是否替换标志，true表示替换，false表示不替换
     * @isDelete: 如果replace为true时，是否删除标志
     * 返回值：成功返回true，失败返回false
     */
    bool regist(const std::string& name, const Listen* value, bool replace = true, bool isDelete = true);

    /*
     * FunctionName: unregist
     * Desc: 注销一个监听器
     * Author: zfs
     * Date: 2021-06-06 10:35
     * @name: 监听器名称
     * @isDelete: 是否删除标志
     */
    void unregist(const std::string& name, bool isDelete = true);

    /*
     * FunctionName: get
     * Desc: 查询指定监听器
     * Author: zfs
     * Date: 2021-06-06 10:37
     * @name: 监听器名称
     */
    Listen* get(const std::string& name);

private:
    typedef PtrMapTable<std::string> ListenTableType;

    ListenTableType list_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_LISTEN_TABLE__H
