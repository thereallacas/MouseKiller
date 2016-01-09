#include "eger.h"

void printtutorial(SDL_Surface *hova, char** texts, char *kepnev){
    CLRSCR(hova);
    int i;
    SDL_Surface *tkep = IMG_Load(kepnev);
    SDL_Rect tkeppos;
    tkeppos.x=KSZELESSEG/2-120; tkeppos.y=FONTSIZE*2.5;
    SDL_BlitSurface(tkep, NULL, hova, &tkeppos);
for (i=0; texts[i]!=NULL; i++)
    TTF_KIIR(hova, KSZELESSEG/80, FONTSIZE*(i+1), texts[i], betutipus4, WHITE);
    SDL_FreeSurface(tkep);
    TTF_KIIR(screen, KSZELESSEG/80, KMAGASSAG-FONTSIZE*2, "PRESS ESC TO QUIT", betutipus, WHITE);
}

typedef struct{
    SDL_Surface *hova;
    char* texts;
    char *kepnev;
}fgvargs;

char *texts1[100]={
{"Your life is decreasing continously!"},
{"Refill it by killin'more mice..."},
{"Don't forget that wrong strikes"},
{"cause life-loss, too!"},
{"Can you survive 100 sec?"},
{""},
{""},
{"PRESS SPACE FOR NEXT"},
{NULL}
};

char *texts2[100]={
{"You can use the mouse for almost everything:"},
{"navigating in the menu, killin' mouses,"},
{"...and thats all."},
{"BUT you can always use tha keys on the numpad."},
{"...At least in the menu, fo sure."},
{"Press ENTER in the menu to enable fullscreen."},
{""},
{"PRESS SPACE FOR NEXT"},
{NULL}
};

char *texts3[100]={
{"So what are you waiting for?"},
{"Beat the top players"},
{"and make it to the high-scores!"},
{NULL}
};

void tutorial(status *aktualis, int *quit){
int enough = 0;
/*a jol ismert enough flag*/
int mc = 0;
SDL_Event tev;
/*esemény*/
fgvargs tomb[]={
    {screen, texts1, "jatek.png"},
    {screen, texts2, "mouse.png"},
    {screen, texts3, "end.png"},
};
CLRSCR(screen);
printtutorial(tomb[mc].hova, tomb[mc].texts, tomb[mc].kepnev);
SDL_Flip(screen);
while (!(*quit)&&!enough){
    SDL_WaitEvent(&tev);
    switch (tev.type) {
        case SDL_KEYDOWN:
            switch (tev.key.keysym.unicode){
                case SDLK_ESCAPE:
                    enough=1;
                    break;
                case SDLK_SPACE:
                    tomb[mc].kepnev=="end.png" ? mc=0:mc++;
                printtutorial(tomb[mc].hova, tomb[mc].texts, tomb[mc].kepnev);
                SDL_Flip(screen);
                    break;
                }
            break;
        case SDL_QUIT:
            *quit=1;
            break;
        }
    }
*aktualis=menu;
}
