#include <Spider.h>

int Spider_Request(url_t* u, int webfd, ssl_t* ssl)
{
	char head[4096];
	bzero(head,4096);
	sprintf(head,"GET %s HTTP/1.1\r\n"\
			"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,;q=0.8\r\n"\
			"Accept-language: zh-cn\r\n"\
			"User-Agent: Mozilla/5.0 (compatible;Windows NT 6.1; WOW64;Trident/6.0;MSIE 9.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/33.0.1750.27 Safari/537.36\r\n"\
			"Host: %s\r\n"\
			"Connection: close\r\n\r\n", u->url, u->domain);
	if(ssl){
		if((SSL_write(ssl->socket, head, strlen(head))) == -1)
		{
			return -1;
		}else{
			return 0;
		}
	}else{
		if((send(webfd, head, strlen(head), 0)) == -1)
		{
			return -1;
		}else{
			return 0;
		}
	}
}
