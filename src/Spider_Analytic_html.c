#include <Spider.h>

int IsNumber(char c)
{
	if(c >= '0' && c <= '9')
		return 1;
	return 0;
}

int IsLetter(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	return 0;
}

int Spider_Analytic_html(char* src)
{
	if(src == NULL)
		return -1;
	char word[64];
	char mean[255];
	char* pWord = src;
	char* pMean = src;
	char* pText = (char*)malloc(sizeof(char)*8192);
	memset(pText,0,sizeof(char)*8192);
	int i;
	int flag = 0;
	int fd = open("../result/words.txt",O_RDWR | O_CREAT | O_APPEND, 0775);
	while(1)
	{	
		memset(word,0,sizeof(word));
		memset(mean,0,sizeof(mean));
		if((pWord = strstr(pWord,".jpg\" alt=\"")) == NULL) break;
		if((pMean = strstr(pMean,"<p>")) == NULL) break;
		pWord += 11;
		pMean += 3;

		//截取单词
		i = 0;
		while(*pWord != '\"')
		{
			word[i++] = *pWord++;
		}
		
		//截取释义
		i = 0;
		while(*pMean != '<')
		{
			if(*pMean == '\n')
			{
				if(IsNumber(*(pMean+1)) || IsNumber(*(pMean+2)))
				{
					flag = 1;
					break;
				}
				pMean++;
				continue;
			}

			mean[i++] = *pMean++;
			if(i > 254)
			{
				break;
			}
		}

		if(flag == 1)
			break;

		if(strlen(mean) < 2)
			continue;

		strcat(pText,word);
		strcat(pText,"\t");
		strcat(pText,mean);
		strcat(pText,"\n");

	}

	printf("%s\n",pText);
	if(flag == 0)
	{
		write(fd,pText,strlen(pText));
		close(fd);
		free(pText);
		pText = NULL;
	}else{
		free(pText);
		pText = NULL;
		return -1;
	}

	munmap(src,strlen(src));
	return 0;
}
