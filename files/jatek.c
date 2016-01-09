#include "eger.h"
#include "jatek.h"
#define TEST /*Tesztmodban cheat kod es roviditett jatekido van*/
//#define BLUESCREEN_MODE /*Egy kis erdekesseg*/

/**Ez a fuggveny megcsereli a pp tipusu strukturakat tartalmazo tomb ket megadott elemet.
 * @param a a tomb egyik eleme (egyik struktura)
 * @param b a tomb masik eleme
 */
   void swapper(pp *a, pp *b){
    int temp=a->x;
    a->x=b->x;
    b->x=temp;
    /*Megcsereli mindket strukturatagot egymassal*/
    temp=a->y;
    a->y=b->y;
    b->y=temp;
}

/** Ez a fuggveny a Fisher-Yates fele algoritmust felhasznalva megkeveri egy tomb
 * (jelen esetben a mi tombunk) elemeit. Az implementacio szamos forrasbol elerheto
 * az interneten, es ket reszbol all: az indexek kivalasztasa majd ezek egy kulon
 * fuggvenyben valo megcserelese n db alkalommal.
 * jelen valtozat tesztelesre es modositasra kerult, hogy megfeleljen a kulonleges,
 * strukturakat tartalmazo tomb elvarasainak.
 * @param tomb a strukturakat tartalmazo tomb
 * @param n a tomb elemszama
 */
  void kever(pp *tomb, int n){
    int i;
    for (i = n-1; i > 0; i--){
        int j = rand() % (i+1);
        /*meghivodik a csere fuggveny*/
        swapper(&(tomb[i]), &(tomb[j]));
    }
}

/**Ez a fuggveny 4 SDL-timer egyszerre valo letiltasara alkalmas. Letezese csupan az
 * ugynevezett "sorminta" elkerulese vegett fontos. A megadott SDL_TimerID tipusu
 * parametereket tombbe rendezi, majd vegigmegy a tombon, sorra letiltva annak elemeit.
 * @param felbukkan a nev csak a programozo dolgat szandekozik megkonnyiteni.
 * @param eletetveszt SDL_TIMERID 2. parameter
 * @param nehezedik SDL_TIMERID 3. parameter
 * @param jatek_vege SDL_TIMERID 4. parameter
 */
  void REMOVE_TIMERS(SDL_TimerID felbukkan, SDL_TimerID eletetveszt, SDL_TimerID nehezedik, SDL_TimerID jatek_vege){
    SDL_TimerID tomb[]={felbukkan, eletetveszt, nehezedik, jatek_vege};
    int i;
    for (i=0; i<4; i++){
        SDL_RemoveTimer(tomb[i]);
    }
}

/**Ez a fuggveny 3 SDL felulet egyszerre valo felszabaditasara alkalmas.
 * Hasonlo celokbol irodott, mint a REMOVE_TIMERS nevu testvere. A megadott SDL_Surface tipusu
 * pointerket tombbe rendezi, majd vegigmegy a tombon, sorra felszabaditva annak elemeit.
 * @param egerkep a nev csak a programozo dolgat szandekozik megkonnyiteni.
 * @param deadmau SDL_Surface *2. parameter
 * @param win SDL_Surface *3. parameter
 */
  void FREE_SURFACES(SDL_Surface *egerkep, SDL_Surface *deadmau, SDL_Surface *win){
    SDL_Surface *tomb[]={egerkep, deadmau, win};
    int i;
    for (i=0; i<3; i++){
        SDL_FreeSurface(tomb[i]);
    }
}

/**Ez a fuggveny 3 "Hangpointer" egyszerre valo felszabaditasara alkalmas.
 * Hasonlo celokbol irodott, mint a REMOVE_TIMERS es FREE_SURFACES nevu testvere, viszont
 * sajnos gyakorlatilag csak a sormintat helyezi at a fo kodbol. Kesobbi fejleszteseknel
 * viszont hasznos lehet.
 * @param mus Hatterzenere mutato pointer
 * @param wav Egyes szamu hangeffekt
 * @param wav2 Kettes szamu hangeffekt
 */
  void REMOVE_MUSIC(Mix_Music *mus, Mix_Chunk *wav, Mix_Chunk *wav2){
    Mix_FreeMusic(mus);
    Mix_FreeChunk(wav);
    Mix_FreeChunk(wav2);
}

