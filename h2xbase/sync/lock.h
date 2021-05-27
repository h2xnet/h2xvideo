#ifndef H2XBASE_SYNC_LOCK__H
#define H2XBASE_SYNC_LOCK__H

#include "build/build_config.h"
#include "h2xbase/h2x_base_export.h"

#if defined(OS_WIN)
#include <windows.h>
#elif defined(OS_POSIX)
#include <pthread.h>
#endif
#include <assert.h>

namespace h2x {


	class H2XBASE_EXPORT NLock
	{
	public:
#if defined(OS_WIN)
		typedef CRITICAL_SECTION OSLockType;
#elif defined(OS_POSIX)
		typedef pthread_mutex_t  OSLockType;
#endif

		NLock();
		~NLock();

		// If the lock is not held, take it and return true.  If the lock is already
		// held by something else, immediately return false.
		bool Try();

		// Take the lock, blocking until it is available if necessary.
		void Lock();

		// Release the lock.  This must only be called by the lock's holder: after
		// a successful call to Try, or a call to Lock.
		void Unlock();

		// Return the native underlying lock.  Not supported for Windows builds.
#if !defined(OS_WIN)
		OSLockType* os_lock() { return &os_lock_; }
#endif

	private:
		OSLockType os_lock_;
	};

	class H2XBASE_EXPORT NAutoLock
	{
	public:
		NAutoLock(NLock * lock)
		{
			assert(lock);
			lock_ = lock;
			lock_->Lock();
		}

		~NAutoLock()
		{
			if (lock_)
				lock_->Unlock();
		}

	private:
		NLock *lock_;
	};

	class H2XBASE_EXPORT NAutoUnlock
	{
	public:
		NAutoUnlock(NLock * lock)
		{
			assert(lock);
			lock_ = lock;
			lock_->Unlock();
		}

		~NAutoUnlock()
		{
			if (lock_)
				lock_->Lock();
		}

	private:
		NLock *lock_;
	};

} // end namespace h2x

#endif // !H2XBASE_SYNC_LOCK__H
