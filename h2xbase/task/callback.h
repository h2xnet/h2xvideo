#ifndef H2XBASE_TASK_CALLBACK__H
#define H2XBASE_TASK_CALLBACK__H

//#include <string>
#include <memory>
#include <functional>
#include "h2xbase/h2x_base_export.h"

namespace h2x {

// 标准线程任务函数
typedef std::function<void(void)> StdClosure;

// 标准中间件next函数，参数为错误代码和错误消息，如果错误代码为0，则表明没有错误，会继续执行下一个中间件，
// 如果错误代码不为0，则表明发生了错误，会把错误信息一直传递下去，直到最后或传递给错误处理中间件为止
typedef std::function<void(const size_t& errcode, const std::string& errmsg)> StdNextClosure;


class WeakFlag
{

};

template<typename T>
class WeakCallback
{
public:
    WeakCallback(const std::weak_ptr<WeakFlag>& weak_flag, const T& t) :
        weak_flag_(weak_flag),
        t_(t)
    {

    }

    WeakCallback(const std::weak_ptr<WeakFlag>& weak_flag, T&& t) :
        weak_flag_(weak_flag),
        t_(std::move(t))
    {

    }

    template<class WeakType>
    WeakCallback(const WeakType& weak_callback) :
        weak_flag_(weak_callback.weak_flag_),
        t_(weak_callback.t_)
    {

    }

    template<class... Args>
    auto operator ()(Args && ... args) const
#if _MSC_VER > 1900
#else
        ->decltype(t_(std::forward<Args>(args)...))
#endif
    {
        if (!weak_flag_.expired()) {
            return t_(std::forward<Args>(args)...);
        }
        return decltype(t_(std::forward<Args>(args)...))();
    }

    bool Expired() const
    {
        return weak_flag_.expired();
    }


    std::weak_ptr<WeakFlag> weak_flag_;
    mutable T t_;
};

class H2XBASE_EXPORT SupportWeakCallback
{
public:
    typedef std::weak_ptr<WeakFlag> _TyWeakFlag;
public:
    virtual ~SupportWeakCallback() {};

    template<typename CallbackType>
    auto ToWeakCallback(const CallbackType& closure)
        ->WeakCallback<CallbackType>
    {
        return WeakCallback<CallbackType>(GetWeakFlag(), closure);
    }

    std::weak_ptr<WeakFlag> GetWeakFlag()
    {
        if (m_weakFlag.use_count() == 0) {
            m_weakFlag.reset((WeakFlag*)NULL);
        }
        return m_weakFlag;
    }

private:
    template<typename ReturnValue, typename... Param, typename WeakFlag>
    static std::function<ReturnValue(Param...)> ConvertToWeakCallback(
        const std::function<ReturnValue(Param...)>& callback, std::weak_ptr<WeakFlag> expiredFlag)
    {
        auto weakCallback = [expiredFlag, callback](Param... p) {
            if (!expiredFlag.expired()) {
                return callback(p...);
            }
            return ReturnValue();
        };

        return weakCallback;
    }

protected:
    std::shared_ptr<WeakFlag> m_weakFlag;
};

//WeakCallbackFlag一般作为类成员变量使用，要继承，可使用不带Cancel()函数的SupportWeakCallback
//这里禁止继承，主要担心误用。当使用这个类的功能，打包出多个支持weak语义的callback时，一旦错误的调用了Cancel，
//将会取消所有callback，这种情况可能不是用户希望的。此时，应该使用多个不带Cancel函数的WeakCallbackFlag类型的成员变量，
//每个对应一个callback，一一对应的控制每个支持weak语义的callback。
class H2XBASE_EXPORT WeakCallbackFlag final : public SupportWeakCallback
{
public:
    void Cancel()
    {
        m_weakFlag.reset();
    }

    bool HasUsed()
    {
        return m_weakFlag.use_count() != 0;
    }
};


// global function 
template<class F, class... Args, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
auto Bind(F && f, Args && ... args)
->decltype(std::bind(f, args...))
{
    return std::bind(f, args...);
}

// const class member function 
template<class R, class C, class... DArgs, class P, class... Args>
auto Bind(R(C::*f)(DArgs...) const, P && p, Args && ... args)
->WeakCallback<decltype(std::bind(f, p, args...))>
{
    std::weak_ptr<WeakFlag> weak_flag = ((SupportWeakCallback*)p)->GetWeakFlag();
    auto bind_obj = std::bind(f, p, args...);
    static_assert(std::is_base_of<nbase::SupportWeakCallback, C>::value, "nbase::SupportWeakCallback should be base of C");
    WeakCallback<decltype(bind_obj)> weak_callback(weak_flag, std::move(bind_obj));
    return weak_callback;
}

// non-const class member function 
template<class R, class C, class... DArgs, class P, class... Args>
auto Bind(R(C::*f)(DArgs...), P && p, Args && ... args)
->WeakCallback<decltype(std::bind(f, p, args...))>
{
    std::weak_ptr<WeakFlag> weak_flag = ((SupportWeakCallback*)p)->GetWeakFlag();
    auto bind_obj = std::bind(f, p, args...);
    static_assert(std::is_base_of<nbase::SupportWeakCallback, C>::value, "nbase::SupportWeakCallback should be base of C");
    WeakCallback<decltype(bind_obj)> weak_callback(weak_flag, std::move(bind_obj));
    return weak_callback;
}


} // end namespace h2x

#endif // !H2XBASE_TASK_CALLBACK__H
