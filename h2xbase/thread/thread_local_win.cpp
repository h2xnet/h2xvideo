// Copyright (c) 2011, NetEase Inc. All rights reserved.
//
// Author: wrt(guangguang)
// Date: 2011/6/14
//
// This file implements some useful thread local template data structures for Windows

#include "h2xbase/thread/thread_local.h"
#if defined(OS_WIN)
#include <assert.h>
#include <windows.h>

namespace h2x
{

namespace internal
{

// static
void ThreadLocalPlatform::allocateSlot(SlotType &slot)
{
	slot = ::TlsAlloc();
	assert(slot != TLS_OUT_OF_INDEXES);
}

// static
void ThreadLocalPlatform::freeSlot(SlotType &slot)
{
	if (!::TlsFree(slot))
	{
		assert(false);
	}
}

// static
void* ThreadLocalPlatform::getValueFromSlot(SlotType &slot)
{
	return ::TlsGetValue(slot);
}

// static
void ThreadLocalPlatform::setValueInSlot(SlotType &slot, void *value)
{
	if (!::TlsSetValue(slot, value))
	{
		assert(false);
	}
}

}  // namespace internal

}  // namespace h2x

#endif // OS_WIN
