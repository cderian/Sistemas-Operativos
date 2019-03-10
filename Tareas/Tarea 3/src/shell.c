// Sistemas Operativos. 2019-2.
// Tarea 3.
// Estrada Gómez César Derian. 31222446-4.

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include<stdlib.h>
#include <sys/wait.h>

char* inputs[40];
char* instrucciones[40];

void tokens(char * parametro){
	int i = 0;
    char *token = strtok(parametro, " ");

    while(token != NULL){
    	inputs[i] = malloc(strlen(token) + 1);
		strcpy(inputs[i], token);
        token = strtok(NULL, " ");
        i++;
    }
}

void elimina_primero(){
	int j=0;
	while(inputs[j] != NULL)
	{
		instrucciones[j] = inputs[j+1];
		++j;
	}
}

void ejecuta_accion(char * accion){
	int estado;
	int jalo;
	pid_t pid;
	char comando[1024];
	char* algo;
	pid = fork();
	if(pid == 0){
		tokens(accion);
		strcpy(comando, "/bin/");
		strcat(comando, accion);
		jalo = execv(comando, inputs); 
		if(jalo == -1 && strcmp(accion, "exit") != 0){			
			execv(accion, inputs);
			printf("%s\n", "Comando desconocido");
		}
	} else if(pid < 0){
		printf("*****Error no se pudo hacer hijo del proceso.\n*****");
		estado = -1;
	} else{
		if(waitpid(pid, &estado, 0) != pid){
			printf("Error\n");
			estado = -1;
		}
	}
}

int main() {
	char comando[65];

	while(strcmp(comando, "exit") != 0){
	    printf("shell-2.0$ ");
	    fgets(comando, 81, stdin);
	    comando[strlen(comando)-1] = '\0';
	    ejecuta_accion(comando);
    }

    return(0);
}
