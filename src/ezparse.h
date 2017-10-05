#ifndef _EZPARSE_H_
#define _EZPARSE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <glitter.h>

int parseLong (long int *restrict ret, char const str[])
__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result)) ;

#ifdef TEST
int parseLongs (long int ret[], size_t *restrict n, char const str[], size_t len)
__attribute__ ((leaf, nonnull (1, 2, 3), nothrow, warn_unused_result)) ;
#endif

int parseInt (int *restrict ret, char const str[])
__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result)) ;

int parseDouble (double *restrict ret, char const str[])
__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result)) ;

int parseBool (bool *restrict ret, char const str[])
__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _EZPARSE_H_ */