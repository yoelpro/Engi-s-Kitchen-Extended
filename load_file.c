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

int _hex_to_int(char target)
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (target >= '0' && target <= '9') {
        return (int)(CC-'0');
    }
    else if (target >= 'a' && target <= 'f') {
        return (int)(CC - 'a') + 10;
    }
    else if (target >= 'A' && target <= 'F') {
        return (int)(CC - 'A') + 10;
    }
    else {
        return -1;
    }
}

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
    int i, j, jumlahTotalMeja;

    /* ALGORITMA */
    (*ruang).JmlMeja = 0;
     jumlahTotalMeja = 0;

    for (i=1;i<=MAP_VERTICAL_SIZE;i++)
    {
        for (j=1;j<=MAP_HORIZONTAL_SIZE;j++)
        {
            if (_hex_to_int(ElmtMat((*ruang).Map, i, j)) != -1) 
            { // map berisi suatu karakter hexadecimal yang berarti sebuah meja
                ((*ruang).JmlMeja)++;
                jumlahTotalMeja++;

                (DMeja[jumlahTotalMeja]).Posisi = MakePoint(i, j);

                (DMeja[jumlahTotalMeja]).NoMeja = _hex_to_int(ElmtMat((*ruang).Map, i, j));

                if ((*ruang).Tipe == Makan) {
                    (DMeja[jumlahTotalMeja]).JmlKursi = 0;
                    
                    (DMeja[jumlahTotalMeja]).N[1] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i+1, j);
                    (DMeja[jumlahTotalMeja]).N[2] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i, j+1);
                    (DMeja[jumlahTotalMeja]).N[3] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i-1, j);
                    (DMeja[jumlahTotalMeja]).N[4] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i, j-1);

                    (DMeja[jumlahTotalMeja]).N[1] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i+1, j);
                    (DMeja[jumlahTotalMeja]).N[2] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i, j+1);
                    (DMeja[jumlahTotalMeja]).N[3] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i-1, j);
                    (DMeja[jumlahTotalMeja]).N[4] = _kursi_exist(&(*ruang).Map, &(DMeja[jumlahTotalMeja]), i, j-1);
                }
            }
        }
    }
}

void _get_doors(Graph *Doors, int ruangAsal)
{
    /* KAMUS LOKAL */
    int x, y, ruangTujuan;
    adrSuccNode Pt;

    /* ALGORITMA */
    ADV();
    x = _hex_to_int(CC);
    ADV(); ADV();
    y = _hex_to_int(CC);
    ADV(); ADV(); IgnoreBlank();
    
    ruangTujuan = _hex_to_int(CC);
    InsertEdge(Doors, ruangAsal, ruangTujuan, &Pt);
    InfoG(Pt) = MakePoint(x, y);
    ADV(); ADV();
}

void load_arr_ruangan(Graph *Doors, Ruangan Rooms[], int NRooms)
/*  Membaca ruangan dari file eksternal
 *  I.S. : Rooms[] sembarang
 *  F.S. : Rooms[] berisi ruangan dari file eksternal
 */
{
    /* KAMUS LOKAL */
    int ruangNo, i, j, doorCount;

    /* ALGORITMA */
    START("Res/Ruangan.txt");

    for (ruangNo=1;ruangNo<=NRooms;ruangNo++)
    {
        IgnoreBlank();
        Rooms[ruangNo].Tipe = _hex_to_int(CC);
        ADV(); ADV();
        
        doorCount = _hex_to_int(CC);
        ADV(); ADV();

        for (i=1;i<=doorCount;i++) {
            _get_doors(Doors, ruangNo);
        }

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
        
        _search_meja_in_ruangan(&Rooms[ruangNo]);
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
        temp = _hex_to_int(CC);

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