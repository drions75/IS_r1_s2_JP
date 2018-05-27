/*
===============================================
  AUTOMAT KOMÓRKOWY - "Symulator pożaru lasu"
-----------------------------------------------
  Damian Kaniewski 291565 UMK IS r1 s2
===============================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SZER  75
#define WYS  23



void gotoxy(int x, int y)
{
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

  int t1[SZER][WYS] = {0};
  int t2[SZER][WYS] = {0};
  int flaga=0;

void show_tab()
{
  int x,y;
  for(x=0; x<WYS;x++)
  {
    for(y=0;y<SZER;y++)
    {
      if (t1[x][y] == 1)
      {
        if(t2[x][y] != 1)
        {
          gotoxy(x+1,y+1);
          printf("x");
        }
      }
    }
  }
}
int main()
{
show_tab();
return 0;
}
