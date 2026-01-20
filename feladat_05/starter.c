#include <stdio.h>
#include <stdlib.h>

int main() {
    // TODO: Hozz letre egy dinamikus int tombot 2 elem merettel
    // int* data = malloc(...);
    
    int capacity = 2;  // Jelenlegi kapacitas
    int size = 0;      // Jelenleg hany elem van benne
    int* data = (int*)malloc(capacity * sizeof(int));    

    // TODO: Ellenorizd, hogy a malloc sikeres volt-e
    if (data == NULL) {
        perror("malloc");
        return 1;
    }    


    printf("Dinamikus tomb (kezdeti kapacitas: %d)\n", capacity);
    printf("Irj be szamokat (0 = vege):\n");
    
    while (1) {
        int number;
        printf("> ");
        if (scanf("%d", &number) != 1) {
            printf("Hibas bemenet!\n");
            break;
        }
        
        if (number == 0) {
            break;  // Vege a bevitelnek
        }
        
        // TODO: Ha a tomb betelt (size == capacity), duplázzuk a meretet
        // FONTOS: Hasznald a helyes realloc mintát!
        // int* temp = realloc(data, new_capacity * sizeof(int));
        // if (temp == NULL) { ... }
        // data = temp;
        // capacity = new_capacity;
        if (size == capacity) {
            int new_capacity = capacity * 2;
            printf("  -> Betelt! Bővítés: %d -> %d\n", capacity, new_capacity);
            
            // FONTOS: Mindig ideiglenes változót használj a realloc-hoz!
            // Ha a realloc elbukik (NULL), az eredeti adat (data) nem veszik el.
            int* temp = (int*)realloc(data, new_capacity * sizeof(int));
            
            if (temp == NULL) {
                printf("Memória hiba! Nem sikerült bővíteni.\n");
                free(data); // Az eredetit felszabadítjuk
                return 1;
            }
            
            data = temp;       // Sikeres volt, átvesszük az új címet
            capacity = new_capacity; // Frissítjük a kapacitást
        }


        
        // TODO: Add hozza a szamot a tombhoz
        data[size] = number;
        size++;
    }
    
    // Kiirjuk az eredmenyt
    printf("\nBeirt szamok (%d db): ", size);
    // TODO: Irj egy ciklust, ami kiirja az osszes szamot
    printf("\nBeirt szamok (%d db): ", size);
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    

    // TODO: Szabaditsd fel a memoriat!
    free(data);

    
    return 0;
}
