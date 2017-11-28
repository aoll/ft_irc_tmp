/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 17:44:03 by alex              #+#    #+#             */
/*   Updated: 2017/11/28 00:29:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	init_fd(t_env *e)
{
  int	i;

  i = 0;
  e->max = 0;
  FD_ZERO(&e->fd_read);
  FD_ZERO(&e->fd_write);

  while (i < e->maxfd)
    {
	      if (e->fds[i].type != FD_FREE)
		{
		  FD_SET(i, &e->fd_read);
		//   printf("I its i: %d\n", i);
		  if (strlen(e->fds[i].buf_write) > 0)
		    {
		      FD_SET(i, &e->fd_write);
		    }
		  e->max = MAX(e->max, i);
		}
      i++;
    }
}

void	do_select(t_env *e)
{

  // e->r = select(42, &e->fd_read, &e->fd_write, NULL, NULL);
  printf("e->max: %d\n", e->max);
  e->r = select(1, &e->fd_read, &e->fd_write, NULL, NULL);
	printf("RRRRRRRRRRRRRRRR%d\n", e->r);
}

void	check_fd(t_env *e)
{
  int	i;

  i = 0;
  printf("e->r: %d\n", e->r);
  while ((i < e->maxfd) && (e->r > 0))
    {
      if (FD_ISSET(i, &e->fd_read))
	e->fds[i].fct_read(e, i);
      if (FD_ISSET(i, &e->fd_write))
	e->fds[i].fct_write(e, i);
      if (FD_ISSET(i, &e->fd_read) ||
	  FD_ISSET(i, &e->fd_write))
	e->r--;
      i++;
    }
}

void	main_loop(t_env *e)
{
	while (1)
	{
		// printf("%s\n", "print 1");
		init_fd(e);
		// printf("%s\n", "print 2");
		do_select(e);
		// printf("%s\n", "print 3");
		check_fd(e);
		// printf("%s\n", "print 4");
	}
}

int	process(const char *port)
{
	t_env	e;

	printf("%s\n", "process");
	if (server(&e, port))
	{
		printf("%s\n", "ERROR INIT SERVER");
		exit(EXIT_FAILURE);
	}
	main_loop(&e);
	return (EXIT_SUCCESS);
}
