/*  File : general.h
    berisi fungsi dan prosedur yang dibutuhkan program secara general

*/

#ifndef GENERAL_H
#define GENERAL_H

#include "ADT/boolean.h"
#include "data.h"

/* Definisi fungsi umum di program */
void InitGame();
/* Procedure untuk menginisialisasi game data untuk new game */

void UpdateGameState();
/*  Procedure yang menjalankan berbagai routine saat waktu bertambah 1 tick */
/*  Diantaranya: 
    1. Update customer yang sedang nungggu (pending)
    2. Update customer yang sudah duduk dimeja (pending)
    3. Nambah waktu (done)
    4. Add customer(probabilitas) (pending) */

void UpdateWaitingCustomer();
/*  Procedure untuk update customer yang masih berada di waiting list */


void UpdateSeatedCustomer();
/*  Procedure untuk update customer yang sudah duduk*/

void AddCustomer();
/*  Procedure untuk add customer ke waiting list apabila list belum penuh */
/*  Add customer berbasis angka random, sehingga mungkin saja customer bertambah, mungkin tidak */

void Put();
/*  Procedure untuk membuat makanan dari bahan-bahan yang ada di tray */
/*  Hand mungkin kosong, atau bahan-bahan ada di hand secara terurut maupun acak */
/*  Hand kosong, tergantung dari urutan bahan yang ada di hand, mungkin ada makanan,
    mungkin juga tidak terbentuk makanan di Stack Tray */


void Take();
/*I.S. Posisi player dan posisi meja terdefinisi*/
/*F.S. Bahan yang dicari ditambahkan ke tray jika ada meja disekitar player*/
/*     Apabila tidak ada meja, maka tidak terjadi perubahan */

void BuildTreeText(BinTree *P, char* text, int* i);

#endif