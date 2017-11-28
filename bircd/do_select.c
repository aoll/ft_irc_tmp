
#include <stdlib.h>
#include "bircd.h"
#include <stdio.h>

void	do_select(t_env *e)
{
	printf("e->max : %d\n", e->max );
  e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}
