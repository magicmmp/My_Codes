#include<dlfcn.h>
#include<stdlib.h>
#include "test.h"

void(*fn)();
int main()
{
void *handle=dlopen("./libtest.so",RTLD_LAZY);
const char *err=dlerror();
if(err!=NULL)
{
perror("could not open share object!");
}

fn=dlsym(handle,"testA");
fn();
fn=dlsym(handle,"testB");
fn();
dlclose(handle);
return 0;
}
