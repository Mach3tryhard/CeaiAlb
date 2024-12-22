#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    cout<<(n<<3)<<'\n';// n*8
    cout<<(n>>1)<<'\n';// n/4
    cout<<(n<<3)+(n<<1)<<'\n';// n*10
    return 0;
}