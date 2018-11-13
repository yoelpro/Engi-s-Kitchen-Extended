/* File : data.h */
/* berisi data yang diperlukan oleh game agar dapat berjalan  */

#ifndef data_H
#define data_H

#include "ADT/array.h"
#include "ADT/boolean.h"
#include "ADT/jam.h"
#include "ADT/listrekursif.h"
#include "ADT/matriks.h"
#include "ADT/mesinkar.h"
#include "ADT/mesinkata.h"
#include "ADT/pohon.h"
#include "ADT/point.h"
#include "ADT/stackt.h"

#define KOLOM 8
#define BARIS 8
#define MAX_MEJA 4
#define MAX_BAHAN 16
#define MAX_MAKANAN 9

enum JenisRuangan {
	Makan,	//0
	Dapur	//1
};

const char *JenisBahan[MAX_BAHAN] = {
	"Piring",		//0
	"Sendok",		//1
	"Garpu",		//2
	"EsKrim",		//3
	"Nasi",			//4
	"Roti",			//5
	"Spaghetti",	//6
	"Pisang",		//7
	"Stroberi",		//8
	"Telur",		//9
	"AyamGoreng",	//10
	"Patty",		//11
	"Sosis",		//12
	"Bolognese",	//13
	"Carbonara",	//14
	"Keju"			//15
};

const char *JenisMakanan[MAX_MAKANAN] = {
	"BananaSplit",			//0
	"Sundae",				//1
	"NasiTelurDadar",		//2
	"NasiAyamGoreng",		//3
	"Burger",				//4
	"HotDog",				//5
	"Keju",					//6
	"SpaghettiCarbonara",	//7
	"SpaghettiBolognese"	//8
};

typedef struct
{
	Point Posisi;
	int NoMeja;
	int JmlKursi;
	int Terisi; /* jumlah kursi yang terisi */
	boolean N [4+1]; /* array of boolean yang artinya kursi dinomori dari 1-4 secara clockwise, true artinya ada di map */
} Meja;

typedef struct 
{
	Matriks Map;
	Meja DMeja[MAX_MEJA+1];
	int JmlMeja;
	enum JenisRuangan Tipe;
} Ruangan;

typedef struct
{
	Ruangan CurrentRoom;
	Point PosisiPlayer;
	Stack Hand;
	Stack Tray;
	long Waktu;
	long Money;
	int Life;
} GameData;

typedef struct
{
	int NoMeja;
	int Kesabaran;
	int JmlOrang;
	boolean Star; /* true jika dia star */
} Customer;

typedef BinTree ResepMakanan;

#endif