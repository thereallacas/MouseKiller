#include "eger.h"
#include "tabla.h"

/*Rekurzio segitsegevel felszabaditja a jatekosok listajat.
* mivel a lista nem tul hosszu, hasznalhato rekurzio*/
void freelistaj(jatekos* head){
    if (head->kov!=NULL)        /*Ha nem ert a vegere, hivja meg a fuggvenyt a kovetkezore*/
        freelistaj(head->kov);
    free(head);                 /*Ha a vegere ert, szabaditsa fel ot.*/
}

/**A gratulacio szoveg es az ahhoz tartozo kep kirajzolasa. SDL_Flip szukseges, a fuggveny
 * csak rajzolast vegez!
 * @param screen SDL_Surface tipusu pointer, ami arra celteruletre mutat, ahova rajzolni kell
 * @param betutipus TTF_Font tipusu pointer ami a felhasznalando betutipust jelzi
 * @param kep SDL_Surface tipusu pointer amely a felhasznalando kepet jelzi
 */
 void wrajzol(SDL_Surface *screen, TTF_Font *betutipus, SDL_Surface *kep){
     SDL_Rect kepdest;
     kepdest.x=KSZELESSEG/2+50, kepdest.y=KMAGASSAG/4;
     char *grat="Congratulation!";
     /*A TTF_KIIR fuggveny reszletes leirasa megtalalhato a dokumentacioban
     *illetve az eger.h fajlban*/
     TTF_KIIR(screen, KSZELESSEG/8, KMAGASSAG/4, grat, betutipus2, WHITE);
     SDL_BlitSurface(kep, NULL, screen, &kepdest);
}

/**Szovegbekero fuggveny. A forras az infoc oldalrol szarmaztathato,
 * termeszetesen a szukseges modositasokkal ellatva. Egyike a keves fuggvenynek a programban,
 * amelyhez nem kotelezo az SDL_Flip hasznalata, ezt a fuggveny megteszi SDL_UpdateRect
 * paranccsal.
 * @param dest szovegre mutato pointer, a helyet jelzi ahova irni kell
 * @param x a "beviteli doboz" (irando terulet) x koordinataja
 * @param y a "beviteli doboz" (irando terulet) y koordinataja
 * @param sz az irando terulet szelessege pixelekben
 * @param m az irando terulet magassaga pixelekben
 * @param hatter Hatterszin (RGBA)
 * @param szin Betu szine (RGBA)
 * @param font TTF_Font tipusu pointer ami a felhasznalando betutipusra mutat
 * @param screen A celfelulet, ahova rajzolni kell
 */
 void input_text(char *dest, int x, int y, int sz, int m,
               SDL_Color hatter, SDL_Color szin, TTF_Font *font, SDL_Surface *screen) {
    SDL_Rect forras = { 0, 0, sz, m}, cel = { x, y, sz, m };
    SDL_Surface *felirat;
    SDL_Event event;
    int hossz, kilep, enter;
    hossz = 0;
    dest[hossz] = '\0';   /* lezaro 0 */
    enter = 0;
    kilep = 0;
    while (!kilep && !enter) {
        /* szoveg kirajzolasa */
        boxRGBA(screen, x, y, x+sz-1, y+m-1, hatter.r, hatter.g, hatter.b, 255);
        felirat = TTF_RenderText_Blended(font, dest, szin);
        SDL_BlitSurface(felirat, &forras, screen, &cel);
        SDL_FreeSurface(felirat);
        SDL_UpdateRect(screen, x, y, sz, m);
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:                   /*FELEJTSÜK EL AZ ÉKEZETEKET, NINCS ÉKEZET! */
                switch (event.key.keysym.unicode) {
                    case 0x0000:                /*HA NEM ÍRUNK BE SEMMIT, buktuk a highscoret, ne kovessunk el ilyen butasagot!*/
                        /* nincs neki megfelelo karakter (pl. shift gomb) */
                        break;
                    case '\r': case '\n':
                        if (dest[0]!='\0'){
                        /* enter: bevitel vege, ha egyatalan beirt valamit */
                        enter = 1;
                        }
                        break;
                    case '\b':
                        /* backspace: torles visszafele, ha van karakter */
                        if (hossz>0)
                            dest[--hossz] = '\0';
                        break;
                    default:
                        if (hossz>9){       /*9-nel nem enged tobbet. */
                            break;
                        }
                        /* karakter: tombbe vele, plusz lezaro nulla */
                        dest[hossz++] = event.key.keysym.unicode;
                        dest[hossz] = '\0';
                        break;
                }
                break;
            case SDL_QUIT:
                kilep = 1;
                break;
        }
    }
}

