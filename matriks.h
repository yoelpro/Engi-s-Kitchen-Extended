/* ********** Definisi TYPE Matriks dengan matriksIndeks dan elemen integer ********** */

#ifndef Matriks_H
#define Matriks_H

#include "boolean.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define MATRIX_MIN_BRS 1
#define MATRIX_MAX_BRS 10
#define MATRIX_MIN_KOL 1
#define MATRIX_MAX_KOL 10

typedef int matriksIndeks; /* matriksIndeks baris, kolom */
typedef char matriksElType; 
typedef struct { 
	matriksElType Mem[MATRIX_MAX_BRS+1][MATRIX_MAX_KOL+1];
    int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matriks;
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* matriksIndeks matriks yang digunakan: [MATRIX_MIN_BRS..MATRIX_MAX_BRS][MATRIX_MIN_KOL..MATRIX_MAX_KOL] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk Matriks *** */
void MakeMatriks (int NB, int NK, Matriks * M); 
/* Membentuk sebuah Matriks "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor "DUNIA Matriks" *** */
boolean IsIdxValid (int i, int j);
/* Mengirimkan true jika i, j adalah matriksIndeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
matriksIndeks GetFirstIdxBrs (Matriks M);
/* Mengirimkan matriksIndeks baris terkecil M */
matriksIndeks GetFirstIdxKol (Matriks M);
/* Mengirimkan matriksIndeks kolom terkecil M */
matriksIndeks GetLastIdxBrs (Matriks M);
/* Mengirimkan matriksIndeks baris terbesar M */
matriksIndeks GetLastIdxKol (Matriks M);
/* Mengirimkan matriksIndeks kolom terbesar M */
boolean IsIdxEff (Matriks M, matriksIndeks i, matriksIndeks j);
/* Mengirimkan true jika i, j adalah matriksIndeks efektif bagi M */
matriksElType GetElmtDiagonal (Matriks M, matriksIndeks i);
/* Mengirimkan elemen M(i,i) */

/* ********** Assignment  Matriks ********** */
void CopyMatriks (Matriks MIn, Matriks * MHsl);
/* Melakukan assignment MHsl  MIn */

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMatriks (Matriks * M, int NB, int NK);
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMatriks(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
void TulisMatriks (Matriks M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
Matriks TambahMatriks (Matriks M1, Matriks M2);
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
Matriks KurangMatriks (Matriks M1, Matriks M2);
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */ 
Matriks KaliMatriks (Matriks M1, Matriks M2);
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
Matriks KaliKons (Matriks M, matriksElType X);
/* Mengirim hasil perkalian setiap elemen M dengan X */
void PKaliKons (Matriks * M, matriksElType K);
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matriks ********** */
boolean EQ (Matriks M1, Matriks M2);
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan matriksIndeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
boolean NEQ (Matriks M1, Matriks M2);
/* Mengirimkan true jika M1 tidak sama dengan M2 */
boolean EQSize (Matriks M1, Matriks M2);
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */

/* ********** Operasi lain ********** */
int NBElmt (Matriks M);
/* Mengirimkan banyaknya elemen M */

/* ********** KELOMPOK TEST TERHADAP Matriks ********** */
boolean IsBujurSangkar (Matriks M);
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
boolean IsSimetri (Matriks M);
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
boolean IsSatuan (Matriks M);
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */ 
boolean IsSparse (Matriks M);
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
Matriks Inverse1 (Matriks M);
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
float Determinan (Matriks M);
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
void PInverse1 (Matriks * M);
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
void Transpose (Matriks * M);
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */

#endif