#include <Spider.h>

int Spider_Connect_server(url_t* u)
{
	int sockfd;
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, u->ip, &serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(u->port);
	if((sockfd= socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("ERROR Create Scoekt:");
		return -1;
	}
	if((connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) == -1)
	{
		perror("ERROR Connet Server:");
		return -1;
	}
	return sockfd;
}
