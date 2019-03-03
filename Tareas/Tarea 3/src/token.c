#include <string.h>
#include <stdio.h>

//char* instruccion[3];

int params2[2]; 

int main () {
   
   int params[3] = {1, 2, 3};
   memcpy(params2, params+1, 2*sizeof(int));

   for (int i = 0; i < 2; ++i)
   {
     printf("%d\n", params2[i]);
   }
   

   return(0);
}