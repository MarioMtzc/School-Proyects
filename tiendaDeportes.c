#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Permite la definición de valores constantes a utilizar durante tu programa
#define MAX_NOMBRE 100		//Longitud máxima del nombre de un producto
#define MAX_PRODUCTOS 50	//Cantidad máxima de productos
#define SALIR 4				//Opción para salir del programa

//Estructura para el almacenamiento de la información de un producto
struct MiProducto {
	float precio;
	char* nombre;
};
//Sobrenombre "apodo" para que en vez de utilizar struct MiProducto --> Producto
typedef struct MiProducto Producto;

//Funciones para agregar, almacenar y leer productos
void agregarProducto(Producto lista[], int noProductos);
void almacenarProductos(Producto lista[], int noProductos, char* archivo);
Producto* leerProductos(char* archivo);
//Funciones adicionales para imprimir productos y obtener cantidad de productos almacenados
void imprimirProductos(Producto lista[], int noProductos);
int obtenerCantidadProductos(char* archivo);
//Funciones para mostrar el menú de opciones
void imprimirMenu();
int leerOpcion();
int ejecutarOpcion(int opcion, Producto lista[], int noProductos);

/****************************************** MAIN ************************************************/
int main() {
	Producto* lista;
	int noProductos, i, opcion;

	noProductos = obtenerCantidadProductos("productos.dat");
	lista = leerProductos("productos.dat");

	do {
		imprimirMenu();
		opcion = leerOpcion();
		noProductos = ejecutarOpcion(opcion, lista, noProductos);
	} while (opcion != SALIR);
}

void agregarProducto(Producto lista[], int noProductos) {
	Producto prod;
	float precio;
	char* nombre;

	printf("Nombre del producto: ");
	nombre = (char*)malloc(sizeof(char)*MAX_NOMBRE);
	fgets(nombre, 100, stdin);

	printf("Precio del producto: ");
	scanf("%f", &precio);
	getchar();
	prod.precio = precio;

	lista[noProductos].nombre = nombre;
	lista[noProductos].precio = precio;
}

void almacenarProductos(Producto lista[], int noProductos, char* archivo) {
	FILE* f = fopen(archivo, "w");
	int i;
	fprintf(f, "%d\n", noProductos);
	for (i=0; i<noProductos; i++) {
		fprintf(f, "%s\t%.2f\n", lista[i].nombre, lista[i].precio);
	}
	fclose(f);
}

void imprimirProductos(Producto lista[], int noProductos) {
	int i;
	printf("************************************************************\n");
	printf("************************************************************\n");
	printf("Lista de productos\n");
	printf("Producto\t\tPrecio\n");
	for (i=0; i<noProductos; i++) {
		printf("%s\t\t\t%.2f\n", lista[i].nombre, lista[i].precio);
	}
}

Producto* leerProductos(char* archivo) {
	FILE* f = fopen(archivo, "r");
	int i, noProductos;
	char* nombre;
	char* tmp;
	float precio;
	Producto* lista;

	fscanf(f, "%d", &noProductos);
	tmp = malloc(sizeof(char)*MAX_NOMBRE);
	fgets(tmp, MAX_NOMBRE, f);
	printf("Productos leidos del archivo: %d\n", noProductos);
	lista = malloc(sizeof(Producto)*MAX_PRODUCTOS);

	for (i=0; i<noProductos; i++) {
		nombre = malloc(sizeof(char)*MAX_NOMBRE);
		fgets(nombre, MAX_NOMBRE, f);
		lista[i].nombre = malloc(sizeof(char)*MAX_NOMBRE);
		strcpy(lista[i].nombre, nombre);
		fscanf(f, "%f", &precio);
		tmp = malloc(sizeof(char)*MAX_NOMBRE);
		fgets(tmp, MAX_NOMBRE, f);
		lista[i].precio = precio;
		//printf("Elemento leido: %s\t%f\n", lista[i].nombre, lista[i].precio);
	}

	fclose(f);
	return lista;
}

int obtenerCantidadProductos(char* archivo) {
	int noProductos;
	FILE* f = fopen(archivo, "r");
	fscanf(f, "%d", &noProductos);
	fclose(f);

	return noProductos;
}

void imprimirMenu() {
	printf("************************************************************\n");
	printf("************** Tienda de articulos deportivos **************\n");
	printf("********** Modulo de administracion\n");
	printf("Elige una de las siguientes acciones\n");
	printf("\t1. Agregar un nuevo producto\n");
	printf("\t2. Ver lista de productos\n");
	printf("\t3. Almacenar lista en archivo\n");
	printf("\t4. Salir\n");
}

int leerOpcion() {
	int opcion;
	do {
		printf("\tEleccion: ");
		scanf("%d", &opcion);
		getchar();
		if (opcion < 1 || opcion > SALIR)
			printf("Opcion invalida. Elige nuevamente.\n");
	} while (opcion < 1 || opcion > SALIR);

	return opcion;
}

int ejecutarOpcion(int opcion, Producto lista[], int noProductos) {
	switch (opcion) {
		case 1:
			agregarProducto(lista, noProductos);
			noProductos++;
			break;
		case 2:
			imprimirProductos(lista, noProductos);
			break;
		case 3:
			almacenarProductos(lista, noProductos, "productos.dat");
			break;
	}

	return noProductos;
}