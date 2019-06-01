// Sistemas Operativos. 2019-2.
// Tarea 6.
// Estrada Gómez César Derian. 31222446-4.

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define OPCIONES_BANDERA "Opciones:\n-b : Buscar archivo\n-h : Histograma\n"
#define BANDERA_VALIDA(bandera, entrada) (strcmp (bandera, entrada) == 0)

struct dirent **archivos;

/*
 * Busca un archivo dentro de un directorio
 */
int b(const char * archivo)
{
	char* resultado = "No encontrado";
	char cwd[PATH_MAX];
	bool ENCONTRADO = false;
	
	//Número de archivos del directorio
	int n;
	n = scandir(".", &archivos, 0, alphasort);
	if (n < 0){
		perror("Esta carpeta se encuentra vacía");
	}
	else
	{
		while(n--)
		{
			//printf("Tipo: %d - %s \n", archivos[n]->d_type, archivos[n]->d_name);
			if (strcmp (archivos[n]->d_name, archivo) == 0)
			{
				ENCONTRADO = true;
				//execl("/bin/pwd","pwd", NULL);
			}

			// Se libera memoria
			free(archivos[n]);
		}
		// Se libera memoria
		free(archivos);
	}

	if(ENCONTRADO){
		printf("Encontrado! %s/%s\n", getcwd(cwd, sizeof(cwd)), archivo);
	}else{
		printf("No encontrado!\n");
	}

	return 0;
}

/*
 * Realiza un histograma de los archivos que se encuentran
 * en un directorio.
 * Muestra el nombre y tamaño en bytes de los archivos.
 */
int h()
{
	pid_t pid;
	int status;
	pid = fork();

	switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			execl("/usr/bin/du","du", "-ba", NULL);
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

/**
 * Función principal.
 */
int main(int argc, char** argv)
{
	//Caso: Bandera -b
	if (argc == 1)
	{
		printf("Tienes que proporcionar una bandera\n");
		printf(OPCIONES_BANDERA);
	}
	else if (BANDERA_VALIDA(argv[1], "-b"))
	{
		if(argc > 3)
		{
			printf("Error: Ingresaste parámetros de más.\n");
			printf("Sólo ingresa el nombre de un archivo archivo\n");
		}
		else if (argc < 3)
		{
			printf("Error: Ingresa el nombre del archivo que quieres buscar.\n");
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
			printf("Error: No tienes que proporcionar parámetros\n");
		}
		else
		{
			h();
		}
	}
	else
	{
		printf("Error: Ingresaste una bandera equivocada.\n");
		printf(OPCIONES_BANDERA);
	}

	return 0;
}