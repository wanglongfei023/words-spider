#include <Spider.h>

char* Spider_Create_cache(const char * name)
{
	int fd, size;
	char* p = NULL;
	if((fd = open(name, O_RDONLY)) == -1)
		return p;
	size = lseek(fd, 0, SEEK_END);
	p = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	return p;
}
