#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, char> mp;

    mp["0001"] = '1';mp["1001"] = '9';
    mp["0010"] = '2';mp["1010"] = 'a';
    mp["0011"] = '3';mp["1011"] = 'b';
    mp["0100"] = '4';mp["1100"] = 'c';
    mp["0101"] = '5';mp["1101"] = 'd';
    mp["0110"] = '6';mp["1110"] = 'e';
    mp["0111"] = '7';mp["1111"] = 'f';
    mp["1000"] = '8';mp["0000"] = '0';

    string x,rez;
    cin>>x;
    while(x.size()%4!=0)
    {
        x.insert(0,1,'0');
    }
    for(int i=0;i<x.length()/4;i++)
    {
        string n4bit="0000";
        for(int j=0;j<4;j++)
        {
            char c=x[i*4+j];
            n4bit[j] = c;
        }
        cout<<mp[n4bit];
    }
    return 0;
}