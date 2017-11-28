/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:58:04 by alex              #+#    #+#             */
/*   Updated: 2017/11/27 23:56:16 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	clean_fd(t_fd *fd)
{
	fd->type = FD_FREE;
	fd->fct_read = NULL;
	fd->fct_write = NULL;
}

void	client_read(t_env *e, int cs)
{
  int	r;
  int	i;

printf("%s\n", "READ");
  r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
  if (r <= 0)
    {
      close(cs);
      clean_fd(&e->fds[cs]);
      printf("client #%d gone away\n", cs);
    }
  else
    {
		printf("read: %d, %s\n",r, e->fds[cs].buf_read);
      i = 0;
      while (i < e->maxfd)
	{
	  if ((e->fds[i].type == FD_CLIENT) &&
	      (i != cs))
	    send(i, e->fds[cs].buf_read, r, 0);
	  i++;
	}
    }
}

void			srv_accept(t_env *e, int s)
{
	int			cs;
	struct sockaddr_in	csin;
	socklen_t		csin_len;

	printf("CS ::::: %d\n", s);
	csin_len = sizeof(csin);
	if ((cs = accept(s, (struct sockaddr*)&csin, &csin_len)) == -1)
	{
		printf("%s\n", "ERROR ACCEPT");
		exit (1);
	}


	printf("New client #%d from %s:%d\n", cs,
	 inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs]);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	// e->fds[cs].fct_write = client_write;
}

// int	create_server(t_env *e, int port)
// {
// 	int					sock;
// 	struct protoent		*proto;
// 	struct sockaddr_in6	sin;
//
// 	if (!(proto = getprotobyname(PROTOCOLE)))
// 		return (-1);
// 	ft_memset(&sin, 0, sizeof(sin));
// 	if ((sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto)) == -1)
// 	{
// 		printf("%s\n", "ERROR SOCKET");
// 		exit (EXIT_FAILURE);
// 	}
// 	sin.sin6_family = AF_INET6;
// 	sin.sin6_port = htons(port);
// 	sin.sin6_addr = in6addr_any;
// 	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
// 	printf("SOCK: %d\n", sock);
// 	listen(sock, 3);
// 	e->fds[s].type = FD_SERV;
//     e->fds[s].fct_read = srv_accept;
// 	printf("%s\n", "SOCK OK");
// 	return (sock);
// }

int			create_server(t_env *e, int port)
{
  int			s;
  struct sockaddr_in	sin;
  struct protoent	*pe;

  pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");
  s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);
  X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind");
  X(-1, listen(s, e->maxfd), "listen");
  e->fds[s].type = FD_SERV;
  e->fds[s].fct_read = srv_accept;
  return (s);
}

int		init_env_fd(t_env *e)
{
	int		i;
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp))
		return (EXIT_FAILURE);
	e->maxfd = rlp.rlim_cur;
	printf("limit %d\n", rlp.rlim_cur);
	if (!(e->fds = malloc(sizeof(*e->fds) * e->maxfd)))
		return (EXIT_FAILURE);
	i = 0;
	while (++i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
	printf("%s\n", "ENV INIT OK");
	return (EXIT_SUCCESS);
}

int	get_socket_server(t_env *e, const char *port_s)
{
	int	sock;
	int	port;

	if ((port = atoi(port_s) <= 0))
	{
		printf("%s\n", "ERROR: need a port and only a port");
		return (-1);
	}
	if ((sock = create_server(e, port)) < 0)
	{
		printf("%s\n", "ERROR: error interne during creation socket");
		return (-1);
	}
	printf("%s\n", "SUCCESS");
	return (sock);
}

int	server(t_env *e, const char *port)
{
	int sock;

	printf("%s\n", "print a");
	if (init_env_fd(e))
		return (EXIT_FAILURE);
		printf("%s\n", "print b");
	if ((sock = get_socket_server(e, port)) == -1)
	{
		free(e->fds);
		return (EXIT_FAILURE);
	}
	printf("%s\n", "print c");
	e->fds[sock].type = FD_MASTER;
	printf("%s\n", "print d");
	e->fds[sock].fct_read = srv_accept;

	printf("%s\n", "print e");
	printf("SOCK: %d\n", sock);
	return (EXIT_SUCCESS);
}
