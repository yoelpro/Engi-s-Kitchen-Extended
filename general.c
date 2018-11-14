/* Nama: Stefanus Ardi Mulia */
/* NIM: 13517119 */
/* File : stackt.c */
/* Tanggal: 17 Oktober 2018 */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#include "general.h"
#include "data.h"

void InitGame()
/* Procedure untuk menginisialisasi game data untuk new game */
{
    CurrentRoom(GameData) = 4; //Dapur
    GameData.PosisiPlayer = MakePoint(4,4); //Sepakati dapur 4,4 harus kosong dan tidak menjebak
    CreateEmptyStck(&GameData.Hand);
    CreateEmptyStck(&GameData.Tray);
    Waktu(GameData) = 0;
    Money(GameData) = 0;
    Life(GameData) = 5;

    /* Reading dari file (belum diimplementasi) */
    
}