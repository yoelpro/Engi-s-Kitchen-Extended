#include "boolean.h"
#include "array.h"
#include <stdio.h>

void MakeEmptyTabOrder (TabOrder * T){
	Neff(*T)=0;
}

boolean IsFullTabOrder (TabOrder T)
{
	return (Neff(T)==IdxMaxOrder);
}

boolean IsEmptyArrTabOrder (TabOrder T){
	return (Neff(T)==0);
}

void AddAsLastElTabOrder (TabOrder * T, Order X){
	Neff(*T)++;
	ElmtArr(*T,Neff(*T))=X;
}

void DelEliTabOrder (TabOrder * T, IdxType i, Order * X){
	IdxType j;
	*X = ElmtArr(*T,j);
	for(j=i;j<=Neff(*T)-1;j++){
		ElmtArr(*T,j)=ElmtArr(*T,j+1);
	}
	Neff(*T)--;
}

void MakeEmpty (TabInt * T)
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
{
  Neff(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtArr (TabInt T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
  if (IsEmptyArr(T))
  {
    return 0;
  }
  else
  {
    return Neff(T);
  }
}

/* *** Daya tampung container *** */
int MaxNbEl (TabInt T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
  return IdxMax-IdxMin+1;
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
  return IdxMin;
}

IdxType GetLastIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
  return GetFirstIdx(T)+Neff(T)-1;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyArr (TabInt T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
{
  return Neff(T)==0;
}

boolean IsFullArr (TabInt T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
  return (GetFirstIdx(T)==IdxMin && GetLastIdx(T)==IdxMax);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T) Lakukan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{
  int n;
  scanf("%d",&n);
  while (!(n>=0 && n<=MaxNbEl(*T)))
  {
    scanf("%d",&n);
  }
  if (n==0)
  {
    MakeEmpty(T);
  }
  else
  {
    IdxType i=0;
    for(i=IdxMin; i<(IdxMin+n); i++)
    {
      scanf("%d",&ElmtArr(*T,i));
      Neff(*T)++;
    }
  }
}

void TulisIsiTab (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
  printf("[");
  if (!(IsEmptyArr(T)))
  {
    IdxType i;
    for (i=GetFirstIdx(T); i<GetLastIdx(T); i++)
    {
      printf("%d,",ElmtArr(T,i));
    }
    printf("%d",ElmtArr(T,i));
  }
  printf("]");
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search TANPA boolean */
{
  if (IsEmptyArr(T))
  {
    return IdxUndef;
  }
  else
  {
    IdxType i=GetFirstIdx(T);
    while (ElmtArr(T,i)!=X && i<GetLastIdx(T))
    {
      i++;
    }
    if (ElmtArr(T,i)==X)
    {
      return i;
    }
    else
    {
      return IdxUndef;
    }
  }
}

IdxType Search2 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search DENGAN boolean Found */
{
  if (IsEmptyArr(T))
  {
    return IdxUndef;
  }
  else
  {
    boolean found = false;
    IdxType i=GetFirstIdx(T);
    while (!found && i<=GetLastIdx(T))
    {
      if (ElmtArr(T,i)==X)
      {
        found = true;
      }
      else
      {
        i++;
      }
    }
    if (found)
    {
      return i;
    }
    else
    {
      return IdxUndef;
    }
  }
}

boolean SearchB (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Memakai Skema search DENGAN boolean */
{
  if (IsEmptyArr(T))
  {
    return false;
  }
  else
  {
    boolean found = false;
    int i=GetFirstIdx(T);
    while (!found && i<=GetLastIdx(T))
    {
      if (ElmtArr(T,i)==X)
      {
        found = true;
      }
      else
      {
        i++;
      }
    }
    return found;
  }
}

boolean SearchSentinel (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* dengan metoda sequential search dengan sentinel */
/* Untuk sentinel, manfaatkan indeks ke-0 dalam definisi array dalam Bahasa C 
   yang tidak dipakai dalam definisi tabel */
{
  ElmtArr(T,0)=X;
  int i = GetLastIdx(T);
  while (ElmtArr(T,i)!=X)
  {
    i--;
  }
  return (i!=0);
}

/* ********** NILAI EKSTREM ********** */
ElType ValMax (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai maksimum tabel */
{
  ElType max = ElmtArr(T,GetFirstIdx(T));
  int i;
  for (i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++)
  {
    if (ElmtArr(T,i)>max)
    {
      max = ElmtArr(T,i);
    }
  }
  return max;
}

ElType ValMin (TabInt T) 
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai minimum tabel */
{
  ElType min = ElmtArr(T,GetFirstIdx(T));
  int i;
  for (i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++)
  {
    if (ElmtArr(T,i)<min)
    {
      min = ElmtArr(T,i);
    }
  }
  return min;
}

/* *** Mengirimkan indeks elemen bernilai ekstrem *** */
IdxType IdxMaxTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai maksimum pada tabel */
{
  IdxType idxElmtArrMax = GetFirstIdx(T);
  int i;
  for (i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++)
  {
    if (ElmtArr(T,i)>ElmtArr(T,idxElmtArrMax))
    {
      idxElmtArrMax = i;
    }
  }
  return idxElmtArrMax;
}

IdxType IdxMinTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai minimum pada tabel */
{
  IdxType idxElmtArrMin = GetFirstIdx(T);
  int i;
  for (i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++)
  {
    if (ElmtArr(T,i)<ElmtArr(T,idxElmtArrMin))
    {
      idxElmtArrMin = i;
    }
  }
  return idxElmtArrMin;
}

/* ********** OPERASI LAIN ********** */
void CopyTab (TabInt Tin, TabInt * Tout)
/* I.S. Tin terdefinisi, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (elemen dan ukuran identik) */
/* Proses : Menyalin isi Tin ke Tout */
{
  Neff(*Tout)=Neff(Tin);
  IdxType i;
  int j= IdxMin;
  for (i= GetFirstIdx(Tin); i<=GetLastIdx(Tin); i++)
  {
    ElmtArr(*Tout,j) = ElmtArr(Tin,i);
    j++;
  }
}
TabInt InverseTab (TabInt T)
/* Menghasilkan tabel dengan urutan tempat yang terbalik, yaitu : */
/* elemen pertama menjadi terakhir, */
/* elemen kedua menjadi elemen sebelum terakhir, dst.. */
/* Tabel kosong menghasilkan tabel kosong */
{
  TabInt hasil;
  MakeEmpty(&hasil);
  int i;
  int j = GetLastIdx(T);
  for (i=GetFirstIdx(T); i<=GetLastIdx(T); i++)
  {
    ElmtArr(hasil,j-i+IdxMin) = ElmtArr(T,i);
    Neff(hasil)++;
  }
  return hasil;
}

/* ********** SORTING ********** */
void MaxSortDesc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menurun dengan Maximum Sort */
/* Proses : mengurutkan T sehingga elemennya menurun/mengecil */
/*          tanpa menggunakan tabel kerja */
{
  //selection sort
  if (!IsEmptyArr(*T))
  {
    int i;
    for (i=GetFirstIdx(*T); i<GetLastIdx(*T); i++)
    {
      int idxElmtArrMax = i;
      int j;
      int temp = ElmtArr(*T,i);
      for (j=i+1; j<=GetLastIdx(*T); j++)
      {
        if (ElmtArr(*T,j)>ElmtArr(*T,idxElmtArrMax))
        {
          idxElmtArrMax = j;
        }
      }
      ElmtArr(*T,i) = ElmtArr(*T,idxElmtArrMax);
      ElmtArr(*T,idxElmtArrMax) = temp;
    }
  }
}

void InsSortAsc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menaik dengan Insertion Sort */
/* Proses : mengurutkan T sehingga elemennya menaik/membesar */
/*          tanpa menggunakan tabel kerja */
{
  int i;
  if (!IsEmptyArr(*T))
  {
    for (i=GetFirstIdx(*T)+1; i<=GetLastIdx(*T); i++)
    {
      int j;
      int now = ElmtArr(*T,i);
      for (j=i-1; j>GetFirstIdx(*T) && ElmtArr(*T,j)>now; j--)
      {
        ElmtArr(*T,j+1) = ElmtArr(*T,j);
      }
      if (now>=ElmtArr(*T,j))
      {
        ElmtArr(*T,j+1)=now;
      }
      else
      {
        ElmtArr(*T,j+1)=ElmtArr(*T,j);
        ElmtArr(*T,j) = now;
      }
    }
  }
}

void AddAsLastEl (TabInt * T, ElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
  ElmtArr(*T,GetLastIdx(*T)+1)=X;
  Neff(*T)+=1;
}

void AddEli (TabInt * T, ElType X, IdxType i)
/* Menambahkan X sebagai elemen ke-i tabel tanpa mengganggu kontiguitas 
   terhadap elemen yang sudah ada */
/* I.S. Tabel tidak kosong dan tidak penuh */
/*      i adalah indeks yang valid. */
/* F.S. X adalah elemen ke-i T yang baru */
/* Proses : Geser elemen ke-i+1 s.d. terakhir */
/*          Isi elemen ke-i dengan X */
{
  int j;
  for (j=GetLastIdx(*T)+1; j>i; j--)
  {
    ElmtArr(*T,j)=ElmtArr(*T,j-1);
  }
  ElmtArr(*T,i) = X;
  Neff(*T)++;
}

void DelLastEl (TabInt * T, ElType * X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
  *X = ElmtArr(*T,GetLastIdx(*T));
  Neff(*T)--;
}

void DelEli (TabInt * T, IdxType i, ElType * X)
/* Menghapus elemen ke-i tabel tanpa mengganggu kontiguitas */
/* I.S. Tabel tidak kosong, i adalah indeks efektif yang valid */
/* F.S. X adalah nilai elemen ke-i T sebelum penghapusan */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
/* Proses : Geser elemen ke-i+1 s.d. elemen terakhir */
/*          Kurangi elemen efektif tabel */
{
  int j;
  *X = ElmtArr(*T,i);
  for (j=i; j<GetLastIdx(*T); j++)
  {
    ElmtArr(*T,j) = ElmtArr(*T,j+1);
  }
  Neff(*T)--;
}

void AddElUnik (TabInt * T, ElType X)
/* Menambahkan X sebagai elemen terakhir tabel, pada tabel dengan elemen unik */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/*      dan semua elemennya bernilai unik, tidak terurut */
/* F.S. Jika tabel belum penuh, menambahkan X sbg elemen terakhir T, 
        jika belum ada elemen yang bernilai X. 
    Jika sudah ada elemen tabel yang bernilai X maka I.S. = F.S. 
    dan dituliskan pesan "nilai sudah ada" */
/* Proses : Cek keunikan dengan sequential search dengan sentinel */
/*          Kemudian tambahkan elemen jika belum ada */
{
  if (IsEmptyArr(*T))
  {
    ElmtArr(*T,IdxMin)=X;
    Neff(*T)++;
  }
  else
  {
    ElmtArr(*T,GetLastIdx(*T)+1)=X;
    int i=GetFirstIdx(*T);
    while (ElmtArr(*T,i)!=X)
    {
      i++;
    }
    if (i==GetLastIdx(*T)+1) //mmg belum pernah
    {
      Neff(*T)++;
    }
    else
    {
      printf("nilai sudah ada\n");
    }
  }
}

IdxType SearchUrut (TabInt T, ElType X)
/* Prekondisi: Tabel T boleh kosong. Jika tidak kosong, elemen terurut membesar. */
/* Mengirimkan indeks di mana harga X dengan indeks terkecil diketemukan */
/* Mengirimkan IdxUndef jika tidak ada elemen tabel bernilai X */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel kosong */
{
  if (IsEmptyArr(T))
  {
    return IdxUndef;
  }
  else
  {
    int i = GetFirstIdx(T);
    while (i<GetLastIdx(T) && ElmtArr(T,i)<X)
    {
      i++;
    }
    if (ElmtArr(T,i)==X)
    {
      return i;
    }
    else
    {
      return IdxUndef;
    }
  }
}

ElType MaxUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai maksimum pada tabel */
{
  return ElmtArr(T,GetLastIdx(T));
}

ElType MinUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai minimum pada tabel*/
{
  return ElmtArr(T,GetFirstIdx(T));
}

void MaxMinUrut (TabInt T, ElType * Max, ElType * Min)
/* I.S. Tabel T tidak kosong, elemen terurut membesar */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
{
  *Max = ElmtArr(T,GetLastIdx(T));
  *Min = ElmtArr(T,GetFirstIdx(T));
}

void Add1Urut (TabInt * T, ElType X)
/* Menambahkan X tanpa mengganggu keterurutan nilai dalam tabel */
/* Nilai dalam tabel tidak harus unik. */
/* I.S. Tabel T boleh kosong, boleh penuh. */
/*      Jika tabel isi, elemennya terurut membesar. */
/* F.S. Jika tabel belum penuh, menambahkan X. */
/*      Jika tabel penuh, maka tabel tetap. */
/* Proses : Search tempat yang tepat sambil geser */
/*          Insert X pada tempat yang tepat tersebut tanpa mengganggu keterurutan */
{
  if (IsEmptyArr(*T))
  {
    ElmtArr(*T,IdxMin) = X;
    Neff(*T)++;
  }
  else if (!IsFullArr(*T))
  {
    int i=GetLastIdx(*T);
    while (ElmtArr(*T,i)>X && i> GetFirstIdx(*T))
    {
      ElmtArr(*T,i+1)=ElmtArr(*T,i);
      i--;
    }
    if (X>=ElmtArr(*T,i))
    {
      ElmtArr(*T,i+1) = X;
    }
    else
    {
      ElmtArr(*T,i+1) = ElmtArr(*T,i);
      ElmtArr(*T,i) = X;
    }
    Neff(*T)++;
  }
}

void Del1Urut (TabInt * T, ElType X)
/* Menghapus X yang pertama kali (pada indeks terkecil) yang ditemukan */
/* I.S. Tabel tidak kosong */
/* F.S. Jika ada elemen tabel bernilai X , */
/*      maka banyaknya elemen tabel berkurang satu. */
/*      Jika tidak ada yang bernilai X, tabel tetap. */
/*      Setelah penghapusan, elemen tabel tetap kontigu! */
/* Proses : Search indeks ke-i dengan elemen ke-i = X. */
/*          Delete jika ada. */
{
  int i = GetFirstIdx(*T);
  while (ElmtArr(*T,i)<X && i<GetLastIdx(*T))
  {
    i++;
  }
  if (ElmtArr(*T,i)==X)
  {
    int j;
    for (j=i; j<GetLastIdx(*T); j++)
    {
      ElmtArr(*T,j)=ElmtArr(*T,j+1);
    }
    Neff(*T)--;
  }
}