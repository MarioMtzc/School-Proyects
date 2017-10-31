#include <stdio.h>
#include <stdlib.h>
#define NO_VISITADO 1
#define VISITADO 3
#define EN_PROGRESO 2

//Nodo
struct MiNodo{
int dato, estado, distancia;
struct MiNodoAdyacencia *inicio;
struct MiNodo *siguiente;
struct MiNodo *padre;
};
typedef struct MiNodo Nodo;

//Nodo fila
struct MiNodoFila{
    Nodo* dato;
    struct MiNodoFila* siguiente;
};
typedef struct MiNodoFila NodoFila;

//NodoAdyacencia
struct MiNodoAdyacencia{
    Nodo* destino;
    struct MiNodoAdyacencia *siguiente;
};
typedef struct MiNodoAdyacencia NodoAdyacencia;

//Fila
struct MiFila{
    NodoFila* frente;
    NodoFila* final;
};
typedef struct MiFila Fila;

//Grafo
struct MiGrafo {
    Nodo *inicio;
};
typedef struct MiGrafo Grafo ;

//Crear grafo
Grafo grafo_crearGrafo(){
Grafo g;
g.inicio = malloc(sizeof(Nodo*));
g.inicio = NULL;
return g;
}

//Crear fila
Fila fila_crearFila(){
    Fila f;
    f.final = malloc(sizeof(Nodo));
    f.final = NULL;
    f.frente = malloc(sizeof(Nodo));
    f.frente=NULL;
    return f;
}

//Crear nodo
Nodo* grafo_crearNodo(int dato){
    Nodo *n;
    n= malloc(sizeof(Nodo*));
    n->dato = dato;
    n->siguiente = malloc(sizeof(Nodo*));
    n->siguiente = NULL;
    n->inicio= malloc(sizeof(NodoAdyacencia*));
    n->inicio = NULL;
    n->padre = NULL;
    n->padre = malloc(sizeof(Nodo*));
    return n;
}

//Crear nodo Adyacencia
NodoAdyacencia* grafo_crearNodoAdyacencia(Nodo* destino){
    NodoAdyacencia *n;
    n = malloc(sizeof(NodoAdyacencia*));
    n->destino = malloc(sizeof(Nodo*));
    n->destino = destino;
    n->siguiente= malloc(sizeof(NodoAdyacencia*));
    n->siguiente = NULL;
    return n ;
}

//Crear Nodo Fila
NodoFila fila_crearNodo(int dato){
    NodoFila n;
    n.siguiente = malloc(sizeof(Nodo));
    n.siguiente = NULL;
    return n;
}

//enqueue Agregar al final
void fila_enqueue(Fila* f, NodoFila* n){
    if(f->frente == NULL){
        f->frente = n;
        f->final = n;
    }
    else{
        f->final->siguiente = n;
    }
    f->final = n;
}
//Esta vacia
int  fila_estavacia(Fila f){
    if(f.frente == NULL){
        return 1;
    }
    else
        return 0;
}

//dequeue remover el elemento del frente
NodoFila* fila_dequeue(Fila* f){
    NodoFila* aux = f->frente;
    if(f->frente!=NULL){
        f->frente = aux->siguiente;
        aux->siguiente = NULL;
    }
    return aux;
}


//Agregar Vertice
void grafo_agregarVertice(Nodo* n, Grafo* g){
    if(g->inicio  == NULL){
        g->inicio = n;
    }
    else{
    Nodo *aux = g->inicio;
    while (aux->siguiente != NULL) {
        aux = aux->siguiente;
        
    }
        aux->siguiente = n;
}
}

//Agregar Arista
void grafos_agregarArista(Grafo* g, Nodo* origen, Nodo* destino){
    NodoAdyacencia *ady= grafo_crearNodoAdyacencia(destino);
    if(origen->inicio == NULL){
        origen->inicio = ady;
    }
    else{
        NodoAdyacencia *aux =origen->inicio;
    while (aux->siguiente!= NULL) {
        aux = aux->siguiente;
    }
        aux->siguiente = ady;
}
}
//Imprimir Adyacencias
void grafo_imprimirAdyacencias(Nodo* n){
    NodoAdyacencia *aux;
    aux = n->inicio;
    while (aux != NULL) {
        printf("%d\t", aux->destino->dato);
        aux= aux->siguiente;
    }
    printf("\n");
}

//Imprimir Grafo
void grafo_imprimirGrafo(Grafo g){
    Nodo* aux;
    aux= g.inicio;
    printf("Contenido del grafo\n");
    while (aux != NULL) {
    printf("%d: ", aux->dato);
    grafo_imprimirAdyacencias(aux);
    aux = aux->siguiente;
}
}

//Buscar Vertice
Nodo* grafo_BuscarVertice(Grafo g, int dato){
    Nodo* aux = g.inicio;
    while (aux!= NULL) {
        if(aux->dato == dato)
            printf("Vertice encontrada\n");
            return aux;
        aux = aux->siguiente;
    }
    printf("Vertice no encontrada\n");
        return NULL;
}


//Existe Arista
int grafo_existeArista(Grafo g, int origen, int destino){
    Nodo *nOrigen = grafo_BuscarVertice(g, origen);
    NodoAdyacencia* aux = nOrigen->inicio;
    
    while (aux!= NULL) {
        if(aux->destino->dato == destino)
            printf("Arista encontrada\n");
            return 1;
        aux = aux->siguiente;
    }
    printf("Arista no encontrada\n");
    return 0;

}

//Busqueda DFS
void grafo_DFS(Grafo g , Nodo* inicial){
    Nodo* aux = g.inicio;
    //Todos los nodos en estado NO_Visitado
    while (aux!= NULL) {
        aux->estado = NO_VISITADO;
        aux = aux->siguiente;
    }
    grafo_DFSrecursivo(g, g.inicio);
}

void grafo_DFSrecursivo(Grafo g, Nodo* inicial){
    //Nodo inicial EN_PROGRESO
    inicial->estado = EN_PROGRESO;
    //Para cada nodo ligado al inicial ejecutar DFS
    NodoAdyacencia* ady = inicial->inicio;
    while (ady != NULL) {
        if ((ady->destino->estado = NO_VISITADO)) {
            grafo_DFS(g, ady->destino);
            ady = ady->siguiente;
        }
        inicial->estado = VISITADO;
        printf("%d\t", inicial->dato);
    }
}

//Busqueda BFS
void grafo_BFS(Grafo g, Nodo inicial){
    Nodo* aux = g.inicio;
    while (aux != NULL) {
        aux->distancia = -1;
        aux->padre = NULL;
        aux = aux->siguiente;
    }
    
    inicial.distancia =0;
    Fila f = fila_crearFila();
    fila_enqueue(&f, &inicial);
    
        while(fila_estavacia(f) == 0){
            NodoFila *fu = fila_dequeue(&f);
            Nodo *u = fu->dato;
            NodoAdyacencia* ady = u->inicio;
            while (ady!= NULL) {
                if(ady->destino->padre == NULL){
                    fila_enqueue(&f, ady->destino);
                    ady->destino->padre = u;
                    ady->destino->distancia = u->distancia +1;
                }
                ady = ady->siguiente;
            }
            printf("%d\t", u->dato);
        }
    }







