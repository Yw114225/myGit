#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE* fp = NULL;
    if( (fp = fopen("1.txt", "a+")) == NULL){
	puts("open error");
	perror("fopen");
	return -1;
    }
    char buf[32];
    int i = 0;
    while((fgets(buf,32,fp)) != NULL){
	if(buf[strlen(buf)-1] == '\n')
	    ++i;
    }
    time_t t;
    struct tm* tl;
    while(1){
	sleep(1);
	t = time(NULL);
	tl = localtime(&t);
	++i;
	fprintf(fp, "%02d, %04d-%02d-%02d %02d:%02d:%02d\n", i, tl->tm_year+1900, tl->tm_mon+1, tl->tm_mday, tl->tm_hour, tl->tm_min, tl->tm_sec);
    	int flag = printf("%02d, %04d-%02d-%02d %02d:%02d:%02d\n", i, tl->tm_year+1900, tl->tm_mon+1, tl->tm_mday, tl->tm_hour, tl->tm_min, tl->tm_sec);
	fflush(fp);
    }
    return 0;
}
