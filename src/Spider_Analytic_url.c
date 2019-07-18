#include <Spider.h>

url_t * Spider_Analytic_url(char* url)
{
	url_t* u =(url_t *)malloc(sizeof(url_t));
	bzero(u,sizeof(url_t));
	strcpy(u->url,url);
	u->port = WEBPORT;
	u->types = TRUE;
	char * arr[]={"http://", "https://", NULL};
	int startlen=0;
	int j=0;
	struct hostent* ent;
	for(int i=0; arr[i]; i++)
	{
		if(strncmp(u->url,arr[i],strlen(arr[i]))==0)
		{
			startlen = strlen(arr[i]);
			break;
		}
		else{
			u->port = HTTPS;
			u->types = FALSE;
			startlen = strlen(arr[i])+1;
			break;
		}
	}
	for(int i=startlen;u->url[i]!='/' && u->url[i]!='\0';i++)
	{
		u->domain[j]=u->url[i];
		j++;
	}
	j=0;
	/*获取资源文件名*/
	for(j = strlen(u->url); u->url[j]!='/'; j--);
		strcpy(u->name,u->url+j+1);
	char * pos=NULL;
	if((pos = strstr(u->domain, ":")) != NULL)
	{
		//将:后的数据转换为int 存放到u->port当中	
		sscanf(pos,":%d",&u->port);
		for(int i=0; i<strlen(u->domain); i++)
			if(u->domain[i]==':')
				u->domain[i]='\0';
	}

	/*通过gethostbyname访问DNS域名解析器或者本地host文件来得到公网IP*/
	if((ent = gethostbyname(u->domain))!=NULL)
	{
		//ent里保存的为大端ip ,通过inet_ntop 进行转换后存储字符串
		inet_ntop(AF_INET,ent->h_addr_list[0],u->ip,16);
	}else
		return NULL;
	/*获取自定义端口例如    www.baidu.com:1024*/
	return u;
}
