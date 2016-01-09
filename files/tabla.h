#ifndef TABLA_H_INCLUDED
#define TABLA_H_INCLUDED

/** A jatekos struktura a jatekos adatait tartalmazza */
typedef struct jatekos{
    /** a jatekos neve (max 50 elem� karaktertomb) */
    char nev[50];
    /** a jatekos elert pontszama */
    int point;
    /** pointer a lancolt listahoz */
    struct jatekos *kov;
}jatekos;

/** A jatekosok listajanak felszabaditasara szolgalo fuggveny, amely ugyanazon az
 * alapon m�kodik, mint a lyukak listajanak felszabaditasat vegz� fuggveny,
 * tehat rekurziot hasznal.
 * @param head jatekos tipusu pointer amely a lista kezd�elemere mutat.
 */
void freelistaj(jatekos *head);


#endif // TABLA_H_INCLUDED
