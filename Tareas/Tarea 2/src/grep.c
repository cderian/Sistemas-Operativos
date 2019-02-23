// Sistemas Operativos. 2019-2.
// Tarea 2.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <string.h>

void grep(const char * arg1, const char * arg2)
{
	char linea[1024];
	char *subcadena;
    FILE *archivo;
 
    archivo = fopen(arg2, "r");
    
    while(fgets(linea, 1024, (FILE*) archivo))
    {
    	subcadena = strstr(linea, arg1);
    	if (NULL != subcadena)
    	{
    		printf("%s\n", linea);
    	}
    }
    
    fclose(archivo);
}