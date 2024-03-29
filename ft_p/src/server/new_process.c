/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:26:25 by alex              #+#    #+#             */
/*   Updated: 2017/11/27 02:05:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	switch_requet_cmp(t_cs *cs, char *requet, char **split, int ret)
{
	if (!ft_strncmp(requet, REQUET_QUIT, ft_strlen(REQUET_QUIT)))
		ret = quit_requet(cs);
	else if (!ft_strncmp(requet, REQUET_CD, ft_strlen(REQUET_CD)))
		ret =  cd_requet(cs, split);
	else if (!ft_strncmp(requet, REQUET_PWD, ft_strlen(REQUET_PWD)))
		ret =  pwd_requet(cs, split);
	else if (!ft_strncmp(requet, REQUET_LS, ft_strlen(REQUET_LS)))
		ret =  cmd_requet(cs, split);
	else if (!ft_strncmp(requet, REQUET_GET, ft_strlen(REQUET_GET)))
		ret =  get_requet_server(cs, split);
	else if (!ft_strncmp(requet, REQUET_PUT, ft_strlen(REQUET_PUT)))
		ret =  put_requet(cs, split, requet);
	return (ret);
}

static int	switch_requet(t_cs *cs, char *requet)
{
	int			ret;
	char		**split;

	ret = MAGIC_NUMER;
	if (!(split = ft_strsplit(requet, ' ')))
	{
		if ((ret = send_requet(
			cs->fd, R_ERROR, ft_strlen(INTERN_ERROR), INTERN_ERROR)))
			return (ret);
		return (EXIT_FAILLURE);
	}
	ret = switch_requet_cmp(cs, requet, split, ret);
	ft_array_free(&split);
	if (ret == MAGIC_NUMER)
	{
		if ((ret = send_requet(
			cs->fd, R_ERROR, ft_strlen(UNKNOW_CMD), UNKNOW_CMD)))
			return (ret);
		return (EXIT_SUCCESS);
	}
	return (ret);
}

static int	read_requet(t_cs *cs, void *buf, int read)
{
	t_header *header;

	header = (t_header *)buf;
	if (header->requet != R_CMD
		|| !header->size || (header->size + sizeof(header)) != read)
	{
		if (send_requet(cs->fd, R_ERROR,
			ft_strlen(NEED_COMMAND_VALID), NEED_COMMAND_VALID) == C_LOST)
			return (C_LOST);
		return (EXIT_SUCCESS);
	}
	return (switch_requet(cs, (void *)header + sizeof(header)));
}

static int	read_socket(int fd)
{
	t_cs	cs;
	char	buf[RECV_SIZE + 1];
	int	read;
	int		ret;

	if (init_cs(&cs, fd))
		return (EXIT_FAILLURE);
	ft_bzero(buf, RECV_SIZE);
	buf[RECV_SIZE] = '\0';
	ret = 0;
	while ((read = recv(fd, &buf, RECV_SIZE, 0)) > 0)
	{
		printf("read: %d, buf: %s, value: %d\n", read, buf, *buf);
		// if (read >= (int)SIZE_HEADER)
		// {
			// if ((ret = read_requet(&cs, &buf, read)))
			// 	if (ret == QUIT || ret == C_LOST)
			// 		break ;
		// }
		ft_bzero(buf, RECV_SIZE);
	}
	printf("%s\n", "connection close");
	free_cs(&cs);
	return (ret);
}

int			new_process(int fd)
{
	pid_t	pid;
	int		ret;

	printf("%s\n", "new process");
	if ((pid = fork()) == -1)
		return (EXIT_FAILLURE);
	if (!pid)
	{
		ret = read_socket(fd);
		close(fd);
	}
	return (EXIT_SUCCESS);
}
