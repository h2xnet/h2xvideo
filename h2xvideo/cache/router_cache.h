#ifndef H2XVIDEO_CACHE_ROUTER_CACHE__H
#define H2XVIDEO_CACHE_ROUTER_CACHE__H

#include <list>
#include <qstring.h>

/*
 * ClassName: RouterCache
 * Desc: 路由缓存，用于存储页面路由历史记录，高级属性提回撤销
 * Author: zfs
 * Date: 2021-06-12 22:55
 */
class RouterCache {
public:
    typedef struct RouterNode_ {
        RouterNode_(QString name, QString param) {
            if (!name.isEmpty()) {
                pageName = QString::fromUtf8(name.toUtf8().data(), name.toUtf8().size());
            }
            if (!param.isEmpty()) {
                pageParam = QString::fromUtf8(param.toUtf8().data(), param.toUtf8().size());
            }
        }

        QString pageName; // 页面名称
        QString pageParam; // 页面参数
    } RouterNode;

    typedef std::list<RouterNode> RouterListType;
    typedef std::list<RouterNode>::iterator RouterListIterator;

    RouterCache();
    virtual ~RouterCache();

    /*
     * FunctionName: pushBack
     * Desc: 末尾追加一条记录
     * Author: zfs
     * Date: 2021-06-12 23:06
     */
    bool pushBack(QString pageName, QString pageParam = QString(""));

    /*
     * FunctionName: peekFront
     * Desc: 检查头无素，但不删除
     * Author: zfs
     * Date: 2021-06-12 23:17
     */
    bool peekFront(RouterNode& node);

    /*
     * FunctionName: popFront
     * Desc: 检测头元素，并且删除
     * Author: zfs
     * Date: 2021-06-12 23:18
     */
    bool popFront(RouterNode& node);

    bool isEmpty() {
        return list_.empty();
    }

    bool isFull() {
        return (list_.size() == max_count_);
    }

private:
    /*
     * FunctionName: OnReCal
     * Desc: 如果满了，则重新调整，删除部分记录
     * Author: zfs
     * Date: 2021-06-12 23:11
     */
    void OnReCal();

    // 最大记录个数
    int max_count_;

    // 数据列表
    RouterListType list_;
};

#endif // !H2XVIDEO_CACHE_ROUTER_CACHE__H
