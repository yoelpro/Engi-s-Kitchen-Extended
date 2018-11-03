/* Nama: Stefanus Ardi Mulia */
/* NIM: 13517119 */
/* File: jam.h */
/* Tanggal: 5 September 2018 */
/* Implementasi ADT Point */

#include "point.h"
#include "boolean.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (float X, float Y){
/* Membentuk sebuah Point dari komponen-komponennya */
    /* KAMUS LOKAL */
    Point poi;

    /* ALGORITMA */
    Absis(poi) = X;
    Ordinat(poi) = Y;

    return poi;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPoint (Point * P){
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   Point P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk Point <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
    /* KAMUS LOKAL */
    float X, Y;

    /* ALGORITMA */
    scanf("%f %f", &X, &Y);

    * P = MakePoint(X, Y);
}

void TulisPoint (Point P){
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    printf("(%2f,%2f)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ (Point P1, Point P2){
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

boolean NEQ (Point P1, Point P2){
/* Mengirimkan true jika P1 tidak sama dengan P2 */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return !((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (Point P){
/* Menghasilkan true jika P adalah titik origin */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return ((Absis(P) == 0) && (Ordinat(P) == 0));
}

boolean IsOnSbX (Point P){
/* Menghasilkan true jika P terletak Pada sumbu X */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (Ordinat(P) == 0);
}

boolean IsOnSbY (Point P){
/* Menghasilkan true jika P terletak pada sumbu Y */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (Absis(P) == 0);
}

int Kuadran (Point P){
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if ((Absis(P) > 0) && (Ordinat(P) > 0 )){
        return 1;
    }
    else if ((Absis(P) < 0) && (Ordinat(P) > 0 )){
        return 2;
    }
    else if ((Absis(P) < 0) && (Ordinat(P) < 0 )){
        return 3;
    }
    else if ((Absis(P) > 0) && (Ordinat(P) < 0 )){
        return 4;
    }
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
Point NextX (Point P){
/* Mengirim salinan P dengan absis ditambah satu */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return MakePoint(Absis(P) + 1, Ordinat(P));
}

Point NextY (Point P){
/* Mengirim salinan P dengan ordinat ditambah satu */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return MakePoint(Absis(P), Ordinat(P) + 1);
}

Point PlusDelta (Point P, float deltaX, float deltaY){
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return MakePoint(Absis(P) + deltaX, Ordinat(P) + deltaY);
}

Point MirrorOf (Point P, boolean SbX){
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (SbX == true){
        return MakePoint(Absis(P), -Ordinat(P));
    }
    else{
        return MakePoint(-Absis(P), Ordinat(P));
    }
}

float Jarak0 (Point P){
/* Menghitung jarak P ke (0,0) */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return sqrt((Absis(P)*Absis(P)) + (Ordinat(P)*Ordinat(P)));
}

float Panjang (Point P1, Point P2){
/* Menghitung jarak antara P1 dengan P2 */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return sqrt((Absis(P1)-Absis(P2))*(Absis(P1)-Absis(P2))
        + (Ordinat(P1)-Ordinat(P2))*(Ordinat(P1)-Ordinat(P2))
    );
}

void Geser (Point *P, float deltaX, float deltaY){
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Absis(* P) += deltaX;
    Ordinat(* P) += deltaY;
}

void GeserKeSbX (Point *P){
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Ordinat(* P) = 0;
}

void GeserKeSbY (Point *P){
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Absis(* P) = 0;
}

void Mirror (Point *P, boolean SbX){
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (SbX == true){
        Ordinat(* P) *= -1;
    }
    else{
        Absis(* P) *= -1;
    }
}

void Putar (Point *P, float Sudut){
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
    /* KAMUS LOKAL */
    float sudutRad, tempX, tempY;

    /* ALGORITMA */
    sudutRad = (Sudut/180) * PI;
    tempX = Absis(* P);
    tempY = Ordinat(* P);

    Absis(* P) = (tempX * cos(sudutRad)) + (tempY * sin(sudutRad));
    Ordinat(* P) = (tempX * -sin(sudutRad)) + (tempY * cos(sudutRad));
}
