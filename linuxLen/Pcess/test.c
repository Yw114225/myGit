#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    puts("before exit");
    _Exit(1);
    puts("after exit");
    //return 0;
}
