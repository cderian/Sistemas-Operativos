// Sistemas Operativos. 2019-2.
// Tarea 2.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define COMANDO_VALIDO(comando, entrada) (strcmp (comando, entrada) == 0)

char* instruccion[3];
char* params[1];

int token (const char* str) {
   const char s[2] = "-";
   char *token;
   
   token = strtok(str, s);
   
   int i=0;
   while( token != NULL ) {
      instruccion[i] = token;
      token = strtok(NULL, s);
      i++;
   }

   return 0;
}

/*char* obtener_comando(const char* arg){
	const char espacio[2] = " ";
	char *token;
	token = strtok(arg, espacio);
	return token;
}*/

int ejecutar(const char * arg)
{
	pid_t pid;
	int status;
	char comando[256];
	pid = fork();

	token(arg);

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			strcpy(comando, "/bin/");
			memcpy(params, instruccion+1, 1*sizeof(char));
			//execve(strcat(comando, instruccion[0]), params);
			execl(strcat(comando, instruccion[0]), instruccion[0], params[0], NULL);
			perror("Error de execl.\n");
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
		char comando[2048];
		printf("shell-1.0$ ");
		scanf("%s", comando);

		if(COMANDO_VALIDO(comando, "exit"))
		{
			exit(1);
		}

		ejecutar(comando);
	}
	return 0;
}