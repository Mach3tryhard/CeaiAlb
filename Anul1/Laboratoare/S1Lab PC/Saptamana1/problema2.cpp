#include <iostream>

using namespace std;

int main()
{
    int a,b,c,rez=0;
    cin>>a>>b>>c;
    rez=(a>b)?( (a>c)?a:c ):( (b>c)?b:c );
    cout<<rez;
    return 0;
}
