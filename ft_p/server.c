#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "server.h"



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


/*
** usage
*/

void	usage(char *s)
{
	printf("Usage: %s <port>\n", s);
	exit(EXIT_FAILLURE);
}

int	create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;

	if (!(proto = getprotobyname(PROTOCOLE)))
		return (-1);
	ft_memset(&sin, 0, sizeof(sin));
	sock = socket(PF_INET6, SOCK_STREAM, proto->p_proto);
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
	listen(sock, NB_CONN_SOCKET);
	return (sock);
}

/*
** TCP/IP (v4) server example from 42 school
*/

int	main(int ac, char **av)
{
	int					port;
	int					sock;
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	int					nb_con;

	fd_set				readfds;
	int					ret = 0;


	if (ac != 2)
		usage(av[0]);
	if ((port = atoi(av[1])) <= 0)
		usage(av[0]);
	if ((sock = create_server(port)) < 0)
	 	return (EXIT_FAILLURE);
		printf("%s\n", "yo");


	while (42)
	{
		FD_ZERO(&readfds);
		FD_SET(sock, &readfds);
		ret = select(1, &readfds, &readfds, NULL, NULL);
		printf("%s\n", "conection");

	}



	while (42)
	{
		ft_memset(&csin, 0, sizeof(csin));
		ft_memset(&cslen, 0, sizeof(cslen));
		if ((cs = accept(sock, (struct sockaddr *)&csin, &cslen)) == -1)
		{
			ft_putstr_fd(MESS_LIMIT_NB_CON_REACHED, STDERR);
			continue ;
		}
		printf("%s\n", "connect");
		// new_process(cs);
	}
	close(cs);
	close(sock);
	return (EXIT_SUCCESS);
}
