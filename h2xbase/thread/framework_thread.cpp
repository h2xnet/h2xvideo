// Copyright (c) 2011, NetEase Inc. All rights reserved.
//
// Author: rl
// Date: 2011/6/29
//
// Enhanced by: wrt(guangguang)
//
// Thread with framework(message loop)

#include "h2xbase/thread/framework_thread.h"
#include "h2xbase/btype.h"
#include "h2xbase/h2x_macros.h"
#include "h2xbase/memory/lazy_instance.h"

namespace h2x
{

// We use this thread-local variable to record whether or not a thread exited
// because its Stop method was called.  This allows us to catch cases where
// MessageLoop::Quit() is called directly, which is unexpected when using a
// Thread to setup and run a MessageLoop.
h2x::LazyInstance<h2x::ThreadLocalPointer<FrameworkThreadTlsData> > lazy_tls_data;

FrameworkThread::FrameworkThread(const char* name)
	: started_(false),
	  stopping_(false),
	  loop_type_(MessageLoop::kDefaultMessageLoop),
	  message_loop_(NULL),
	  event_(false, false),
	  name_(name)
{

}

FrameworkThread::~FrameworkThread() {
	stop();
}

bool FrameworkThread::start() {
	return startWithLoop(MessageLoop::kDefaultMessageLoop);
}

//#if defined(OS_WIN)
//bool FrameworkThread::StartWithLoop(const MessageLoop::Type type, Dispatcher *dispatcher)
//#else
bool FrameworkThread::startWithLoop(const MessageLoop::Type type)
//#endif
{
	if (message_loop_ != NULL)
		return false;

	loop_type_ = type;
//#if defined(OS_WIN)
//	dispatcher_ = dispatcher;
//#endif

	if (create() == false)
		return false;

	// Wait for the thread to start and initialize message_loop_
	event_.Wait();

	started_ = true;
	return true;
}

//#if defined(OS_WIN)
//bool FrameworkThread::StartWithLoop(CustomMessageLoopFactory *factory, Dispatcher *dispatcher)
//#else
bool FrameworkThread::startWithLoop(CustomMessageLoopFactory *factory)
//#endif
{
	if (factory == NULL)
		return false;

	factory_.reset(factory);
	loop_type_ = MessageLoop::kCustomMessageLoop;
//#if defined(OS_WIN)
//	dispatcher_ = dispatcher;
//#endif

	if (!create())
		return false;

	// Wait for the thread to start and initialize message_loop_
	event_.Wait();

	started_ = true;

	return true;
}

//#if defined(OS_WIN)
//void FrameworkThread::RunOnCurrentThreadWithLoop(const MessageLoop::Type type, Dispatcher *dispatcher)
//#else
void FrameworkThread::runOnCurrentThreadWithLoop(const MessageLoop::Type type)
//#endif
{
	loop_type_ = type;
	started_ = true;
//#if defined(OS_WIN)
//	dispatcher_ = dispatcher;
//#endif
	run();
}

void FrameworkThread::stop()
{
	if (!thread_was_started())
		return;

	stopSoon();

	// Wait for the thread to exit.
	close();

	started_ = false;
	stopping_ = false;
}

void FrameworkThread::stopSoon()
{
	if (stopping_ || !message_loop_)
		return;

	stopping_ = true;
	message_loop_->postNonNestableTask(
		std::bind(&FrameworkThread::doStopSoon, this));
}

void FrameworkThread::doStopSoon()
{
	MessageLoop::current()->quit();
	setThreadWasQuitProperly(true);
}

void FrameworkThread::run()
{
#ifndef NDEBUG
#if defined(OS_WIN) && defined(COMPILER_MSVC)
	setThreadName(GetCurrentThreadId(), name_.c_str());
#endif
#endif

	initTlsData(this);
	setThreadWasQuitProperly(false);
	{
		ThreadId thread_id = Thread::currentId();
		set_thread_id(thread_id);

		// The message loop for this thread.
		MessageLoop *message_loop;
		if (loop_type_ == MessageLoop::kCustomMessageLoop)
			message_loop = factory_->CreateMessageLoop();
		else {
            /*			if (loop_type_ == MessageLoop::kIOMessageLoop)
				message_loop = new IOMessageLoop;
#if defined(OS_WIN)
			else if (loop_type_ == MessageLoop::kUIMessageLoop)
				message_loop = new UIMessageLoop;
#endif
			else*/
				message_loop = new MessageLoop;
		}
		message_loop_ = message_loop;

		// Let the thread do extra initialization.
		// Let's do this before signaling we are started.
		init();

		event_.Signal();

//#if defined(OS_WIN)
//		message_loop_->RunWithDispatcher(dispatcher_);
//#else
		message_loop_->run();
//#endif // OS_WIN

		// Let the thread do extra cleanup.
		cleanup();

		//DCHECK(GetThreadWasQuitProperly());

		// We can't receive messages anymore.
        if (loop_type_ != MessageLoop::kCustomMessageLoop) {
            delete message_loop_;
        } 
        else {
			delete message_loop_;
			factory_.reset();
		}
		message_loop_ = NULL;
	}
	set_thread_id(kInvalidThreadId);
	{
		FrameworkThreadTlsData *tls = getTlsData();
		if (tls != NULL)
		{ }
			//DCHECK(tls->managed == 0); // you must call ThreadManager::UnregisterThread before come there
	}
	freeTlsData();
}

void FrameworkThread::initTlsData(FrameworkThread *self)
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls == NULL);
	if (tls != NULL)
		return;
	tls = new FrameworkThreadTlsData;
	tls->self = self;
	tls->managed = 0;
	tls->managed_thread_id = -1;
	tls->quit_properly = false;
	tls->custom_data = NULL;
	lazy_tls_data.pointer()->set(tls);
}

void FrameworkThread::freeTlsData()
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls != NULL);
	if (tls == NULL)
		return;
	lazy_tls_data.pointer()->set(NULL);
	delete tls;
}

FrameworkThreadTlsData* FrameworkThread::getTlsData()
{
	return lazy_tls_data.pointer()->get();
}

bool FrameworkThread::getThreadWasQuitProperly()
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls != NULL);
	if (tls == NULL)
		return false;
	return tls->quit_properly;
}

void FrameworkThread::setThreadWasQuitProperly(bool flag)
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls != NULL);
	if (tls == NULL)
		return;
	tls->quit_properly = flag;
}

FrameworkThread* FrameworkThread::current()
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls != NULL);
	if (tls == NULL)
		return NULL;
	return tls->self;
}

int FrameworkThread::getManagedThreadId()
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls != NULL);
	if (tls == NULL)
		return -1;
	return tls->managed_thread_id;
}

void* FrameworkThread::getCustomTlsData()
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls != NULL);
	if (tls == NULL)
		return NULL;
	return tls->custom_data;
}

void FrameworkThread::setCustomTlsData(void *data)
{
	FrameworkThreadTlsData *tls = getTlsData();
	//DCHECK(tls != NULL);
	if (tls == NULL)
		return;
	tls->custom_data = data;
}

}  // namespace nbase