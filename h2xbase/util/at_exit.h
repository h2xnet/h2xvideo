#ifndef H2XBASE_UTIL_AT_EXIT_H_
#define H2XBASE_UTIL_AT_EXIT_H_
#pragma once

#include <stack>
#include <mutex>
#include <memory>
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/btype.h"
#include "h2xbase/task/callback.h"

namespace h2x
{

// This class provides a facility similar to the CRT atexit(), except that
// we control when the callbacks are executed. Under Windows for a DLL they
// happen at a really bad time and under the loader lock. This facility is
// mostly used by base::Singleton.
//
// The usage is simple. Early in the main() or WinMain() scope create an
// AtExitManager object on the stack:
// int main(...) {
//    base::AtExitManager exit_manager;
//
// }
// When the exit_manager object goes out of scope, all the registered
// callbacks and singleton destructors will be called.

class H2XBASE_EXPORT AtExitManager
{
public:
	typedef void (*AtExitCallbackType)(void*);

	AtExitManager();

	// The dtor calls all the registered callbacks. Do not try to register more
	// callbacks after this point.
	~AtExitManager();

	// Registers the specified function to be called at exit. The prototype of
	// the callback function is void func(void*).
	static void registerCallback(AtExitCallbackType func, void* param);

	// Registers the specified task to be called at exit.
	static void registerTask(StdClosure task);

	// Calls the functions registered with RegisterCallback in LIFO order. It
	// is possible to register new callbacks after calling this function.
	static void processCallbacksNow();

	protected:
	// This constructor will allow this instance of AtExitManager to be created
	// even if one already exists.  This should only be used for testing!
	// AtExitManagers are kept on a global stack, and it will be removed during
	// destruction.  This allows you to shadow another AtExitManager.
	explicit AtExitManager(bool shadow);

private:
	std::mutex mutex_;
	std::stack<StdClosure> stack_;
	AtExitManager* next_manager_;  // Stack of managers to allow shadowing.

	DISALLOW_COPY_AND_ASSIGN(AtExitManager);
};

}  // namespace h2x

#endif  // H2XBASE_UTIL_AT_EXIT_H_
