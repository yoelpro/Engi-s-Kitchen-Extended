/* File : data.h */
/* berisi data yang diperlukan oleh game agar dapat berjalan  */

#ifndef data_H
#define data_H


#include "boolean.h"

#define Nil NULL

extern StackBahan Hand;
extern StackMakanan Tray;
extern int Waktu;
extern int Life;
extern int Money;
typedef int Indeks;

typedef struct
{
	int NoMeja;
	int JlhKursi;
	int Occ; /* jumlah kursi yang occupied */
	boolean N [4+1]; /* array of boolean yang artinya kursi dinomori dari 1-4 secara clockwise, true artinya ada di map */
} Meja;

typedef struct
{
	int NoMeja;
	int Kesabaran;
	int JlhOrang;
	boolean Star; /* true jika dia star */
} Costumer;

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
	Makanan T [5+1];
	Indeks TOP;
} StackMakanan; /* Struktur data untuk tray didalam game */

typedef struct
{
	Bahan T [5+1];
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