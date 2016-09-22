#include <iostream>

using namespace std;

/* Selection sort O(n2), bad! factor of 2 better than bubble, but can’t end early
F(n) = 1 + 2 + 3 + . . . . + (n-1) = n (n-1)/2 = O(n2)
 
Hence complexity for insertion sort program in C++ is O(n2). VITAL, Ω(n) 
*/

void insertionSort(int x[], int length) 
{
    int temp = 0;
    int j = 0;
    for(int i=1;i<=length-1;i++)
    {
        temp=x[i];
        j=i-1;
 
        while((temp<x[j])&&(j>=0))
        {
            x[j+1]=x[j];    //moves element forward
            j=j-1;
        }
 
        x[j+1]=temp;    //insert element in proper place
         for(int k = 0; k < length; k++)
        {
            cout << " " << x[k] << " ";
        }
        cout << "\n";
    }
    
}


int main()
{
    
    int list[] = { 8, 3, 4, 2, 9, 6, 5, 7, 1, 10 };
    const int listSize = sizeof(list)/sizeof(int);

    for(int i = 0; i < listSize; i++)
    {
        cout << " " << list[i] << " ";
    }
    cout << "\n";
    
    
    insertionSort(list, 10);
    
     for(int i = 0; i < listSize; i++)
    {
        cout << " " << list[i] << " ";
    }
    
    return 0;
}
