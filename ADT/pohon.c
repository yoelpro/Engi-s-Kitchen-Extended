/* Nama: Stefanus Ardi Mulia */
/* NIM: 13517119 */
/* Tanggal: 21 November 2018 */
/* File: bintree.c */
/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type InfotypeTree, type addrNode, dan beberapa fungsi disesuikan 
   karena melibatkan modul list rekursif. */

#include "pohon.h"
#include <stdlib.h>
#include <stdio.h>

/* *** Konstruktor *** */
BinTree Tree(InfotypeTree Akar, BinTree L, BinTree R)
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
{
  /* KAMUS */
	BinTree T;

  /* ALGORITMA */
	T= (addrNode) malloc (sizeof(Node));
	if (T == Nil) {
		return Nil;
	} else {
		Akar(T)= Akar;
		Left(T)= L;
		Right(T)= R;
		return T;
	}
}

void MakeTree(InfotypeTree Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
		jika alokasi berhasil. P = Nil jika alokasi gagal. */
{
  /* KAMUS */

  /* ALGORITMA */
  *P= Tree(Akar, L, R);
}

BinTree BuildBalanceTree(int n)
/* Menghasilkan sebuah balanced tree dengan n node, nilai setiap node dibaca */
{
  /* KAMUS */
	BinTree P, L, R;
	int nL, nR;
	InfotypeTree X;

  /* ALGORITMA */
	if (n == 0)
    return Nil;
	else {
		scanf("%d", &X);
		MakeTree(X, Nil, Nil, &P);
		if (P!= Nil) {
			nL= n/2;
			nR= n-nL-1;
			L= BuildBalanceTree(nL);
			R= BuildBalanceTree(nR);
			Left(P)= L;
			Right(P)= R;
			return P;
		}
    else 
      return Nil;
	}
}

/* Manajemen Memory */
addrNode AlokNode(InfotypeTree X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  /* KAMUS */
	addrNode T;

  /* ALGORITMA */
	T= (addrNode) malloc (sizeof(Node));

	if (T != Nil) {
		Akar(T)= X;
		Left(T)= Nil;
		Right(T)= Nil;
	}

	return T;
}

void DealokNode(addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
  /* KAMUS */

  /* ALGORITMA */
  free(P);
}


/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
  /* KAMUS */

  /* ALGORITMA */
	if (P == Nil) {
		return true;
	} else {
		return false;
	}
}

boolean IsTreeOneElmt(BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
  /* KAMUS */

  /* ALGORITMA */
	if (!IsTreeEmpty(P)) {
		if (Left(P) == Nil && Right(P) == Nil) {
			return true;
		}
		else {
			return false;
		}
	} else {
		return false;
	}
}

boolean IsUnerLeft(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
  /* KAMUS */

  /* ALGORITMA */
	if (!IsTreeEmpty(P)) {
		if (!IsTreeEmpty(Left(P)) && IsTreeEmpty(Right(P))) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

boolean IsUnerRight(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
  /* KAMUS */

  /* ALGORITMA */
	if (!IsTreeEmpty(P)) {
		if (IsTreeEmpty(Left(P)) && !IsTreeEmpty(Right(P))) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

boolean IsBiner(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
  /* KAMUS */

  /* ALGORITMA */
	if (!IsTreeEmpty(P)) {
		if (!IsTreeEmpty(Left(P)) && !IsTreeEmpty(Right(P))) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/* *** Traversal *** */
void PrintPreorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara preorder: akar, pohon kiri, dan pohon kanan. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (A()()) adalah pohon dengan 1 elemen dengan akar A
   (A(B()())(C()())) adalah pohon dengan akar A dan subpohon kiri (B()()) dan subpohon kanan (C()()) */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P)) {
		printf("()");
	} else {
		printf("(%d", Akar(P));
		PrintPreorder(Left(P));
		PrintPreorder(Right(P));
		printf(")");
	}
}

void PrintInorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara inorder: pohon kiri, akar, dan pohon kanan. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (()A()) adalah pohon dengan 1 elemen dengan akar A
   ((()B())A(()C())) adalah pohon dengan akar A dan subpohon kiri (()B()) dan subpohon kanan (()C()) */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P))
		printf ("()");
	else
	{
		printf("(");
		PrintInorder(Left(P));
		printf("%d", Akar(P));
		PrintInorder(Right(P));
		printf(")");
	}
}

void PrintPostorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara postorder: pohon kiri, pohon kanan, dan akar. 
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup (). 
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh: 
   (()()A) adalah pohon dengan 1 elemen dengan akar A
   ((()()B)(()()C)A) adalah pohon dengan akar A dan subpohon kiri (()()B) dan subpohon kanan (()()C) */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P))
		printf("()");
	else {
		printf("(");
		PrintPostorder(Left(P));
		PrintPostorder(Right(P));
		printf("%d)",Akar(P));
	}
}

void PrintTreeRec (BinTree P, int level, int h) {
	if (!IsTreeEmpty(P)) {
		int i;
		for (i = 0; i < level * h; i++)
			printf(" ");
		printf("%d\n", Akar(P));
		PrintTreeRec(Left(P), level+1, h);
		PrintTreeRec(Right(P), level+1, h);
	}
}

void PrintTree(BinTree P, int h)
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
{
  /* KAMUS */

  /* ALGORITMA */
	PrintTreeRec(P, 0, h);
}

/* *** Searching *** */
boolean SearchTree(BinTree P, InfotypeTree X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P)) return false;
	else {
		if (Akar(P) == X) {
			return true;
		} else {
			return (SearchTree(Left(P), X) || SearchTree(Right(P), X));
		}
	}
}

/* *** Fungsi-Fungsi Lain *** */
int NbElmt(BinTree P)
/* Mengirimkan banyaknya elemen (node) pohon biner P */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P)) return 0;
	else {
		return (1 + NbElmt(Left(P)) + NbElmt(Right(P)));
	} 
}

int NbDaun(BinTree P)
/* Mengirimkan banyaknya daun (node) pohon biner P */
/* Prekondisi: P tidak kosong */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P)) return 0;
	if (IsTreeOneElmt(P)) return 1;
	return (NbDaun(Left(P)) + NbDaun(Right(P)));
}

boolean IsSkewLeft(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P))
		return true;
	else
		return Right(P) == Nil && IsSkewLeft(Left(P));
}

boolean IsSkewRight(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P))
		return true;
	else
		return Left(P) == Nil && IsSkewRight(Right(P));
}

int Level(BinTree P, InfotypeTree X)
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P. 
   Akar(P) level-nya adalah 1. Pohon P tidak kosong. */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P))	return 0;
	if (Akar(P)==X) return 1;
	else {
		if (SearchTree(Left(P),X))
			return (Level(Left(P),X)+1);
		else
			return (Level(Right(P),X)+1);
	}
}

int Tinggi(BinTree P)
/* Pohon Biner mungkin kosong. Tinggi pohon kosong = 0.
   Mengirim "height" yaitu tinggi dari pohon */
{
  /* KAMUS */
  int l, r;

  /* ALGORITMA */
  if (IsTreeEmpty(P)) {
    return 0;
  }
  else {
    l = Tinggi(Left(P));
    r = Tinggi(Right(P));

    if (l > r) {
      return l + 1;
    }
    else {
      return r + 1;
    }
  }
}


/* *** Operasi lain *** */
void AddDaunTerkiri(BinTree *P, InfotypeTree X)
/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(*P))
		*P = Tree(X, Nil, Nil);
	else if (IsUnerRight(*P))
		Left(*P) = Tree(X,Nil,Nil);
	else
		AddDaunTerkiri(P, X);
}

