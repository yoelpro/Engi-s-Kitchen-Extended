/* Nama: Stefanus Ardi Mulia */
/* NIM: 13517119 */
/* File : stackt.c */
/* Tanggal: 17 Oktober 2018 */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#include "stackt.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStck (Stack *S){
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nol */
    /* KAMUS */

    /* ALGORITMA */
    Top(*S) = Nol;
}


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStck (Stack S){
/* Mengirim true jika Stack kosong: lihat definisi di atas */
    /* KAMUS */

    /* ALGORITMA */
    return Top(S) == Nol;
}

boolean IsFullStck (Stack S){
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
    /* KAMUS */

    /* ALGORITMA */
    return Top(S) == MaxEl;
}


/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, stackInfoType X){
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
    /* KAMUS */

    /* ALGORITMA */
    if(IsEmptyStck(*S)){
        Top(*S) = 1;
    }
    else{
        Top(*S)++;
    }

    InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, stackInfoType* X){
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    /* KAMUS */

    /* ALGORITMA */
    *X = InfoTop(*S);

    if(Top(*S) == 1){
        Top(*S) = Nol;
    }
    else{
        Top(*S)--;
    }
}