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

/*
 * Busca un archivo dentro de un directorio
 */
int b(const char * archivo)
{
	char cwd[PATH_MAX];
	char *buffer;
	FILE *p;
	char ch;

	buffer = malloc(strlen(archivo) + 5);
	strcpy(buffer, archivo);
	char a[500] = "find -iname ";
	char subdireccion[500] = "";
	
	strcat(a, buffer);
	int tamanio;

	p = popen(a,"r");
	if( p == NULL)
	{
		puts("Unable to open process");
		return(1);
	}
	
	int n = 0;
	while( (ch=fgetc(p)) != EOF)
	{
		// Guardamos la dirección del archivo.
		// La dirección esta dada a partir de la carpeta donde estamos.
		subdireccion[n] = ch;
		n = n+1;
		tamanio = tamanio +1;
	}
	
	if(tamanio == 0)
	{
		printf("No encontrado!\n");
	}
	else
	{
		// Obtenemos la ruta completa del archivo.
		char direccion[500] = "";
		int i = 1;
		while (i < sizeof(subdireccion) )
		{
			direccion[i-1] = subdireccion[i];
			i = i+1;
		}

		printf("Encontrado! %s%s", getcwd(cwd, sizeof(cwd)), direccion);
	}

	free(buffer);	
	pclose(p);
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