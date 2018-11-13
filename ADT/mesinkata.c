#include "boolean.h"
#include "mesinkata.h"
#include "mesinkar.h"
#include <stdio.h>

void STARTKATA()
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
  START();
  switch (CC)
  {
    case MARK :
    {
      EndKata = true;
      break;
    }
    default :
    {
      EndKata = false;
      SalinKata();
    }
  }
}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
  if (CC==MARK)
  {
    EndKata = true;
  }
  else
  {
     EndKata = false;
     SalinKata();
  }
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
  int i;
  //Algoritma
  i=1;
  do
  {
    // printf("%c\n",CC);
    if (i<=NMax)
    {
      CKata.TabKata[i] = CC;
      i++;
    }
    ADV();
  } while (!(CC==MARK || CC==BLANK));
  i--;
  CKata.Length = i;
}

boolean EqualKata(char* inputMesin, int length, char* inputBanding)
/*  Fungsi yang berguna untuk membandingkan input dengan suatu kata, misalnya:
    EqualKata(CKata.TabKata,CKata.Length,"UP")
    Akan menghasilkan true apabila sama, false jika string berbeda
*/
{
  int i = 0;
  while (i<length-1 && *(inputMesin+(i+1))==*(inputBanding+i))
  {
    i++;
  }
  return *(inputMesin+(i+1))==*(inputBanding+(i));
}

void BacaCommand()
/* Procedure yang digunakan 
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
  STARTCommand();
  switch (CCommand)
  {
    case MARK:
    {
      EndCommand = true;
      break;
    }
    default :
    {
      EndCommand = false;
      SalinCommand();
    }
  }
}

void SalinCommand()
/* Mengakuisisi command dari console, menyimpan dalam CCommand
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CCommand berisi kata yang sudah diakuisisi; 
          CC = \n */
{
  int i;
  //Algoritma
  i=1;
  do
  {
    // printf("%c\n",CC);
    if (i<=NMax)
    {
      Command.TabKata[i] = CCommand;
      i++;
    }
    ADVCommand();
  } while (!CCommand==ENTER);
  i--;
  Command.Length = i;
}