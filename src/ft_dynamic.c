/* Copyright (c) 2007-2012 Björn Brandenburg, <bbb@mpi-sws.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define _GNU_SOURCE
#include <link.h>  /* linux only: to iterate over linked objects */
#include <dlfcn.h> /* dlopen(), dlsym(), dlclose() */

#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#include "ft_event.h"
#include "ft_userspace.h"

int init_ft_events_in_table(struct trace_event* start, struct trace_event* stop);

typedef  int (*iterator_fun_id_t)(unsigned long id,
				struct trace_event* start,
				struct trace_event* stop);

typedef  int (*iterator_fun_t)(	struct trace_event* start,
				struct trace_event* stop);

struct iterator_state {
	int count;
	unsigned long id;
	int use_id;
	iterator_fun_t    fun;
	iterator_fun_id_t fun_id;
};

static int  so_iterator(struct dl_phdr_info *info,
			size_t size __attribute__((unused)),
			void *data)
{
	struct iterator_state* state = (struct iterator_state*) data;
	void *handle, *start, *end;

	handle = dlopen(info->dlpi_addr ? info->dlpi_name : NULL, RTLD_LAZY);
	if (handle) {
		start = dlsym(handle, "__start___event_table");
		end   = dlsym(handle, "__stop___event_table");
		if (state->use_id)
			state->count += state->fun_id(state->id, start, end);
		else
			state->count += state->fun(start, end);
		dlclose(handle);
	} else
		printf("Could not open.\n");
	return 0;
}

int for_each_table_id(unsigned long id, iterator_fun_id_t fun)
{
	struct iterator_state state;
	state.count = 0;
	state.id = id;
	state.use_id = 1;
	state.fun_id = fun;
	dl_iterate_phdr(so_iterator, &state);
	return state.count;
}

int for_each_table(iterator_fun_t fun)
{
	struct iterator_state state;
	state.count = 0;
	state.use_id = 0;
	state.fun = fun;
	dl_iterate_phdr(so_iterator, &state);
	return state.count;
}

int ft_enable_event(unsigned long id)
{
	return for_each_table_id(id, ft_enable_event_in_table);
}

int ft_enable_matching_events(unsigned long mask) {
	return for_each_table_id(mask, ft_enable_matching_events_in_table);
}

int ft_disable_all_events(void)
{
	return for_each_table(ft_disable_all_events_in_table);
}

int ft_disable_event(unsigned long id)
{
	return for_each_table_id(id, ft_disable_event_in_table);
}

int ft_disable_matching_events(unsigned long mask) {
	return for_each_table_id(mask, ft_disable_matching_events_in_table);
}

int ft_is_event_enabled(unsigned long id)
{
	return for_each_table_id(id, ft_is_event_enabled_in_table);
}

int init_ft_events(void)
{
	return for_each_table(init_ft_events_in_table);
}
