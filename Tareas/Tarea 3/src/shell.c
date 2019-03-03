// Sistemas Operativos. 2019-2.
// Tarea 3.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define COMANDO_VALIDO(comando, entrada) (strcmp (comando, entrada) == 0)

char* instruccion[3];
char* params[2];

int tokenizar (char* comando, const char * caracter) {
   char *token;
   
   token = strtok(comando, caracter);
   
   int i=0;
   while( token != NULL ) {
      instruccion[i] = token;
      token = strtok(NULL, caracter);
      i++;
   }

   return 0;
}

char* separar_params(){
	int i=1;
	while(instruccion[i] != NULL)
	{
		params[i-1] = instruccion[i];
		++i;
	}
}

int ejecutar()
{
	pid_t pid;
	int status;
	char comando[256];
	pid = fork();

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			strcpy(comando, "/bin/");
			execv(strcat(comando, instruccion[0]), params);
			perror("Error de execv.\n");
			exit(-1);
			break;
		default:
			while(wait(&status) != pid);
				if(status != 0)
				{
					printf("Error del hijo\n");
				}
	}

	return status;
}

int main(int argc, char const *argv[])
{
	while(1)
	{
		char comando[81];
		printf("shell-1.0$ ");
		fgets(comando, 81, stdin);
		comando[strlen(comando)-1] = '\0';

		if(COMANDO_VALIDO(comando, "exit"))
		{
			exit(1);
		}
		tokenizar(comando, " ");
		separar_params();
		ejecutar();
	}
	return 0;
}