#include "eger.h"
//#define DEBUG_WIN32

/**
 * @mainpage
 * Ez a MOUSE KILLER nagy hazi feladat program
 * dokumentacioja.
 */

/*Deklaralas kinnt. Kepernyo, betutipus, kilepes flag.*/
SDL_Surface *screen;
TTF_Font *betutipus;
TTF_Font *betutipus2;
TTF_Font *betutipus3;
TTF_Font *betutipus4;

/** A fo-fo fuggveny, a main logika iranyitoja, minden ut ide vezet, ez dont mindenrol.
 * Ez a fuggveny gondoskodik a vegso felszabaditasrol.
 */
int main(int argc, char *argv[]){
/* SDL inicializalasa es ablak megnyitasa */
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO);
/*ikon es felirat*/
    SDL_WM_SetIcon(SDL_LoadBMP("desktopicon.bmp"), NULL);
    SDL_WM_SetCaption("Mouse Killer", "Mouse Killer");
/* Konzolablak, ha kell a szabvanyos kimenethez (Vigyazat kilepeskor problemas!)*/
    #ifdef DEBUG_WIN32
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    #endif
/*Zenedoboz megnyitasa itt*/
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 600);
    screen=SDL_SetVideoMode(KSZELESSEG, KMAGASSAG, 0, SDL_ANYFORMAT);
/*Ha meg nem tortent volna meg, akkor betutipusok inicializalasa. */
    if (!TTF_WasInit()){
        TTF_Init();
        betutipus = TTF_OpenFont("StencilStd.otf", FONTSIZE);
        betutipus2 = TTF_OpenFont("Title.ttf", FONTSIZE);
        betutipus3 = TTF_OpenFont("data.ttf", FONTSIZE);
        betutipus4 = TTF_OpenFont("data.ttf", 15);

    }
/*status enumeracio felvetele "aktualis" neven, majd beallitasa "menu" statuszba. */
    status aktualis=menu;
    /*A pont es a quit beallitasa*/
    int quit=0;
    int point=0;
/*A fo logika: menure a menu modul, game-re a jatek modul, highscore-ra a
 * highscore felvevo modul, hsdisplay-re megjelenik a dicsosegtabla*/
    while(!quit){
        switch (aktualis){
            case menu:
                bazis(&aktualis, &quit);
                break;
            case game:
                jatek(&aktualis, &point, &quit);
                break;
            case highscore:
                tabla(&aktualis, &point, &quit);
                break;
            case hsdisplay:
                tabla_r(&aktualis, &quit);
                break;
            case howtoplay:
                tutorial(&aktualis, &quit);
                break;
            case spec:
                credits(&aktualis, &quit);
        }
    }
/*Minden ut ide vezet, ezert akarmilyen csunyan is lepunk ki, ezek fel lesznek szabaditva*/
    Mix_CloseAudio();
    SDL_FreeSurface(screen);
    TTF_CloseFont(betutipus);
    TTF_CloseFont(betutipus2);
    TTF_CloseFont(betutipus3);
    TTF_Quit();
    SDL_Quit();

return 0;
}
