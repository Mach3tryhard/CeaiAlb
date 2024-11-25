#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int v[10005];

int binarySearch(int low, int high, int x)
{
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (v[mid] == x)
            return mid;
        if (v[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int  main()
{
    int x,y,n;
    cin>>n;
    cin>>x>>y;
    for(int i=0;i<n;i++)
    {
        cin>>v[i];
    }
    for(int i=binarySearch(0, n - 1, x);i<=binarySearch(0, n - 1, y);i++)
    {
        cout<<v[i]<<' ';
    }
    return 0;
}