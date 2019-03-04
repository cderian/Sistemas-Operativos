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
#define true 0
#define false 1

int contar_blancos(char* comando)
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

/*int tokenizar (char* comando, const char * caracter, int num_params) {
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
}*/

int ejecutar (char* comando, const char * caracter, int num_params) 
{
	pid_t pid;
	int status;
	char com[256];

	if(num_params == 0)
	{
		pid = fork();

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			strcpy(com, "/bin/");
			execl(strcat(com, comando), comando, NULL);
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
	}else{

	char* instruccion[num_params+1];
	char* params[num_params];
	/* Tokenización */
	char *token;
	token = strtok(comando, caracter);
	int i=0;

	while( token != NULL ) {
		instruccion[i] = token;
		token = strtok(NULL, caracter);
		i++;
	}

	/* Separando params */
	int j=1;
	while(instruccion[j] != NULL)
	{
		params[j-1] = instruccion[j];
		++j;
	}

	/* Parte de ejecución*/
	/*pid_t pid;
	int status;
	char com[256];*/
	pid = fork();

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			strcpy(com, "/bin/");
			execv(strcat(com, instruccion[0]), params);
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
		ejecutar(comando, " ", contar_blancos(comando));
		//separar_params();
		//ejecutar();
	}
	return 0;
}