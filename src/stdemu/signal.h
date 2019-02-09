#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIGNAL_H
#define SIGNAL_H

// should be atomic; we're dealing with only 1 thread anyway
typedef int sig_atomic_t;

#define SIG_DFL	NULL
#define SIG_ERR	NULL
#define SIG_IGN	NULL

#define SIGABRT	1
#define SIGFPE	2
#define SIGILL	3
#define SIGINT	4
#define SIGSEGV	5
#define SIGTERM	6

void (*signal(int sig, void(*func)(int)))(int);
int raise(int sig);

#endif

#ifdef __cplusplus
}
#endif
