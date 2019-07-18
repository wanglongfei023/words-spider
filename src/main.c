#include <Spider.h>
#include <pthread.h>

#define THREAD_NUM 3
#define SLEEP_TIME 3

url_t* u_info;
int webfd;
ssl_t* ssl = NULL;
char url[MAX_URL][LEN_URL];
int record[MAX_URL];
pthread_mutex_t lock;

void TimeFunc(int sig)
{
	Spider_Request(u_info, webfd, ssl);
	printf("retry to send the request....\n");
	signal(SIGALRM,TimeFunc);
	alarm(INTERVAL);
}

void* SpiderWork(void* data)
{
	for(int i = START; i < MAX_URL; i++)
	{
		pthread_mutex_lock(&lock);
		if(record[i] == 1)
		{
			pthread_mutex_unlock(&lock);
			continue;
		}else{
			record[i] = 1;
			pthread_mutex_unlock(&lock);
		}

		printf("[tid:%lu]  [url:%s]\n", pthread_self(), url[i]);
		if((u_info = Spider_Analytic_url(url[i])) == NULL)
		{
			printf("[1]URL Analyize failed!\n");
			return (void*)-1;
		}else{
			printf("[1]URL Analyize success!\n");
		}

		ssl_t* ssl = u_info->types == 1 ? NULL : Spider_Openssl_Create(webfd);

		if((webfd = Spider_Connect_server(u_info)) <= 0)
		{
			printf("[2]Connect server failed!\n");
			return (void*)-1;
		}else{
			printf("[2]Connect server success!\n");
		}

		if((Spider_Request(u_info, webfd, ssl)) == -1)
		{
			printf("[3]Request success!\n");
		}else{
			printf("[3]Request success!\n");
		}

		signal(SIGALRM, TimeFunc);
		alarm(SLEEP_TIME);
		if((Spider_Response(webfd, ssl)) == -1)
		{
			printf("[4]Page:%d,Get response failed!\n", i+1);
			i--;
			record[i] = 0;
			continue;
		}else{
			printf("[4]Get response success!\n");
		}
		alarm(0);

		char* src = Spider_Create_cache("../result/temp.txt");
		if(i == START) 
			printf("[5]Mmap success!\n");

		if(Spider_Analytic_html(src) == -1)
		{
			printf("retry to request the number %d page!\n\n",i+1);
			i--;
			record[i] = 0;
		}else{
			printf("the number %d page analyize success!\n\n",i+1);
		}
		sleep(1);
	}
	return 0;
}

int main(void)
{
	bzero(url, sizeof(url));
	pthread_mutex_init(&lock, NULL);
	pthread_t threads[10];

	for(int i = 0;i < MAX_URL;i++)
	{
		sprintf(url[i], "http://www.youdict.com/ciku/id_0_0_0_0_%d.html", i);
		record[i] = 0;
	}

	for(int i = 0; i < THREAD_NUM; i++)
	{
		pthread_create(&threads[i], NULL, SpiderWork, NULL);
	}

	for(int i = 0; i < THREAD_NUM; i++)
	{
		pthread_join(threads[i], NULL);
	}

	if(ssl)
	{
		free(ssl);
		close(webfd);
		ssl = NULL;
	}
	return 0;
}
