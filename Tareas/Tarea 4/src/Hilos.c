// Sistemas Operativos. 2019-2.
// Tarea 4.
// Estrada Gómez César Derian. 31222446-4.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define TAMANIO 6

int arreglo[] = {1, 0, 0, 1, 1, 0};
int arreglo_copia[TAMANIO];

// Un hilo por cada elemento del arreglo.
pthread_t hilos[TAMANIO];

// Hilo que controlará la sección crítica
pthread_mutex_t mutex;

/*
 * Crea una copia del arreglo principal.
 */
void copiar(){
	int i;
	for(i = 0; i < TAMANIO; i++){
		arreglo_copia[i] = arreglo[i];
	}
}

/*
 * Imprime en pantalla el arreglo principal.
 */
void imprimir(){
	printf("\nArray: ");

	for(int j=0; j < TAMANIO; j++){
		printf("%d ", arreglo[j]);
	}

	printf("\n");
}

/*
 * Checa los vecinos de cada elemento del arreglo.
 * Dada un elemento del arreglo, si los vecinos adyacentes tienen el mismo valor,
 * entonces el valor del vecino que quiere actualizar su valor será 1.
 * Será 0 en otro caso.
 * 
 * Para el primer elemento, su vecino adyacente izquierdo tendrá valor 0.
 * Para el último elemento, su vecino adyacente derecho tendrá valor 0.
 */
void *checarVecinos(void *id_hilo){
	// Iniciamos sección crítica
	pthread_mutex_lock(&mutex);

	int id = (int*) id_hilo;

	printf("\nVerificando hilo %d en tiempo 0\n", id);
	
	// Estado Arreglo Posición 1
	if(id == 0){
		if(arreglo_copia[1] == 0){
			arreglo[0] = 1;
		}else{
			arreglo[0] = 0;
		}
	// Estado Arreglo Posición 2-5
	}else if(id >= 1 && id <5){
		if(arreglo_copia[id-1] == arreglo_copia[id+1]){
			arreglo[id] = 1;
		}else{
			arreglo[id] = 0;
		}
	// Estado Arreglo Posición 6
	}else if(id == 5){
		if(arreglo_copia[4] == 0){
			arreglo[5] = 1;
		}else{
			arreglo[5] = 0;
		}
	}
	printf("Terminando hilo %d en tiempo 0\n", id);

	// Finalizamos sección crítica
	pthread_mutex_unlock(&mutex);
}

/*
 * Ejecuta los hilos de cada elemento del arreglo.
 */
void ejecutar(){

	// Imprimos el array inicial y creamos una copia de él.
	imprimir();
    copiar();

	// Creamos los hilos y los ejecutamos con la función verificación
	pthread_create(&(hilos[0]), NULL, checarVecinos, (int *) 0);
	pthread_create(&(hilos[1]), NULL, checarVecinos, (int *) 1);
	pthread_create(&(hilos[2]), NULL, checarVecinos, (int *) 2);
	pthread_create(&(hilos[3]), NULL, checarVecinos, (int *) 3);
	pthread_create(&(hilos[4]), NULL, checarVecinos, (int *) 4);
	pthread_create(&(hilos[5]), NULL, checarVecinos, (int *) 5);

	// Esperamos que termine la ejecución del hilo.
	pthread_join(hilos[0], NULL);
	pthread_join(hilos[1], NULL);
	pthread_join(hilos[2], NULL);
	pthread_join(hilos[3], NULL);
	pthread_join(hilos[4], NULL);
	pthread_join(hilos[5], NULL);

	// Imprimos el array resultante.
	imprimir();
}

/*
 * Función principal.
 */
int main(){
	if (pthread_mutex_init(&mutex, NULL) != 0){
        printf("\n Fallo la inicializacion del hilo mutex\n");
        return 1;
    }

	ejecutar();
	pthread_mutex_destroy(&mutex);
	return 0;
}