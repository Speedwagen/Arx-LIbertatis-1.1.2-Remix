/*
 * Copyright 2011-2013 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "platform/Thread.h"

#include "platform/CrashHandler.h"
#include "platform/Platform.h"

void Thread::setThreadName(const std::string & _threadName) {
	threadName = _threadName;
}

#if defined(ARX_HAVE_PTHREADS)

#include <sched.h>
#include <unistd.h>

#if !defined(ARX_HAVE_PTHREAD_SETNAME_NP) && !defined(ARX_HAVE_PTHREAD_SET_NAME_NP) \
    && defined(ARX_HAVE_PRCTL)
#include <sys/prctl.h>
#endif

#if defined(ARX_HAVE_PTHREAD_SET_NAME_NP)
#include <pthread_np.h>
#endif

Thread::Thread() : started(false) {
	setPriority(Normal);
}

void Thread::start() {
	
	if(started) {
		return;
	}
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	sched_param param;
	param.sched_priority = priority;
	pthread_attr_setschedparam(&attr, &param);
	
	pthread_create(&thread, NULL, entryPoint, this);
	
	pthread_attr_destroy(&attr);
	
	started = true;
}

void Thread::setPriority(Priority _priority) {
	
#ifdef ARX_HAVE_SCHED_GETSCHEDULER
	int policy = sched_getscheduler(0);
#else
	int policy = SCHED_RR;
#endif
	
	int min = sched_get_priority_min(policy);
	int max = sched_get_priority_max(policy);
	
	priority = min + ((_priority - Lowest) * (max - min) / (Highest - Lowest));
	
	if(started && min != max) {
		sched_param param;
		param.sched_priority = priority;
		pthread_setschedparam(thread, policy, &param);
	}
}

Thread::~Thread() { }

void Thread::waitForCompletion() {
	if(started) {
		pthread_join(thread, NULL);
	}
}

void * Thread::entryPoint(void * param) {
	
	Thread & thread = *((Thread *)param);
	
	// Set the thread name.
#if defined(ARX_HAVE_PTHREAD_SETNAME_NP) && ARX_PLATFORM != ARX_PLATFORM_MACOSX
	// Linux
	pthread_setname_np(thread.thread, thread.threadName.c_str());
#elif defined(ARX_HAVE_PTHREAD_SETNAME_NP) && ARX_PLATFORM == ARX_PLATFORM_MACOSX
	// Mac OS X
	pthread_setname_np(thread.threadName.c_str());
#elif defined(ARX_HAVE_PTHREAD_SET_NAME_NP)
	// FreeBSD & OpenBSD
	pthread_set_name_np(thread.thread, thread.threadName.c_str());
#elif defined(ARX_HAVE_PRCTL) && defined(PR_SET_NAME)
	// Linux
	prctl(PR_SET_NAME, reinterpret_cast<unsigned long>(thread.threadName.c_str()), 0, 0, 0);
#else
	// This is non-fatal, but let's print a warning so future ports will be
	// reminded to implement it.
	#pragma message ( "No function available to set thread names!" )
#endif
	
	CrashHandler::registerThreadCrashHandlers();
	thread.run();
	CrashHandler::unregisterThreadCrashHandlers();
	return NULL;
}

void Thread::exit() {
	pthread_exit(NULL);
}

thread_id_type Thread::getCurrentThreadId() {
	return pthread_self();
}

process_id_type getProcessId() {
	return getpid();
}

#elif defined(ARX_HAVE_WINAPI)

Thread::Thread() {
	thread = CreateThread(NULL, 0, entryPoint, this, CREATE_SUSPENDED, NULL);
	arx_assert(thread);
	setPriority(Normal);
}

void Thread::start() {
	DWORD ret = ResumeThread(thread);
	arx_assert(ret != (DWORD)-1);
	ARX_UNUSED(ret);
}

static const int windowsThreadPriorities[] = {
	THREAD_PRIORITY_LOWEST,
	THREAD_PRIORITY_BELOW_NORMAL,
	THREAD_PRIORITY_NORMAL,
	THREAD_PRIORITY_ABOVE_NORMAL,
	THREAD_PRIORITY_HIGHEST
};

void Thread::setPriority(Priority priority) {
	
	arx_assert(priority >= Lowest && priority <= Highest);
	
	BOOL ret = SetThreadPriority(thread, windowsThreadPriorities[priority - Lowest]);
	arx_assert(ret);
	ARX_UNUSED(ret);
}

Thread::~Thread() {
	CloseHandle(thread);
}

namespace {

void SetCurrentThreadName(const std::string & threadName) {
#if ARX_COMPILER_MSVC
	
	if(threadName.empty() || !IsDebuggerPresent()) {
		return;
	}
	
	typedef struct tagTHREADNAME_INFO {
		DWORD   dwType;         // must be 0x1000
		LPCSTR  szName;         // pointer to name (in user addr space)
		DWORD   dwThreadID;     // thread ID (-1=caller thread)
		DWORD   dwFlags;        // reserved for future use, must be zero
	} THREADNAME_INFO;
	
	THREADNAME_INFO info;
	info.dwType         = 0x1000;
	info.szName         = threadName.c_str();
	info.dwThreadID     = ::GetCurrentThreadId();
	info.dwFlags        = 0;
	
	const DWORD MS_VC_EXCEPTION = 0x406D1388;
	
	__try
	{
			RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(DWORD), (ULONG_PTR *)&info);
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
	}
	
#else
	ARX_UNUSED(threadName);
#endif
}

} // anonymous namespace

DWORD WINAPI Thread::entryPoint(LPVOID param) {
	
	SetCurrentThreadName(((Thread*)param)->threadName);
	
	CrashHandler::registerThreadCrashHandlers();
	((Thread*)param)->run();
	CrashHandler::unregisterThreadCrashHandlers();
	return 0;
}

void Thread::exit() {
	ExitThread(0);
}

void Thread::waitForCompletion() {
	DWORD ret = WaitForSingleObject(thread, INFINITE);
	arx_assert(ret == WAIT_OBJECT_0);
	ARX_UNUSED(ret);
}

thread_id_type Thread::getCurrentThreadId() {
	return GetCurrentThreadId();
}

process_id_type getProcessId() {
	return GetCurrentProcessId();
}

#endif

#if defined(ARX_HAVE_NANOSLEEP)

#include <time.h>

void Thread::sleep(unsigned milliseconds) {
	
	timespec t;
	t.tv_sec = milliseconds / 1000;
	t.tv_nsec = (milliseconds % 1000) * 1000000;
	
	nanosleep(&t, NULL);
}

#elif defined(ARX_HAVE_WINAPI)

void Thread::sleep(unsigned milliseconds) {
	Sleep(milliseconds);
}

#else
#error "Sleep not supported: need either ARX_HAVE_NANOSLEEP or ARX_HAVE_WINAPI"
#endif
