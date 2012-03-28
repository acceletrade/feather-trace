/* Do not directly include this file. Include feather_trace.h instead */

#define feather_callback __attribute__((regparm(0)))  __attribute__((used))

/*
 * make the compiler reload any register that is not saved in
 * a cdecl function call
 */
#define __FT_CLOBBER_LIST "memory", "cc", "eax", "ecx", "edx"
#define __FT_ARG(x) "r" ((long) (x))

#define ft_event(id, callback)                                  \
        __asm__ __volatile__(                                   \
            "1: jmp 2f                                    \n\t" \
	    " call " #callback "                          \n\t" \
            ".section __event_table, \"aw\"               \n\t" \
            ".long " #id  ", 0, 1b, 2f                    \n\t" \
            ".previous                                    \n\t" \
            "2:                                           \n\t" \
        : : : __FT_CLOBBER_LIST)

#define ft_event0(id, callback)                                 \
        __asm__ __volatile__(                                   \
            "1: jmp 2f                                    \n\t" \
	    " subl $4, %%esp                              \n\t" \
            " movl $" #id  ", (%%esp)                     \n\t" \
	    " call " #callback "                          \n\t" \
	    " addl $4, %%esp                              \n\t" \
            ".section __event_table, \"aw\"               \n\t" \
            ".long " #id  ", 0, 1b, 2f                    \n\t" \
            ".previous                                    \n\t" \
            "2:                                           \n\t" \
        : :  : __FT_CLOBBER_LIST)

#define ft_event1(id, callback, param)                          \
        __asm__ __volatile__(                                   \
            "1: jmp 2f                                    \n\t" \
	    " subl $8, %%esp                              \n\t" \
	    " movl %0, 4(%%esp)                           \n\t" \
            " movl $" #id  ", (%%esp)                     \n\t" \
	    " call " #callback "                          \n\t" \
	    " addl $8, %%esp                              \n\t" \
            ".section __event_table, \"aw\"               \n\t" \
            ".long " #id  ", 0, 1b, 2f                    \n\t" \
            ".previous                                    \n\t" \
            "2:                                           \n\t" \
        : : __FT_ARG(param)  : __FT_CLOBBER_LIST)

#define ft_event2(id, callback, param, param2)                  \
        __asm__ __volatile__(                                   \
            "1: jmp 2f                                    \n\t" \
	    " subl $12, %%esp                             \n\t" \
	    " movl %1, 8(%%esp)                           \n\t" \
	    " movl %0, 4(%%esp)                           \n\t" \
            " movl $" #id  ", (%%esp)                     \n\t" \
	    " call " #callback "                          \n\t" \
	    " addl $12, %%esp                             \n\t" \
            ".section __event_table, \"aw\"               \n\t" \
            ".long " #id  ", 0, 1b, 2f                    \n\t" \
            ".previous                                    \n\t" \
            "2:                                           \n\t" \
        : :  __FT_ARG(param),  __FT_ARG(param2)  : __FT_CLOBBER_LIST)


#define ft_event3(id, callback, p, p2, p3)                      \
        __asm__ __volatile__(                                   \
            "1: jmp 2f                                    \n\t" \
	    " subl $16, %%esp                             \n\t" \
	    " movl %2, 12(%%esp)                          \n\t" \
	    " movl %1, 8(%%esp)                           \n\t" \
	    " movl %0, 4(%%esp)                           \n\t" \
            " movl $" #id  ", (%%esp)                     \n\t" \
	    " call " #callback "                          \n\t" \
	    " addl $16, %%esp                             \n\t" \
            ".section __event_table, \"aw\"               \n\t" \
            ".long " #id  ", 0, 1b, 2f                    \n\t" \
            ".previous                                    \n\t" \
            "2:                                           \n\t" \
        : :  __FT_ARG(p),  __FT_ARG(p2), __FT_ARG(p3)  : __FT_CLOBBER_LIST)

static inline unsigned long long ft_read_tsc(void)
{
	unsigned long long ret;
	__asm__ __volatile__("rdtsc" : "=A" (ret));
	return ret;
}
