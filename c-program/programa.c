#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 100
#define MAX_NOMBRE 50

typedef struct {
    char nombre[MAX_NOMBRE];
    int numeroAtomico;
    int numeroNeutrones;
    float neutronesObtenidos;
    float redondeoCercano;
    float redondeoTruncado;
    float resultado1;               // numeroNeutrones - redondeoCercano
    float resultado2;               // numeroNeutrones - redondeoTruncado
} Elemento;

void loadElements(Elemento elementos[]) {
    FILE *archivo;
    char linea[100]; // Suficientemente grande para leer una línea del archivo
    int i = 0;

    archivo = fopen("elementos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%[^,], %d, %d", elementos[i].nombre, &elementos[i].numeroAtomico, &elementos[i].numeroNeutrones);
        i++;
        if (i >= MAX_ELEMENTOS) {
            break;
        }
    }

    fclose(archivo);
}

int main() {
    // Declarar un arreglo de estructuras Elemento
    Elemento elementos[MAX_ELEMENTOS];

    // Llamar a la función para leer el archivo y guardar los elementos en el arreglo
    loadElements(elementos);

    // Mostrar los elementos guardados en el arreglo (solo para verificar)
    for (int i = 0; i < MAX_ELEMENTOS; i++) {
        printf("Nombre: %s, Número Atómico: %d, Número de Neutrones: %d\n", elementos[i].nombre, elementos[i].numeroAtomico, elementos[i].numeroNeutrones);
    }

    return 0;
}