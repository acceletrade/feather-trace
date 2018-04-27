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

#ifndef _FEATHER_TRACE_EVENTS_H_
#define _FEATHER_TRACE_EVENTS_H_

/* for each event, there is an entry in the event table */
struct trace_event {
	unsigned long	id;
	long		count;
	unsigned long	start_addr;
	unsigned long	end_addr;
};

int ft_is_event_enabled_in_table(unsigned long id,
				 struct trace_event* te, /* start of table */
				 struct trace_event* stop);

int ft_disable_all_events_in_table(struct trace_event* te, /* start of table */
				   struct trace_event* stop);

int ft_disable_event_in_table(unsigned long id,
			      struct trace_event* te, /* start of table */
			      struct trace_event* stop);

int ft_enable_event_in_table(unsigned long id,
			     struct trace_event* te, /* start of table */
			     struct trace_event* stop);

int ft_enable_matching_events_in_table(unsigned long mask,
			     struct trace_event* te, /* start of table */
			     struct trace_event* stop);

int ft_disable_matching_events_in_table(unsigned long mask,
			     struct trace_event* te, /* start of table */
			     struct trace_event* stop);

#endif
