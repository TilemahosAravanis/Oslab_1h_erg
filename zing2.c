#include <stdio.h>
#include <unistd.h>

void zing(void){

    const char *usr = getlogin();
    fprintf(stdout, "Hello from zing2 %s\n", usr);

}
