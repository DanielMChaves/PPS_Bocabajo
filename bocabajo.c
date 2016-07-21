#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

/* Creamos nuestro tipo Pila */

typedef struct elementoLista {
    char* dato;
    struct elementoLista *siguiente;
} pila;

/* Metodo APILAR */

void apilar (pila **pil, char* cadena) {
    
    pila *nuevo;

    /* Crear un nodo nuevo */
    nuevo = malloc(sizeof(pila));
    nuevo->dato = strdup(cadena);
   
    /* Añadimos el nuevo nodo en la pila */
    nuevo->siguiente = *pil;

    /* El comienzo de nuestra pila es el nuevo nodo */
    *pil = nuevo;
}

/* Metodo DESAPILAR */

char* desapilar (pila **pil) {

    /* variable auxiliar para manipular el nodo */
    pila *nodo;
    /* variable auxiliar para retornar el elemento a extraer */
    char* cadena;
   
    /* Nodo apunta al primer elemento de la pila */
    nodo = *pil;

    /* Asignamos a pila todos los elementos menos la cima */
    *pil = nodo->siguiente;

    /* Guardamos el valor de retorno en cadena */
    cadena = nodo->dato; 

    /* Borrar el nodo */
    free (nodo);
    return cadena;
}

int main (int argc, char *argv[]) {

        /* Declaracion de Variables */
        int i;
        int contador = 0;
        FILE *archivo;
        char lineas[2048];
        pila *cima = NULL;

        /* Caso de Salida Estandar */
        if(argv[0] != NULL && argv[1] == NULL){

            /* Bucle para meter las lineas en la pila */
            for(i = 0; fgets(lineas, 2048, stdin) != NULL; i++){
                apilar(&cima, lineas);
            }

            /* Bucle para sacar las cosas de la pila */
            for(contador = i; contador > 0; contador--){
                printf(desapilar(&cima));
            }
            
            exit(EX_OK);
        }

        /* Caso de -h y --help */
        else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf ("bocabajo: Uso: bocabajo [ fichero... ]\n");
            printf ("bocabajo: Invierte el orden de las lineas de los ficheros (o de la entrada).\n");
        }

        /* Caso de Ficheros */
        else {

            /* Bucle para abrir cada fichero */
            for (i = 1; i < argc; i++){

                /* Abrimos el archivo */
                archivo = fopen(argv[i], "r");

                if(archivo == NULL){
                    fprintf(stderr, "bocabajo: Error(EX_NOINPUT), fallo en el parámetro de entrada. \"Success\"\n");
                    fprintf(stderr, "bocabajo+ El fichero \"%s\" no puede ser ledo.\n", argv[i]);
                    exit(EX_NOINPUT);
                }

                else{

                    /* Bucle para meter las lineas en la pila */
                    while(fgets(lineas, 2048, archivo) != NULL){
                        apilar(&cima, lineas);
                        contador++;
                    }

                }

                /* Cerramos el archivo */
                fclose(archivo);

            }

            /* Bucle para sacar las cosas de la pila */
            for(;contador > 0; contador--){
                printf(desapilar(&cima));
            }

            exit(EX_OK);
        }

        return EX_OK;
}

