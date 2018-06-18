/*===============================================
  AUTOMAT KOMORKOWY - "Symulator pozaru lasu" v1.0
-----------------------------------------------
  Damian Kaniewski 291565 UMK IS r1 s2
===============================================
  Projekt symuluje pozar lasu na niewielkim z gory okreslonym obszarze.
  Program wypelnia plansze losowo rozmieszczonymi drzewami po czym uzytkownik wybiera czy maja wystapic opady deszczu i jak geste, kierunek
  wiatru, ktory jest odpowiedzialny za szybsze rozprzestrzenianie sie wiatru w danym kierunku oraz wspolrzedne podpalenia.

  Ponizsza wersja to uproszczony model, ktory cechuje sie takimi zasadami:

  Komorki dzielimy na trzy rodzaje:
    - puste [ ]
    - z drzewem [T]
    - plonace [#]
  1.[x] Losowa plansza wypelniona drzewami oraz pustymi miejscami,
  2.[x] Wybieramy wspolrzedne gdzie ma zaczac rozprzestrzeniac sie plomien,
  3.[x] Drzewo zacznie sie palic jesli conajmniej jeden sasiad plonie,
  4.[x] Plonaca komorka zmienia sie w pusta,
  5.[x] Rozchodzenie sie ognia w zaleznosci od kierunku wiatru.
      np. wiatr wieje ze Wschodu <-- czyli w lewo to ogien rozchodzi się np. 2 razy szybciej w lewo niz w innych kierunkach,
  6.[x] Predkosc wiatru w skali od 1-5,
  7.[x] Opady deszczu - podajac gestosc opadow uwzgledniamy ile komorek z planszy zostanie dotknietych deszczem.
    Jezeli komorka posiada drzewo, zostanie podpalona i pada na nia deszcz wtedy drzewo nie zostanie spalone.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///WINDOWS///
#ifdef _WIN32
#include <windows.h>
#define czysc() system("cls")
#endif
///LINUX///
#ifdef __linux__
#include <unistd.h>
#define czysc() system("clear")
#define Sleep(ms) usleep((ms)*1000)
#endif
/////PLANSZA/////
#define WYS  23
#define SZER  76


void zerowanie_licz(int licznik[WYS][SZER])//zerowanie licznika
{
    int i,j;
    for(i=0; i<WYS; i++){
      for(j=0; j<SZER; j++){
          licznik[i][j]=0;}}
}
void wiatr(char kierunek, int *w1, int *w2, int i, int j, int predkosc) // funkcja odpowiedzialna za implementacje rozchodzenia sie ognia wraz z kierunkiem wiatru, w1 i w2 to zmienne wskaznikowe, ktore odnosza sie do petli spalanie.
{
  // i wysokosc j szerokosc
  //w1 wys , w2 szer
    switch(kierunek){
        case 'E': // wiatr ze Wschodu (wieje w lewo)
            if(j<2+predkosc) *w2=0;
              else  *w2=-predkosc;
              *w1=0;
        break;
        case 'W': // wiatr z Zachodu (wieje w prawo)
            if(j>SZER-(3+predkosc)) *w2=0;
              else  *w2=predkosc;
              *w1=0;
        break;
        case 'N': // wiatr z Północy (wieje na dół)
            if(i<2+predkosc) *w1=0;
              else  *w1=-predkosc;
              *w2=0;
        break;
        case 'S': // wiatr z Południa (wieje w górę)
            if(i>WYS-(3+predkosc)) *w1=0;
              else  *w1=predkosc;
              *w2=0;
        break;

    }
}
char spr_ogien(char tab[WYS][SZER])// funkcja sprawdzajaca czy na planszy jest ogien potrzebna do zatrzymania funkcji spalanie
{
  int i,j;
  for(i=0; i<WYS; i++){
    for(j=0; j<SZER; j++){
          if(tab[i][j]=='#') return 0;
        }
    }
            return 1;
}
void miejsce_podpalenia(char tab[WYS][SZER], int x, int y) // Podpalenie wybranego miejsca
{
 tab[x][y]='#';
}
int losowanie(void)
{
  return rand()%2+1; // losowanie liczb przystej i nie parzystej
}
void zalesianie(char tab[WYS][SZER]) // funkcja ktora wypelnia plansze drzewami na podstawie wylosowanych liczb
{
  int i,j;
  for(i=0; i<WYS; i++){
      for(j=0; j<SZER; j++){
        if(losowanie()==1) tab[i][j]=' '; // jezeli parzysta to pole jest puste
        else   tab[i][j]='T'; //jezeli nieparzysta to rosnie drzewo
    }
  }
}
void tab_cpy(char tab[WYS][SZER], char tab2[WYS][SZER]) // funkcja kopiujaca tablice
{
  int i,j,tmp=0;
  for(i=0; i<WYS; i++){
      for(j=0; j<SZER; j++){
        tab2[i][j]=tab[i][j];
    }
  }
}
void show_tab(char tab[WYS][SZER]) // funkcja odpowiedzialna za zbudowanie planszy
{
    int i,j;
  for(i=0; i<=SZER+1; i++){
    if(i==0)
      printf("%c",'X');//lewy gorny rog
    else{
      if(i==SZER+1)
        printf("%c",'X');//prawu gorny rog
      else
        printf("%c",'X');//gorna belka
    }
  }
    printf("\n");
  for(i=0; i<WYS; i++){
    printf("%c",'Y'); //lewa sciana
        for(j=0; j<SZER; j++){
          printf("%c", tab[i][j]);
          if(j==SZER-1)
            printf("%c\n",'Y');//prawa sciana
      }
    }
  for(i=0;i<=SZER+1;i++){ //dolna belka
      printf("%c",'X');
  }
    printf("\n");
}
void spalanie(char tab[WYS][SZER], char tab2[WYS][SZER], int licznik[WYS][SZER], char kierunek, int predkosc)
{ //glowna funkcja w ktorej znajduja sie warunki dotyczace spalania (komorka plonie kiedy jeden z 8 sasiadow plonie)
  int i,j,k,l;
  int w1=0, w2=0;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
        if(tab[i][j]=='#')
        { //konczenie spalania drzewa  tab[WYS][SZER]
           if(licznik[i][j]==2) tab2[i][j]=' ';
           else licznik[i][j]++;

             for(k=-1; k<2; k++){
                for(l=-1; l<2; l++){
                  int p1=i+k; //WYS
                  int p2=j+l; //SZER

                  if(i==0 && k==-1) p1=0; //pierwszy wiersz
                  if(j==0 && l==-1)    p2=0; // pierwsza kolumna
                  if(i==WYS-1 && k==1) p1=WYS-1; // ostatni wiersz
                  if(j==SZER-1 && l==1) p2=SZER-1;// ostatnia kolumna

                  if(i==0 && j==0){ //lewy gorny rog
                      if(k==-1) p1=0;
                      if(l==-1) p2=0;
                  }
                  if(i==0 && j==SZER){ //prawy gorny rog
                      if(k==-1) p1=0;
                      if(l==1) p2=SZER;
                  }
                  if(i==WYS && j==SZER){//prawy dolny rog
                      if(k==1) p1=WYS;
                      if(l==1) p2=SZER;
                  }
                  if(i==WYS && j==0){ //lewy dolny rog
                      if(k==1) p1=WYS;
                      if(l==-1) p2=0;;
                  }

                  wiatr(kierunek,&w1,&w2,i,j,predkosc);
                    if(!(k==0 && l==0)){ //tab[WYS][SZER]
                        if(tab[p1][p2]=='T') tab2[p1][p2]='#'; //krok bez uwzgl wiatru
                        if(kierunek!='Z'){
                              if(tab[p1+w1][p2+w2]=='T') tab2[p1+w1][p2+w2]='#';//nastepny krok ktory uwzglednia kierunek wiatru
                    }
                  }
                }
              }
            }
         }
      }

      tab_cpy(tab2,tab); //kopiowanie tab
}
void deszcz(char tab3[WYS][SZER]) // funkcja odpowiedzialna za parametr opadow na planszy
{
  srand(time(NULL));
  int opady=0,i,j,x,y;
  printf("\nPodaj ilosc opadow deszczu (1-1000):");
  scanf("%d",&opady);

  if(opady>1000){
    printf("\nPrzekroczyles zakres!\nOpady ustawione na 1000.\n");
    opady=1000;
  }
  else{
    for(i=0; i<WYS; i++){ // ustawianie licznika na -1
      for(j=0; j<SZER; j++){
          tab3[i][j]=-1;}}
    for(i=0;i<opady;i++){ // uzuplnianie losowych miejsc tablicy nr 3 "deszczem"
      x=rand()%23;
      y=rand()%76;
      if(tab3[x][y]!='d') tab3[x][y]='d'; //nie powielaja sie!
      }
    }
}
void gaszenie(char tab3[WYS][SZER], char tab2[WYS][SZER], int licznik[WYS][SZER])//funkcja odpowiedzialna za gaszenie
//drzewek jeśli są w miejscu opadow
{ int i,j;
  for(i=0; i<WYS; i++){
    for(j=0; j<SZER; j++){
        if(tab2[i][j]=='#' && tab3[i][j]=='d') {
          tab2[i][j]='T';
          licznik[i][j]=0;
        }
      }
    }
}
void start(char tab[WYS][SZER], char tab2[WYS][SZER], char tab3[WYS][SZER], int licznik[WYS][SZER])
{
  zerowanie_licz(licznik);
  int x=0,y=0,flaga=1,predkosc=1;
  char kierunek; //kierunek wiatru
  zalesianie(tab); //losowo rozmieszczane drzewa
  show_tab(tab); //plansza
  deszcz(tab3); // uzupelnienie tab3 deszczem
  printf("\nWprowadz kierunek wiatru N,E,S,W lub Z (brak wiatru): "); // N - z Gory na Dol, S - z Dolu w Gore , E - W Lewo , W - w Prawo
  scanf("%s",&kierunek);
  if(kierunek!='N' && kierunek!='E' && kierunek!='S' && kierunek!='W' && kierunek!='Z'){
    kierunek='Z';
    printf("\nNieprawidlowa wartosc dla wiatru!\nWiatr ustawiony na Z - brak.\n");
  }
  if(!(kierunek=='Z')){
    printf("\nWprowadz predkosc wiatru 1-5: ");
    scanf("%d",&predkosc);
    if(predkosc>5){
      predkosc=1;
      printf("\nNieprawidlowa wartosc!\nPredkosc = 1\n");
    }
  }
  do{
    printf("\nWprowadz wspolrzedne podpalenia:");
    printf("\nX_max 75:");
    scanf("%d",&x);
    printf("\nY_max 22:");
    scanf("%d",&y);
    if(x>76 || y>23){
      czysc();
      show_tab(tab);
      printf("\nBledne dane!");
      flaga=0;
    }
      else break;
  }while(flaga==0);
  miejsce_podpalenia(tab,y,x);
  tab_cpy(tab,tab2);

  do{ //glowna petla odpowiedzialna za odswiezanie planszy
      czysc();//odswiezanie ekranu
      show_tab(tab2);
      spalanie(tab,tab2,licznik,kierunek,predkosc);
      gaszenie(tab3,tab2,licznik);
      Sleep(300);
  }while(spr_ogien(tab2)!=1);

    czysc();
    show_tab(tab2);
}
int main(){
  srand(time(NULL));
  int wybor=1;
  char tab[WYS][SZER];
  char tab2[WYS][SZER];
  char tab3[WYS][SZER];//tablica z deszczem
  int licznik[WYS][SZER];

  while(wybor!=2){
      start(tab,tab2,tab3,licznik);
      printf("\nCzy chcesz zaczac od nowa? (1)-TAK (2)-NIE : ");
      scanf("%d",&wybor);
      if(wybor==1) czysc();
  }
  printf("\nDo zobaczenia!\n");

    return 0;
}
