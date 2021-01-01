#include "utility_funcs.h"


uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int int_to_str(uint8_t* str, int num)
{
    int temp = 0;
    int n1 = 10000;
    int n2 = 1000;
    int k = 0;
    if (num < 10)//9
    {
        n1 = 10;
        n2 = 1;
        k = 1;
    }
    else if(num <100)//99
    {
        n1 = 100;
        n2 = 10;
        k = 2;
    }
    else if (num < 1000)//999
    {
        n1 = 1000;
        n2 = 100;
        k = 3;
    }
    else//1000
    {
         n1 = 10000;
         n2 = 1000;
         k = 4;
    }
    for (int i = 0; i < k; i++)
    {
        str[i] = ((num % n1) / n2)+48;
        n1 =n1/ 10;
        n2 = n2 / 10;
    }
    str[k] = '\0';
    return k;  //returns size
}
