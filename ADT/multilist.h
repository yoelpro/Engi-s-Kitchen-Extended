/* File : stackt.h */
/* Deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#ifndef MULTILIST_H
#define MULTILIST_H

#include "boolean.h"
#include "point.h"
#include <stdlib.h>

#define Nol 0
#define MaxEl 10
/* Nil adalah stack dengan elemen kosong . */
/* Karena indeks dalam bhs C dimulai 0 maka tabel dg indeks 0 tidak dipakai */

typedef struct tNodeG* adrNode;

typedef struct tSuccNode* adrSuccNode;

typedef struct tGraph{
    adrNode First;
} Graph;

typedef struct tSuccNode{
    Point Info;
    adrNode Succ;
    adrSuccNode Next; 
} SuccNode;

typedef struct tNodeG{
    int Id;
    int NPred;
    adrSuccNode Trail;
    adrNode Next;
} NodeG;

#define FirstG(G) (G).First
#define Id(Pn) (Pn)->Id
#define Trail(Pn) (Pn)->Trail
#define NPred(Pn) (Pn)->NPred
#define NextG(P) (P)->Next
#define Succ(Pt) (Pt)->Succ
#define InfoG(Pt) (Pt)->Info

/* Konstruktor */
void CreateGraph(Graph *G);

adrNode AlokNodeG(int X);

adrSuccNode AlokSuccNode(adrNode Pn);

/* Destruktor */
void DealokNodeG(adrNode P);

void DealokSuccNode(adrSuccNode P);

/* Primitif lain */
adrNode SearchNode(Graph G, int X);

adrSuccNode SearchEdge(Graph G, int prec, int succ);

void InsertNode(Graph* G, int X, adrNode* Pn);

void InsertEdge(Graph* G, int prec, int succ, adrSuccNode *Pt);

boolean IsEmptyG(Graph G);

#endif
