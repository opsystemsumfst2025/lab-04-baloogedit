# Feladat 05: Dinamikus Tomb es Realloc

## A tortenet

Egy naplo rendszert irsz, ami szamokat tarol. A problema: NEM tudod elore, hany szam jon.

Kezded egy kis 2 elemu tombbel. Ahogy toobb adat jon, meg kell novelned a tomb meretet.
Ehhez a `realloc()` fuggvenyt kell hasznalni.

## Mi az a realloc?

A `realloc()` atmeretezi a mar foglalt memoriat. Peldaul:
- Van egy 2 elemu tomob (8 byte)
- Meghivod: `realloc(ptr, 16)` - most mar 4 elemnek van hely
- A `realloc` LEHET, hogy ugyanott hagyja a memoriat, de LEHET, hogy atmasolja mashova

## A VESZELYES csapda

Sok kezdo (es AI is!) ezt irja:

```c
ptr = realloc(ptr, new_size);  // HIBAS!
```

Mi a problema? Ha a `realloc` ELBUKIK (nincs eleg memoria), NULL-t ad vissza.
Ilyenkor a `ptr` NULL lesz, es az eredeti memoriacim ELVESZETT - memory leak!

## A HELYES minta

```c
int* temp = realloc(ptr, new_size);
if (temp == NULL) {
    // Hiba tortent - de a ptr meg mindig ervenyes!
    free(ptr);
    return;
}
ptr = temp;  // Csak sikeres realloc utan frissitjuk a ptr-t
```

## A feladat leirasa

Irj egy programot, amely:

1. Letrehoz egy 2 elemu dinamikus `int` tombot
2. Egy vegtelen ciklusban beolvas szamokat a billentyuzetrol (0 = vege)
3. Ha a tomb betelt, megduplazza a meretet `realloc`-al
4. A program vegen kiirja az osszes beirt szamot
5. Felszabaditja a memoriat

## Reszletes lepesek

1. `int* data = malloc(2 * sizeof(int));` - kezdeti tomb
2. `int capacity = 2;` - mennyi fér bele
3. `int size = 0;` - mennyi van benne
4. Ciklus:
   - Beolvas egy szamot
   - Ha `size == capacity`, realloc dupla meretre
   - Hozzaadja a szamot a tombhoz

## Amit ellenorizni kell

- Van hiba ellenorzes minden `malloc` es `realloc` utan?
- A `realloc` helyes mintajat hasznalod?
- Minden foglalt memoria fel van szabaditva?
- Valgrind mit mond: `make valgrind_05`

## Forditás és futtatás

```bash
make feladat_05
./feladat_05
```

Pelda bemenet:
```
10
20
30
40
50
0
```

Vart kimenet:
```
Kapacitas novel: 2 -> 4
Kapacitas novel: 4 -> 8
Beirt szamok: 10 20 30 40 50
```

## Bonus kihivas

Mi tortenik, ha a `realloc` elbukik? Probald szimulalni:
- Kerts hihetetlen nagy tombot (100 millio elem)
- Ellenorizd, hogy a kod helyesen kezeli a hibat
- A regi memoria ne vesszen el!

## Tanulsag

A `realloc` hatekony, de veszelyes.
Mindig ellenorizd a visszateresi erteket, es hasznalj ideiglenes valtozot!
