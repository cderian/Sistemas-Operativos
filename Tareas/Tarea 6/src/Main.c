// Sistemas Operativos. 2019-2.
// Tarea 6.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include <dirent.h>

#define ERROR "Error: Ingresaste parámetros de más.\n"
#define ERROR_BANDERA "Error: Ingresaste una bandera equivocada.\nOpciones:\n-b : Buscar archivo\n-h : Histograma\n"
#define ENCONTRAR(archivo) execl("/usr/bin/find","find", archivo, NULL)
#define IMPRIMIR_DIRECCION() execl("/bin/pwd","pwd", NULL);
#define BANDERA_VALIDA(bandera, entrada) (strcmp (bandera, entrada) == 0)

/*void b(char* archivo)
{
    printf("%s\n", archivo);
	printf("Función no implementada\n");
}*/

int b(const char * archivo)
{
	char* resultado = "No encontrado";
	struct dirent **namelist;
	
	int n;
	n = scandir(".", &namelist, 0, alphasort);
	if (n < 0){
		perror("scandir");
	}
	else
	{
		while(n--)
		{
			printf("Tipo: %d - %s \n", namelist[n]->d_type, namelist[n]->d_name);
			if ((strcmp (namelist[n]->d_name, archivo) == 0))
			{
				resultado = "Encontrado!";
				//execl("/bin/pwd","pwd", NULL);
			}
			free(namelist[n]);
		}
		free(namelist);
	}
	printf("%s\n", resultado);
	
	/*pid_t pid;
	int status;
	pid = fork();*/
	/*switch(pid){
		case -1:
			perror("Error en el fork\n");
			exit(-1);
		case 0:
			if( (ENCONTRAR(archivo) < 0)){
                perror("Error de execl.\n");
			    exit(-1);
            }else{
                printf("Encontrado! ");
                IMPRIMIR_DIRECCION();
                //ENCONTRAR(archivo);
            }
			break;
		default:
			while(wait(&status) != pid);
				if(status != 0)
				{
					printf("Error del hijo\n");
				}
	}*/
	//return status;
	return 0;
}

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