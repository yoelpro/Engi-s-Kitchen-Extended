/* Nama: Stefanus Ardi Mulia */
/* NIM: 13517119 */
/* File: matriks.c */
/* Tanggal: 20 September 2018 */
/* Implementasi ADT MATRIX */

#include "boolean.h"
#include "matriks.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk Matriks *** */
void MakeMatriks (int NB, int NK, Matriks * M)
/* Membentuk sebuah Matriks "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA Matriks" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return ((i>=MATRIX_MIN_BRS && i<=MATRIX_MAX_BRS) && (j>=MATRIX_MIN_KOL && j<=MATRIX_MAX_KOL));
}


/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
matriksIndeks GetFirstIdxBrs (Matriks M)
/* Mengirimkan indeks baris terkecil M */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return MATRIX_MIN_BRS;
}

matriksIndeks GetFirstIdxKol (Matriks M)
/* Mengirimkan indeks kolom terkecil M */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return MATRIX_MIN_KOL;
}

matriksIndeks GetLastIdxBrs (Matriks M)
/* Mengirimkan indeks baris terbesar M */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return GetFirstIdxBrs(M) + NBrsEff(M) - 1;
}

matriksIndeks GetLastIdxKol (Matriks M)
/* Mengirimkan indeks kolom terbesar M */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return GetFirstIdxKol(M) + NKolEff(M) - 1;
}

boolean IsIdxEff (Matriks M, matriksIndeks i, matriksIndeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return ((i>=GetFirstIdxBrs(M) && i<=GetLastIdxBrs(M)) && (j>=GetFirstIdxKol(M) && j<=GetLastIdxKol(M)));
}

matriksElType GetElmtMatDiagonal (Matriks M, matriksIndeks i)
/* Mengirimkan elemen M(i,i) */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return ElmtMat(M,GetFirstIdxBrs(M)+i-1,GetFirstIdxKol(M)+i-1);
}


/* ********** Assignment  Matriks ********** */
void CopyMatriks (Matriks MIn, Matriks * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;

    /* ALGORITMA */
    MakeMatriks(NBrsEff(MIn), NKolEff(MIn), MHsl);

    for(i=GetFirstIdxBrs(MIn);i<=GetLastIdxBrs(MIn);i++){

        for(j=GetFirstIdxKol(MIn);j<=GetLastIdxKol(MIn);j++){
            ElmtMat(*MHsl,i,j) = ElmtMat(MIn,i,j);
        }

    }
}


/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMatriks (Matriks * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMatriks(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;

    /* ALGORITMA */
    MakeMatriks(NB,NK,M);

    for(i=GetFirstIdxBrs(* M);i<=GetLastIdxBrs(* M);i++){

        for(j=GetFirstIdxKol(* M);j<=GetLastIdxKol(* M);j++){
            scanf("%d", &ElmtMat(* M,i,j));
        }

    }
}

void TulisMatriks (Matriks M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;

    /* ALGORITMA */
    for(i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++){

        for(j=GetFirstIdxKol(M);j<GetLastIdxKol(M);j++){
            printf("%d ", ElmtMat(M,i,j));
        }

        if(i==GetLastIdxBrs(M)){
            printf("%d", ElmtMat(M,i,GetLastIdxKol(M)));
        }
        else{
            printf("%d\n", ElmtMat(M,i,GetLastIdxKol(M)));
        }

    }
}


/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
Matriks TambahMatriks (Matriks M1, Matriks M2)
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    Matriks temp;

    /* ALGORITMA */
    MakeMatriks(NBrsEff(M1), NKolEff(M1), &temp);

    for(i=GetFirstIdxBrs(M1);i<=GetLastIdxBrs(M1);i++){

        for(j=GetFirstIdxKol(M1);j<=GetLastIdxKol(M1);j++){
            ElmtMat(temp,i,j) = ElmtMat(M1,i,j) + ElmtMat(M2,i,j);
        }
        
    }

    return temp;
}

