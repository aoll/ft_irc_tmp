/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:42:38 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/27 23:10:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H
# define FT_IRC_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <strings.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/select.h>
# include "libft.h"

# define BUF_SIZE				4096

# define NB_CONN_SOCKET			3
# define FD_MASTER				1
# define FD_CLIENT				2
# define FD_FREE				0

# define FD_SERV	1

# define MAX_LEN_CMD 			42
# define MAX_LEN_CHANEL_NAME	9
# define MAX_LEN_LOGIN_NAME 	9

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)

typedef struct	s_buf
{
	size_t		size;
	char		*start_buf;
	char		*end_buf;
	char		*start_data;
	char		*end_data;
}	t_buf;

typedef struct	s_chanel
{
	char			*name;
	int				*fds;
	int				fdsize;
}	t_chanel;

typedef struct	s_chanels
{
	int			nb_chanel;
	int			nb_chanel_active;
	t_chanel	*l_chanel;
}	t_chanels;

typedef struct	s_fd
{
	int			type;
	void		(*fct_read)();
	void		(*fct_write)();
	char		name[MAX_LEN_LOGIN_NAME];
	// t_buf		*buf_write;
	// t_buf		*buf_read;
	char	buf_read[BUF_SIZE + 1];
	char	buf_write[BUF_SIZE + 1];
}	t_fd;

typedef struct	s_env
{
	t_fd		*fds;
	t_chanels	*cha;
	int			port;
	int			maxfd;
	int			max;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;

}	t_env;

//tool
int	x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);

//process
int			process(const char *port);

//server socket
void			srv_accept(t_env *e, int s);
# define PROTOCOLE	"tcp"
int			create_server(t_env *e, int port);
int			server(t_env *e, const char *port);

//chanel
void		test_cha(void);

//buffer_circulaire
t_buf		*ft_buf_new(size_t size);
void		ft_buf_get_data(char *dest, t_buf *buf_e, int full);
int			ft_buf_add_data(t_buf *buf_e, const char *s, size_t size);

#endif
