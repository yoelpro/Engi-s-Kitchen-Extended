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
    1. Update customer yang sedang nungggu (pending)
    2. Update customer yang sudah duduk dimeja (pending)
    3. Nambah waktu (done)
    4. Add customer(probabilitas) (pending) */

void UpdateWaitingCustomer();
/*  Procedure untuk update customer yang masih berada di waiting list */


void UpdateSeatedCustomer();
/*  Procedure untuk update customer yang sudah duduk*/

void AddCustomer();
/*  Procedure untuk add customer ke waiting list apabila list belum penuh */
/*  Add customer berbasis angka random, sehingga mungkin saja customer bertambah, mungkin tidak */

void Put();
/*  Procedure untuk membuat makanan dari bahan-bahan yang ada di tray */
/*  Hand mungkin kosong, atau bahan-bahan ada di hand secara terurut maupun acak */
/*  Hand kosong, tergantung dari urutan bahan yang ada di hand, mungkin ada makanan,
    mungkin juga tidak terbentuk makanan di Stack Tray */


void Take();
/*I.S. Posisi player dan posisi meja terdefinisi*/
/*F.S. Bahan yang dicari ditambahkan ke tray jika ada meja disekitar player*/
/*     Apabila tidak ada meja, maka tidak terjadi perubahan */

void FreeMeja(Meja * table);
/*I.S. Meja berisi customer
F.S. Meja kosong dari customer. Id=-1, Terisi=0, order=-1, NIsiCustomer false*/

int searchMejaII(Point Posisi, Meja meja,int X); //X==1 for place. X==2 for give and order
/*Lanjutan dari searchMejaII
I.S. Meja mempunyai arah atas bawah kiri kanan yang mungkin berisi kursi atau tidak
F.S. Sesuai fungsi nilai X, fungsi akan mencari Point Posisi yang sama terhadap empat arah meja tersebut*/

int searchMeja(Point P1, Meja meja, int X);
/*I.S. Player memiliki 4 arah, yaitu atas bawah kiri kanan yang kemungkinan memiliki object di arah tersebut atau tidak
F.S. Mengembalikan NoMeja apabila posisi player dalam 4 arah tersebut sama dengan posisi bersangkutan dari meja. searchMeja akan menyambung ke searchMejaII*/

int searchTabOrders(int tableno);
/*I.S. TabOrders ialah variabel global yang berisi pesanan yang ada pada saat itu
F.S. mengembalikan urutan array keberapa dalam TabOrders yang bersangkutan dengan nomor meja di parameter*/

void orderFood();
/*I.S. Meja bisa saja kosong. Meja kemungkinan berisi customer yang telah memesan sebelumnya. Player berada di manapun*/
/*F.S. List Order bertambah apabila memenuhi syarat. Failed apabila player berada tidak berdampingan dari kursi meja atau meja secara langsung dan order telah dilakukan seblumnya*/

void placeCustomer();
/*I.S. Player berada di manapun. Tabel QWaitingC mungkin kosong
F.S. apabila memenuhi, Tabel QSeatedC bertambah satu elemennya dan QWaitingC berkurang satu elemennya. Kesabaran customer bertambah secara random. Failed jika player berada jauh. Customer di meja bersangkutan belum melakukan order*/

void giveFood();
/*I.S.player dapat berada di manapun. Tray mungkin kosong.
F.S. Apabila memenuhi, meja yang telah menerima makanan akan mengosongkan meja dan QSeatedC berkurang satu elemennya*/

#endif