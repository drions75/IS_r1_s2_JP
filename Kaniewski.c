/*
===============================================
  AUTOMAT KOMÓRKOWY - "Symulator pożaru lasu"
-----------------------------------------------
  Damian Kaniewski 291565 UMK IS r1 s2
===============================================
  Zasady:
  Komórki dzielimy na trzy rodzaję:
    - puste [0]
    - z drzewem [T]
    - płonące [#]
  1. Losowa plansza wypełniona drzewami oraz pustymi miejscami,
  2. Wybieramy współrzędne gdzie ma zacząć rozprzestrzeniać się płomień,
  3. Drzewo zacznie się palić jeśli conajmniej jeden sąsiad płonie,
  4. Płonąca komórka zmienia się w pustą,
  5. Opcjonalnie rozchodzenie się ognia od podania kierunku wiatru.

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define WYS  20
#define SZER  100

void tablice(char tab[WYS][SZER])
{
  int i,j;
  for(i=0; i<WYS; i++)
  {
      for(j=0; j<SZER; j++)
      {
          tab[i][j]=' ';
      }
  }
}
void show_tab(char tab[WYS][SZER])
{
    int i,j;
  for(i=0; i<=SZER+1; i++)
  {
    if(i==0)
      printf("%c",'H' );
    else if(i==SZER+1)
      printf("%c",'H');
    else
      printf("%c",'H');
  }
    printf("\n");
  for(i=0; i<WYS; i++)
    {
        printf("%c",'H');
        for(j=0; j<SZER; j++)
        {
          printf("%c", tab[i][j]);
          if(j==SZER-1)
            printf("%c\n",'H');
        }

    }
  for(i=0;i<=SZER+1;i++)
  {
      printf("%c",'H');
  }
}

int main()
{
  int x=3,y=3;
  int i=0;
  int j=0;
  char tab[SZER][WYS];

  tablice(tab);
  show_tab(tab);
}
