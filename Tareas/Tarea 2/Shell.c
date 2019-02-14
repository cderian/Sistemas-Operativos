// Sistemas Operativos. 2019-2.
// Tarea 2.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMANDO_VALIDO(comando, entrada) (strcmp (comando, entrada) == 0)

void procesarComando()
{

}

int main(int argc, char const *argv[])
{
	while(1)
	{
		char comando[2048];
		printf("shell-1.0$ ");
		scanf("%s", comando);

		if(COMANDO_VALIDO(comando, "exit"))
		{
			exit(1);
		}
		else if (COMANDO_VALIDO(comando, "ls"))
		{
			printf("Comando ls aún no implementado\n");
		}
		else if (COMANDO_VALIDO(comando, "pwd"))
		{
			printf("Comando pwd aún no implementado\n");
		}
		else if (COMANDO_VALIDO(comando, "cat"))
		{
			printf("Comando cat aún no implementado\n");
		}
		else if (COMANDO_VALIDO(comando, "cp"))
		{
			printf("Comando cp aún no implementado\n");
		}
		else if (COMANDO_VALIDO(comando, "grep"))
		{
			printf("Comando grep aún no implementado\n");
		}
		else
		{
			printf("ERROR: Comando Inválido\n");
		}
	}
	return 0;
}