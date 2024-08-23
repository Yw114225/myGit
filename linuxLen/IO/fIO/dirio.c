#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    struct stat* statbuf = NULL;
    int retstat = stat("fileio.txt", statbuf);
    if(!retstat){
	perror("stat");
	return -1
    }
    if(statbuf->st_mode == S_ISREG)
	printf("-"); 
    else if(statbuf->st_mode == S_ISDIR)
	printf("d");
    else if(statbuf->st_mode == S_ISCHR)
	printf("c");
    else if(statbuf->st_mode == S_ISBLK)
	printf("b");
    else if(statbuf->st_mode == S_ISFIFO)
	printf("p");
    else if(statbuf->st_mode == S_ISLNK)
	printf("l");
    else if(statbuf->st_mode == S_ISSOCK)
	printf("s");
    for(int i = 8; i >= 0; --i){
	if(statbuf->st_mode && (1<<i))
	    switch{
		case 2:
		    printf("r");
		    break;
		case 1:
		    printf("w");
		    break;
		case 0:
		    printf("x");
		    break;
	    }
    }
    printf(" %d", (int)stat->st_size);
    struct tm* t = stat->st_ctime;
    struct tm* lt = localtime(t);
    
    return 0;
}
