#include <fstream>

using namespace std;

ifstream in("mayonaka.in");
ofstream out("mayonaka.out");

int v[100005];

int  main()
{
    int n,m,salt,g,y,x;
    in>>n>>m;
    for(int i=1;i<=m;i++)
    {
        in>>x>>y>>salt>>g;
        for(int i=0;i*salt+x<=y;i++)
        {
            v[x+i*salt]+=g;
        }
    }
    for(int i=1;i<=n;i++)
    {
        out<<v[i]<<' ';
    }
    return 0;
}