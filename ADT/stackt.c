/* File : stackt.c */

#include "stackt.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStck (Stack *S)
{
    Top(*S) = Nol;
}


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStck (Stack S)
{
    return Top(S) == Nol;
}

boolean IsFullStck (Stack S)
{    
    return Top(S) == MaxEl;
}


/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, stackInfoType X)
{
    if (IsEmptyStck(*S))
    {
        Top(*S) = 1;
    }
    else
    {
        Top(*S)++;
    }

    InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, stackInfoType* X)
{
    *X = InfoTop(*S);

    if(Top(*S) == 1)
    {
        Top(*S) = Nol;
    }
    else
    {
        Top(*S)--;
    }
}