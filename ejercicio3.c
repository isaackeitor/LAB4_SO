#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESOS 5
#define NUM_RECURSOS 3

// Matriz de asignación actual: recursos asignados a cada proceso
int asignados[NUM_PROCESOS][NUM_RECURSOS] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Matriz de máxima demanda de cada proceso
int maxima[NUM_PROCESOS][NUM_RECURSOS] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Recursos disponibles
int disponibles[NUM_RECURSOS] = {3, 3, 2};

// Función para calcular la necesidad de cada proceso
void calcularNecesidad(int necesidad[NUM_PROCESOS][NUM_RECURSOS]) {
    for (int i = 0; i < NUM_PROCESOS; i++) {
        for (int j = 0; j < NUM_RECURSOS; j++) {
            necesidad[i][j] = maxima[i][j] - asignados[i][j];
            printf("Necesidad[%d][%d] = %d\n", i, j, necesidad[i][j]);
        }
    }
}

// Función para verificar si el proceso puede ser satisfecho con los recursos disponibles
bool verificar(int proceso, int necesidad[NUM_PROCESOS][NUM_RECURSOS], int disponibles[]) {
    for (int j = 0; j < NUM_RECURSOS; j++) {
        if (necesidad[proceso][j] > disponibles[j]) {
            printf("No se puede satisfacer el proceso %d con los recursos disponibles.\n", proceso);
            return false;
        }
        printf("Disponibles[%d] = %d\n", j, disponibles[j]);
    }
    return true;
}

// Implementación del algoritmo del banquero
bool algoritmoDelBanquero() {
    int necesidad[NUM_PROCESOS][NUM_RECURSOS];
    calcularNecesidad(necesidad);

    bool terminado[NUM_PROCESOS] = {0};
    int trabajo[NUM_RECURSOS];
    for (int i = 0; i < NUM_RECURSOS; i++) {
        trabajo[i] = disponibles[i];
    }

    while (true) {
        bool encontrado = false;
        for (int i = 0; i < NUM_PROCESOS; i++) {
            if (!terminado[i] && verificar(i, necesidad, trabajo)) {
                for (int j = 0; j < NUM_RECURSOS; j++) {
                    trabajo[j] += asignados[i][j];
                }
                terminado[i] = true;
                encontrado = true;
                printf("Proceso %d satisfecho.\n", i);
            }
            printf("Proceso %d no satisfecho.\n", i);
        }

        if (!encontrado) {
            for (int i = 0; i < NUM_PROCESOS; i++) {
                if (!terminado[i]) {
                    return false; // No es seguro
                    printf("El estado no es seguro.\n");
                }
            }
            return true; // Es seguro
        }
        printf("El estado es seguro.\n");
    }
}

int main() {
    if (algoritmoDelBanquero()) {
        printf("El estado es seguro.\n");
    } else {
        printf("El estado no es seguro.\n");
    }
    return 0;
}
