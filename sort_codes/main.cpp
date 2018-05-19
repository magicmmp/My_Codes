#include <iostream>
#include<ctime>
#include <sys/time.h>
#include "Straight_Insertion_Sort.h"
#include "binary_insertion_sort.h"
#include "quick_sort.h"
#include "srand.h"
const int len = 1000000;
const int N = 100;
using namespace std;

void print(int a[], int len)
{
    int i;    
    for (i = 0; i < len; i++)
      cout<<a[i]<<" ";
    cout<<endl;
}

int main()
{   
    int i;
    int a[len];
    clock_t start,finish;
    struct timeval t1, t2 ;
    double timeSpan;
    cout <<"data length to sort = "<<len<<",  sort times: N= "<<N<<endl;
    random(a,len);
    cout <<"straight_insertion_sort,before sort:"<<endl;
 //   print(a,len);
    timeSpan=0;
    gettimeofday(&t1,NULL) ;
    for(i=0;i<N;i++)
    random(a,len);
//    straight_insertion_sort(a,0,len-1);
    gettimeofday(&t2, NULL) ;
    timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
    cout <<"after sort:"<<endl;
//    print(a,len);
    cout << "time="<<timeSpan<<" sec ."<< endl;

    random(a,len);
    cout <<"binary_insertion_sort,before sort:"<<endl;
//    print(a,len);
    timeSpan=0;
    gettimeofday(&t1,NULL) ;
    random(a,len);
//    binary_insertion_sort(a,0,len-1);
    gettimeofday(&t2, NULL) ;
    timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
    cout <<"after sort:"<<endl;
    cout << "time="<<timeSpan<<" sec ."<< endl;
 //   print(a,len);

    random(a,len);
    cout <<"quicksort,before sort:"<<endl;
//    print(a,100);
    timeSpan=0;
    gettimeofday(&t1,NULL) ;
    for(i=0;i<N;i++)
    {
      random(a,len);
      quicksort(a,0,len-1);
    }
    gettimeofday(&t2, NULL) ;
    timeSpan = (double)(t2.tv_sec-t1.tv_sec) + (double)t2.tv_usec*1e-6 - (double)t1.tv_usec*1e-6 ;
    cout <<"after sort:"<<endl;
    cout << "time="<<timeSpan<<" sec ."<< endl;
    print(a,100);


    return 0;
}
