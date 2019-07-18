#include <Spider.h>

int Spider_Response(int webfd, ssl_t* ssl)
{
	char buf[8192];
	int len, fd;
	bzero(buf,sizeof(buf));

	if((fd = open("../result/temp.txt", O_RDWR | O_CREAT, 0775)) == -1)
		return -1;

	if(ssl)
	{
		while((len = SSL_read(ssl->socket, buf, sizeof(buf) - 1)) > 0)
		{
			write(fd, buf, len);
			bzero(buf, sizeof(buf));
		}
	}else{
		while((len = recv(webfd, buf, sizeof(buf) - 1, 0)) > 0)
		{
			write(fd, buf, len);
			bzero(buf, sizeof(buf));
		}
	}
	return 0;
}
