#include "ADT/boolean.h"
#include "ADT/stackt.h"
#include "ADT/matriks.h"
#include "ADT/point.h"
#include "ADT/pohon.h"
#include "ADT/mesinkar.h"
#include "ADT/mesinkata.h"
#include "data.h"
#include <stdlib.h>

#define MAP_HORIZONTAL_SIZE 8
#define MAP_VERTICAL_SIZE 8

boolean _kursi_exist (Matriks *map, Meja *meja, int i, int j) 
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (i < GetFirstIdxBrs(*map) || i > GetLastIdxBrs(*map) || j < GetFirstIdxKol(*map) || j > GetLastIdxKol(*map))
    {
        return false;
    }

    else if (ElmtMat(*map, i, j) == 'X' || ElmtMat(*map, i, j) == 'C')
    {
        ((*meja).JmlKursi)++;

        return true;
    }
}

boolean _kursi_isi_exist (Matriks *map, Meja *meja, int i, int j)
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (i < GetFirstIdxBrs(*map) || i > GetLastIdxBrs(*map) || j < GetFirstIdxKol(*map) || j > GetLastIdxKol(*map)) {
        return false;
    }

    else if (ElmtMat(*map, i, j) == 'C')
    {
        ((*meja).Terisi)++;

        return true;
    }
}

void _search_meja_in_ruangan (Ruangan *ruang)
{
    /* KAMUS LOKAL */
    int i, j;

    /* ALGORITMA */
    (*ruang).JmlMeja = 0;

    for (i=1;i<=MAP_VERTICAL_SIZE;i++)
    {
        for (j=1;j<=MAP_HORIZONTAL_SIZE;j++)
        {
            if (ElmtMat((*ruang).Map, i, j) >= '1' && ElmtMat((*ruang).Map, i, j) <= '9') 
            { // map berisi suatu karakter angka yang berarti sebuah meja
                ((*ruang).JmlMeja)++;

                ((*ruang).DMeja[(*ruang).JmlMeja]).Posisi = MakePoint(i, j);

                ((*ruang).DMeja[(*ruang).JmlMeja]).NoMeja = (int)(ElmtMat((*ruang).Map, i, j) - '0');

                ((*ruang).DMeja[(*ruang).JmlMeja]).JmlKursi = 0;
                
                ((*ruang).DMeja[(*ruang).JmlMeja]).N[1] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i+1, j);
                ((*ruang).DMeja[(*ruang).JmlMeja]).N[2] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i, j+1);
                ((*ruang).DMeja[(*ruang).JmlMeja]).N[3] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i-1, j);
                ((*ruang).DMeja[(*ruang).JmlMeja]).N[4] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i, j-1);

                ((*ruang).DMeja[(*ruang).JmlMeja]).N[1] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i+1, j);
                ((*ruang).DMeja[(*ruang).JmlMeja]).N[2] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i, j+1);
                ((*ruang).DMeja[(*ruang).JmlMeja]).N[3] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i-1, j);
                ((*ruang).DMeja[(*ruang).JmlMeja]).N[4] = _kursi_exist(&(*ruang).Map, &((*ruang).DMeja[(*ruang).JmlMeja]), i, j-1);
            }
        }
    }
}

void load_arr_ruangan(Ruangan Rooms[])
/*  Membaca ruangan dari file eksternal
 *  I.S. : Rooms[] sembarang
 *  F.S. : Rooms[] berisi ruangan dari file eksternal
 */
{
    /* KAMUS LOKAL */
    int ruangNo, i, j;

    /* ALGORITMA */
    START("Res/Ruangan.txt");

    for (ruangNo=1;ruangNo<=1;ruangNo++)
    {
        Rooms[ruangNo].Tipe = CC - '0';
        ADV(); ADV();

        MakeMatriks(MAP_VERTICAL_SIZE, MAP_HORIZONTAL_SIZE, &(Rooms[ruangNo].Map));
        for (i=1;i<=MAP_VERTICAL_SIZE;i++)
        {
            for (j=1;j<=MAP_HORIZONTAL_SIZE;j++)
            {
                ElmtMat(Rooms[ruangNo].Map, i, j) = CC;
                ADV();
            }
            ADV();
        }
        if( Rooms[ruangNo].Tipe == Makan) {
            _search_meja_in_ruangan(&Rooms[ruangNo]);
        }

        ADV();
    }

    while (!EOP)
    {
        ADV();
    }
}


void _build_resep (BinTree *ResepTree)
/* Membentuk sebuah pohon biner P dari file yang dibaca */
/* I.S. File berisi pohon resep dalam bentuk prefix.
Memori pasti cukup, alokasi pasti berhasil. */
/* F.S. ResepTree dibentuk dari pohon resep dalam dile */
{
    /* KAMUS LOKAL */
    int temp;

    /* ALGORITMA */
	ADV(); //karakter pertama sudah dibaca di driver dg START();
    IgnoreBlank();
	
    if (CC == ')')
	{
		*ResepTree = Nil;
	}
	else
	{
        if (CC >= '0' && CC <= '9') {
            temp = (int)(CC-'0');
        }
        else if (CC >= 'A' && CC <= 'F') {
            temp = (int)(CC - 'A') + 10;
        }
        else if (CC >= 'a' && CC <= 'f') {
            temp = (int)(CC - 'a') + 10;
        }
        else {
            temp = -1;
        }

        if (temp != -1) {
            *ResepTree = Tree(temp, Nil, Nil);

            IgnoreBlank();
            ADV();
            _build_resep(&Left(*ResepTree));

            IgnoreBlank();
            _build_resep(&Right(*ResepTree ));
        }
	}

    ADV();
}

void load_resep(BinTree *ResepTree)
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    START("Res/Resep.txt");

    if (!EOP) {
        _build_resep(ResepTree);
    }

    while (!EOP)
    {
        ADV();
    }
}

void load_gamedata()
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    
}