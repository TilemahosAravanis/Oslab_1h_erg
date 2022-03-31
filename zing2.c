#include <stdio.h>
#include <unistd.h>

void zing(void){

fprintf(stdout, "Hello from zing2 %s\n", getlogin());
}
