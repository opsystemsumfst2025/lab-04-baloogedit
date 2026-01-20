#include <stdio.h>
#include <stdlib.h>

// Ez a program szandekosan tobb hibat tartalmaz
// Futtasd GDB-vel es Valgrind-dal, hogy megtalald oket!

void null_pointer_bug() {
    printf("\n--- 1. Hiba: NULL pointer dereference ---\n");
    
    int* ptr = NULL;
    
    // HIBA: NULL pointerre probalsz irni
    *ptr = 42;
    
    printf("Ha ez kiir, akkor nem volt segfault (furcsa...)\n");
}

void array_overflow_bug() {
    printf("\n--- 2. Hiba: Tomb tulinexeles ---\n");
    
    int array[10];
    
    // HIBA: A tomb 0-9 indexeket tartalmazza, nem 0-15!
    for (int i = 0; i <= 9; i++) {
        array[i] = i * 10;
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    printf("Ha ide eljutott, akkor nem volt segfault (meg...)\n");
}

void use_after_free_bug() {
    printf("\n--- 3. Hiba: Use after free ---\n");
    
    int* data = (int*)malloc(5 * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Malloc hiba\n");
        return;
    }
    
    // Feltoltjuk a tombot
    for (int i = 0; i < 5; i++) {
        data[i] = i + 100;
    }
    
    printf("Adatok: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    
    // Felszabaditjuk a memoriat
    free(data);
    printf("Memoria felszabaditva.\n");
    
    // HIBA: Mar felszabaditott memoriat hasznalunk!
    printf("Megprobaljuk hasznalni a felszabaditott memoriat...\n");
    for (int i = 0; i < 5; i++) {
        data[i] = i + 200;  // Use after free!
    }
    
    printf("Ha ide eljutott, akkor nem volt segfault (szerencses vagy)\n");
}

int main() {
    printf("Segmentation Fault Demonstracio\n");
    printf("================================\n");
    printf("\nFuttasd GDB-vel: gdb ./feladat_06\n");
    printf("Vagy Valgrind-dal: valgrind ./feladat_06\n");
    
    // Kommenteld ki az egyiket, hogy kulon-kulon teszteld a hibakat
    
    // 1. hiba: NULL pointer
    // null_pointer_bug();
    
    // 2. hiba: Tomb tulinexeles
    array_overflow_bug();
    
    // 3. hiba: Use after free
    // use_after_free_bug();
    
    printf("\nProgram vege.\n");
    return 0;
}
