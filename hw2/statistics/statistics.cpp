// Name: Gregory Byrne
// Assignment: HW3a Statistics
#include <iostream>
using namespace std;

void printArray(const double g[], const int n) 
{
	//cout << "SIZEOF my parameter: " << sizeof(g) << '\n';
	for (int i = 0; i < n; i++)
	{
		cout << i << ":" <<g[i] << endl;
	}
	cout << endl;
	//	g[0] = -1;
}

double mean(const double g[], int length) 
{
    double sum = 0;
    for( int i = 0; i < length; i++ )
	{
		sum += g[i];
	}
	cout << "sum is equal to = " << sum << endl;
	return sum/length;
}

void stats(const int g[], int length, double& mean, int& max, int& min) 
{


}

int main()
{
	// We know that we need a constant number of elements
	//const int max = 10;
	int max;
	cout << "Enter the Size of the Array" << endl;
	cin >> max;
	double values[max];
	// We will calculate their sum
	double sum = 0;
	
	cout << "Please type doubles.\n";

	for( int i = 0; i < max; i++ )
	{
		cout << "Number " << i + 1 << ": ";
		cin >> values[i];
	}

	cout << "\n\nThe mean of these numbers is = " << mean(values, max) << "\n\n";
	printArray(values, max);

	return 0;
}