/**A tabla fuggveny, ami lehetove teszi, hogy beirjuk nevunket es a jatek elmentse azt
 * pontszamunkkal egyutt a dicsoseglistaba. Ugyancsak cim szerint kapja parametereit
 * @param aktualis aktualis allapot
 * @param point pontok szama
 * @param quit kilepes flag
 */
void tabla(status *aktualis, int *point, int *quit) {
    char *szoveg[100]={0};          /*100 elemu ures karaktertomb*/
    FILE *fp;                       /*File pointer*/
    SDL_Surface *cats_catching;     /*Egy felulet*/
    fp=fopen("highscore.txt", "r+");    /*Megnyitjuk a highscore.txt nevu fajlt irasra es olvasasra*/
    cats_catching = IMG_Load("cats_catching.png");  /*Betoltjuk a szukseges kepet*/
    int i=0;            /*hasznos iterator*/
    int rekord=0;       /*A rekord flag*/

    CLRSCR(screen);     /*A hasznos ClearScreen. Ehhez nem kell flip.*/

    jatekos *head=(jatekos*)malloc(sizeof(jatekos));    /*lefoglaljuk a jatekos tipusu lista kezdoelemet*/
    jatekos *mozgo=head;                                /*a mozgo iteratort deklaraljuk es raalitjuk*/
    fscanf(fp, " %s%d\n", head->nev, &head->point);     /*a kezdoelembe beolvassuk a txt elso sorat, nevet, pontot*/
    if (head->point<*point){                            /*Ha mar a top jatekosnal is nagyobb pontot kaptunk, kapunk flaget a rekordra*/
            rekord=1;
        }
    for(i=0; i<4; i++){                                 /*Ebben a szellemben olvassuk be a kovetkezo 4 elemet is.*/
        mozgo->kov=(jatekos*)malloc(sizeof(jatekos));
        mozgo=mozgo->kov;
        mozgo->kov=NULL;
        fscanf(fp, " %s%d\n", mozgo->nev, &mozgo->point);
        printf("%s\t%d\n", mozgo->nev, mozgo->point);
        if (mozgo->point<*point){
            rekord=1;
        }
    }
/*Fontos! csak akkor irhatjuk majd be a nevunket, ha rekordot dontottunk! Hosszu kapcsos jon.*/
    if (rekord){

    wrajzol(screen, betutipus, cats_catching);
    SDL_Flip(screen);
    SDL_EnableKeyRepeat(500, 30);               /*Infoc segitsege*/
    input_text(szoveg, 100, 150, FONTSIZE*10, FONTSIZE, YELLOW, BLACK, betutipus3, screen);
    /*Elmegyunk a lista vegere, hogy az utolso elemet fel tudjuk szabaditani es a lista
    veget lezarjuk*/
    for (mozgo=head; mozgo->kov->kov!=NULL; mozgo=mozgo->kov){
    }
    free(mozgo->kov);
    mozgo->kov=NULL;
    /*letrehozunk es inicializalunk egy player listaelemet (beszurando).*/
    jatekos *player=(jatekos*)malloc(sizeof(jatekos));
    player->point=*point;
    strncpy(player->nev, szoveg, 49);
    jatekos* lemarado;
    lemarado = NULL; mozgo = head;
    while (mozgo != NULL && mozgo->point > player->point) {
    /*A kincstari infoc fuggveny alkalmazasa modositott relacios jellel*/
    lemarado = mozgo; mozgo = mozgo->kov;
    }
    if (lemarado == NULL) {
        player->kov = head;
        head=player;                /*ekkor a head a player lesz*/
    }
    else{
        lemarado->kov = player;
        player->kov = mozgo;
    }
/*a fajl elejere "porgetunk"*/
        fseek(fp, 0, SEEK_SET);
        mozgo=head;             /*a mozgo segitsegevel beirogatjuk a fajlba a listat*/
        while (mozgo!=NULL){
            fprintf(fp, "%s\t%d\n", mozgo->nev, mozgo->point);
            printf("%s\t%d\n", mozgo->nev, mozgo->point);
             mozgo=mozgo->kov;
        }
    }
/*Bezarjuk a fajlt, felszabaditjuk amit fel kell szabaditani,
 * a pontot kinullazzuk, hogy legkozelebb ne azzal induljunk es irany a hsdisplay*/
    fclose(fp);
    SDL_FreeSurface(cats_catching);
    freelistaj(head);
    *point=0;
    *aktualis=hsdisplay;
}
