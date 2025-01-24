#include <bits/stdc++.h>

using namespace std;

struct numarmare{
    int v[1005];
    char semn;
};

numarmare a,b,sum;

string s1,s2;
int n,m,r,x,y;

bool compare(numarmare a,numarmare b,int size)
{
    int i=size;
    while(a.v[i]==b.v[i])
        i--;
    if(a.v[i]<b.v[i])
        return true;
    else
        return false;
}

int suma(numarmare a,numarmare b,numarmare &sum)
{
    bool add=true;
    r=max(s1.size(),s2.size());
    int rest=0,size=0,urest=0;
    if(a.semn=='-' && b.semn=='-')
    {
        sum.semn='-';
        add=true;
    }
    if(a.semn=='+' && b.semn=='+')
    {
        sum.semn='+';
        add=true;
    }
    if((a.semn=='+' && b.semn=='-') || (a.semn=='-' && b.semn=='+'))
        add=false;
    if(add==true)
    {
        for(int i=0;i<=r;i++)
        {
            urest=rest;
            sum.v[i]=(a.v[i]+b.v[i]+rest)%10;
            rest = (a.v[i]+b.v[i]+rest)/10;
        }
        if(urest!=0)
            size=r;
        else
            size=r-1;
    }
    else
    {
        if(b.semn=='-' && compare(a,b,r+5)==false)
            sum.semn='+';
        else
        if(b.semn=='+' && compare(a,b,r+5)==false)
            sum.semn='-';
        else
        if(b.semn=='-' && compare(a,b,r+5)==true)
        {
            sum.semn='-';
            swap(a,b);
        }
        else
        if(b.semn=='+' && compare(a,b,r+5)==true)
        {
            sum.semn='+';
            swap(a,b);
        }
        rest=0;
        for(int i=0;i<r;i++)
        {
            if(a.v[i]-rest-b.v[i]<0)
            {
                sum.v[i]=a.v[i]+10-rest-b.v[i];
                rest=1;
            }
            else
            {
                sum.v[i]=a.v[i]-b.v[i]-rest;
                rest=0;
            }
        }
    }
    return r+5;
}

int  main()
{
    ///CITIRE
    getline(cin,s1);
    getline(cin,s2);
    n=s1.size();m=s2.size();
    ///SETARE SEMN
    if(s1[0]=='+' || s1[0]=='-')
    {
        a.semn=s1[0];
        s1.erase(s1.begin());
    }
    else
        a.semn='+';

    if(s2[0]=='+' || s2[0]=='-')
    {
        b.semn=s2[0];
        s2.erase(s2.begin());
    }
    else
        b.semn='+';

    ///TRADUCERE DIN STRING IN STRUCT

    int k=0;
    for(int i=s1.size()-1;i>=0;i--)
    {
        a.v[k]=s1[i]-'0';
        k++;
    }
    k=0;
    for(int i=s2.size()-1;i>=0;i--)
    {
        b.v[k]=s2[i]-'0';
        k++;
    }
    ///OPERATII
    int marime;
    marime=suma(a,b,sum);
 
    //AFISARE
    if(sum.semn=='-')
        cout<<'-';
    bool incepf=true;
    for(int i=marime;i>=0;i--)
    {
        while(sum.v[i]==0 && incepf==true)
        {
            i--;
        }
        incepf=false;
        cout<<sum.v[i];
    }
    return 0;
}