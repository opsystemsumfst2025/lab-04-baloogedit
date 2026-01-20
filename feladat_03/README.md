# Feladat 03: Parhuzamos Kereses

## A tortenet

Van egy hatalmas tomb tele veetlen szamokkal (10 millio elem).
Meg kell talalnod benne a **-1** erteket (ami csak egyszer fordul elo).

Egy szallal ez sokig tartana. 4 szallal viszont elmeletileg 4-szer gyorsabb lehet!

## Feladat leirasa

Irj egy programot, amely:

1. Letrehoz egy 10 millio elemu tombot es feltolti veletlen szamokkal (0-999)
2. Elhelyez pontosan egy darab **-1** erteket a tombben egy veletlen pozicion
3. Elindit 4 szalat, mindegyik a tomb egy negyedet kutatja:
   - 0. szal: 0 - 2,499,999
   - 1. szal: 2,500,000 - 4,999,999
   - 2. szal: 5,000,000 - 7,499,999
   - 3. szal: 7,500,000 - 9,999,999
4. Ha egy szal megtalalta a -1-et, tarolja el a poziciot es **jelezze a tobbi szalnak**, hogy fejezzek be

## A nehezites

Az igazi kihivas: ha az egyik szal megtalalta a szamot, **a tobbinak le kell allnia**.

Megoldasok:
- Egy globalis `int found_at = -1` valtozo (kezdeti ertek: nincs meg)
- Minden szal minden iteracioban ellenorzi ezt a flaget
- Ha valaki talalt, beallitja, es a tobbi szal leall

## Amit meg kell oldanod

1. **Szalak koordinacioja**: Hogyan mondod meg a tobbi szalnak, hogy alljanak le?
2. **Mutex vedelem**: A `found_at` valtozot VEDENI KELL, kulonben race condition lesz
3. **Hatekonyag**: Ne ellenorrizd minden iteracioban a flaget, csak peldaul minden 10000. elemnel

## Optimalizalas

Ha nagyon gyors akarsz lenni, kiprobalhatsz mas megkozeliteseket:
- Egy `volatile int found` flag mutex nelkul (nem 100% helyes, de gyors)
- Atomic valtozok hasznalata (`stdatomic.h`)

## Forditás és futtatás

```bash
make feladat_03
./feladat_03
```

## Vart kimenet

```
Tomb generalasa: 10000000 elem...
Kereses 4 szallal...
Szal 0 megkezdte a keresest: 0 - 2499999
Szal 1 megkezdte a keresest: 2500000 - 4999999
Szal 2 megkezdte a keresest: 5000000 - 7499999
Szal 3 megkezdte a keresest: 7500000 - 9999999

Szal 2 TALALT: pozicio 6543210
Tobbi szal leallitasa...

Kereses befejezve. Talalt pozicio: 6543210
Ellenorzes: array[6543210] = -1 ✓
```

## Tanulsag

Ez a feladat megmutatja:
- Hogyan lehet nagy adathalmazt felosztani szalak kozott
- Hogyan lehet koordinalni a szalakat egy kozos cel erdekeben
- Hogy a parhuzamositasnak van kommunikacios koltsege
