#include <iostream>

using namespace std;

void badshuffle(int x[], int length)
{
	for(int i = 0; i < length; i++)
	{
		int pick = rand() % (length);
		swap(x[i], x[pick]);
    }
}

int main()
{
    int answer = 0;
    do{
        int list[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        const int listSize = sizeof(list)/sizeof(int);
    
        for(int i = 0; i < listSize; i++)
        {
            cout << " " << list[i] << " ";
        }
        cout << "\n";
        
        
        badshuffle(list, 10);
        
         for(int i = 0; i < listSize; i++)
        {
            cout << " " << list[i] << " ";
        }
        
        cout << "\n Run it again ? 1 = Yes, 2 = No \n";
        cin >> answer;
    }while(answer <= 1);
    return 0;
}







