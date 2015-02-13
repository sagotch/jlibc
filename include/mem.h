#include <stdlib.h>
#include <sys/mman.h>

#define JLIBC_MEM_LOAD(pid,load)					\
	do								\
	{								\
		*(pid) = fork () ;					\
		if (*(pid) == 0)					\
		{							\
                        long _PS = sysconf (_SC_PAGE_SIZE) ;            \
                        long _n = (load) / _PS ;                        \
                        if (mlockall (MCL_FUTURE) != 0)                 \
                                exit (-1) ;                             \
                        for (int i = 0 ; i <= _n; i++)                  \
                        {                                               \
                                char * p = mmap (NULL, _PS, PROT_READ,  \
                                                 MAP_ANONYMOUS, -1, 0) ; \
                                if (_p == MAP_FAILED)                   \
                                        exit (-1) ;                     \
                                (*_p) ;                                 \
                        }                                               \
                        pause () ;                                      \
                        exit (0) ;                                      \
                }                                                       \
        }                                                               \
        while (0)
