#if HAVE_CONFIG_H
#include <config.h>
#endif

#define XOPEN_SOURCE 600
/*#define _BSD_SOURCE
#define _SVID_SOURCE*/
#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#include <math.h>

#include <ezparse.h>

__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result))
int parseLong (long int *restrict ret, char const str[]) {
	char *endptr;
	long int tmp;
	errno = 0;
	tmp = strtol (str, &endptr, 0);
	error_check (tmp == LONG_MIN && errno == ERANGE) return -2;
	error_check (tmp == LONG_MAX && errno == ERANGE) return -3;
	error_check (tmp == 0        && errno != 0)      return -4;
	/*error_check (endptr != NULL) return -1;*/
	error_check (endptr == str)   return -5;
	*ret = tmp;
	error_check (*endptr != '\0') return -6;
	return 0;
}

#ifdef TEST
__attribute__ ((leaf, nonnull (1, 2, 3), nothrow, warn_unused_result))
int parseLongs (long int ret[], size_t *restrict n, char const str[], size_t len) {
	char const *restrict startptr = str;
	char *endptr;
	size_t N = *n;

	errno = 0;
	for (*n = 0; *n != N && startptr < str + len; (*n)++) {
		/* no more input */
		error_check (*startptr == '\0') return -1;
		/* get next long */
		ret[*n] = strtol (startptr, &endptr, 0);
		/* long too small */
		error_check (ret[*n] == LONG_MIN && errno == ERANGE) return -2;
		/* long too big */
		error_check (ret[*n] == LONG_MAX && errno == ERANGE) return -3;
		/* other parsing error */
		error_check (ret[*n] == 0        && errno != 0)      return -4;
		/* no digits at all */
		error_check (ret[*n] == 0 && endptr == startptr) return -5;
		/* no more input */
		error_check (*endptr == '\0' && *n != N - 1) return -6;
		TODO (maybe ppl wanna know what delimeters we skipped)
		/* skip invalid char */
		startptr = endptr + 1;
	}

	return 0;
}
#endif

__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result))
int parseInt (int *restrict ret, char const str[]) {
	long int tmp;
	error_check (parseLong (&tmp, str) != 0) return -1;
	error_check (tmp < INT_MIN) return -2;
	error_check (tmp > INT_MAX) return -3;
	*ret = (int) tmp;
	return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result))
int parseDouble (double *restrict ret, char const str[]) {
	char *endptr;
	errno = 0;
	*ret = strtod (str, &endptr);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wfloat-equal"
	TODO (is float-equal acceptable here?)
	error_check (*ret == HUGE_VAL && errno == ERANGE) return -2;
	error_check (*ret == HUGE_VAL && errno == ERANGE) return -3;
	error_check (*ret == 0        && errno != 0)      return -4;
	#pragma GCC diagnostic pop
	/*error_check (endptr != NULL) return -1;*/
	error_check (endptr == str)   return -5;
	error_check (*endptr != '\0') return -6;
	return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result))
int parseBool (bool *restrict ret, char const str[]) {
	int tmp;
	error_check (parseInt (&tmp, str) != 0) return -1;
	*ret = !! tmp;
	return 0;
}

#ifdef TEST
typedef __attribute__ ((nonnull (1, 2, 3), warn_unused_result))
int (*str_to_any_t) (void *restrict dest,
	char const str[], char const **restrict endptr) ;

__attribute__ ((leaf, nonnull (1, 3, 4, 5, 6), nothrow, warn_unused_result))
int parseMultiple (void *restrict restrict data, size_t esz,
	size_t *restrict n,
	str_to_any_t str_to_any, char const str[],
	char const **restrict endptr) {
	char const *restrict startptr = str;
	size_t i;
	for (i = 0; i != *n; i++) {
		error_check (startptr == str + len) return -1;
		error_check (*startptr == '\0') return -2;
		error_check (str_to_any (dest, startptr, endptr) != 0) return -3;
		error_check (startptr == *endptr) return -4;
		startptr = *endptr;
		dest += esz;
	}
	*n = i;
	return 0;
}
#endif
