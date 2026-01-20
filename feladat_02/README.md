# Feladat 02: Mutex Vedelem

## A tortenet

Az elozo feladatban lattuk, hogy a race condition adatveszteshez vezet.
Most megoldjuk a problemat egy **mutex** (mutual exclusion) hasznalataval.

A mutex olyan, mint egy kulcs egy ajtohoz: csak az a szal ferhet hozza a kozos eroforrashoz,
amelyik eppen birtokolja a kulcsot. Mig egy szal bent van, a tobbit varnia kell.

## Feladat leirasa

Egeszitsd ki az elozo feladat kodjat mutex vedelmmel:

1. Hozz letre egy globalis `pthread_mutex_t` valtozot
2. Inicializald a mutexet a `pthread_mutex_init` fuggvennyel (vagy hasznald a `PTHREAD_MUTEX_INITIALIZER` makrot)
3. Minden szalban, **kozvetlenul a balance novelese elott**, zarold a mutexet (`pthread_mutex_lock`)
4. Minden szalban, **kozvetlenul a balance novelese utan**, oldsd fel a mutexet (`pthread_mutex_unlock`)
5. A program vegen szuntetsd meg a mutexet (`pthread_mutex_destroy`)

## Vart eredmeny

Most mar **mindig** pontosan 10,000 dollar lesz az eredmeny, fuggetlenul attol, hanyszor futtatod.

## Mit fogsz eszrevenni?

A program **lassabb** lesz, mint az elozo (verdelme). Miert?

Mert minden szalnak varnia kell a tobbi szalra. Nem tudnak tenylegesen parhuzamosan futni,
mert egymasra kell varniuk a mutex miatt. Ez a **szinkronizacio koltsege**.

## A mutex hasznalat szabalyai

1. **Mindig unlock-old, amit lock-oltal** - kulonben deadlock lesz
2. **Tartsad a lockot a leheto legrovidebbig** - ne csinalj lassu muveleteket lockolt szakaszban
3. **Vedd mindig ugyanabban a sorrendben a lockokat** - ha tobb mutexed van

## Forditás és futtatás

```bash
make feladat_02
./feladat_02
```

Futtasd tobbszor - most mar mindig ugyanaz az eredmeny lesz!

## Kiegeszito kiserlet

Ha van idod, probald ki:
- Tedd a lock-ot a cikluson KIVULRE (egy nagy lock az osszes 1000 novelesre)
- Figyeld meg, hogy meg lassabb lesz, de meg mindig helyes
- Ez azt mutatja: minél tovabb tartod a lockot, annal lassabb, de annal biztonsagosabb
