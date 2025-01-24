#include <iostream>

using namespace std;

int main()
{
    int x,y,n,p,mask;
    scanf("%d%d%d%d",&x,&y,&n,&p);
    for(int i=p;i<p+n;i++)
    {
        mask=1<<i;
        if(x|mask!=y|mask)
            x=x|mask;
    }
    printf("%d",x);
    return 0;
}