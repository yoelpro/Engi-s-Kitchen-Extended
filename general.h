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
    1. Update customer yang sedang nungggu
    2. Update customer yang sudah duduk dimeja
    3. Nambah waktu
    4. Add customer(probabilitas) */


#endif