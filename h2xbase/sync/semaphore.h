#ifndef H2XBASE_SYNC_SEMAPHORE__H
#define H2XBASE_SYNC_SEMAPHORE__H

#include "h2xbase/h2x_base_export.h"
#include "h2xbase/btype.h"

#if defined(OS_WIN)
#include <windows.h>
#else
#include <sys/semaphore.h>
#endif

namespace h2x {


	class H2XBASE_EXPORT Semaphore
	{
	public:
#if defined(OS_WIN)
		typedef HANDLE OSSemaphoreType;
#elif defined(OS_POSIX)
		typedef sem_t *OSSemaphoreType;
#endif

		Semaphore();
		~Semaphore();

	public:
		bool CreateSemaphore(const char *sem_name, uint32_t init_value, uint32_t max_value);
		/* wait the semaphore until some post one*/
		bool WaitSemaphore();
		/* wait the semaphore until some post one or timeout */
		bool WaitSemaphore(uint32_t timeout_ms);
		/* post some semaphore*/
		bool PostSemaphore(uint32_t post_num);

	private:
		uint32_t        init_value_;
		OSSemaphoreType semaphore_;
	};


} // end namespace h2x

#endif // !H2XBASE_SYNC_SAMAPHORE__H
