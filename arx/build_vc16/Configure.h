
#ifndef ARX_CONFIGURE_H
#define ARX_CONFIGURE_H

#define ARX_HAVE_WINAPI

// Threads
/* #undef ARX_HAVE_PTHREADS */
/* #undef ARX_HAVE_PRCTL */
/* #undef ARX_HAVE_PTHREAD_SETNAME_NP */
/* #undef ARX_HAVE_PTHREAD_SET_NAME_NP */

// Audio backend
#define ARX_HAVE_OPENAL
#define ARX_HAVE_OPENAL_EFX
#define ARX_HAVE_DSOUND

// Renderer backend
#define ARX_HAVE_OPENGL
#define ARX_HAVE_D3D9

// Input backend
#define ARX_HAVE_SDL
#define ARX_HAVE_DINPUT8

// Crash handler
/* #undef ARX_HAVE_CRASHHANDLER_POSIX */
/* #undef ARX_HAVE_CRASHHANDLER_WINDOWS */

// POSIX / Linux features
/* #undef ARX_HAVE_NANOSLEEP */
/* #undef ARX_HAVE_CLOCK_GETTIME */
/* #undef ARX_HAVE_FORK */
/* #undef ARX_HAVE_READLINK */
/* #undef ARX_HAVE_DUP2 */
/* #undef ARX_HAVE_EXECL */
/* #undef ARX_HAVE_EXECLP */
/* #undef ARX_HAVE_WAITPID */
/* #undef ARX_HAVE_BACKTRACE */
/* #undef ARX_HAVE_ISATTY */
/* #undef ARX_HAVE_WORDEXP_H */
/* #undef ARX_HAVE_FPATHCONF */
/* #undef ARX_HAVE_PATHCONF */
/* #undef ARX_HAVE_PC_NAME_MAX */
/* #undef ARX_HAVE_PC_CASE_SENSITIVE */
/* #undef ARX_HAVE_NAME_MAX */
/* #undef ARX_HAVE_SCHED_GETSCHEDULER */
/* #undef ARX_HAVE_UNAME */
/* #undef ARX_HAVE_GETRUSAGE */
/* #undef ARX_HAVE_POPEN */
/* #undef ARX_HAVE_PCLOSE */
/* #undef ARX_HAVE_SYSCONF */
/* #undef ARX_HAVE_SIGACTION */
/* #undef ARX_HAVE_DIRFD */
/* #undef ARX_HAVE_FSTATAT */
/* #undef ARX_HAVE_GETCWD */
/* #undef ARX_HAVE_GETEXECNAME */
/* #undef ARX_HAVE_SYSCTL */
/* #undef ARX_HAVE_SETENV */

// Mac OS X features
/* #undef ARX_HAVE_MACH_CLOCK */

// Arx components
/* #undef BUILD_EDITOR */
#define BUILD_EDIT_LOADSAVE

// Build system
#define UNITY_BUILD

#endif // ARX_CONFIGURE_H
