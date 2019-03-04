#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contar_blancos(const char* comando)
{
	int blancos = 0;
	for (int i = 0; i < strlen(comando); i++)
	{
		if (comando[i] == ' ')
		{
			blancos++;
		}
	}

	return blancos;
}

int main(int argc, char const *argv[])
{
	char* comando[256];
	strcpy(comando, "Esta es una cadena de prueba :v");
	printf("%d\n", contar_blancos(comando) );
	return 0;
}