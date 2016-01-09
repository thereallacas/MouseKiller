#ifndef EGER_H_INCLUDED
#define EGER_H_INCLUDED

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/**Sugar a sajtlyukakhoz...*/
extern int LYUKSUGAR;
/**Sugar a sajtlyukak korvonalahoz*/
extern int KORVONALSUGAR;

/**eletkocka...*/
extern int HEALTHSQUARE;

/**maximum egeszseg beallitasa*/
extern int MAXHEALTH;

/**Szinek hexadecimalis formatumban*/
typedef enum{
/**A sajt szine*/
SAJTSZIN=0xFFEC8BFF,
/**A lyuk szine*/
LYUKSZIN=0xFFDF3FFF,
/**Az egeszseges zold szin az eletcsikhoz*/
HEALTHGREEN=0xADFF2FFF,
/**A sarga szin az eletcsikhoz*/
HEALTHYELLOW=0xFFEB43FF,
/**A piros nem jelent jot az eletcsikon*/
HEALTHRED=0xD11919FF
}szinek;

/**A jatekter meretei*/
typedef enum{
/**Jatekter magassaga...*/
JMAGASSAG=400,
/**Jatekter szelessege*/
JSZELESSEG=500
}Jatekter;

/**A jatekban levo adatfelulet meretei (jobb oldalt)*/
typedef enum{
/**Adatfelulet magassaga*/
AMAGASSAG=400,
/**Adatfelulet szelessege*/
ASZELESSEG=300
}Adatok;

/**Altalanos betumeret*/
typedef enum{
/**a betu merete*/
FONTSIZE=30
}Betumeret;

/**A kepernyo meretei*/
typedef enum {
/**A kepernyo magassaga*/
KMAGASSAG=400,
/**A kepernyo szelessege*/
KSZELESSEG=800
}Kepernyo;

/**Fontos enumeracio a jatek allapotainak jelzesere*/
typedef enum {
/**A "menu" allapot*/
menu,
/**A "jatek" allapot*/
game,
/**A dicsosegtabla bevitelt lehetove tevo moduljat jelzo allapot*/
highscore,
/**A dicsosegtabla megjelenitese*/
hsdisplay,
/**Hogyan játsszunk?*/
howtoplay,
/**Creadits*/
spec
}status;

/**A fokepernyo pointere, amit hasznaluk*/
extern SDL_Surface *screen;
/**A fomenuben es az egyeb szovegeknel altalaban hasznalt betutipus - amugy StencilStd.otf*/
extern TTF_Font *betutipus;
/**A cimnel es a dicsosegtablanal hasznalt vagany betutipus - ingyenesen felhasznalhato, mint a tobbi is*/
extern TTF_Font *betutipus2;
/**Az adatbevitelhez hasznalhato futurisztikus betutipus*/
extern TTF_Font *betutipus3;
/**A betutipus 2 kisebb meretben*/
extern TTF_Font *betutipus4;

/**Van olyan fuggveny ami csak RGBA szinmegadast engedelyez - erre vannak ezek deklaralva,
 * a nevuk alapjan egyertelmu mi lesz bennuk (FEHER)*/
extern SDL_Color WHITE;
/**A sajttomb sargajaval egyezo sarga*/
extern SDL_Color YELLOW;
/**FEKETE*/
extern SDL_Color BLACK;

/**Kiir az adott betutipussal egy adott szoveget. Itt sincs kivetelesen szukseg az
 * SDL_Flip-re, mert UpdateRect-et hasznal a fuggveny.
 * @param cel SDL_Surface pointer, a celteruletre mutat
 * @param celx A szoveg poziciojanak x koordinataja
 * @param cely A szoveg poziciojanak y koordinataja
 * @param szoveg A kiirando szoveg
 * @param betutipus A falhasznalando betutipusre mutato pointer (TTF_Font *)
 * @param szin A felhasznalando szin (RGBA)
 */
void TTF_KIIR(SDL_Surface *cel, int celx, int cely, char* szoveg, TTF_Font *betutipus, SDL_Color szin);

/**Letakaritja a kepernyot, egy fekete doboz kirajzolasaval. Mivel az SDL_Flip-et is
 * meghivja, ezert nincs szuksegunk semmi masra, csak a celparametert kell megadni
 * @param screen SDL_Surface tipusu pointer ami a celteruletre mutat
 */
void CLRSCR(SDL_Surface *screen);

#endif // EGER_H_INCLUDED
