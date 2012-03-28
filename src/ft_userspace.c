#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include "feather_buffer.h"
#include "ft_event.h"
#include "ft_userspace.h"

struct ft_buffer* alloc_ft_buffer(unsigned int slots,
				  unsigned int size)
{
	void *mem;
	struct ft_buffer* buf;
	mem = malloc(sizeof(struct ft_buffer) +
		     sizeof(char) * slots +
		     size * slots);
	if (!mem)
		return NULL;
	buf = (struct ft_buffer*) mem;
	if (init_ft_buffer(buf, slots, size,
			    (char*) (mem + sizeof(struct ft_buffer)),
			    mem + sizeof(struct ft_buffer) +
			    sizeof(char) * slots)) {
		return buf;
	} else {
		free(mem);
		return NULL;
	}
}

int init_ft_events_in_table(struct trace_event* start, struct trace_event* stop){
	struct trace_event* te = start;
	int ret;
	unsigned long addr;
	unsigned long pagemask;

	pagemask = getpagesize();
	pagemask = ~(pagemask - 1);

	while (te < stop) {
		addr = te->start_addr & pagemask;
		ret  = mprotect((void*) addr, te->end_addr - addr,
			       PROT_READ | PROT_WRITE | PROT_EXEC);
		te++;
		if (ret) {
			perror("feather trace (mprotect)");
		}

	}
	addr = (unsigned long) start & pagemask;
	ret  = mprotect((void*) addr, ((long) stop) - addr,
			PROT_READ | PROT_WRITE | PROT_EXEC);
	return ret == 0;
}

static  __attribute__((constructor))
void ft_feather_trace_init(void)
{
	if (!init_ft_events()) {
		perror("could not init ft events");
		exit(100);
	}
}
