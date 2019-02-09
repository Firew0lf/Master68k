#ifdef __cplusplus
extern "C" {
#endif

#ifndef ASSERT_H
#define ASSERT_H

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(ignore) ((void)0) // TODO debugger
#endif

#endif

#ifdef __cplusplus
}
#endif
