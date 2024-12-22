#include <bits/stdc++.h>

using namespace std;

int a[17][17];

int  main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(j>=i)
                a[i][j]=2;
            else
                a[i][j]=0;
            cout<<a[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}