Matriks KurangMatriks (Matriks M1, Matriks M2)
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    Matriks temp;

    /* ALGORITMA */
    MakeMatriks(NBrsEff(M1), NKolEff(M1), &temp);

    for(i=GetFirstIdxBrs(M1);i<=GetLastIdxBrs(M1);i++){

        for(j=GetFirstIdxKol(M1);j<=GetLastIdxKol(M1);j++){
            ElmtMat(temp,i,j) = ElmtMat(M1,i,j) - ElmtMat(M2,i,j);
        }
        
    }

    return temp;
}

Matriks KaliMatriks (Matriks M1, Matriks M2)
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j, k;
    Matriks temp;

    /* ALGORITMA */
    MakeMatriks(NBrsEff(M1), NKolEff(M2), &temp);

    for(i=GetFirstIdxBrs(M1);i<=GetLastIdxBrs(M1);i++){
        for(j=GetFirstIdxKol(M2);j<=GetLastIdxKol(M2);j++){
            ElmtMat(temp,i,j) = 0;
            for(k=GetFirstIdxKol(M1);k<=GetLastIdxKol(M1);k++){
                ElmtMat(temp,i,j) += ElmtMat(M1,i,k) * ElmtMat(M2,k,j);
            }
        }
    }

    return temp;
}

Matriks KaliKons (Matriks M, matriksElType X)
/* Mengirim hasil perkalian setiap elemen M dengan X */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    Matriks temp;

    /* ALGORITMA */
    MakeMatriks(NBrsEff(M), NKolEff(M), &temp);

    for(i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++){
        for(j=GetFirstIdxKol(M);j<=GetLastIdxKol(M);j++){
            ElmtMat(temp,i,j) = ElmtMat(M,i,j) * X;
        }
    }

    return temp;
}

void PKaliKons (Matriks * M, matriksElType K)
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;

    /* ALGORITMA */
    for(i=GetFirstIdxBrs(*M);i<=GetLastIdxBrs(*M);i++){
        for(j=GetFirstIdxKol(*M);j<=GetLastIdxKol(*M);j++){
            ElmtMat(*M,i,j) *= K;
        }
    }
}


/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matriks ********** */
boolean EQ (Matriks M1, Matriks M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmtMat(M1) = NBElmtMat(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    boolean flag;

    /* ALGORITMA */
    if(
    (EQSize(M1,M2))&&
    (GetFirstIdxBrs(M1)==GetFirstIdxBrs(M2))&&
    (GetLastIdxKol(M1)==GetLastIdxKol(M2))
    ){
        flag = true;
        i = GetFirstIdxBrs(M1);
        while(i<=GetLastIdxBrs(M1) && flag){

            j = GetLastIdxKol(M1);
            while(j<=GetLastIdxKol(M1) && flag){

                if(ElmtMat(M1,i,j)!=ElmtMat(M2,i,j)){
                    flag = false;
                }
                ++j;
            }
            ++i;
        }
    }
    else{
        flag = false;
    }
    
    return flag;
}

boolean NEQ (Matriks M1, Matriks M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return !(EQ(M1,M2));
}

boolean EQSize (Matriks M1, Matriks M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (NBrsEff(M1)==NBrsEff(M2)) && (NKolEff(M1)==NKolEff(M2));
}


/* ********** Operasi lain ********** */
int NBElmtMat (Matriks M)
/* Mengirimkan banyaknya elemen M */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (NBrsEff(M) * NKolEff(M));
}


/* ********** KELOMPOK TEST TERHADAP Matriks ********** */
boolean IsBujurSangkar (Matriks M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (NBrsEff(M)==NKolEff(M));
}

boolean IsSimetri (Matriks M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    boolean flag;

    /* ALGORITMA */
    flag = IsBujurSangkar(M);
    i = GetFirstIdxBrs(M);

    while(i<GetLastIdxBrs(M) && flag){

        j = GetFirstIdxKol(M) + (i - GetFirstIdxBrs(M)) + 1;

        while(j<=GetLastIdxKol(M) && flag){
            if(ElmtMat(M,i,j)!=ElmtMat(M,j,i)){
                flag = false;
            }
            ++j;
        }

        ++i;
    }

    return flag;
}