/**Ez a fuggveny kirajzolja a sajttombot es a lyukakat ra, gyakorlatilag a kepernyo bal
 * reszet. Meg kell hivni az SDL_Flip-et!
 * @param hova megadjuk, hova szeretnenk a palyat rajzolni
 * @param head megadjuk a lyukak listajanak kezdoelemet.
 */
  void palyarajzolas(SDL_Surface* hova, lyuk* head){
    /*a sajttomb kirajzolasa*/
    boxColor(hova, 0, 0, JSZELESSEG, JMAGASSAG, SAJTSZIN);
    /*lyukak kirajzolasa ciklussal*/
        lyuk* mozgo=head;
    for (mozgo; mozgo->kov!=NULL; mozgo=mozgo->kov){
        filledCircleColor(hova, mozgo->kov->x, mozgo->kov->y, mozgo->kov->r, LYUKSZIN);
        /*egy kitoltott lyuk*/
        aacircleColor(hova, mozgo->kov->x, mozgo->kov->y, mozgo->kov->kr, LYUKSZIN);
        /*egy kitoltetlen, de elsimitott karika*/
    }
}

/**Ez a fuggveny veszi a listat es az aktiv listaelem-pointernek egy random szamot general,
 * ugyelve az esetleges ismetlodes elkerulesere a jatek erdekessegenek fenntartasa erdekeben.
 * Eddig kell elmennie az aktiv pointernek, amelyet meg fog valtoztatni a fuggveny.
 * Az aktiv listalelem altal jelzett lyukba rajzol egy egeret.
 * Ebben a fuggvenyben mar meghivjuk a palyarajzolas fuggvenyt is.
 * Meg kell hivni az SDL_Flip-et a hasznalat utan!
 * @param hova a hely ahova szeretnenk rajzoltatni az egeret
 * @param head a lyukak listajanak kezdoeleme
 * @param egerkep az eger kepenek felulete
 * @param pindex az aktiv-index, amit cim szerint kapunk, hogy valtoztathassuk azt
 * @param dest Az eger helyet tartalmazo struktura
 * @param lyukakszama A lyukak szama, a randomindex generalo felso hatarahoz.
 * @param aktiv A lyuk tipusu aktiv listaelem pointert cim szerint valtoztatjuk
 */
  void egerrajzolo(SDL_Surface *hova, lyuk *head, SDL_Surface *egerkep, int *pindex,
                 SDL_Rect *dest, int lyukakszama, lyuk **aktiv){
            palyarajzolas(screen, head);
            int temp=*pindex;
            /*aktivba teszi az egyik lyukat, es ugyel az ismetlodes elkerulesere*/
            *pindex=(rand() %lyukakszama);
            while (temp==*pindex){
                *pindex=(rand() % (lyukakszama+1));
            }
            int i;
            *aktiv=head;
            for (i=0; (i)<*pindex; i++){
                *aktiv=(*aktiv)->kov;
            }
            dest->x=(*aktiv)->x-LYUKSUGAR;
            dest->y=(*aktiv)->y-LYUKSUGAR;
            SDL_BlitSurface(egerkep, NULL, hova, dest);
 }

/**EVENTRESERVED3-at(egermegjelenest) idez elõ. Ez a fuggveny tovabba megkapja a
 * MAXIDO-MINIDO-ket tartalmazo IDOK tipusu strukturat, hogy aztan o is sajat egyeni
 * idot szabhasson maganak (az egerek felbukkanasa szuksegszeruen veletlen kell, hogy legyen)
 * @param ms a parameterek ennel a fuggvenynel kotottek, ezutan nem reszletezzuk oket (Uint32)
 * @param param Egyedul ennel a fuggvenynel hasznaljuk ki a szabadon valaszthato parametert (IDOK)
 * @return ms Uint32 tipusu idovel, ami most veletlenszeruen generalva van.
 */
  Uint32 kibuvik(Uint32 ms, IDOK *param) {
    SDL_Event event;
    event.type = SDL_EVENT_RESERVED3;
    SDL_PushEvent(&event);
    return  (rand()%param->MAXIDO+param->MINIDO);   /* ujabb varakozas */
}

