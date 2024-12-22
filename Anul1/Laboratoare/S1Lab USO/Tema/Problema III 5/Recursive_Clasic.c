#include <stdio.h>

int n, x[10],k=1;

void _back(int k)
{
    for (int i = 1; i <= n; i++)
    {
        int verificare=1;
        x[k] = i;
        for (int i = 1; i < k; ++i)
        {
            if (x[i] == x[k])
            {
                verificare=0;
            }
        }
        if(verificare==1)
        {
            if (k == n)
            {
                for (int i = 1; i <= n; i++)
                {
                    printf("%d ", x[i]);
                }
                printf("\n");
            }
            else
            {
                _back(k + 1);
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    _back(1);
    return 0;
}
