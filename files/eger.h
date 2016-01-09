#ifndef EGER_H_INCLUDED
#define EGER_H_INCLUDED

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/*globalis konstansokat adunk meg...sugarakat...*/
#define LYUKSUGAR 40
#define KORVONALSUGAR 40

/*eletkockat...*/
#define HEALTHSQUARE 25

/*maximum egeszseget*/
#define MAXHEALTH 6

typedef enum{
/*...es szineket.*/
SAJTSZIN=0xFFEC8BFF,
LYUKSZIN=0xFFDF3FFF,
HEALTHGREEN=0xADFF2FFF,
HEALTHYELLOW=0xFFEB43FF,
HEALTHRED=0xD11919FF
}szinek;

/*meretek*/
typedef enum{
JMAGASSAG=400,
JSZELESSEG=500
}Jatekter;

typedef enum{
AMAGASSAG=400,
ASZELESSEG=300
}Adatok;

typedef enum{
FONTSIZE=30
}Betumeret;

typedef enum {
KMAGASSAG=400,
KSZELESSEG=800
}Kepernyo;

typedef enum {
menu, game, highscore, hsdisplay
}status;

extern SDL_Surface *screen;
extern TTF_Font *betutipus;
extern TTF_Font *betutipus2;
extern TTF_Font *betutipus3;

extern SDL_Color WHITE;
extern SDL_Color GREEN;
extern SDL_Color YELLOW;
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
