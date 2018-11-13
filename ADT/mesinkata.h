/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "boolean.h"
#include "mesinkar.h"

#define NMax 50
#define BLANK ' '
#define ENTER '\n'

typedef struct {
	char TabKata[NMax+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;
extern boolean EndCommand;
extern Kata Command;

void STARTKATA();
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

boolean EqualKata(char* inputMesin, int length, char* inputBanding);
/*  Fungsi yang berguna untuk membandingkan input dengan suatu kata, misalnya:
    EqualKata(CKata.TabKata,CKata.Length,"UP")
    Akan menghasilkan true apabila sama, false jika string berbeda
*/

void BacaCommand();
/* I.S. : CCommand sembarang 
   F.S. : EndKata = true, dan CCommand = MARK; 
          atau EndKata = false, Command adalah kata yang sudah diakuisisi,
          CCommand karakter pertama sesudah karakter terakhir kata */

void SalinCommand();
/* Mengakuisisi command dari console, menyimpan dalam CCommand
   I.S. : CCommand adalah karakter pertama dari kata
   F.S. : CCommand berisi kata yang sudah diakuisisi; 
          CCommand = \n */


#endif

