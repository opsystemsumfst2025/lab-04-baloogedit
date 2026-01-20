# Feladat 01: Race Condition Demonstralas

## A tortenet

Van egy kozos bankszamlank, amelynek egyenlege 0 dollarra all be induaskor.
A bank 10 penztarosa (mindegyik egy kulon szal) egyszerre akar befizetni penzt a szamlara.
Minden penztaros 1000 dollaart fizet be, egyenként 1 dollaros reszletekben (1000 tranzakcio).

## Feladat leirasa

Irj egy C programot, amely:

1. Letrehoz egy globalis `int balance = 0` valtozot
2. Elindit 10 szalat a `pthread_create` fuggveny hasznalataval
3. Minden szal egy ciklusban 1000-szer noveli a `balance` valtozot egyel
4. A program megvarjaa, hogy minden szal befejezodjon (`pthread_join`)
5. Kiirja a vegeredmenyt

## Vart eredmeny

Mivel 10 szal mindegyike 1000-szer noval, a vart eredmeny: **10,000 dollar**

## A valosag

Ha eleg gyorsan fut a program es tobb CPU magod van, valoszinuleg NEM 10,000 lesz az eredmeny.
Lehet 9,870, lehet 9,950, lehet 9,234 - minden futassal mas.

## Miert tortenik ez?

Ez egy **race condition**. Amikor tobb szal egyidoben probablja meg ugyanazt a valtozot novelni, a kovetkezo tortenik:

```
Szal A: beolvassa balance erteket (pl. 100)
Szal B: beolvassa balance erteket (100)  <- meg mindig 100, mert A meg nem irta vissza
Szal A: hozzaad 1-et (101) es visszairja
Szal B: hozzaad 1-et (101) es visszairja  <- felulirja A munkajat!
```

Eredmeny: 2 szal dolgozott, de csak 1-gyel nott a balance (100 -> 101 helyett 100 -> 102).

## Tanulsag

A parhuzamos iras kulonleges vedelem nelkul adatveszteshez vezet.
A kovetkezo feladatban megoldjuk ezt a problemat.

## Forditás és futtatás

```bash
make feladat_01
./feladat_01
```

Futtasd tobbszor es figyeld meg, hogy kulonbozo eredmenyeket kapsz!
