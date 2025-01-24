#include <iostream>

using namespace std;

int pv[2005],nv[2005];

int  main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        if(x<0)
            nv[-x]=1;
        else
            pv[x]=1;
    }
    for(int i=1;i<=m;i++)
    {
        int x;
        cin>>x;
        if(x<0)
            nv[-x]++;
        else
            pv[x]++;
    }
    for(int i=1;i<=2000;i++)
    {
        if(nv[i]>1)
            cout<<"-"<<i<<' ';
    }
    for(int i=1;i<=2000;i++)
    {
        if(pv[i]>1)
            cout<<i<<' ';
    }
    return 0;
}