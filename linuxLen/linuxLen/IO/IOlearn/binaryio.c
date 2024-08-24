#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE* fp = NULL;
    if( ( fp = fopen("binary.bin", "r+") ) == NULL ){
	puts("open failed");
	perror("fopen");
	return -1;
    }
    int bufw[] = {1,2,3,4,5};
    int bufr[5] = {};
    size_t n_w = fwrite(bufw, sizeof(int), 4, fp);
    printf("%ld ", ftell(fp));
    rewind(fp);
    //fseek(fp, -16, SEEK_CUR);
    printf("%ld ", ftell(fp));
    size_t n_r = fread(bufr, sizeof(int) , 4, fp);
    printf("nw = %ld, nr = %ld\n", n_w, n_r);
    for(int i = 0; i < 5; ++i){
	printf("%d ", bufr[i]);
    }
    if( fclose(fp) == -1)
	perror("fclose");
    return 0;
}
