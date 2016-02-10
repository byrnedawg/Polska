// Name: Gregory Byrne
// Assignment: HW3a Statistics
#include <iostream>
using namespace std;

void printArray(double g[], int n) 
{
	cout << "SIZEOF my parameter: " << sizeof(g) << '\n';
	for (int i = 0; i < 5; i++)
	{
		cout << i << ":" <<g[i] << endl;
	}
	cout << endl;
	//	g[0] = -1;
}

double mean(const int g[], int length) 
{

}

void stats(const int g[], int length, double& mean, int& max, int& min) 
{


}

int main()
{
    unsigned char n;
    double values[256] = {12.4, 5.5, 74.5};
    cout << "Enter in the number of values in array" << endl;
    cin >> n;
    printArray(values, n);
    return 0;
}