void AddDaun(BinTree *P, InfotypeTree X, InfotypeTree Y, boolean Kiri)
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */
/*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */
{
  /* KAMUS */

  /* ALGORITMA */
	if (!IsTreeEmpty(*P)) {
		if (IsTreeOneElmt(*P) && Akar(*P) == X) {
			if (Kiri)
				Left(*P) = Tree(Y, Nil, Nil);
			else
				Right(*P) = Tree(Y, Nil, Nil);
		} else {
			List daun = MakeListDaun(Left(*P));
			if (Search(daun, X))
				AddDaun(&Left(*P), X, Y, Kiri);
			else
				AddDaun(&Right(*P), X, Y, Kiri);
		}
	}
}

void DelDaunTerkiri(BinTree *P, InfotypeTree *X)
/* I.S. P tidak kosong */
/* F.S. P dihapus daun terkirinya, dan didealokasi, dengan X adalah info yang semula 
        disimpan pada daun terkiri yang dihapus */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeOneElmt(*P))
		*X = Akar(*P), *P = Nil;
	else if (IsUnerRight(*P)) {
		if (IsTreeOneElmt(Right(*P))) {
			*X = Akar(Right(*P));
			DealokNode(Right(*P));
			Right(*P) = Nil;
		} else
			DelDaunTerkiri(&Right(*P), X);
	} else if (IsTreeOneElmt(Left(*P))) {
		*X = Akar(Left(*P));
		DealokNode(Left(*P));
		Left(*P) = Nil;
	} else
		DelDaunTerkiri(&Left(*P), X);
}

void DelDaun(BinTree *P, InfotypeTree X)
/* I.S. P tidak kosong, minimum ada 1 daun bernilai X. */
/* F.S. Semua daun bernilai X dihapus dari P. */
{
  /* KAMUS */

  /* ALGORITMA */
	if (!IsTreeEmpty(*P)) {
		if (IsTreeOneElmt(*P)) {
			if (Akar(*P) == X)
				DealokNode(*P), *P = Nil;
		} else if (Left(*P) != Nil && Akar(Left(*P)) == X && IsTreeOneElmt(Left(*P))) {
			DealokNode(Left(*P));
			Left(*P) = Nil;
		} else if (Right(*P) != Nil && Akar(Right(*P)) == X && IsTreeOneElmt(Right(*P))) {
			DealokNode(Right(*P));
			Right(*P) = Nil;
		}
		if (!IsTreeEmpty(*P))
			DelDaun(&Left(*P), X), DelDaun(&Right(*P), X);
	}
}

List MakeListDaun(BinTree P)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua daun pohon P,
   jika semua alokasi list berhasil.
   Daun terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P))
		return Nil;
	if (IsTreeOneElmt(P))
		return Alokasi(Akar(P));
	else
		return Concat(MakeListDaun(Left(P)), MakeListDaun(Right(P)));

}

List MakeListPreorder(BinTree P)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P 
   dengan urutan preorder, jika semua alokasi berhasil.   
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
  /* KAMUS */
	Address Q;

  /* ALGORITMA */
	if (IsTreeEmpty(P)) return Nil;
	else {
		Q = Alokasi(Akar(P));
		if (Q!=Nil) {
			Next(Q) = MakeListPreorder(Left(P));
			return Concat(Q,MakeListPreorder(Right(P)));
		} else
			return Nil;
	}
}

List MakeListLevel(BinTree P, int N)
/* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
/* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P 
   yang levelnya=N, jika semua alokasi berhasil. 
   Elemen terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
   Menghasilkan list kosong jika ada alokasi yang gagal. */
{
  /* KAMUS */

  /* ALGORITMA */
	if (IsTreeEmpty(P))
    return Nil;
	if (N == 1)
    return Alokasi(Akar(P));
	else
    return Concat(MakeListLevel(Left(P),N-1), MakeListLevel(Right(P),N-1));
}
