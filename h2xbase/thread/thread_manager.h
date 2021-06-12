// a thread manager for iter-thread communicatios, etc.

#ifndef H2XBASE_THREAD_THREAD_MANAGER_H_
#define H2XBASE_THREAD_THREAD_MANAGER_H_

#include <map>
#include <mutex>
#include <memory>
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/btype.h"
#include "h2xbase/thread/framework_thread.h"
#include "h2xbase/memory/singleton.h"

/**
 * 一些预定义的线程 ID 值，提供开发者使用
 */
enum ThreadIds
{
	kThreadUI,
	kThreadIO,
	kThreadGlobalMisc,
};

namespace h2x
{
class MessageLoop;
class MessageLoopProxy;

class ThreadMap {
public:
	SINGLETON_DEFINE(ThreadMap);
	static bool aquireAccess();

	bool registerThread(int self_identifier);
	bool unregisterThread();
	int queryThreadId(const FrameworkThread *thread);
	std::shared_ptr<MessageLoopProxy> getMessageLoop(int identifier) const;
	FrameworkThread* queryThreadInternal(int identifier) const;

private:
	ThreadMap() { }

    std::mutex mutex_;
	std::map<int, FrameworkThread*> threads_;
};

// 使用ThreadManager可以极大地方便线程间通信
// 注意：只有受ThreadManager托管的线程（通过Register托管）才允许调用除Register和Post族外的成员函数
class H2XBASE_EXPORT ThreadManager
{
public:

	// 托管当前FrameworkThread线程
	// identifier >= 0
	// 必须在self的线程过程内被调用
	static bool registerThread(int self_identifier);
	// 取消当前线程托管
	// 线程运行结束之前必须调用UnregisterThread取消托管
	static bool unregisterThread();

	// 查找
	static FrameworkThread* currentThread();
	template<typename T> static T* currentThreadT();
	static int queryThreadId(const FrameworkThread *thread);

	static bool postTask(const StdClosure &task);
	static bool postTask(int identifier, const StdClosure &task);

	static bool postDelayedTask(const StdClosure &task, TimeDelta delay);
	static bool postDelayedTask(int identifier, const StdClosure &task, TimeDelta delay);

	static const int TIMES_FOREVER = -1;
	static void postRepeatedTask(const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times = TIMES_FOREVER);
	static void postRepeatedTask(int thread_id, const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times = TIMES_FOREVER);

	static bool postNonNestableTask(const StdClosure &task);
	static bool postNonNestableTask(int identifier, const StdClosure &task);

	static bool postNonNestableDelayedTask(const StdClosure &task, TimeDelta delay);
	static bool postNonNestableDelayedTask(int identifier, const StdClosure &task, TimeDelta delay);

	template<typename T1, typename T2>
	static bool await(int identifier, const std::function<T1> &task, const std::function<T2> &reply) {
		std::shared_ptr<MessageLoopProxy> message_loop =
			ThreadMap::GetInstance()->getMessageLoop(identifier);
		if (message_loop == NULL)
			return false;
		message_loop->postTaskAndReply(task, reply);
		return true;
	}

private:
	static void runRepeatedly(const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times);
	static void runRepeatedly2(int thread_id, const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times);

	DISALLOW_COPY_AND_ASSIGN(ThreadManager);
};

template<typename T>
T* ThreadManager::currentThreadT()
{
	return static_cast<T *>(CurrentThread());
}

}

#endif // H2XBASE_THREAD_THREAD_MANAGER_H_
