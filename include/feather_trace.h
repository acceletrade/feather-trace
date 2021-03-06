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

#ifndef _FEATHER_TRACE_H_
#define _FEATHER_TRACE_H_


#if defined(__i386)
#include "feather_trace_x86_32.h"
#elif defined(__x86_64)
#include "feather_trace_x86_64.h"
#else
#error Unsupported HW platform.
#endif

/* The Feather-Trace event management functions assume exclusive access to the
 * event table. Any locking must be provided by the caller.
 */

int ft_enable_event(unsigned long id);
int ft_disable_all_events(void);
int ft_disable_event(unsigned long id);
int ft_is_event_enabled(unsigned long id);

int ft_enable_matching_events(unsigned long mask);
int ft_disable_matching_events(unsigned long mask);

#endif
