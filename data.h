/* File : data.h */
/* berisi data yang diperlukan oleh game agar dapat berjalan  */

#ifndef data_H
#define data_H
#define kol 8;
#define bar 8;
#define MaxMeja 4;

#include "boolean.h"

enum JenisRuangan {Makan,Dapur};
extern StackBahan Hand;
extern StackMakanan Tray;

typedef int Indeks;

typedef struct
{
	long Waktu;
	int Life;
	long Money;
} Game;

typedef struct 
{
	enum JenisRuangan Tipe;
	char Map [bar+1][kol+1];
	int JmlMeja;
	Meja DMeja [MaxMeja+1];


} Ruangan;

typedef struct
{
	int NoMeja;
	int JmlKursi;
	int Occ; /* jumlah kursi yang occupied */
	boolean N [4+1]; /* array of boolean yang artinya kursi dinomori dari 1-4 secara clockwise, true artinya ada di map */
} Meja;

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

typedef struct tElmtlist* address;

typedef struct tElmtlist {
	infotype info;
	address next;
} ElmtList;

typedef struct {
	address First;
} List;

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list : jika addressnya Last, maka Next(Last)=Nil */

#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) (L).First

/* PROTOTYPE */

#endif