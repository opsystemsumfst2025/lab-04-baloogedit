#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 10000000
#define NUM_THREADS 4

// Globalis tomb
int* array = NULL;

// Globalis flag: melyik pozicion talaltuk a -1-et
int found_at = -1;

// TODO: Deklaralj egy mutexet a found_at vedelmere
pthread_mutex_t mutex;

// Struktura a szalak parametereinek atadasahoz
typedef struct {
    int thread_id;
    int start_index;
    int end_index;
} ThreadData;

// A kereses fuggveny, amit minden szal vegrehajt
void* search_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    printf("Szal %d megkezdte a keresest: %d - %d\n", 
           data->thread_id, data->start_index, data->end_index);
    
    // TODO: Irj egy ciklust data->start_index-tol data->end_index-ig
    // TODO: Minden iteracioban ellenorizd:
    //       1. Megtalaltam mar a -1-et? (ellenorizd a found_at flaget mutex-al)
    //       2. Ha igen, lepj ki a ciklusbol (break)
    //       3. Ha nem, vizsgald meg az aktualis elemet
    //       4. Ha az aktualis elem -1, zarold a mutexet, allitsd be a found_at-ot, oldsd fel a mutexet
    
    // TIPP: Optimalizalas miatt ne minden iteracioban ellenorizd a flaget,
    //       hanem csak minden 10000. elemnel
    
    for (int i=data->start_index; i < data->end_index; i++)
    {
        if(i % 1000 == 0)
        {
            pthread_mutex_lock(&mutex);
            if(found_at != -1)
            {
                pthread_mutex_unlock(&mutex);
                break;
            }
            pthread_mutex_unlock(&mutex);
        }
        if (array[i] == -1) {
            pthread_mutex_lock(&mutex);
            // Még egyszer ellenőrizzük, nem előztek-e meg
            if (found_at == -1) {
                found_at = i;
                printf("--- Szal %d TALALT: pozicio %d ---\n", data->thread_id, i);
            }
            pthread_mutex_unlock(&mutex);
            break; // Kilépünk a ciklusból
        }
    }





    return NULL;
}

int main() {
    srand(time(NULL));
    
    // Tomb letrehozasa
    array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        perror("malloc");
        exit(1);
    }
    
    printf("Tomb generalasa: %d elem...\n", ARRAY_SIZE);
    
    // Tomb feltoltese veletlen szamokkal
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;
    }
    
    // Egy veletlen helyre betesszuk a -1-et
    int target_position = rand() % ARRAY_SIZE;
    array[target_position] = -1;
    printf("A -1 elhelyezve a(z) %d. pozicion\n\n", target_position);
    
    // TODO: Inicializald a mutexet
    pthread_mutex_init(&mutex, NULL);

    
    printf("Kereses %d szallal...\n", NUM_THREADS);
    
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    
    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    
    // TODO: Inditsd el a szalakat
    // Minden szal egy chunk_size meretu reszletett fog keresni
    // thread_data[i].thread_id = i;
    // thread_data[i].start_index = i * chunk_size;
    // thread_data[i].end_index = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunk_size;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].start_index = i * chunk_size;
        
        // Az utolsó szál kapja a maradékot is (ha nem osztható pontosan)
        if (i == NUM_THREADS - 1)
            {
                thread_data[i].end_index = ARRAY_SIZE;
            }
        else
            {
                thread_data[i].end_index = (i + 1) * chunk_size;
            }

        if (pthread_create(&threads[i], NULL, search_thread, &thread_data[i]) != 0)
            {
                perror("pthread_create");
                exit(1);
            }
    }

    
    // TODO: Vard meg a szalakat
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    
    // TODO: Szuntessed meg a mutexet
    pthread_mutex_destroy(&mutex);


    
    printf("\nKereses befejezve.\n");
    
    if (found_at != -1) {
        printf("Talalt pozicio: %d\n", found_at);
        printf("Ellenorzes: array[%d] = %d ", found_at, array[found_at]);
        if (array[found_at] == -1) {
            printf("✓\n");
        } else {
            printf("✗ HIBA!\n");
        }
    } else {
        printf("Nem talaltuk meg a -1-et! (Ez nem kellene, hogy megtortenjen)\n");
    }
    
    free(array);
    return 0;
}