boolean IsSatuan (Matriks M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    boolean flag;

    /* ALGORITMA */
    flag = IsBujurSangkar(M);
    i = GetFirstIdxBrs(M);

    while(i<=GetLastIdxBrs(M) && flag){

        j = GetFirstIdxKol(M);
        
        while(j<=GetLastIdxKol(M) && flag){
            if((i-GetFirstIdxBrs(M)==j-GetFirstIdxKol(M)) && (ElmtMat(M,i,j)!=1)){
                flag = false;
            }
            else if((i-GetFirstIdxBrs(M)!=j-GetFirstIdxKol(M)) && (ElmtMat(M,i,j)!=0)){
                flag = false;
            }
            ++j;
        }

        ++i;
    }

    return flag;
}

boolean IsSparse (Matriks M)
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    float threshold;
    int count;

    /* ALGORITMA */
    threshold = (0.05)*NBElmtMat(M);
    count = 0;
    
    i = GetFirstIdxBrs(M);

    while(i<=GetLastIdxBrs(M) && (count<=threshold)){

        j = GetFirstIdxKol(M);
        
        while(j<=GetLastIdxKol(M) && (count<=threshold)){

            if(ElmtMat(M,i,j)!=0){
                ++count;
            }

            ++j;
        }

        ++i;
    }

    return (count<=threshold);
}

Matriks Inverse1 (Matriks M)
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return KaliKons(M, -1);
}

float Determinan (Matriks M)
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
{
    /* KAMUS LOKAL */
    matriksIndeks iter,i,j,row,col;
    float det,sign;
    Matriks kofaktor;

    /* ALGORITMA */
    if(NBrsEff(M)==1){
        return ElmtMat(M,GetFirstIdxBrs(M),GetFirstIdxKol(M));
    }
    else if(NBrsEff(M)==2){
        return (
            (ElmtMat(M,GetFirstIdxBrs(M),GetFirstIdxKol(M))*ElmtMat(M,GetLastIdxBrs(M),GetLastIdxKol(M)))-
            (ElmtMat(M,GetFirstIdxBrs(M),GetFirstIdxKol(M)+1)*ElmtMat(M,GetFirstIdxBrs(M)+1,GetFirstIdxKol(M)))
        );
    }
    else{
        det = 0;
        sign = 1;
        /* Inisialisasi matriks kofaktor */
        MakeMatriks(NBrsEff(M)-1,NKolEff(M)-1,&kofaktor);
        
        for(iter=GetFirstIdxKol(M);iter<=GetLastIdxKol(M);iter++){

            /* Cari matriks kofaktor */
            row = MATRIX_MIN_BRS;

            for(i=GetFirstIdxBrs(M)+1;i<=GetLastIdxBrs(M);i++){

                col = MATRIX_MIN_KOL;
                for(j=GetFirstIdxKol(M);j<=GetLastIdxKol(M);j++){

                    if(j != iter){
                        ElmtMat(kofaktor,row,col) = ElmtMat(M,i,j);

                        ++col;
                    }
                }

                ++row;
            }

            /* Hitung determinan */
            det += sign * ElmtMat(M,GetFirstIdxBrs(M),iter) * Determinan(kofaktor);
            
            sign = -sign;
        }

        return det;
    }
}

void PInverse1 (Matriks * M)
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    PKaliKons(M,-1);
}

void Transpose (Matriks * M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
    /* KAMUS LOKAL */
    matriksIndeks i, j;
    matriksElType temp;

    /* ALGORITMA */
    i = GetFirstIdxBrs(*M);

    while(i<GetLastIdxBrs(*M)){

        j = GetFirstIdxKol(*M) + (i - GetFirstIdxBrs(*M)) + 1;

        while(j<=GetLastIdxKol(*M)){
            
            temp = ElmtMat(*M,i,j);
            ElmtMat(*M,i,j) = ElmtMat(*M,j,i);
            ElmtMat(*M,j,i) = temp;

            ++j;
        }

        ++i;
    }
}
