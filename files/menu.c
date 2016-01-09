#include "eger.h"
#include "menu.h"

SDL_Color WHITE={255, 255, 255};
SDL_Color GREEN={0,255,0};
SDL_Color YELLOW={255, 236, 139};
SDL_Color BLACK={0,0,0};

/*Letisztitja a kepernyõt. Nincs szukseg az SDL_Flip-re, a fuggveny magatol elvegzi!*/
void CLRSCR(SDL_Surface *screen){
    /*rajzol egy megfelelõ meretû fekete dobozt*/
    boxColor(screen, 0, 0, KSZELESSEG, KMAGASSAG, 0x0000FF);
    SDL_Flip(screen); /*A flippet elvegzi a fuggveny*/
}

/*Kiir egy adott betûtipussal egy adott szoveget. Nincs szukseg az SDL_Flipre!*/
void TTF_KIIR(SDL_Surface *screen, int celx, int cely, char* szoveg, TTF_Font *betutipus, SDL_Color szin){
    SDL_Surface *honnan;        /*ideiglenes valtozok*/
    SDL_Rect hova;
    hova.x = celx; hova.y = cely;
    honnan = TTF_RenderText_Blended(betutipus, szoveg, szin);   /*Az SDL fuggvenye*/
    SDL_BlitSurface(honnan, NULL, screen, &hova);
    SDL_FreeSurface(honnan);            /*vegen felszabadituk a foglalt teruletet*/
    SDL_UpdateRect(screen, hova.x, hova.y, 10*FONTSIZE, FONTSIZE);
    /*a flippelest a fuggveny maga vegzi el*/
    }

/** A menu kiirasa, a fuggveny a kod atlathatosaga erdekeben jott letre.
 * @param menukep A menukepre mutato feluletpointer
*/
 void menukiir(SDL_Surface *menukep){
    CLRSCR(screen);
    SDL_Rect mkpos;
    mkpos.x=KSZELESSEG/80; mkpos.y=KMAGASSAG/40;
    SDL_BlitSurface(menukep, NULL, screen, &mkpos);
    TTF_KIIR(screen, KSZELESSEG/2+10, 50, "MOUSE KILLER", betutipus2, WHITE);
    TTF_KIIR(screen, KSZELESSEG/2+10, 100, "New Game-1", betutipus, WHITE);
    TTF_KIIR(screen, KSZELESSEG/2+10, 140, "High score-2", betutipus, WHITE);
    TTF_KIIR(screen, KSZELESSEG/2+10, 180, "Kilepes-3", betutipus, WHITE);
    SDL_Flip(screen);
}

/** A kattintas koordinatainak vizsgalatat atlathatobba tevõ fuggveny
 * @param x a kattintas x koordinataja
 * @param y a kattintas y koordinataja
*/
int menu_number(int x, int y){
    if ((x>KSZELESSEG/2)&&(y>100)&&(y<130)){
        return 1;}
    else if ((x>KSZELESSEG/2)&&(y>140)&&(y<170))
        return 2;
    else if ((x>KSZELESSEG/2)&&(y>180)&&(y<210))
        return 3;
}

/** Ez a fuggveny a menut jeleniti meg, innen lehet valasztani, jatszani akarunk-e,
 * megnezni a dicsõsegtablat vagy egyszerûen csak kilepni. Ez a fuggveny is a fõfuggvenyekhez
 * tartozik, ami azt jelenti, hogy ez is a main.c-bõl hivodik meg, es oda ter vissza
 * megvaltoztatott ertekekkel.
 * @param aktualis status tipusu pointer az aktualis allapotot jelzi
 * @param quit a quit flag-et is cim szerint kell atadni, hogy valtoztatni tudja azt
 */
void bazis(status *aktualis, int*quit){
    SDL_EnableUNICODE(1);
    SDL_Event event;
    SDL_Surface *menukep;
    int change=0;
    menukep = IMG_Load("cats_wait.png");
    menukiir(menukep);
    SDL_Flip(screen);
    while (!*quit&&!change){
    SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.unicode){
                    case '1':
                    *aktualis=game;
                    CLRSCR(screen);
                    change=1;
                        break;
                    case '2':
                    *aktualis=hsdisplay;
                    CLRSCR(screen);
                    change=1;
                        break;
                    case '3':
                    *quit=1;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (menu_number(event.button.x, event.button.y)){
                    case 1:
                    TTF_KIIR(screen, KSZELESSEG/2+10, 100, "New Game-1", betutipus, YELLOW);
                    SDL_Delay(500);
                    *aktualis=game;
                    CLRSCR(screen);
                    change=1;
                        break;
                    case 2:
                    TTF_KIIR(screen, KSZELESSEG/2+10, 140, "High score-2", betutipus, YELLOW);
                    SDL_Delay(500);
                    *aktualis=hsdisplay;
                    CLRSCR(screen);
                    change=1;
                        break;
                    case 3:
                    TTF_KIIR(screen, KSZELESSEG/2+10, 180, "Kilepes-3", betutipus, YELLOW);
                    SDL_Delay(500);
                    *quit=1;
                        break;
                }
                break;
            case SDL_QUIT:
            *quit=1;
                break;
        }
    }
    SDL_FreeSurface(menukep);
}

