#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int solutii=-1;
    int a,b,c,x1,x2,delta=0;
    cin>>a>>b>>c;
    delta = b*b -4*a*c;
    x1= (-b+sqrt(delta))/(2*a);
    x1= (-b-sqrt(delta))/(2*a);
    cout<<x1<<" "<<x2;
    return 0;
}

