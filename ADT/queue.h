/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#ifndef queue_H
#define queue_H

#include "boolean.h"

#define Nol 0
/* Konstanta untuk mendefinisikan address tak terdefinisi */

/* Definisi elemen dan address */
typedef int infotype;
typedef int address;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct { infotype * T;   /* tabel penyimpan elemen */
                 address HEAD;  /* alamat penghapusan */
                 address TAIL;  /* alamat penambahan */
                 int MaxElQ;     /* Max elemen queue */
               } Queue;
/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxElQ(Q) (Q).MaxElQ

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFull (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmt (Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmpty (Queue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void Del (Queue * Q, infotype * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

/* ------------------------------ Queue Pelanggan ------------------------ */

/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */

/* Definisi elemen dan address */
#define MaxElQC 20  /* Max Pelanggan 20 orang */

typedef int addressCustomer;   /* indeks tabel */

struct TypeCustomer
{
    int Id;
	int NoMeja;
	int Kesabaran;
	int JmlOrang;
	boolean Star; /* true jika dia star */
};


/* Deklarasi variabel bertype Queue : */
typedef struct
{   
    struct TypeCustomer Customer[MaxElQC+1];   /* tabel penyimpan elemen */
    addressCustomer HEAD;
    addressCustomer TAIL;
}   TypeQueueCustomer;

/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define InfoHeadC(Q) (Q).Customer[(Q).HEAD]
#define InfoTailC(Q) (Q).Customer[(Q).TAIL]

/* ********* Prototype ********* */
boolean IsEmptyQC (TypeQueueCustomer QC);
/* Mengirim true jika Q kosong: lihat definisi di atas */
/* Status: Tested */

boolean IsFullQC (TypeQueueCustomer QC);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
/* Status: Tested */

int NBElmtQC (TypeQueueCustomer QC);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
/* Status: Tested */

/* *** Kreator *** */
void CreateEmptyQC(TypeQueueCustomer* QC);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
/* Status: Tested */

/* *** Primitif Add/Delete *** */
void AddCustomerWC(TypeQueueCustomer *QC, int id, int kesabaran, int Orang, boolean IsStar);
/* Proses: Menambahkan X pada Q dengan aturan FIFO kecuali star */
/* I.S. Q mungkin kosong, tabel penampung elemen QC TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" */
/* Status: Tested */

void DelCustomerQC(TypeQueueCustomer *QC, int id);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. Setelah mendelete customer dengan id tertentu, maka element akan maju
        Q mungkin kosong */
/* Status: Tested */        

void CleanQC(TypeQueueCustomer *QC);
/* Proses: Menghapus customer yang sudah hilang kesabaran */
/* I.S. Q tidak mungkin kosong */
/* F.S. Menghapus customer yang kesabarannya 0
        Q mungkin kosong */
/* Status: Tested */
#endif