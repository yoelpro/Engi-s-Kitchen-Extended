#ifndef load_file_H
#define load_file_H

#include "ADT/boolean.h"
#include "ADT/stackt.h"
#include "ADT/matriks.h"
#include "ADT/point.h"
#include "ADT/pohon.h"
#include "data.h"

extern int jumlahTotalMeja;

void load_arr_ruangan(Graph *Doors, Ruangan Rooms[], int NRooms);
/*  Membaca ruangan dari file eksternal
 *  I.S. : Rooms[] sembarang, NRooms terdefinisi
 *  F.S. : Rooms[] berisi Nrooms buah ruangan dari file eksternal
 */

void load_resep(BinTree *ResepTree);
/*  Membaca resep dari file eksternal mengacu pada daftar bahan
 *  I.S. : ResepTree sembarang
 *  F.S. : ResepTree berisi resep dari file eksternal
 */

void load_gamedata(); //not implemented yet

#endif