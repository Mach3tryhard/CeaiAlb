#include <iostream>

using namespace std;

int a[105][105];

int  main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    if(n<=m)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=m;j++)
            {
                swap(a[i][j],a[j][i]);
            }
        }
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cout<<a[i][j]<<' ';
            }
            cout<<'\n';
        }
        return 0;
    }
    if(m<n)
    {
        for(int i=1;i<=m;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                swap(a[i][j],a[j][i]);
            }
        }
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)
            {
                cout<<a[i][j]<<' ';
            }
            cout<<'\n';
        }
        return 0;
    }
    return 0;
}