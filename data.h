/* File : data.h */
/* berisi data yang diperlukan oleh game agar dapat berjalan  */

#ifndef data_H
#define data_H

#include "boolean.h"

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

extern StackBahan Hand;
extern StackMakanan Tray;

typedef int Indeks;

typedef struct
{
	long Waktu;
	int Life;
	long Money;
} GameData;

typedef struct
{
	int NoMeja;
	int JmlKursi;
	int Occ; /* jumlah kursi yang occupied */
	boolean N [4+1]; /* array of boolean yang artinya kursi dinomori dari 1-4 secara clockwise, true artinya ada di map */
} Meja;

typedef struct 
{
	enum JenisRuangan Tipe;
	char Map[BARIS+1][KOLOM+1];
	int JmlMeja;
	Meja DMeja[MAX_MEJA+1];
} Ruangan;

typedef struct
{
	int NoMeja;
	int Kesabaran;
	int JmlOrang;
	boolean Star; /* true jika dia star */
} Customer;

typedef struct
{
	int No; /* Nomor makanan yang berkorespondensi dengan jenis makanan tertentu */
} Makanan;

typedef struct
{
	int No; /* Nomor bahan makanan yang berkorespondensi dengan jenis bahan tertentu */
} Bahan;

typedef struct 
{
	Makanan TI [5+1];
	Indeks TOP;
} StackMakanan; /* Struktur data untuk tray didalam game */

typedef struct
{
	Bahan TI [5+1];
	Indeks TOP;
} StackBahan;

typedef struct tElmtlist *address;

typedef struct tElmtlist {
	infotype info;
	address next;
} ElmtList;

typedef struct {
	address First;
} List;

#endif