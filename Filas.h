#include <stdio.h>
#include <stdlib.h>

typedef struct MiNodo{
	int dato;
	struct MiNodo* siguiente;
}Nodo;

typedef struct MiFila{
	Nodo* frente;
	Nodo* final;
}Fila;

Nodo fila_crearNodo(int dato){
	Nodo n;
	n.dato = dato;
	n.siguiente = malloc(sizeof(Nodo));
	n.siguiente = NULL;

	return n;
}

Fila fila_crearFila(){
	Fila f;
	f.frente = malloc(sizeof(Nodo));
	f.frente = NULL;
	f.final = malloc(sizeof(Nodo));
	f.final = NULL;

	return f;
}

//Agrega un elemento en el final
void fila_enqueve(Fila* f, Nodo* n){
	if(f->frente == NULL){
		f->frente = n;
	}
	else{
		f->final->siguiente = n;
	}
	f->final = n;
}

//Remover el elemento del frente
Nodo fila_dequeve(Fila* f){
	Nodo* aux = f->frente;
	if(f->frente != NULL){
		f->frente = aux->siguiente;
	}
	return *aux;
}

void fila_imprimir(Fila f){
	Nodo* aux = f.frente;
	printf("Datos en la fila: \n");
	while(aux != NULL){
		printf("-%d\n", aux->dato);
		aux = aux->siguiente;
	}
}

Nodo fila_frente(Fila f){
	return *(f.frente);
}

int fila_estaVacia(Fila f){
	return f.frente == NULL;
}