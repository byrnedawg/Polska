#include <iostream>
using namespace std;

unsigned long long x;
unsigned long long y;

bool isPrime(unsigned long long p) 
{
    unsigned long long divcount = 0;
    for(int i = 1; i <= p; i++)
    {
        if(p % i == 0)
        {
            divcount++;
            
            if(divcount > 2)
            {
                return  false;
            }
        }
    }
    if(divcount < 2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int countPrimes(unsigned long long a, unsigned long long b)
{
    int primecount = 0;
    while(a<=b)
    {
        if(isPrime(a))
        {
            primecount++;
        }
        
        a++;
    }
    return primecount;
    
}

int main() 
{
    cout << "Enter a range to check for primes" << endl;
    cout << "Enter Start" << endl;
    cin >> x;
    cout << "Enter Stop" << endl;
    cin >> y;
    cout<< "The Number of Primes in that range is = "<< countPrimes(x,y) <<endl;
    
    return 0;
}
