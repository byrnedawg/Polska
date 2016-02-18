#include <iostream>
using namespace std;

void printGrades(const int g[], int n) 
{
    for (int i = 0; i < n; i++)
	{
		cout << i << ":" << g[i] << endl;
	}
	cout << endl;
}

double calcmean(const int g[], int length) 
{
    double mean = g[0];
    for( int i = 1; i < length; i++ )
	{
		mean += g[i];
	}
    return mean / length;
}

void stats(const int g[], int length, double& mean, int& max, int& min) 
{
	double varSum = 0;
	mean = g[0];
	max = g[0];
	min = g[0];
	
	for( int i = 1; i < length; i++ )
	{
		mean += g[i];
		
		if(g[i] > max)
		{
			max = g[i];
		}
		if(g[i] < min)
		{
			min = g[i];
		}
	}
	
	mean = mean / length;
}

int main() 
{
	int gr[] = { 95, 80, 90, 65, 93 };
	const int n = sizeof(gr)/sizeof(int);
	double mean;
	int max, min;
	stats(gr, n, mean, max, min);
	printGrades(gr, n);
	cout << "The max grade is " << max << endl;
	cout << "The min grade is " << min << endl;
	cout << "The mean of the grades is " << mean << endl;
	cout << "The mean calculated with its own function = " << calcmean(gr, n) << '\n';
	
    return 0;
}

