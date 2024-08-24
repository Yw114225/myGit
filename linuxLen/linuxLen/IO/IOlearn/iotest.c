#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    FILE* fp = fopen("1.txt", "r+");
    extern int errno;
    char buff[10] = {};
    if(!fp){
	//printf("open failed\n");
	//perror("fopen");
	char* err = strerror(errno);
	printf("%s\n", err);
    }
    else{ 
	printf("successful\n");
	printf("%d\n",fgetc(fp));
	fgets(buff, 10, fp);
	printf("%p ", fp);
	for(int i = 0; i < sizeof(buff)/sizeof(char); ++i){
	    printf("%d ", buff[i]);
	}
	int flag = fputs("ABCD", fp);
	if(!fclose(fp))
	    printf("close success\n");
	else perror("fclose");
    }
    puts("hello world");
    int flag = fputs("ABCD", fp);
	printf("%d ", flag);
	printf("%p ", fp);
    return 0;
}
