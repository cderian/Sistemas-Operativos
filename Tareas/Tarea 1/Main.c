// Sistemas Operativos. 2019-2.
// Tarea 1. Ejercicio 2.
// Estrada Gómez César Derian. 31222446-4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.1416
#define ERROR "Error: Ingresaste parámetros de más.\n"
#define ERROR_BANDERA "Error: Ingresaste una bandera equivocada.\nOpciones:\n-t : Triángulo\n-c : Círculo\n-dc : Cuadrado\n-dr : Rectángulo\n"
#define FIGURA_VALIDA(f, a) (strcmp (f, a) == 0)

/**
 * Función que calcula el área de un círculo.
 * AreaCirculo = radio * PI
 */
double calcularCirculo(char* radio)
{
	double r = atof(radio);
	double resultado = r*PI;
	printf("Área del círculo: %f\n", resultado);
}

/**
 * Función que calcula el área de un triángulo.
 * AreaTriangulo = (base * altura) / 2
 */
double calcularTriangulo(char* base, char* altura)
{
	double b = atof(base);
	double h = atof(altura);
	double resultado = (b*h)/2;
	printf("Área del triángulo: %f\n", resultado);
}

/**
 * Función que calcula el área de un cuadrilátero.
 * AreaCuadrilatero = lado * lado
 */
double calcularCuadrilatero(char* num1, char* num2)
{
	double lado1 = atof(num1);
	double lado2 = atof(num2);
	float resultado = lado1*lado2;
	printf("Área del cuadrilatero: %f\n", resultado);
}

/**
 * Función principal.
 */
int main(int argc, char** argv)
{
	//Caso: Círculo
	if (FIGURA_VALIDA(argv[1], "-c"))
	{
		if(argc > 3)
		{
			printf(ERROR);
			printf("Para el círculo sólo ingresa el radio.\n");
		}
		else
		{
			calcularCirculo(argv[2]);
		}
	}
	//Caso: Cuadrado
	else if (FIGURA_VALIDA(argv[1], "-dc"))
	{
		if(argc > 3)
		{
			printf(ERROR);
			printf("Para el cuadrado sólo ingresa un lado.\n");
		}
		else
		{
			calcularCuadrilatero(argv[2], argv[2]);
		}

	}
	//Caso: Triángulo
	else if (FIGURA_VALIDA(argv[1], "-t"))
	{
		if(argc > 4)
		{
			printf(ERROR);
			printf("Para el triángulo sólo ingresa su base y su altura.\n");
		}
		else
		{
			calcularTriangulo(argv[2], argv[3]);
		}
	}
	//Caso: Rectángulo
	else if (FIGURA_VALIDA(argv[1], "-dr"))
	{
		if(argc > 4)
		{
			printf(ERROR);
			printf("Para el rectángulo sólo ingresa su lado mayor y su lado menor.\n");
		}
		else
		{
			calcularCuadrilatero(argv[2], argv[3]);
		}
	}
	else
	{
		printf(ERROR_BANDERA);
	}

	return 0;
}