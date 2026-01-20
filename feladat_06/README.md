# Feladat 06: Segmentation Fault Vadaszat

## A tortenet

A leggyakoribb hiba, amit C-ben latsz: **Segmentation fault (core dumped)**

Ez azt jelenti: hibas memoriacimre probaltal irni vagy olvasni.
Lehet tul nagy index, lehet felszabaditott memoria hasznalata, lehet NULL pointer.

A te feladatod: szandekosan okozz ilyen hibakat, aztan derítsd fel oket debuggerrel.

## Mi az a Segmentation Fault?

A processzor vedte a memoriait. Ha olyan cimre probaltal hozzaferni, amihez nincs jogod:
- NULL pointer dereference
- Tömb tulinexeles
- Felszabaditott memoria hasznalata (use-after-free)
- Stack overflow

Az operacios rendszer leallitja a programot.

## A feladat leirasa

A `buggy.c` fajl harom kulonbozo hibatipust tartalmaz.
Mindharom segfaultot okoz, de mas-mas okbol.

### 1. resz: Futtasd a programot

```bash
make feladat_06
./feladat_06
```

Biztos, hogy segfault lesz. De melyik sorban?

### 2. resz: GDB hasznalata

```bash
gdb ./feladat_06
(gdb) run
```

A program osszeomlott. Most ird be:
```
(gdb) backtrace
```

Ez megmutatja, HOVA jutott el a program az osszeomlaskor.

```
(gdb) print i
(gdb) print array
```

Ezzel megnezed a valtozok erteket.

### 3. resz: Valgrind hasznalata

```bash
valgrind ./feladat_06
```

Valgrind pontosabban megmondja, mi a problema:
- Invalid write (rossz helyre irsz)
- Invalid read (rossz helyrol olvasol)
- Use after free (mar felszabaditott memoriat hasznalod)

### 4. resz: Javitsd ki!

A kod szandekosan hibas. Nezd meg, mik a hibak, es javitsd ki oket.

## Hiba tipusok a kodban

A `buggy.c` tartalmazza ezeket a problémákat:

1. **NULL pointer dereference** - NULL-ra mutato pointeren keresztul probalsz irni
2. **Tul nagy tomb index** - 10 elemu tomb 15. elemere probalz irni
3. **Use after free** - Felszabaditott memoriat hasznalsz

## GDB alapparancsok

```
gdb ./program          # GDB inditasa
(gdb) run              # Program futtatasa
(gdb) backtrace        # Stack trace (hol tortent a hiba)
(gdb) frame 0          # Ugras a stack frame-re
(gdb) print valtozo    # Valtozo ertekenek kiirasa
(gdb) list             # Kod megtekintese
(gdb) quit             # Kilepes
```

## Forditás és futtatás

```bash
make feladat_06        # Forditas
./feladat_06           # Futtatás (segfault var!)

gdb ./feladat_06       # Debugger inditasa
valgrind ./feladat_06  # Valgrind elemzes
```

## Tanulsag

1. **Segfault nem random** - mindig van oka
2. **GDB a barat** - megmondja, melyik sorban tortent a hiba
3. **Valgrind tobb mint memory leak detektor** - megtalaljaa memoria hozzaferesi hibakat is

A vizsgan es projektben ezek az eszkozok elengedhetetlenek lesznek!
