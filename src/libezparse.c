#if HAVE_CONFIG_H
#include <config.h>
#endif

#define XOPEN_SOURCE 600
#define _BSD_SOURCE
#define _SVID_SOURCE
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

__attribute__ ((leaf, nonnull (1, 2, 3), nothrow, warn_unused_result))
int parseLongs (long int ret[], size_t *n, char const str[], size_t len) {
	char const *restrict startptr = str;
	char *endptr;
	size_t N = *n;

	errno = 0;
	for (*n = 0; *n != N && startptr < str + len; (*n)++) {
		/* no more input */
		if (*startptr == '\0') return -1;
		/* get next long */
		ret[*n] = strtol (startptr, &endptr, 0);
		/* long too small */
		error_check (ret[*n] == LONG_MIN && errno == ERANGE) return -2;
		/* long too big */
		error_check (ret[*n] == LONG_MAX && errno == ERANGE) return -3;
		/* other parsing error */
		error_check (ret[*n] == 0        && errno != 0)      return -4;
		/* no digits at all */
		if (ret[*n] == 0 && endptr == startptr) return -5;
		/* no more input */
		if (*endptr == '\0') return -6;
		TODO (maybe ppl wanna know what delimeters we skipped)
		/* skip invalid char */
		startptr = endptr + 1;
	}

	return 0;
}

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

/*
size_t parseMultiple (void *data, size_t esz,
	char const fmt[], size_t n, char const str[]) {
	size_t i;
	array_t array;
	init_array (&array, data, esz, n);

	for (i = 0; i != n; i++)
		sscanf (str, fmt, index_array (&array, i));
		NEED strtok

	return i;
}
*/