/**EVENTRESERVED2-õt(jatekbefejezest) idez elõ. Ha idaig eljutott a jatekos, akkor nyert.
 * @param ms Uint32 ido
 * @param param tetszoleges parameter
 * @return ms Uint32
 */
  Uint32 finish(Uint32 ms, void *param){
    SDL_Event even;
    even.type = SDL_EVENT_RESERVED2;
    SDL_PushEvent(&even);
    return ms;
}

/**EVENTRESERVED4-et(eletvesztest) idez elõ. Ez a fuggveny teszi lehetove, hogy a
 * jatekos ne tudja megnyerni a jatekot olbe tett kezzel. Bizonyos idokozonkent
 * eletvesztes esemenyt tesz az esemenyek koze.
 * @param ms Uint32 ido
 * @param param tetszoleges parameter
 * @return ms Uint32
 */
  Uint32 fogyo(Uint32 ms, void *param){
    SDL_Event even;
    even.type = SDL_EVENT_RESERVED4;
    SDL_PushEvent(&even);
    return ms;
}

/**EVENTRESERVED5-ot(nehezedest) idez elõ. Mit is erne a jatek nehezedes nelkul?
 * Ez a fuggveny olyan esemenyt ad, ami majd modositja a randomido generalasanak
 * also es felso hatarait.(MINIDO, MAXIDO)
 * @param ms Uint32 ido
 * @param param tetszoleges parameter
 * @return ms Uint32
 */
  Uint32 harder(Uint32 ms, void *param){
    SDL_Event even;
    even.type = SDL_EVENT_RESERVED5;
    SDL_PushEvent(&even);
    return ms;
}

/**EVENTRESERVED6-ot(uj lyuk bevezeteset) idezi elo.
 * @param ms Uint32 ido
 * @param param tetszoleges parameter
 * @return ms Uint32
 */
  Uint32 newhole(Uint32 ms, void *param){
    SDL_Event even;
    even.type = SDL_EVENT_RESERVED6;
    SDL_PushEvent(&even);
    return ms;
}

/**Ez a fuggveny elintez minden, gyozelemmel kapcsolatos kirajzolast.
 * Habar a TTF_KIIR tartalmazza az SDL_UpdateRect fuggvenyt, ezutan is szukseges
 * az SDL_Flip meghivasa!
 * @param win SDL_Surface nyerteseknek jaro kep
 * @param point a pontok szama
 */
  void winnerspicture(SDL_Surface *win, int point){
    char szoveg[40];
    SDL_Rect dest;
    dest.x=0, dest.y=0;
    CLRSCR(screen);
    SDL_BlitSurface(win, NULL, screen, &dest);
    TTF_KIIR(screen, KSZELESSEG/2+10, 150, "You won!", betutipus, WHITE);
    sprintf(szoveg, "Points = %d", point);
    TTF_KIIR(screen, KSZELESSEG/2+10, 200, szoveg, betutipus, WHITE);
}

/**Ez a fuggveny kirajzolja a control panelt. Ez a pontszamot es a kepet jelenti
 * a kep jobb szelen. SDL_Flip meghivasa kotelezo!
 * @param hova hova rajzolja a control panelt
 * @param kep A kep amit ratesz
 * @param point A jatekos pontjai
 */
  void cprajzolas(SDL_Surface *hova, SDL_Surface *kep, int point){
    boxRGBA(screen, JSZELESSEG+1, 0, KSZELESSEG, KMAGASSAG, 0, 0, 0, 255);
    SDL_Rect dest;
    dest.x=KSZELESSEG-280;
    dest.y=KMAGASSAG-180;
    char buffer[50]={0};
    SDL_BlitSurface(kep, NULL, hova, &dest);
    sprintf(buffer, "Points so far=%d", point);
    TTF_KIIR(screen, JSZELESSEG+10, 10, buffer, betutipus, WHITE);
}

