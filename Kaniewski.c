/*===============================================
  AUTOMAT KOMÓRKOWY - "Symulator pożaru lasu" do 17.06.2018
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
  5.[ ] Rozchodzenie się ognia od podania kierunku wiatru.
      a)np. wiatr wieje z Wschodu <-- czyli w lewo to ogień rozchodzi się 3 razy szybciej w lewo niż w innych kierunkach.
  6.[ ] Możliwość wprowadzenia opadów deszczu
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define WYS  20
#define SZER  100

void miejsce_podpalenia(char tab[WYS][SZER], int x, int y)
{
         tab[x][y]='#';
}


int losowanie(void)
{ return rand()%3+1;} // Dlatego 3 bo większa gęstość drzewek
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
void spalanie(char tab[WYS][SZER], char tab2[WYS][SZER], int licznik[WYS][SZER], char wiatr)
{
  int i,j,k,l;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
        if(tab[i][j]=='#')
        { //kończenie spalania drzewa  tab[WYS][SZER]
           if(licznik[i][j]==2) tab2[i][j]='0';
           else licznik[i][j]++;
           for(k=-1; k<2; k++){
              for(l=-1; l<2; l++){
              int p1=i+k;
              int p2=j+l;

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
                if(wiatr=='W')
                {
                  if(tab[i][j-2]=='T')    tab2[i][j-2]='#';
                }
                  if(!(k==0 && l==0) && wiatr=='W'){
                      if(tab[p1][p2]=='T') tab2[p1][p2]='#';
                        if(tab[p1-1][p2]=='T') tab2[p1-1][p2]='#';
                }
              }
            }
        /*
           if(tab[i+1][j]=='T')    tab2[i+1][j]='#';
           //nad
           if(tab[i-1][j]=='T')    tab2[i-1][j]='#';
           //lewo
           if(tab[i][j-1]=='T')    tab2[i][j-1]='#';
           //prawo
           if(tab[i][j+1]=='T')    tab2[i][j+1]='#';
           // doł lewo
           if(tab[i+1][j-1]=='T')  tab2[i+1][j-1]='#';
           // dol prawo
           if(tab[i-1][j+1]=='T')  tab2[i-1][j+1]='#';
           //gora lewo
           if(tab[i-1][j-1]=='T')  tab2[i-1][j-1]='#';
           //gora prawo
           if(tab[i-1][j+1]=='T')  tab2[i-1][j+1]='#';
          */

            }

        }
      }
      tab_cpy(tab2,tab);
  }



int main()
{

  srand(time(NULL));
  int x=0,y=0;
  int i,j;
  char znak=0;
  char wiatr=0;
  char tab[WYS][SZER];
  char tab2[WYS][SZER];
  int licznik[WYS][SZER];
  //zerowanie licznika
  for(i=0; i<WYS; i++){
    for(j=0; j<SZER; j++){
        licznik[i][j]=0;}}

  zalesianie(tab);
  show_tab(tab);
  printf("\nWprowadz kierunek wiatru N,E,S,W i Z - brak wiatru: "); // N - z Góry na Dół, S - z Dołu w Górę , E - W Lewo , W - w Prawo
  scanf("%c", &wiatr);
  printf("\n\nWprowadz wspolrzedne podpalenia:");
  printf("\nX:");
  scanf("%d",&x);
  printf("\nY:");
  scanf("%d",&y);

  miejsce_podpalenia(tab,x,y);
  tab_cpy(tab,tab2);
//wersja manualne odświezanie
/*
  do
  {
      system("cls");
    show_tab(tab2);
    spalanie(tab,tab2,licznik);

   }while((znak=getch())!=27);
*/
//Automatyczne odswiezanie

do
  {
      system("cls");
    show_tab(tab2);
    spalanie(tab,tab2,licznik,wiatr);
    Sleep(100);
   }while(1);



}
