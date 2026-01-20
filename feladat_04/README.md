# Feladat 04: Valgrind es Memory Leaks

## A tortenet

Kaptal egy kest programot, ami lefordul es le is fut. Minden jónak tunik.
De titokban **memoria szivargas** van benne - a program nem szabaditja fel az osszes memoriajat.

A te feladatod: detektiv vagy, es meg kell talalnod a bunelkovetoket (a memory leakeket).

## Mi az a memory leak?

Ha `malloc`-al foglalsz memoriait, de soha nem hivod meg ra a `free`-t, akkor az a memoria
"elveszett" - a program nem hasznaalja, de nem is adja vissza az operacios rendszernek.

Kis programokban ez nem problema. De egy szerver, ami napokig fut? Az osszeomlik.

## A feladat leirasa

1. Futtasd le a `buggy.c` programot normalisan:
   ```bash
   make feladat_04
   ./feladat_04
   ```
   Minden jonak tunik, igaz?

2. Most futtasd le Valgrind-dal:
   ```bash
   make valgrind_04
   # vagy
   valgrind --leak-check=full ./feladat_04
   ```

3. Olvasd el a Valgrind kimenetat. Azt fogja mondani:
   ```
   LEAK SUMMARY:
       definitely lost: X bytes in Y blocks
   ```

4. A Valgrind meg azt is megmondja, MELYIK SORBAN foglaltal memoriait, amit nem szabaditottal fel.

5. Nyisd meg a `buggy.c` fajlt es tedd bele a hianyzó `free()` hivatasokat.

6. Fordits ujra es futtasd ismet Valgrind-dal.

7. A cel: `All heap blocks were freed -- no leaks are possible`

## Amit megtanulsz

- Hogyan hasznald a Valgrind eszkott
- Hogyan ertelmezheted a memoria leak uzenetekett
- Hogy minden `malloc`-hoz kell egy `free`

## Valgrind kimenet ertelmezese

```
==12345== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12345==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/...)
==12345==    by 0x108A: create_person (buggy.c:15)
==12345==    by 0x10C2: main (buggy.c:28)
```

Ez azt jelenti:
- **40 bytes** veszett el
- A `malloc` hivatas a **buggy.c 15. soraban** tortent
- Amit a `main` hivott meg a **28. sorbol**

Menj a 15. sorra, nezd meg mit foglaltal, es keresd meg, hol kellene `free`-zni!

## Forditás és futtatás

```bash
make feladat_04       # Normalis forditas
./feladat_04          # Normalis futtatás

make valgrind_04      # Valgrind futtatás
```

## Tanulsag

A Valgrind olyan, mint egy rontgen - latja a programa belso memoria problemait.
Hasznald mindig, amikor dinamikus memoriait kezelsz!
