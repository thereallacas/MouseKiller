#ifndef TABLA_H_INCLUDED
#define TABLA_H_INCLUDED

/** A jatekos struktura a jatekos adatait tartalmazza */
typedef struct jatekos{
    /** a jatekos neve (max 50 elemu karaktertomb) */
    char nev[50];
    /** a jatekos elert pontszama */
    int point;
    /** pointer a lancolt listahoz */
    struct jatekos *kov;
}jatekos;

/** A jatekosok listajanak felszabaditasara szolgalo fuggveny, amely ugyanazon az
 * alapon mukodik, mint a lyukak listajanak felszabaditasat vegzo fuggveny,
 * tehat rekurziot hasznal.
 * @param head jatekos tipusu pointer amely a lista kezdoelemere mutat.
 */
void freelistaj(jatekos *head);


#endif // TABLA_H_INCLUDED
