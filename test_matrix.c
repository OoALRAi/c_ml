#include "matrix.h"
#include "nn.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
double max(double *arr)
{
  double maxx = arr[0];
  for (int i = 0; i < 100000; i++)
  {
    if (maxx < arr[i])
    {
      maxx = arr[i];
    }
  }
  return maxx;
}

int main()
{
  int counter = 0;
  double arr[100000];

  while (counter < 100000)
  {
    srand(time(NULL));
    arr[counter] = nn_normal_rand_double() * 10;
    counter++;
  }
  double maxx = max(arr);
  printf("max value = %f\n", maxx);
  return 0;
}
