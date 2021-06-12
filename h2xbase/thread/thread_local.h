// This file implements some useful thread local template data structures

#ifndef H2XBASE_THREAD_THREAD_LOCAL_H_
#define H2XBASE_THREAD_THREAD_LOCAL_H_

#include "build/build_config.h"
#if defined(OS_POSIX)
#include <pthread.h>
#endif
#include "h2xbase/h2x_macros.h"

namespace h2x
{

namespace internal
{

struct ThreadLocalPlatform
{
#if defined(OS_WIN)
	typedef unsigned long SlotType;
#elif defined(OS_POSIX)
	typedef pthread_key_t SlotType;
#endif

	static void allocateSlot(SlotType &slot);
	static void freeSlot(SlotType &slot);
	static void* getValueFromSlot(SlotType &slot);
	static void setValueInSlot(SlotType &slot, void *value);
};

} // namespace internal

template<typename Type>
class ThreadLocalPointer
{
public:

	ThreadLocalPointer() : slot_()
	{
		internal::ThreadLocalPlatform::allocateSlot(slot_);
	}

	~ThreadLocalPointer()
	{
		internal::ThreadLocalPlatform::freeSlot(slot_);
	}

	Type* get()
	{
		return static_cast<Type*>(internal::ThreadLocalPlatform::getValueFromSlot(slot_));
	}

	void set(Type *ptr)
	{
		internal::ThreadLocalPlatform::setValueInSlot(slot_, ptr);
	}

private:
	typedef internal::ThreadLocalPlatform::SlotType SlotType;
	SlotType slot_;

	DISALLOW_COPY_AND_ASSIGN(ThreadLocalPointer);
};

class ThreadLocalBoolean
{
public:

	ThreadLocalBoolean() {}
	~ThreadLocalBoolean() {}

	bool get()
	{
		return !!tlp_.get();
	}

	void set(bool val)
	{
		tlp_.set(reinterpret_cast<void*>(val ? 1 : 0));
	}

private:
	ThreadLocalPointer<void> tlp_;

	DISALLOW_COPY_AND_ASSIGN(ThreadLocalBoolean);
};

} // namespace h2x

#endif // H2XBASE_THREAD_THREAD_LOCAL_H_
