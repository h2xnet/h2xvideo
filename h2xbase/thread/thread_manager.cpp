// Copyright (c) 2012, NetEase Inc. All rights reserved.
//
// wrt(guangguang)
// 2012/2/22
//
// a thread manager for iter-thread communicatios, etc.

#include "h2xbase/thread/thread_manager.h"
#include "h2xbase/task/message_loop.h"
#include "h2xbase/task/message_loop_proxy.h"
#include "h2xbase/memory/singleton.h"
#include "h2xbase/third_party/chrome/atomicops.h"

#define AUTO_MAP_LOCK()  std::unique_lock<std::mutex> __l(GetInstance()->mutex_); //NAutoLock __l(&GetInstance()->lock_);
#define AQUIRE_ACCESS() {if (!aquireAccess()) { /*DCHECK(false);*/ return false; }}

namespace h2x
{

bool ThreadMap::aquireAccess()
{
	FrameworkThreadTlsData *tls = FrameworkThread::getTlsData();
	if (!tls || tls->managed < 1)
		return false;
	return true;
}

bool ThreadMap::registerThread(int self_identifier)
{
	//DCHECK(self_identifier >= 0);
	if (self_identifier < 0)
		return false;

	FrameworkThreadTlsData *tls = FrameworkThread::getTlsData();
	//DCHECK(tls); // should be called by a Framework thread
	if (tls == NULL)
		return false;

	AUTO_MAP_LOCK()
	std::pair<std::map<int, FrameworkThread*>::iterator, bool> pr =
		ThreadMap::GetInstance()->threads_.insert(
			std::make_pair(self_identifier, tls->self));
	if (!pr.second)
	{
		if (pr.first->second != tls->self)
		{
			//DCHECK(false); // another thread has registered with the same id
			return false;
		}
		// yes, it's me, check logic error
		//DCHECK(tls->managed > 0);
		//DCHECK(tls->managed_thread_id == self_identifier);
	}
	// 'self' is registered
	tls->managed++;
	tls->managed_thread_id = self_identifier;
	return true;
}

bool ThreadMap::unregisterThread()
{
	FrameworkThreadTlsData *tls = FrameworkThread::getTlsData();
	//DCHECK(tls); // should be called by a Framework thread
	//DCHECK(tls->managed > 0); // should be managed
	if (!tls || tls->managed < 1)
		return false;

	// remove from internal thread map
	// here, since tls->managed is greater than zero,
	// we must have a reference of the glabal ThreadManager instance (see RegisterThread)
	if (--tls->managed == 0)
	{
		AUTO_MAP_LOCK()
		std::map<int, FrameworkThread*>::iterator iter = GetInstance()->threads_.find(tls->managed_thread_id);
		if (iter != GetInstance()->threads_.end())
			GetInstance()->threads_.erase(iter);
		else {}
			//DCHECK(false);	// logic error, we should not come here
		tls->managed_thread_id = -1;
	}

	return true;
}

// no lock
FrameworkThread* ThreadMap::queryThreadInternal(int identifier) const
{
	std::map<int, FrameworkThread*>::iterator iter
		= GetInstance()->threads_.find(identifier);
	if (iter == GetInstance()->threads_.end())
		return NULL;
	return iter->second;
}

int ThreadMap::queryThreadId(const FrameworkThread *thread)
{
	AQUIRE_ACCESS()
	AUTO_MAP_LOCK()
	std::map<int, FrameworkThread*>::iterator iter;
	for (iter = GetInstance()->threads_.begin();
		iter != GetInstance()->threads_.end(); iter++) {
		if (iter->second == thread)
			return iter->first;
	}
	return -1;
}

std::shared_ptr<MessageLoopProxy> ThreadMap::getMessageLoop(int identifier) const
{
	FrameworkThread *thread = queryThreadInternal(identifier);
	if (thread == NULL)
		return NULL;
	MessageLoop *message_loop = thread->message_loop();
	if (message_loop == NULL)
		return NULL;
	return message_loop->message_loop_proxy();
}

bool ThreadManager::registerThread(int self_identifier)
{
	return ThreadMap::GetInstance()->registerThread(self_identifier);
}

bool ThreadManager::unregisterThread()
{
	return ThreadMap::GetInstance()->unregisterThread();
}

int ThreadManager::queryThreadId(const FrameworkThread *thread)
{
	return ThreadMap::GetInstance()->queryThreadId(thread);
}

FrameworkThread* ThreadManager::currentThread()
{
	FrameworkThreadTlsData *tls = FrameworkThread::getTlsData();
	//DCHECK(tls); // should be called by a Framework thread
	//DCHECK(tls->managed > 0); // should be managed
	
	if (!tls || tls->managed < 1)
		return NULL;
	return tls->self;
}

bool ThreadManager::postTask(const StdClosure &task)
{
	MessageLoop::current()->postTask(task);
	return true;
}

bool ThreadManager::postTask(int identifier, const StdClosure &task)
{
	std::shared_ptr<MessageLoopProxy> message_loop =
		ThreadMap::GetInstance()->getMessageLoop(identifier);
	if (message_loop == NULL)
		return false;
	message_loop->postTask(task);
	return true;
}

bool ThreadManager::postDelayedTask(const StdClosure &task, TimeDelta delay)
{
	MessageLoop::current()->postDelayedTask(task, delay);
	return true;
}

bool ThreadManager::postDelayedTask(int identifier, const StdClosure &task, TimeDelta delay)
{
	std::shared_ptr<MessageLoopProxy> message_loop =
		ThreadMap::GetInstance()->getMessageLoop(identifier);
	if (message_loop == NULL)
		return false;
	message_loop->postDelayedTask(task, delay);
	return true;
}

void ThreadManager::postRepeatedTask(const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times)
{
	StdClosure closure = std::bind(&ThreadManager::runRepeatedly, task, delay, times);
	h2x::ThreadManager::postDelayedTask(closure, delay);
}

void ThreadManager::postRepeatedTask(int thread_id, const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times)
{
	StdClosure closure = std::bind(&ThreadManager::runRepeatedly2, thread_id, task, delay, times);
	h2x::ThreadManager::postDelayedTask(thread_id, closure, delay);
}

bool ThreadManager::postNonNestableTask(const StdClosure &task)
{
	MessageLoop::current()->postNonNestableTask(task);
	return true;
}

bool ThreadManager::postNonNestableTask(int identifier, const StdClosure &task)
{
	std::shared_ptr<MessageLoopProxy> message_loop =
		ThreadMap::GetInstance()->getMessageLoop(identifier);
	if (message_loop == NULL)
		return false;
	message_loop->postNonNestableTask(task);
	return true;
}

bool ThreadManager::postNonNestableDelayedTask(const StdClosure &task, TimeDelta delay)
{
	MessageLoop::current()->postNonNestableDelayedTask(task, delay);
	return true;
}

bool ThreadManager::postNonNestableDelayedTask(int identifier, const StdClosure &task, TimeDelta delay)
{
	std::shared_ptr<MessageLoopProxy> message_loop =
		ThreadMap::GetInstance()->getMessageLoop(identifier);
	if (message_loop == NULL)
		return false;
	message_loop->postNonNestableDelayedTask(task, delay);
	return true;
}

void ThreadManager::runRepeatedly(const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times)
{
	if (task.Expired()) {
		return;
	}
	task();
	if (task.Expired()) {
		return;
	}
	if (times != TIMES_FOREVER) {
		times--;
	}
	if (times != 0) {
		postRepeatedTask(task, delay, times);
	}
}

void ThreadManager::runRepeatedly2(int thread_id, const WeakCallback<StdClosure>& task, const TimeDelta& delay, int times)
{
	if (task.Expired()) {
		return;
	}
	task();
	if (task.Expired()) {
		return;
	}
	if (times != TIMES_FOREVER) {
		times--;
	}
	if (times != 0) {
		postRepeatedTask(thread_id, task, delay, times);
	}
}


}
