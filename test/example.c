#include <stdio.h>

#include "ft_userspace.h"
#include "gcc-helper.h"

feather_callback void event(int id, char* msg)
{
	printf("Event %d, msg=%s.\n", id, msg);
}

int main(unused(int argc), char** argv)
{
	ft_event1(99, event, "default: event disabled");

	ft_enable_event(25);
        ft_enable_event(99);

	ft_event1(25, event, argv[0]);

	ft_event1(99, event, "now the event is enabled");

	ft_disable_event(99);

	ft_event1(99, event, "disabled again");

	printf("good bye\n");

	return 0;
}
