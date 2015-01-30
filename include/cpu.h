/** FIXME:
 * Sleep less than 1s in order to have more constant load
 * and faster balancing. */

#ifndef JLIBC_CPU_H
#define JLIBC_CPU_H 1

#include <unistd.h>
#include <sys/times.h>

/**
 * Create a child process which will load cpu with dummy operations.
 * May take several second to reach the cpu load aimed.
 * @param pid receives process id of the child loading cpu (int *)
 * @param load percentage of cpu load aimed (float)
 */
#define JLIBC_CPU_LOAD(pid,load)					\
	do								\
	{								\
		*(pid) = fork () ;					\
		if (*(pid) == 0)					\
		{							\
			float _lc = 100000000 ;				\
			float _tck = sysconf (_SC_CLK_TCK) ;		\
			float _usg ;					\
			struct tms _t0, _t1 ;				\
			clock_t _c0, _c1 ;				\
			while (1)					\
			{						\
				_c0 = times (&_t0) ;			\
				for (int __i = 0; __i < _lc; __i++) ;	\
				sleep (1) ;				\
				_c1 = times (&_t1) ;			\
				if (_c1 == _c0) continue ;		\
				_usg = _tck *				\
					(_t1.tms_utime - _t0.tms_utime) \
					/ (_c1 - _c0) ;			\
				if (_usg == 0) continue ;		\
				_lc *= ((load) / _usg) ;		\
			}						\
		}							\
	}								\
	while (0)

#endif  // #ifndef JLIBC_CPU_H

#ifdef JLIBC_CPU_NO_PREFIX
#define CPU_LOAD JLIBC_CPU_LOAD
#endif
