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
#include "ADT/queue.h"

#define KOLOM 8
#define BARIS 8
#define MAX_MEJA 4
#define MAX_BAHAN 16
#define MAX_MAKANAN 9

enum JenisRuangan
{
	Makan,	//0
	Dapur	//1
};

/* ********** SELEKTOR ********** */

/* Selektor untuk GameData */
#define Waktu(SimulationData)		(SimulationData).Waktu
#define Money(SimulationData)		(SimulationData).Money
#define Life(SimulationData)		(SimulationData).Life
#define CurrentRoom(SimulationData)	(SimulationData).CurrentRoom

extern const char * JenisBahan[MAX_BAHAN];

const char * JenisMakanan[MAX_MAKANAN];

typedef struct
{
	int Id;
	Point Posisi;
	int NoMeja;
	int JmlKursi;
	int Terisi; /* jumlah kursi yang terisi */
	boolean N [4+1]; /* array of boolean yang artinya kursi dinomori dari 1-4 secara clockwise, true artinya ada di map */
	boolean NIsiCustomer[4+1]; //array of boolean yang diduduki dari atas dan clockwise
	int order; //menu yang dipesan dari 0 ke 8
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
	int CurrentRoom;
	Point PosisiPlayer;
	Stack Hand;
	Stack Tray;
	long Waktu;
	long Money;
	int Life;
	int JmlCustomer;
} SimulationData;


typedef struct
{
	int NoMeja;
	int Kesabaran;
	int JmlOrang;
	boolean Star; // true jika dia star
} TypeCustomer;

typedef BinTree ResepMakanan;

/* Declaration of global variable */
extern SimulationData GameData;
extern Stack Hand;
extern Stack Tray;
extern TypeQueueCustomer QWaitingC;	// Waiting customer
extern TypeQueueCustomer QSeatedC;	// Seating customer
extern TabOrder TabOrders;
extern Ruangan RSkrg;
extern Ruangan Room [4+1];

#endif
