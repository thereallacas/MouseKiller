#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED

/**A lyuk struktura egy lyuk adatait tartalmazza. A lyukak, csakugy mint a
 * jatekosok, lancolt listaba vannak szervezve*/
typedef struct lyuk{
    /**A lyuk koordinatai - integer tipus*/
    int x, y;
    /**A lyuk sugara*/
    int r;
    /**korvonal: Az antialiasing miatt!*/
    int kr;
    /**Pointer a lancolt listahoz*/
    struct lyuk *kov;
}lyuk;

/**A possiblepos (lehetseges helyek) egy olyan struktura, amely
 * egy koordinatapart tartalmaz*/
typedef struct possiblepos{
    /**A pozicio x es y koordinataja*/
    int x, y;
}pp;

/**Ez a struktura az egerek felbukkkanasanak SDL_Timer -ehez valo visszateresi
 * idõ veletlenszerû generalasahoz szukseges. Also es felsõ korlatot szab a
 * rand() fuggvenynek.*/
typedef struct IDOK{
    /**rand()%MAXIDO+MINIDO -> MINIDO es MAXIDO a ket korlat. */
    int MINIDO, MAXIDO;
}IDOK;

#endif // JATEK_H_INCLUDED