/**Ez a fuggveny ciklust es kulonfele felteteleket alkalmazva rajzolja ki
 * az eletcsikot, harom kulonbozo szinben
 * @param hova melyik feluletre keruljon az eletcsik
 * @param health a jatekos elete
 */
  void drawhealthbar(SDL_Surface *hova, int health){
    int i=1, posx=KSZELESSEG-(ASZELESSEG/3), posy=(AMAGASSAG/2);
    /*Fekete dobozt rajzol, hogy kitisztitsa a teruletet*/
    boxColor(hova, posx, posy, posx+HEALTHSQUARE, posy-MAXHEALTH*HEALTHSQUARE, 0x000000FF);
    Uint32 actualcolor=HEALTHRED;
        while(i<=health){
    boxColor(hova, posx, posy, posx+HEALTHSQUARE, posy-HEALTHSQUARE, actualcolor);
    posy-=HEALTHSQUARE;
    i++;
    /*A szinek valtoznak az iterator erteke szerint*/
    if (i==(MAXHEALTH/2)) actualcolor=HEALTHYELLOW;
    else if (i==MAXHEALTH) actualcolor=HEALTHGREEN;
    }
}

/**Ez a fuggveny ad egy eletet, abban az esetben ha az nem volt mar eleve a maximumon.
 * Cim szerint kapja az erteket, hogy valtoztatni tudja azt!
 * @param phealth A jatekos elete cim szerint atadva
 */
  void gethealth(int *phealth){
    if (*phealth<MAXHEALTH){
        *phealth=*phealth+1;
    }
}

/**Ez a fuggveny eletvesztest idez elo. Also hatart nem kell vizsgalni,
 * ha a health nulla, a jatekos veszit majd.
 * Cim szerint kapja az erteket, hogy valtoztatni tudja azt!
 * @param phealth A jatekos elete cim szerint atadva
 */
  void losehealth(int *phealth){
    *phealth=*phealth-1;
}

/**Rekurzio a lyukak listajanak felszabaditasara, mivel az nem tulzottan nagy.
 * @param head a lista kezdoelemere mutato pointert kell megadni
 */
  void freelista(lyuk* head){
   if (head->kov!=NULL)
        freelista(head->kov);
    free(head);
}

/**Új lyukat fûz a regiek listajahoz, tomb kovetkezo elemebõl vesz hozza adatokat.
 * @param head a lista kezdoelemere mutato pointert kell megadni
 * @param lyukakszama a lyukakszama a pptomb indexenek kivalasztasahoz szukseges
 * @param tomb a lehetseges helyek tombje
 */
  void ujlyuk(lyuk *head, int lyukakszama, pp *tomb){
    lyuk *mozgo, *uj;
    for (mozgo = head; mozgo->kov != NULL; mozgo = mozgo->kov)
            ;
    uj = (lyuk*) malloc(sizeof(lyuk));
    mozgo->kov = uj;
    /*A lyukakszama a fuggvenybol kilepve fog inkrementalodni, ezert az indexeles jo*/
    uj->x = tomb[lyukakszama].x;
    uj->y = tomb[lyukakszama].y;
    uj->kr=LYUKSUGAR;
    uj->r=LYUKSUGAR;
    uj->kov = NULL;
    }

/**A fo-fo jatek fuggveny, parameterkent kapja a quit es az aktualis valtozokat,
 * cim szerint, hogy modositani tudja oket.
 * @param aktualis az allapota a jateknak (enumeracio adatszerkezet)
 * @param point a jatekos pontjai
 * @param quit a kilepes flag
 */
