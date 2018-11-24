/* File: mesinkar.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#include "boolean.h"

#define MARK '.'
#define ENTER '\n'
/* State Mesin */
extern char CC;
extern char CCommand;
extern boolean EOP;

void START(char *fileName);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
          Jika CC != MARK maka EOP akan padam (false)
          Jika CC = MARK maka EOP akan menyala (true) */

void ADV();
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */

void STARTCommand();
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CCommand adalah karakter pertama pada pita. Jika CCommand != MARK maka EOP akan padam (false).
          Jika CCommand = MARK maka EOP akan menyala (true) */

void ADVCommand();
/*Pita dimajukan satu karakter. 
  I.S. : Karakter pada jendela = 
          CCommand, CCommand != MARK
  F.S. : CCommand adalah karakter berikutnya dari CCommand yang lama, 
          CCommand mungkin = MARK.
  Jika CCommand = MARK maka EOP akan menyala (true) */

void CurseADVCommand();
/*Pita dimajukan satu karakter. 
  I.S. : Karakter pada jendela = 
          CCommand, CCommand != MARK
  F.S. : CCommand adalah karakter berikutnya dari CCommand yang lama, 
          CCommand mungkin = MARK.
  Jika CCommand = MARK maka EOP akan menyala (true) */

#endif
