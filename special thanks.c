#include "eger.h"

credits(status *aktualis, int *quit){

int enough = 0;
/*a jol ismert enough flag*/
SDL_Event cev;
/*esemény*/
CLRSCR(screen);
SDL_Surface *mancs=IMG_Load("specialthanks.png");
SDL_Rect mancsdest;
mancsdest.x=0; mancsdest.y=50;
SDL_BlitSurface(mancs, NULL, screen, &mancsdest);
SDL_FreeSurface(mancs);
TTF_KIIR(screen, KSZELESSEG/2, 80, "Special thanks to:", betutipus3, WHITE);
TTF_KIIR(screen, KSZELESSEG/2, 130, "Sarkadics", betutipus3, WHITE);
TTF_KIIR(screen, KSZELESSEG/2, 160, "Shido Tousaka", betutipus3, WHITE);
TTF_KIIR(screen, KSZELESSEG/2, 190, "\"Andi\"", betutipus3, WHITE);
TTF_KIIR(screen, KSZELESSEG/2, 220, "bandrasi & dienes", betutipus3, WHITE);
TTF_KIIR(screen, KSZELESSEG/2, 250, "Code: Kyle Brandson", betutipus3, WHITE);
TTF_KIIR(screen, KSZELESSEG/2, 280, "Music: Mendel", betutipus3, WHITE);
TTF_KIIR(screen, KSZELESSEG/2, 310, "2014", betutipus3, WHITE);

SDL_Flip(screen);
while (!(*quit)&&!enough){
    SDL_WaitEvent(&cev);
    switch (cev.type) {
        case SDL_KEYDOWN:
            switch (cev.key.keysym.unicode){
                case SDLK_ESCAPE:
                    enough=1;
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
