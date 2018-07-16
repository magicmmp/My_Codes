#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
 using namespace std;

 int main()
{
    const int N=11;
    int array1[N]={1,2,0,3,3,0,7,7,7,0,8};
    vector<int> vector1;
    for (int i=0;i<N;++i)
        vector1.push_back(array1[i]);
    cout<<"before sort:  ";
    for (int i=0;i<vector1.size();++i)
        cout<<vector1[i]<<' ';
    cout<<endl;

    sort(vector1.begin(),vector1.end());
    cout<<"after sort:  ";
    for (int i=0;i<vector1.size();++i)
        cout<<vector1[i]<<' ';
    cout<<endl;

    vector<int>::iterator new_end;
    new_end=unique(vector1.begin(),vector1.end());
    cout<<"after unique:  ";
    for (int i=0;i<vector1.size();++i)
        cout<<vector1[i]<<' ';
    cout<<endl;
    cout<<"*new_end="<<*new_end;
    cout<<endl;    
    vector1.erase(new_end,vector1.end());
    cout<<"after erase:  ";
    for (int i=0;i<vector1.size();++i)
        cout<<vector1[i]<<' ';
    cout<<endl;

    return 0;
}
