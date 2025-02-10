#include <stdio.h>
#include <stdlib.h>

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
}
