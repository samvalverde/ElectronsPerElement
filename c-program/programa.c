#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ELEMENTS 100
#define MAX_NOMBRE 50
#define EULER 2.71828182845904523536028747135266249775724709369995

typedef struct {
    char nombre[MAX_NOMBRE];
    int numeroAtomico;
    int numeroNeutrones;
    double neutronesObtenidos;
    double redondeoCercano;
    double redondeoTruncado;
    double difNObtRC;               // numeroNeutrones - redondeoCercano
    double difNObtRT;               // numeroNeutrones - redondeoTruncado
} Element;

typedef struct {
    double A;
    double B;
    double C;
    double D;
    double E;
    double F;
} Variables;

typedef struct {
    double constantK;                        // constant k
    double constantA;                       // constant a
    double constantB;                        // constant b
} Constants;

void loadElements(Element elements[]) {
    FILE *archivo;
    char linea[100]; // Suficientemente grande para leer una línea del archivo
    int i = 0;

    archivo = fopen("elementos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%[^,], %d, %d", elements[i].nombre, &elements[i].numeroAtomico, &elements[i].numeroNeutrones);
        i++;
        if (i >= MAX_ELEMENTS) {
            break;
        }
    }

    fclose(archivo);
}

void calcVariables(Element elements[], Variables *variables){
    variables->A, variables->B, variables->C, variables->D, variables->E, variables->F = 0;
    for(int i = 1; i < MAX_ELEMENTS; i++){
        variables->B = variables->B + log(elements[i].numeroAtomico);
        variables->D = variables->D + (log(elements[i].numeroAtomico) * log(elements[i].numeroAtomico));
        variables->E = variables->E + log(elements[i].numeroNeutrones);
        variables->F = variables->F + (log(elements[i].numeroAtomico) * log(elements[i].numeroNeutrones));
    }
    variables->A = MAX_ELEMENTS;
    variables->C = variables->B;
}

void solveLinearSystem(Variables *variables, Constants *constants){
    float determinantEBFD = (variables->E * variables->D) - (variables->B * variables->F);
    float determinantAECF = (variables->A * variables->F) - (variables->E * variables->C);
    float determinantABCD = (variables->A * variables->D) - (variables->B * variables->C);
    constants->constantK = determinantEBFD/determinantABCD;
    constants->constantB = determinantAECF/determinantABCD;
}

void calcFunction(Element elements[], Variables *variables, Constants *constants){
    calcVariables(elements, variables);
    solveLinearSystem(variables, constants);
    constants->constantA = pow(EULER,constants->constantK);
}

void elementCalculations(Element *element, Constants *constants){
    element->neutronesObtenidos = (constants->constantA * pow(element->numeroAtomico,constants->constantB));
    element->redondeoCercano = round(element->neutronesObtenidos);
    element->redondeoTruncado = (int)element->neutronesObtenidos;
    element->difNObtRC = element->numeroNeutrones - element->redondeoCercano;
    element->difNObtRT = element->numeroNeutrones - element->redondeoTruncado;
}

void verifyFunction(Element elements[], Constants *constants){
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        elementCalculations(&elements[i], constants);
    }
}

void showElements(Element elements[], Variables *variables, Constants *constants){
    printf("\n");
    printf("CONSTANTS\n");
    printf("____________\n");
    printf("\n");
    printf("A: %.2f\n", variables->A);
    printf("B: %.2f\n", variables->B);
    printf("C: %.2f\n", variables->C);
    printf("D: %.2f\n", variables->D);
    printf("E: %.2f\n", variables->E);
    printf("F: %.2f\n", variables->F);
    printf("b: %.2f\n", constants->constantB);
    printf("k: %.2f\n", constants->constantK);
    printf("a: %.2f\n", constants->constantA);
    printf("____________\n");
    printf("\n");
    printf("\n");
    printf("RESULTS\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        printf("Nombre: %s\n", elements[i].nombre);
        printf("Numero Atomico: %d\n", elements[i].numeroAtomico);
        printf("Numero de Neutrones: %d\n", elements[i].numeroNeutrones);
        printf("Numero de Neutrones Obtenidos: %.2f\n", elements[i].neutronesObtenidos);
        printf("Redondeo Cercano: %f\n", elements[i].redondeoCercano);
        printf("Redondeo Truncado: %f\n", elements[i].redondeoTruncado);
        printf("Diferencia Neutrones-RC: %f\n", elements[i].difNObtRC);
        printf("Diferencia NeutronesRT: %f\n", elements[i].difNObtRT);
        printf("-----------------------------------------\n");
    }
}

int main() {
    printf("\n");
    printf("\n");
    printf("Instituto Tecnologico de Costa Rica\n");
    printf("IC4700 Lenguajes de Programacion\n");
    printf("Proyecto de Programacion 1\n");
    printf("Paradigma imperativo/procedimental\n");
    printf("\n");
    printf("Erick Kauffmann Porcar\n");
    printf("Samuel Valverde Arguedas\n");
    printf("\n");
    printf("\n");

    // Declarar un arreglo de estructuras Element
    Element elements[MAX_ELEMENTS];
    // Declara la estructura que almacena las variables
    Variables variables;
    // Declara la estructura que almacena las constantes
    Constants constants;

    // Llamar a la función para leer el archivo y guardar los elementos en el arreglo
    loadElements(elements);

    // Llamar función que calcula la Función de la Curva de Ajuste 
    calcFunction(elements, &variables, &constants);

    // Llamar función que verifica las diferencias de Neutrones Reales y Neutrones Obtenidos
    verifyFunction(elements, &constants);

    // Mostrar los elementos guardados en el arreglo
    showElements(elements, &variables, &constants);

    return 0;
}