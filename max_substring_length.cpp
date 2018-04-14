#include <vector>
#include <string>
#include <iostream>
using namespace std;

int substring_length(string s) {
        int i,j,k,len,maxlen,strlen;
        int flag;
        if(s.empty())
            maxlen=0;
        else  {
        strlen=s.length();
        len=1;maxlen=1;
        for(i=0;i<strlen;i++)
      { 
        if(len>1)
          len=len-1;
        else
          len=1;   
        for(j=i+len;j<strlen;j++)
        { flag=1;
        for(k=i;k<j;k++)
          if(s[k]==s[j])
            { j=strlen; k=j;flag=0;        }
            
            if(flag)
            {   
             len=len+1; 
            if(maxlen<len)
              maxlen=len;  }
                                 }
                                    }  } 
        return maxlen;   }
int main()
{
string s1="";
string s2="sd a ";
string s3="shhdhweubasbUH\n";
cout << "s1 is empty? "<<s1.empty()<<endl;
cout << "s1 len="<<s1.length()<<endl;
cout << "s2 len="<<s2.length()<<endl;
cout << "s3 len="<<s3.length()<<endl;
cout << "the max substring len of "<<s3<<"= "<<substring_length(s3)<<endl;


return 0;
}
