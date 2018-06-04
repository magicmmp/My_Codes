#include<vector>
#include <iostream>
using namespace std;

int main()
{
vector<int> v;
v.push_back(2);
v.push_back(6);
v.push_back(8);
vector<int>::iterator i,j;
i=v.begin();
j=v.end();
cout<<"Vi="<<*i<<",Vj="<<*j<<endl;
cout<<"j-i="<<j-i<<endl;








}
