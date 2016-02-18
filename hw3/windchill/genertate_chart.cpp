#include <iostream>
#include <cmath>

using namespace std;


double wind_chill = 0.0;


double calc_wind_chill(int wind_speed, int air_temp)
{
   double wind_chill = 0.0;
   wind_chill = 35.74 + (0.6215*air_temp) - (35.75*pow(wind_speed, 0.16)) + (0.4275* air_temp*pow(wind_speed, 0.16));
   return round(wind_chill);
}
int main() 
{
   for(int i = 5; i<=60; i = i+5)
   {
      for(int j = 40; j >= -45; j = j-5)
      {
         cout <<calc_wind_chill(i, j) << "   ";
      }
      cout<< endl;
   }
   
   return 0;
}
