#include <errno.h>
#include <limits.h>
#include <stdlib.h>

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
