// Sistemas Operativos. 2019-2.
// Tarea 6.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR "Error: Ingresaste parámetros de más.\n"
#define ERROR_BANDERA "Error: Ingresaste una bandera equivocada.\nOpciones:\n-b : Buscar archivo\n-h : Histograma\n"
#define BANDERA_VALIDA(bandera, entrada) (strcmp (bandera, entrada) == 0)

void b(char* archivo)
{
    printf("%s\n", archivo);
	printf("Función no implementada\n");
}

void h()
{
	printf("Función no implementada\n");
}

/**
 * Función principal.
 */
int main(int argc, char** argv)
{
	//Caso: Bandera -b
	if (BANDERA_VALIDA(argv[1], "-b"))
	{
		if(argc > 3)
		{
			printf(ERROR);
			printf("Sólo ingresa el nombre del archivo\n");
		}
		else
		{
			b(argv[2]);
		}
	}
	//Caso: Bandera -h
	else if (BANDERA_VALIDA(argv[1], "-h"))
	{
		if(argc > 2)
		{
			printf(ERROR);
			printf("No tienes que proporcionar más parámetros\n");
		}
		else
		{
			h();
		}

	}
	else
	{
		printf(ERROR_BANDERA);
	}

	return 0;
}