#ifndef H2XBASE_H2X_MAP_TABLE__H
#define H2XBASE_H2X_MAP_TABLE__H

#include <map>
#include <string>

#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
 * ClassName: ValueMapTable
 * Desc: 值映射表类，采用键值对方式进行映射
 * Author: zfs
 * Date: 2021-06-06 08:41
 */
template<typename keyType, typename valueType>
class H2XBASE_EXPORT ValueMapTable {
public:
    ValueMapTable();
    ~ValueMapTable();

    /*
     * FunctionName: set
     * Desc: 新增一条记录
     * Author: zfs
     * Date: 2021-06-06 09:30
     * @key: 键
     * @value: 键对应的值
     * @replace: 如果为true，当键已经存在时会替换，为false,当键存在时直接返回false
     */
    bool set(const keyType& key, const valueType& value, bool replace = true);

    /*
     * FunctionName: get
     * Desc: 获取键对应的值
     * Author: zfs
     * Date: 2021-06-06 09:31
     * @value: 保存找到的值，会进行内在拷贝
     * 返回值：成功返回true，失败返回false
     */
    bool get(const keyType& key, valueType& value);

    /*
     * FunctionName: remove
     * Desc: 删除一行记录
     */
    void remove(const keyType& key);

    bool isEmpty() {
        return list_.empty();
    }

    size_t count() {
        return list_.size();
    }

    void clear() {
        if (!list_.empty()) {
            list_.clear();
        }
    }

private:
    typedef std::map<keyType, valueType> ValueMapType;

    ValueMapType list_;
};

template<typename keyType, typename valueType>
ValueMapTable<keyType, valueType>::ValueMapTable() {

}

template<typename keyType, typename valueType>
ValueMapTable<keyType, valueType>::~ValueMapTable() {
    this->clear();
}

template<typename keyType, typename valueType>
bool ValueMapTable<keyType, valueType>::set(const keyType& key, const valueType& value, bool replace) {
    std::map<keyType, valueType>::iterator it = list_.find(key);
    if (it != list_.end()) {
        // 替换
        if (replace) {
            memcpy(it->second, value, sizeof(value));
            return true;
        }
        return false;
    }

    // 添加
    std::pair<std::map<keyType, valueType>::iterator, bool> result = 
        list_.insert(std::pair<keyType, valueType>(key, value));

    return result.second;
}

template<typename keyType, typename valueType>
bool ValueMapTable<keyType, valueType>::get(const keyType& key, valueType& value) {
    std::map<keyType, valueType>::iterator it = list_.find(key);
    if (it != list_.end()) {
        //memcpy(&value, it->second, sizeof(value));
        value = it->second;
        return true;
    }
    return false;
}

template<typename keyType, typename valueType>
void ValueMapTable<keyType, valueType>::remove(const keyType& key) {
    std::map<keyType, valueType>::iterator it = list_.find(key);
    if (it != list_.end()) {
        list_.erase(it);
    }
}


///////////////////////////////////////////////////////////////////////////////////
////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////
template<typename keyType>
class H2XBASE_EXPORT PtrMapTable {
public:
    PtrMapTable();
    ~PtrMapTable();

    //
    // set : 添加一条记录，当已经存在时，replace决定是否替换为新值
    //
    const void* set(const keyType& key, const void* value, bool replace = true, bool isDelete = true);

    //
    // get : 查找一条记录
    //
    const void* get(const keyType& key);

    //
    // remove : 删除一条记录,isDelete决定是否要删除对象,true则执行delte删除，否则不删除
    //
    bool remove(const keyType& key, bool isDelete = true);

    bool isEmpty() {
        return list_.empty();
    }

    size_t count() {
        return list_.size();
    }

private:
    typedef std::map<keyType, const void*> PtrMapType;

    PtrMapType list_;
};

template<typename keyType>
PtrMapTable<keyType>::PtrMapTable() {

}

template<typename keyType>
PtrMapTable<keyType>::~PtrMapTable() {

}

template<typename keyType>
const void* PtrMapTable<keyType>::set(const keyType& key, const void* value, bool replace, bool isDelete) {
    std::map<keyType, const void*>::iterator it = list_.find(key);
    if (it != list_.end()) {
        if (!replace) {
            return false;
        }
        if (it->second && isDelete) {
            delete it->second;
        }

        it->second = value;

        return value;
    }

    std::pair<std::map<keyType, const void*>::iterator, bool>
        result = list_.insert(std::pair<keyType, const void*>(key, value));

    if (!result.second) {
        return NULL;
    }

    return value;
}

template<typename keyType>
const void* PtrMapTable<keyType>::get(const keyType& key) {
    std::map<keyType, const void*>::iterator it = list_.find(key);
    if (it != list_.end()) {
        return it->second;
    }
    return NULL;
}

template<typename keyType>
bool PtrMapTable<keyType>::remove(const keyType& key, bool isDelete) {
    std::map<keyType, const void*>::iterator it = list_.find(key);
    if (it != list_.end()) {
        if (it->second && isDelete) {
            delete it->second;
        }
        list_.erase(it);
        return true;
    }
    return false;
}

} // end namespace h2x

#endif // !H2XBASE_H2X_MAP_TABLE__H
