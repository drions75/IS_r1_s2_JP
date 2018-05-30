/*
===============================================
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
  2.[ ] Wybieramy współrzędne gdzie ma zacząć rozprzestrzeniać się płomień,
  3.[ ] Drzewo zacznie się palić jeśli conajmniej jeden sąsiad płonie,
  4.[ ] Płonąca komórka zmienia się w pustą,
  5.[ ] Opcjonalnie rozchodzenie się ognia od podania kierunku wiatru.

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define WYS  20
#define SZER  100
void miejsce_podpalenia(char tab[WYS][SZER], int x, int y)
{ int i,j;
  for(i=0; i<x; i++)
  {
      for(j=0; j<y; j++)
      {
         tab[i][j]='#';

      }
  }
}

int losowanie(void)
{ return rand()%3+1;} // Dlatego 3 bo większa gęstość drzewek
void tablice(char tab[WYS][SZER])
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

int main()
{
  srand(time(NULL));
  int x=0,y=0;
  int i=0;
  int j=0;
  char tab[SZER][WYS];

  tablice(tab);
  show_tab(tab);
  printf("\n\nWprowadz wspolrzedne podpalenia:");
  printf("\nX:");
  scanf("%d",&x);
  printf("\nY:");
  scanf("%d",&y);
  miejsce_podpalenia(tab,x,y);
  system("cls");
  show_tab(tab);
}
