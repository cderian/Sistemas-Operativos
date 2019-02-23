// Sistemas Operativos. 2019-2.
// Tarea 2.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Grep.h"
#define COMANDO_VALIDO(comando, entrada) (strcmp (comando, entrada) == 0)

int pwd()
{
	pid_t pid;
	int status;
	pid = fork();

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			execl("/bin/pwd","pwd", NULL);
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

int ls()
{
	pid_t pid;
	int status;
	pid = fork();

	switch(pid){
		case -1:
		perror("Error en el fork\n");
		exit(-1);
		case 0:
			execl("/bin/ls","ls", NULL);
			perror("Error de execl.\n");
			exit(-1);
		break;
		default:
		while(wait(&status) != pid);
		if(status != 0){
			printf("Error del hijo\n");
		}
	}

	return status;
}

int cp(const char * arg1, const char * arg2)
{
	pid_t pid;
	int status;
	pid = fork();

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			execl("/bin/cp","cp", arg1, arg2, NULL);
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

int cat(const char * arg1, const char * arg2)
{
	pid_t pid;
	int status;
	pid = fork();

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			execl("/bin/cat","cat", arg1, arg2, NULL);
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
		char arg1[2048];
		char arg2[2048];
		printf("shell-1.0$ ");
		scanf("%s", comando);

		if(COMANDO_VALIDO(comando, "exit"))
		{
			exit(1);
		}
		else if (COMANDO_VALIDO(comando, "ls"))
		{
			scanf("%s", arg1);
			scanf("%s", arg2);
			if(NULL != arg1 && NULL != arg2){
				ls(arg1, arg2);
			}else if(NULL != arg1 && NULL == arg2){
				ls(arg1);
			}else{
				ls();
			}
		}
		else if (COMANDO_VALIDO(comando, "pwd"))
		{
			pwd();
		}
		else if (COMANDO_VALIDO(comando, "cat"))
		{
			scanf("%s", arg1);
			scanf("%s", arg2);
			cat(arg1, arg2);
		}
		else if (COMANDO_VALIDO(comando, "cp"))
		{
			scanf("%s", arg1);
			scanf("%s", arg2);
			cp(arg1, arg2);
		}
		else if (COMANDO_VALIDO(comando, "grep"))
		{
			scanf("%s", arg1);
			scanf("%s", arg2);
			grep(arg1, arg2);
		}
		else
		{
			printf("ERROR: Comando Inválido\n");
		}
	}
	return 0;
}