void jatek (status *aktualis, int *point, int *quit){
/*random seed*/
srand((unsigned)time(NULL));
/*A lehetseges helykoordinatak tombje(possible positions)*/
pp tomb[9];
int i;          /*iterator altalanos hasznalatra*/
*point=0;       /*a point kinullazodik*/

/*A tombot feltoltjuk a lyukak koordinataival.
 * Összesen (a kepernyon) 9 db lyuk van, ezek
 * elhelyezese nagyjabol koveti a szabalyos
 * 3x3-as elrendezest, de nemi modositassal*/

tomb[0].x=100;
tomb[0].y=100;

/* A tomb feltoltese egy ciklussal nehezkes.
 * Az egyes lyukak bizonyos hatarokon belul eltolodhatnak.
 * Az sem jelent gondot, ha atfedes van koztuk.*/

for (i=1; i<3; i++){
    tomb[i].x=tomb[i-1].x+150+(rand()%20)*-1*(rand()%2+1);
    tomb[i].y=tomb[0].y+(rand()%20)*-1*(rand()%2+1);
}
for (i=3; i<6; i++){
    tomb[i].x=tomb[i-3].x+150-150+(rand()%20)*-1*(rand()%2+1);
    tomb[i].y=tomb[0].y+150+(rand()%20)*-1*(rand()%2+1);
}
for (i=6; i<9; i++){
    tomb[i].x=tomb[i-3].x+150-150+(rand()%20)*-1*(rand()%2+1);
    tomb[i].y=tomb[0].y+250+(rand()%20)*-1*(rand()%2+1);
}

/*a tomb megkeverese*/
kever(tomb, 9);

/*A lyukakbol listat keszitunk. A lista kezdoeleme, amire majd
 * hivatkozni fogunk, egy, a kepernyon kivul allo lyuk. Ez alapesetben az aktiv lyuk,
 * mert erre lehetetlen rakattintani.*/
lyuk *head=(lyuk*)malloc(sizeof(lyuk));
head->kov=NULL;
head->x=KSZELESSEG+LYUKSUGAR*2;
head->y=KMAGASSAG+LYUKSUGAR*2;
head->r=LYUKSUGAR;
head->kr=LYUKSUGAR;

/*Az SDL foesemeny felvetele*/
    SDL_Event ev;

/*Feluletek felvetele*/
    SDL_Surface *egerkep;
    SDL_Surface *deadmau;
    SDL_Surface *cats_hunting;
    SDL_Surface *win;
    #ifdef BLUESCREEN_MODE
    SDL_Surface *file;
    SDL_Surface *bluescreen;
    #endif // BLUESCREEN_MODE

/*Idozitok felvetele*/
    SDL_TimerID felbukkan;
    SDL_TimerID eletetveszt;
    SDL_TimerID nehezedik;
    SDL_TimerID jatek_vege;
    SDL_TimerID uj;

/*a kepek helyeihez szukseges SDL_Rect strukturak*/
    SDL_Rect dest;
    #ifdef BLUESCREEN_MODE
    SDL_Rect filedest;
    #endif // BLUESCREEN_MODE

/*IDOK tipusu struktura felvetele*/
    IDOK idok;
    idok.MINIDO=600;
    idok.MAXIDO=1000;

/*Hatterzene es hangeffektek*/
    Mix_Music *mus;
    mus = Mix_LoadMUS("mjuzik3.mp3");
    Mix_Chunk *wav, *wav2;
    wav = Mix_LoadWAV("talalt.wav");
    wav2 = Mix_LoadWAV("macskarov.wav");
    Mix_FadeInMusicPos(mus, -1, 3000, 0);
    Mix_Volume(0,40);

/*Kepek betoltese*/
    egerkep=IMG_Load("rsz_2egergif312x279.gif");
    deadmau=IMG_Load("rsz_2egergif312x279dead.gif");
    #ifdef BLUESCREEN_MODE
    file=IMG_Load("file.png");
    #endif // BLUESCREEN_MODE
    cats_hunting=IMG_Load("cats_hunting.png");
    win=IMG_Load("win.png");

/*Egyeb valtozok, flag-ek*/
    int start=0;
    int index=0;
    int health=MAXHEALTH;
    int lose=0;
    int end=0;
    int enough=0;
    int nincstobblyuk=0;
    int LYUKAKSZAMA=0;
    lyuk *aktiv=head;

    palyarajzolas(screen, head);

/*Unicode engedelyezese*/
    SDL_EnableUNICODE(1);
/* Egy "elotet loop"*/
    while (!(*quit)&&!start){
    TTF_KIIR(screen, KSZELESSEG/80, FONTSIZE, "PRESS SPACE TO START", betutipus2, BLACK);
    SDL_Flip(screen);
    SDL_WaitEvent(&ev);
    switch (ev.type) {
        case SDL_KEYDOWN:
            switch (ev.key.keysym.unicode){
                case SDLK_SPACE:
                    start=1;
                    break;
                case SDLK_ESCAPE:
                    quit=1;
                    break;
                }
            break;
        case SDL_QUIT:
            *quit=1;
            break;
        }
    }

/*Timerek inicializalasa*/
    felbukkan = SDL_AddTimer((rand()%idok.MAXIDO+idok.MINIDO), kibuvik, &idok);
    jatek_vege = SDL_AddTimer(100*1000, finish, NULL);
    #ifdef TEST
    jatek_vege = SDL_AddTimer(15*1000, finish, NULL);
    #endif // TEST
    eletetveszt=SDL_AddTimer(3*1000, fogyo, NULL);
    nehezedik=SDL_AddTimer(5*1000, harder, NULL);
    uj=SDL_AddTimer(3*1000, newhole, NULL);

/*Harom lyuk elore kirajzolasa*/
/*A program akkor sem omlik ossze, ha nulla lyukkal akarunk kezdeni, (vagyis az iteracio
 * felso korlatjat nullara vesszuk, vagy kihagyjuk az egeszet), ez kesobbi fejlesztesek
 * szempontjabol erdekes lehet*/
    for (i=0; i<3; i++){
                ujlyuk(head, LYUKAKSZAMA, tomb);
                palyarajzolas(screen, head);
                SDL_Flip(screen);
                LYUKAKSZAMA+=1;
    }

/*A parancsok onmagukert beszelnek, ezentul csak a legfontosabbakat magyarazzuk*/
    palyarajzolas(screen, head);
    cprajzolas(screen, cats_hunting, *point);
    drawhealthbar(screen, health);
    SDL_Flip(screen);

/*A jatek fo while ciklusa, innentol kezdodnek a kulonbozo esemenyek es azok leirasai.
 * A kilepesi feltetelek: kilepes, vesztes, jatek vege flagek felallitasa*/
    while (!(*quit)&&!lose&&!end&&!enough){
        SDL_WaitEvent(&ev);     /*Esemenyre var*/
        switch (ev.type) {
            case SDL_EVENT_RESERVED6:
                ujlyuk(head, LYUKAKSZAMA, tomb);
                SDL_Flip(screen);
                LYUKAKSZAMA+=1;         /*lyukak szama megno, ha eleri a maximalis szamot, eltavolitja az ehhez tartozo idozitot, es felallitja
                a nincstobblyuk flaget*/
                if (LYUKAKSZAMA==9){
                    SDL_RemoveTimer(uj);
                    nincstobblyuk=1;
                }
                break;
            case SDL_EVENT_RESERVED3:   /*Az if feltetel csak akkor kell, ha az elejen nem rajzoltunk ki lyukakat. Lehetne ugy is.*/
                if (LYUKAKSZAMA!=0){
                egerrajzolo(screen, head, egerkep, &index, &dest, LYUKAKSZAMA, &aktiv);
                SDL_Flip(screen);
                }
                break;
            case SDL_EVENT_RESERVED2:
                /*ha vege van a jateknak, a gyozelmi kepernyo fogadja a jatekost.
                * (Persze ez nem jelenti meg azt hogy rekordot dontott.*/
                winnerspicture(win, *point);
                SDL_Flip(screen);
                Mix_FadeOutMusic(3000);
                /*A zene halkulasarol is gondoskodik, ebben van SDL_Delay is,
                 * ezert a program 3 mp-ig nem csinal semmit.*/
                end=1;
                /*vege flag felallitasa (cikluskiugrasi feltetel)*/
                break;
            case SDL_EVENT_RESERVED4:
                losehealth(&health);
                /*Életvesztes, ha elfogyott az elet, lose flag (ismet kiugrasi feltetel*/
                if (health==0) {lose=1;}
                /*Aki veszit, meg Kiirast sem erdemel*/
                drawhealthbar(screen, health);
                SDL_Flip(screen);
                break;
            case SDL_KEYDOWN:
                switch(ev.key.keysym.unicode){
                    #ifdef TEST
            /*Teszteloi cheat kod. Ha ENTER-t nyomunk, akkor talalat van
            *(nem tokeletesen helyezi el a halott egeret,
            *de az most mindegy*/
                    case SDLK_RETURN:               /*LEÍRÁS KÉSŐBB*/
                    palyarajzolas(screen, head);
                        aktiv=head;
                    /*halott egeret rajzol*/
                    SDL_BlitSurface(deadmau, NULL, screen, &dest);
                    SDL_Flip(screen);
                    Mix_PlayChannel(0,wav,0);
                    (*point)++;
                    gethealth(&health);
                    cprajzolas(screen, cats_hunting, *point);
                    drawhealthbar(screen, health);
                    SDL_Flip(screen);
                        break;
                    #endif // TEST
                    case SDLK_ESCAPE:
                    enough=1;
                        break;
                }
                    break;

            case SDL_EVENT_RESERVED5:
                /*Az egerek elobukkanasanak letiltasa, majd ujboli
                 * engedelyezese megvaltoztatott idokorlatokkal.*/
                SDL_RemoveTimer(felbukkan);
                if (idok.MINIDO>400) idok.MINIDO-=50;
                /*Azert a negativ idot ne ertelmezzuk.*/
                if (idok.MAXIDO>500) idok.MAXIDO-=50;
                felbukkan = SDL_AddTimer((rand()%idok.MAXIDO+idok.MINIDO), kibuvik, &idok);
                    break;
            case SDL_MOUSEBUTTONDOWN:       /*A kattintas erzekelese*/
                if ((abs((ev.motion.x)-aktiv->x)<=LYUKSUGAR)&&(abs((ev.motion.y)-aktiv->y)<=LYUKSUGAR)){    /*aktiv kor es kattintas helyzete feltetel*/
                    aktiv=head;
                    /*a lehetetlen pozicioban levo listakezdo lyuk lesz az aktiv (default)*/
                    palyarajzolas(screen, head);
                    SDL_BlitSurface(deadmau, NULL, screen, &dest);
                    /*halott egeret rajzol a regi helyere */
                    SDL_Flip(screen);
                    Mix_PlayChannel(0,wav,0);
                    /*Hangeffekt, pontnoveles, stb*/
                    (*point)++;
                    gethealth(&health);
                    cprajzolas(screen, cats_hunting, *point);
                    drawhealthbar(screen, health);
                    SDL_Flip(screen);
                    }
                    else{
                    Mix_PlayChannel(0,wav2,0);
                    /*Minden mas esetben a macska sertodott nyavogasa
                     * es eletvesztes a reakcio*/
                    losehealth(&health);
                    cprajzolas(screen, cats_hunting, *point);
                    drawhealthbar(screen, health);
                    SDL_Flip(screen);
                    if (health==0){lose=1;}
                    /*Veszit flag beallitasa ha elfogy az elet*/
                    }
                break;
            case SDL_QUIT:
                *quit=1;
                /*mivel pointer, a dereferaltat kell egybe rakni, ha SDL_QUIT esemeny van*/
                break;
        }
    }

/*A kulonbozo elemek felszabaditasa*/
#ifdef BLUESCREEN_MODE
 bluescreen=SDL_SetVideoMode(0,0, 0, SDL_ANYFORMAT|SDL_FULLSCREEN);
 filedest.x=70; filedest.y=0;
 SDL_BlitSurface(file, NULL, bluescreen, &filedest);
 SDL_Flip(bluescreen);
 SDL_Delay(4*1000);
#endif  //BLUESCREEN_MODE

    freelista(head);
    #ifdef BLUESCREEN_MODE
    SDL_FreeSurface(bluescreen);
    SDL_FreeSurface(file);
    #endif // BLUESCREEN_MODE
    REMOVE_MUSIC(mus, wav, wav2);
    REMOVE_TIMERS(felbukkan,nehezedik,eletetveszt,jatek_vege);
    FREE_SURFACES(egerkep, deadmau, win);
    if (!nincstobblyuk){            /*csak akkor tavolitjuk el, ha ez nem tortent meg mar elobb*/
        SDL_RemoveTimer(uj);
    }
    if (end){
        *aktualis=highscore;        /*csak akkor kaphatunk high-score-t, ha tuleltuk*/
    }
    else if (lose){
        *aktualis=hsdisplay;        /*ha nem, bamulhatjuk a toplistat*/
    }
    else if(enough){
        *aktualis=menu;
    }
}
