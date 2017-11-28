#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

// int
// main(int argc, char *argv[])
// {
//   struct in_addr addr;
//
//   if (argc != 2) {
//     fprintf(stderr, "%s <dotted-address>\n", argv[0]);
//     exit(EXIT_FAILURE);
//   }
//
//   if (inet_aton(argv[1], &addr) == 0) {
//     fprintf(stderr, "Invalid address\n");
//     exit(EXIT_FAILURE);
//   }
//
//   printf("%s\n", inet_ntoa(addr));
//   exit(EXIT_SUCCESS);
// }

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{

	struct addrinfo* feed_server = NULL;

   struct addrinfo hints;
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;
   printf("ret : %d\n", getaddrinfo("127.0.0.1", "4242", &hints, &feed_server));
   // getaddrinfo("localhost", "4243", &hints, &feed_server);
   struct addrinfo *res;
   for(res = feed_server; res != NULL; res = res->ai_next){
      struct sockaddr_in* saddr = (struct sockaddr_in*)res->ai_addr;
      printf("hostname: %s  ", inet_ntoa(saddr->sin_addr));
      printf("ai_family: %d\n", res->ai_family);
   }
   return 0;
}
