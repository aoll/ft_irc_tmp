/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 03:54:07 by alex              #+#    #+#             */
/*   Updated: 2017/11/27 17:43:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>



int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s [port]\n", *av);
		exit(1);
	}
	process(av[1]);
	return (0);



	fd_set rfds;
	struct timeval tv;
	int retval;
	char buf[MAX_LEN_CMD];
	char buf2[MAX_LEN_CMD];
	int rd;
	t_buf *buf_e;

	buf_e = ft_buf_new(MAX_LEN_CMD);
	/* Watch stdin (fd 0) to see when it has input. */
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);
	while (42)
	{
		ft_bzero(buf, MAX_LEN_CMD);
		retval = select(1, &rfds, NULL, NULL, NULL);
		if (retval)
		{
			rd = read(0, buf, MAX_LEN_CMD);
			printf("read: %d - buf: %s\n", rd, buf);
			if (rd > 0)
			{
				if (ft_buf_add_data(buf_e, buf, rd))
				{
					buf_e->start_data = buf_e->end_data;
					printf("%s\n", "ERROR: cmd to big");
				}
				else
				{
					ft_bzero(buf2, MAX_LEN_CMD);
					if (buf[rd - 1] == 10)
					{
						ft_buf_get_data(
							buf2, buf_e, buf_e->start_data == buf_e->end_data);
						printf("buf2 : %s\n", buf2);
					}
					else
					{
						if (buf_e->start_data == buf_e->end_data)
							printf("%s\n", "ERROR: cmd to big");
					}
				}
			}
		}
	}
	exit(EXIT_SUCCESS);
}


// int	main(int argc, char const *argv[])
// {
// 	t_buf *buf_e;
// 	char *s = ft_strnew(MAX_LEN_CMD);
//
// 	ft_bzero(s, MAX_LEN_CMD);
// 	if (!(buf_e = ft_buf_new(MAX_LEN_CMD)))
// 	{
// 		printf("%s\n", "ERROR: malloc()");
// 		return (EXIT_FAILURE);
// 	}
// 	printf("ret: %d\n", ft_buf_add_data(buf_e, argv[1], ft_strlen(argv[1])));
// 	printf("%s\n", "--------------------");
// 	ft_buf_get_data(s, buf_e, buf_e->start_data == buf_e->end_data);
// 	printf("s: %s\n", s);
// 	// printf("ret: %d\n", ft_buf_add_data(buf_e, argv[1], ft_strlen(argv[1])));
// 	return (EXIT_SUCCESS);
// }
