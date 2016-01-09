#include "eger.h"
#include "tabla.h"

/** A dics�segtabla kirajzolasat vegz� fuggveny. A fuggveny valtoztatni tudja a neki adott
 * parametereket.
 * @param aktualis status tipusu pointer, amely az aktualis allapotat mutatja a jateknak
 * @param quit a kilepes flag-je
*/
void tabla_r(status *aktualis, int *quit){
    CLRSCR(screen);             /*letisztitja a keperny�t*/
    FILE *fp;
    SDL_Surface *cats_sit=IMG_Load("cats_sit.png"); /*Megnyitja az almenu kepet*/
    SDL_Rect catdest; catdest.x=KSZELESSEG/8-50; catdest.y=KMAGASSAG/4-70;
    SDL_Event event;
    int i;
    char sor[50];       /*ide lesznek irva a sorok*/
    int enough=0;
    SDL_BlitSurface(cats_sit, NULL, screen, &catdest);  /*kirajzolja a keperny�re a kepet*/

    fp=fopen("highscore.txt", "rt");        /*megnyitja az adatokat tartalmazo szovegfajlt*/

    jatekos *head=(jatekos*)malloc(sizeof(jatekos));
    /*A tabla fuggvenyben lev� esemenyek ujra megtortennek, ezuttal nem vizsgalunk
    semmit, csak beolvassuk a lancolt listaba a sorokat, majd kiirjuk �ket TTF_KIIR-el*/
    jatekos *mozgo=head;
    fscanf(fp, " %s%d\n", head->nev, &head->point);
    sprintf(sor, "%s....%d", mozgo->nev, mozgo->point);
    TTF_KIIR(screen, KSZELESSEG/2, 50, sor, betutipus2, WHITE);
    for(i=0; i<4; i++){
        mozgo->kov=(jatekos*)malloc(sizeof(jatekos));
        mozgo=mozgo->kov;
        mozgo->kov=NULL;
        fscanf(fp, " %s%d\n", mozgo->nev, &mozgo->point);
        char sor[50];
        sprintf(sor, "%s....%d", mozgo->nev, mozgo->point);
        printf("%s....%d\n", mozgo->nev, mozgo->point);
        TTF_KIIR(screen, KSZELESSEG/2, (90+(FONTSIZE+10)*i), sor, betutipus2, WHITE);
    }
    SDL_Flip(screen);
/*Keperny�re flippelunk es varunk*/
    while (!(*quit)&&!enough){      /*enough es quit flag*/
        SDL_WaitEvent(&event);
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.unicode)
                        case SDLK_RETURN:
                            enough=1;
                            break;
                case SDL_QUIT:
                    *quit=1;
                        break;
            }
    }
    /*kotelez� felszabaditas*/
    fclose(fp);
    SDL_FreeSurface(cats_sit);
    freelistaj(head);
    *aktualis=menu;     /*a menube ugrunk*/
}
