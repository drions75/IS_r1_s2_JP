/*===============================================
  AUTOMAT KOMÓRKOWY - "Symulator pożaru lasu"
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
  5.[ ] Opcjonalnie rozchodzenie się ognia od podania kierunku wiatru.

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
      printf("%c",'|' );
    else if(i==SZER+1)
      printf("%c",'|');
    else
      printf("%c",'|');
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
void spalanie(char tab[WYS][SZER], char tab2[WYS][SZER], int licznik[WYS][SZER])
{
  int i,j;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
        if(tab[i][j]=='#')
        {
           //kończenie spalania drzewa
           if(licznik[i][j]==2) tab2[i][j]=' ';
           else licznik[i][j]++;
           //pod
           if(tab[i+1][j]=='T')    tab2[i+1][j]='#';
           //nad
           if(tab[i-1][j]=='T')    tab2[i-1][j]='#';
           //lewo
           if(tab[i][j-1]=='T')    tab2[i][j-1]='#';
           //prawo
           if(tab[i][j+1]=='T')    tab2[i][j+1]='#';
           //pod lewo
           if(tab[i+1][j-1]=='T')  tab2[i+1][j-1]='#';
           //nad lewo
           if(tab[i-1][j-1]=='T')  tab2[i-1][j-1]='#';
           //pod lewo
           if(tab[i-1][j+1]=='T')  tab2[i-1][j+1]='#';
           //nad lewo
           if(tab[i+1][j+1]=='T')  tab2[i+1][j+1]='#';

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
  char tab[WYS][SZER];
  char tab2[WYS][SZER];
  int licznik[WYS][SZER];
  //zerowanie licznika
  for(i=0; i<WYS; i++)
    for(j=0; j<SZER; j++)
        licznik[i][j]=0;

  zalesianie(tab);
  show_tab(tab);

  printf("\n\nWprowadz wspolrzedne podpalenia:");
  printf("\nX:");
  scanf("%d",&x);
  printf("\nY:");
  scanf("%d",&y);
  miejsce_podpalenia(tab,x,y);
  tab_cpy(tab,tab2);
//wersja manualne odświezanie
  /*do
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
    spalanie(tab,tab2,licznik);
    Sleep(1000);
   }while(1);
}
