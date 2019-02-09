#ifdef __cplusplus
extern "C" {
#endif

#ifndef SETJMP_H
#define SETJMP_H

typedef void* jmp_buf;

int setjmp(jmp_buf environment);
void longjmp(jmp_buf environment, int value);

#endif

#ifdef __cplusplus
}
#endif
