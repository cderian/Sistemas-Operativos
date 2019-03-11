// Sistemas Operativos. 2019-2.
// Tarea 3.
// Estrada Gómez César Derian. 31222446-4.
// Barbosa Carranza Andres Luisos. 31305540-7.

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#define BANDERA_VALIDA(bandera, entrada) (strcmp (bandera, entrada) == 0)

//Función que permite imprimir los permisos
void imprimir (struct stat estru)
{
    printf( (S_ISDIR(estru.st_mode)) ? "d" : "-" );
    printf( (estru.st_mode & S_IRUSR) ? "r" : "-" );
    printf( (estru.st_mode & S_IWUSR) ? "w" : "-" );
    printf( (estru.st_mode & S_IXUSR) ? "x" : "-" );
    printf( (estru.st_mode & S_IRGRP) ? "r" : "-" );
    printf( (estru.st_mode & S_IWGRP) ? "w" : "-" );
    printf( (estru.st_mode & S_IXGRP) ? "x" : "-" );
    printf( (estru.st_mode & S_IROTH) ? "r" : "-" );
    printf( (estru.st_mode & S_IWOTH) ? "w" : "-" );
    printf( (estru.st_mode & S_IXOTH) ? "x" : "-" );
    printf("%-3s", " ");
}

void ls()
{
    struct stat estru;
    struct dirent *dt;
    DIR *dire;
    char dir;
    char bandera[3];

    //Ingreso de info por teclado
    printf("Ingresa bandera: ");
    scanf("%s",&bandera);
    printf("Ingresa directorio: ");
    scanf("%s",&dir);

    //Abrimos el directorio
    dire = opendir(&dir);

    if(BANDERA_VALIDA(bandera, "-t"))
    {
        //readdir lee el directorio completo
        while((dt=readdir(dire)) != NULL)
        {
            //Con stat vemos el estado de los archivos
            stat(dt->d_name, &estru);
            printf("%-50s %s",dt->d_name, ctime(&estru.st_atime));
        }        
    }else if(BANDERA_VALIDA(bandera, "-m"))
    {
        //readdir lee el directorio completo
        while((dt=readdir(dire)) != NULL)
        {
          //Con stat vemos el estado de los archivos
            stat(dt->d_name, &estru);
            printf("%-50s %s",dt->d_name, ctime(&estru.st_mtime));
        }
    }else if(BANDERA_VALIDA(bandera, "-p"))
    {
        //readdir lee el directorio completo
        while((dt=readdir(dire)) != NULL)
        {
            //Con stat vemos el estado de los archivos
            stat(dt->d_name, &estru);
            imprimir(estru);
            printf("%-35s \n",dt->d_name);
        }
    }else if(BANDERA_VALIDA(bandera, "-a"))
    {
        //readdir lee el directorio completo
        while((dt=readdir(dire)) != NULL)
        {
            //Con stat vemos el estado de los archivos
            stat(dt->d_name, &estru);
            printf("%-35s \n",dt->d_name);
        }
    }else if(BANDERA_VALIDA(bandera, "-l"))
    {
        //readdir lee el directorio completo
        while((dt=readdir(dire)) != NULL)
        {
           //Con stat vemos el estado de los archivos
            stat(dt->d_name, &estru);
            imprimir(estru);
            printf("%-35s %s",dt->d_name, ctime(&estru.st_mtime));
        }
    }else
    {
        printf("%s\n", "ERROR: La bandera es incorrecta");
    }
    closedir(dire);
}

int main(int argc, char const *argv[])
{
    ls();
    return 0;
}