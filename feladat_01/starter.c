#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Globalis bankszamla egyenleg
int balance = 0;

// TODO: Definiald a szalak szamat (10)
#define NUM_THREADS ???

// TODO: Definiald, hogy hanyszor noveljen minden szal (1000)
#define INCREMENTS_PER_THREAD ???

// A szal fuggveny, amit minden szal vegre fog hajtatni
void* deposit_money(void* arg) {
    // TODO: Irj egy ciklust, ami INCREMENTS_PER_THREAD-szer fut
    // TODO: Minden iteracioban noveld a balance valtozot egyel
    
    return NULL;
}

int main() {
    // TODO: Hozz letre egy pthread_t tombot NUM_THREADS meretu elemmel
    
    printf("Kezdeti egyenleg: %d dollar\n", balance);
    printf("Inditas: %d penztaros, mindegyik %d dollar befizetesevel...\n", 
           NUM_THREADS, INCREMENTS_PER_THREAD);
    
    // TODO: Inditsd el a szalakat egy ciklussal
    // Hasznald a pthread_create fuggvenyt
    // pthread_create(&threads[i], NULL, deposit_money, NULL);
    
    // TODO: Vard meg, hogy minden szal befejeződjon
    // Hasznald a pthread_join fuggvenyt
    
    printf("Vegso egyenleg: %d dollar\n", balance);
    printf("Vart egyenleg: %d dollar\n", NUM_THREADS * INCREMENTS_PER_THREAD);
    
    if (balance != NUM_THREADS * INCREMENTS_PER_THREAD) {
        printf("\nADATVESZTES TORTENT! Ez egy race condition.\n");
    } else {
        printf("\nSzerencses vagy - ezuttal jo lett az eredmeny.\n");
        printf("De ez nem jelenti, hogy a kod helyes!\n");
    }
    
    return 0;
}
