/*===============================================
  AUTOMAT KOMÓRKOWY - "Symulator pożaru lasu" do 19.06.2018
-----------------------------------------------
  Damian Kaniewski 291565 UMK IS r1 s2
===============================================
  Zasady:
  Komórki dzielimy na trzy rodzaję:
    - puste [ ]
    - z drzewem [T]
    - płonące [#]
  1.[x] Losowa plansza wypełniona drzewami oraz pustymi miejscami,
  2.[x] Wybieramy współrzędne gdzie ma zacząć rozprzestrzeniać się płomień,
  3.[x] Drzewo zacznie się palić jeśli conajmniej jeden sąsiad płonie,
  4.[x] Płonąca komórka zmienia się w pustą,
  5.[x] Rozchodzenie się ognia od podania kierunku wiatru.
      a)np. wiatr wieje z Wschodu <-- czyli w lewo to ogień rozchodzi się 2 razy szybciej w lewo niż w innych kierunkach.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///WINDOWS///
#ifdef _WIN32
#include <windows.h>
#define czysc() system("cls")
#endif
////////////

///LINUX///
#ifdef __linux__
#include <unistd.h>
#define czysc() system("clear")
#define Sleep(ms) usleep((ms)*1000)

#endif
///////////

#define WYS  23
#define SZER  76
void wiatr(char kierunek, int *w1, int *w2, int i, int j) // funkcja odpowiedzialna za implementacje rozchodzenia sie ognia wraz z kierunkiem wiatru, w1 i w2 to zmienne wskaznikowe, ktore odnosza sie do petli spalanie.
{
  // i wysokosc j szerokosc
  //w1 wys , w2 szer
    switch(kierunek){
        case 'W': // wiatr z Zachodu (wieje w lewo)
            if(j<2) *w2=0;
            else  *w2=-1;
            *w1=0;
        break;
        case 'E': // wiatr ze Wschodu (wieje w prawo)
            if(j>SZER-3) *w2=0;
            else  *w2;
            *w1=0;
        break;
        case 'S': // wiatr z Południa (wieje w górę)
            if(i<2) *w1=0;
            else  *w1=-1;
            *w2=0;
        break;
        case 'N': // wiatr z Północy (wieje na dół)
            if(i>WYS-3) *w1=0;
            else  *w1;
            *w2=0;
        break;

    }
}
char spr_ogien(char tab[WYS][SZER])
{
  int i,j;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
        if(tab[i][j]=='#') return 0;
      }
    }
      return 1;
}
void miejsce_podpalenia(char tab[WYS][SZER], int x, int y)
{
         tab[x][y]='#';
}

int losowanie(void)
{ return rand()%2+1;} // Dlatego 3 bo większa gęstość drzewek

void zalesianie(char tab[WYS][SZER])
{
  int i,j;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
        if(losowanie()==1) tab[i][j]=' '; // jeżeli parzysta to pole jest puste
        else   tab[i][j]='T'; //jeżeli nieparzysta to rośnie drzewo
      }
  }
}
void tab_cpy(char tab[WYS][SZER], char tab2[WYS][SZER])
{
  int i,j,tmp=0;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
        tab2[i][j]=tab[i][j];
      }
  }
}
void show_tab(char tab[WYS][SZER])
{
    int i,j;
  for(i=0; i<=SZER+1; i++)
  {
    if(i==0)
      printf("%c",'|');
    else{
      if(i==SZER+1)
      printf("%c",'|');
      else
      printf("%c",'|');
      }
  }
    printf("\n");
  for(i=0; i<WYS; i++)
    {
        printf("%c",'|');
        for(j=0; j<SZER; j++)
        {
          printf("%c", tab[i][j]);
          if(j==SZER-1)
            printf("%c\n",'|');
        }

    }
  for(i=0;i<=SZER+1;i++)
  {
      printf("%c",'|');
  }
}
void spalanie(char tab[WYS][SZER], char tab2[WYS][SZER], int licznik[WYS][SZER], char kierunek)
{
  int i,j,k,l;
  int w1=0, w2=0;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
        if(tab[i][j]=='#')
        { //kończenie spalania drzewa  tab[WYS][SZER]
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
                if(i==WYS && j==0){ //lewy dolny rog
                    if(k==1) p1=WYS;
                    if(l==-1) p2=0;;
                }
                if(i==WYS && j==SZER){//prawy dolny rog
                    if(k==1) p1=WYS;
                    if(l==1) p2=SZER;
                }
                wiatr(kierunek,&w1,&w2,i,j);
                  if(!(k==0 && l==0)){ //tab[WYS][SZER]
                      if(tab[p1][p2]=='T') tab2[p1][p2]='#';
                      if(kierunek!='Z'){
                            if(tab[p1+w1][p2+w2]=='T') tab2[p1+w1][p2+w2]='#';
                  }
                }
              }
            }
          }
        }

      }

      tab_cpy(tab2,tab);
  }
int main(){
  srand(time(NULL));
  int x=0,y=0,i,j;;

  char kierunek='Z';
  char tab[WYS][SZER];
  char tab2[WYS][SZER];
  int licznik[WYS][SZER];
  //zerowanie licznika
  for(i=0; i<WYS; i++){
    for(j=0; j<SZER; j++){
        licznik[i][j]=0;}}

  zalesianie(tab); //losowo rozmieszczane drzewa
  show_tab(tab); //plansza
  printf("\nWprowadz kierunek wiatru N,E,S,W i Z - brak wiatru: "); // N - z Góry na Dół, S - z Dołu w Górę , E - W Lewo , W - w Prawo
  scanf("%c", &kierunek);

  printf("\n\nWprowadz wspolrzedne podpalenia:");
  printf("\nX:");
  scanf("%d",&x);
  printf("\nY:");
  scanf("%d",&y);

  miejsce_podpalenia(tab,y,x);
  tab_cpy(tab,tab2);

do
  {
    czysc();
    show_tab(tab2);
    spalanie(tab,tab2,licznik,kierunek);

    Sleep(500);
   }while(spr_ogien(tab2)!=1);
    czysc();
    show_tab(tab2);


}
