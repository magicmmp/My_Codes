#include <iostream>
#include<unistd.h>
#include "abc.h"
using namespace std;

int main()
{   A a;
   a.set_a(8);
   cout << "PID=" <<getpid()<< endl;
   cout << "a=" <<a.ret_a()<< endl;
    return 0;
}

