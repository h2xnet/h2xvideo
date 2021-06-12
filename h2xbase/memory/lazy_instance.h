#ifndef H2XBASE_MEMORY_LAXY_INSTANCE__H
#define H2XBASE_MEMORY_LAXY_INSTANCE__H

#include "build/build_config.h"
#include "h2xbase/btype.h"
#include "h2xbase/third_party/chrome/atomicops.h"
#include "h2xbase/thread/thread.h"
#include "h2xbase/util/at_exit.h"

namespace h2x {


template<typename Type>
class LazyInstance
{
public:

    LazyInstance() : instance_(NULL) {
        h2x::subtle::NoBarrier_Store(&state_, kNone);
    }

    ~LazyInstance() {
        // |instance_| should be deleted by |OnExit|
        //DCHECK(instance_ == 0);
    }

    Type& get() {
        return *pointer();
    }

    Type* pointer() {
        using namespace h2x::subtle;

        if (Acquire_Load(&state_) != kCreated)
        {
            Atomic32 state =
                NoBarrier_CompareAndSwap(&state_, kNone, kCreating);
            if (state == kNone) {
                // we take the chance to create the instance
                instance_ = reinterpret_cast<AtomicWord>(new Type());
                AtExitManager::registerCallback(OnExit, this);
                Release_Store(&state_, kCreated);
            }
            else if (state != kCreated) {
                // wait, util another thread created the instance
                while (Acquire_Load(&state_) != kCreated) {
                    Thread::yieldThread();
                }
            }
        }

        return reinterpret_cast<Type *>(instance_);
    }

    bool operator ==(Type *object) const {
        switch (h2x::subtle::NoBarrier_Load(&state_))
        {
        case kNone:
            return object == NULL;
        case kCreating:
        case kCreated:
            return instance_ == object;
        default:
            return false;
        }
    }

private:
    enum
    {
        kNone = 0,
        kCreating,
        kCreated,
        kDeleting,
    };

    static void OnExit(void *lazy_instance) {
        LazyInstance<Type>* me =
            reinterpret_cast<LazyInstance<Type>*>(lazy_instance);
        delete reinterpret_cast<Type*>(me->instance_);
        h2x::subtle::NoBarrier_Store(&me->instance_, 0);
    }

    h2x::subtle::Atomic32 state_;
    h2x::subtle::AtomicWord instance_;

    DISALLOW_COPY_AND_ASSIGN(LazyInstance);
};

} // end namespace h2x

#endif // !H2XBASE_MEMORY_LAXY_INSTANCE__H
