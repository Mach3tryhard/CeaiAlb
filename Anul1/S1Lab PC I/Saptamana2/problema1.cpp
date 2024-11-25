#include <iostream>
#include <stack>

using namespace std;

stack<int> v;

int main()
{
    int n;
    scanf("%d",&n);
    while(n!=0)
    {
        v.push(n&1);
        n=n>>1;
    }
    while(!v.empty())
    {
        printf("%d",v.top());
        v.pop();
    }
    return 0;
}