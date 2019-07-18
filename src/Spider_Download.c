#include <Spider.h>



int Spider_Download(int filefd,char * title,char * description)
{
	char t[1024];
	char p[4096];
	bzero(t,sizeof(t));
	bzero(p,sizeof(p));
	sprintf(t,"<h6>%s</h6>\r\n",title);
	sprintf(p,"<p>%s</p>\r\n",description);
	write(filefd,t,strlen(t));
	write(filefd,p,strlen(p));
	return 0;
}
