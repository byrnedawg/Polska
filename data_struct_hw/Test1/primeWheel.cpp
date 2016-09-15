// Name: Gregory Byrne

#include <iostream>

using namespace std;


void testPrime(int n)
{
    for(int i = 6; i <= n; i+=6)
    {
        testPrime(i+1);
        testPrime(i+5);
    }
}

int main()
{
    testPrime(30);
    
    return 0;
}