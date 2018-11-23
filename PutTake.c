#include <stdio.h>
#include "ADT/boolean.h"
#include "ADT/listrekursif.c"
#include "ADT/mesinkar.c"
#include "ADT/pohon.c"
#include "ADT/stackt.c"
#include "ADT/point.c"
#include "ADT/matriks.c"
#include "data.c"
#include "data.h"


/*Membaca Resep*/
Stack BacaResep(BinTree recipe){
    /*I.S. Order tidak kosong*/
    /*F.S. Order dibaca, mengembalikan List JenisBahan yang dibutuhkan*/

}
/*konversi hex ke int*/
int hexToInt(char target)
    {
        if (target >= '0' && target <= '9')
            return target - '0';
        if (target >= 'a' && target <= 'f')
            return target - 'a' + 10;
        return -1;
    }

/*fungsi isMeja*/
boolean isMeja(Point kotak)
    {
        char x = (Room[GameData.CurrentRoom].Map.Mem[Absis(kotak)][Ordinat(kotak)]);
        return (x != 'T' && x != 'B');
    }
/*Membuat prosedur Take*/
void Take (){
    /*I.S. Tray terdefinisi, pohon resep terdifinisi, Tray mungkin penuh*/
    /*F.S. Bahan yang dicari ditambahkan ke tray*/
    Stack Hand;
    Point kotak;
    char dataMeja;
    int bahan;

    /*kondisi hand penuh*/
    if (IsFullStck(Hand))
    {
        printf("Hand penuh.\n");
    }
    else
    {
        
        if(isMeja(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)+1))) //meja di atas
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)][Ordinat(GameData.PosisiPlayer)+1]);
            bahan = hexToInt(dataMeja);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,bahan);
            printf("Bahan ditambahkan ke hand.\n");
        }
        else if (isMeja(MakePoint(Absis(GameData.PosisiPlayer)+1,Ordinat(GameData.PosisiPlayer)))) //meja di kanan
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)+1][Ordinat(GameData.PosisiPlayer)]);
            bahan = hexToInt(dataMeja);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,bahan);
            printf("Bahan ditambahkan ke hand.\n");
        }
        else if (isMeja(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)-1))) //meja di bawah
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)][Ordinat(GameData.PosisiPlayer)+1]);
            bahan = hexToInt(dataMeja);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,bahan);
            printf("Bahan ditambahkan ke hand.\n");
        }
        else if (isMeja(MakePoint(Absis(GameData.PosisiPlayer)-1,Ordinat(GameData.PosisiPlayer)))) //meja di kiri
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)+1][Ordinat(GameData.PosisiPlayer)]);
            bahan = hexToInt(dataMeja);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,bahan);
            printf("Bahan ditambahkan ke hand.\n");
        }
    }
}
/*bikin pohon resep yay*/
void BuildTreeText(BinTree *P, char* text, int* i)
    {
        (*i)++;
        if(text[*i] == ')')
        {
            *P = Nil;
            (*i)++;
        }
        else
        {
            *P = Tree(text[*i],Nil,Nil);
            (*i)++;
            // printf("%d",*i);
            while(text[*i] == ' ') 
            {
                (*i)++;
            }
            BuildTreeText(&Left(*P),text,i);
            while(text[*i] == ' ')
            {
                (*i)++;
            }
            BuildTreeText(&Right(*P),text,i);
            (*i)++;
        }
    }

/*Membuat prosedur Put*/
void Put ()
{
    /*I.S. Hand memiliki bahan penyusun makanan, nama makanan yang di
        order dipastikan ada*/
    /*F.S. Makanan dalam order dicari dan dipindahkan ke FoodStack*/

    // Membangun tree untuk pengetesan program
    char x[120] = "(0(1(3(7(0()())())(8(1()())()))(4(9(2()())())(a(3()())())))(2(5(b(4()())())(c(5()())()))(6(d(f(8()())())())(e(7()())))))";
    BinTree Resep = Nil;
    int textPointer = 0;
    BuildTreeText(&Resep, x, &textPointer);
    PrintTree(Resep,1);
    Stack TempHand; /*Menyimpan sementara bahan" yang dikumpulkan*/
    Stack ReverseStack;
    BinTree ScopePencarian = Resep;
    stackInfoType X;
    /*Diasumsikan order berupa list bahan*/
    char Food; /*Food adalah nama makanan dari fungsi order*/

    if(IsEmptyStck(Hand))
    {
        printf("hand kosong\n");
    }
    else //kalau hand gk kosong
    {
        /*Membuat salinan Hand*/
        CreateEmptyStck(&TempHand);
        CreateEmptyStck(&ReverseStack);
        do
        {
            Pop(&Hand,&X);
            Push(&ReverseStack,X);
            Push(&TempHand,X);
            printf("%c ",X);
            printf("\n");
        }
        while (!IsEmptyStck(Hand));

        // Mulai iterasi per item
        char target;
        int hasil = 0;
        boolean stillFind = true;
        do
        {
            printf("1\n");
            ScopePencarian = Resep;
            do
            {
                Pop(&ReverseStack,&target); //change target
                printf("2-- %c  %c\n",target,Akar(ScopePencarian));
                if (target == '0') //piring
                {
                    ScopePencarian = Resep;
                    stillFind = true;
                }
                else
                {
                    if (Akar(Left(ScopePencarian)) == target) //kalau ketemu
                    {
                        ScopePencarian = Left(ScopePencarian);
                    }
                    else if (Akar(Right(ScopePencarian))==target)
                    {
                        ScopePencarian = Right(ScopePencarian);
                    }
                    else
                    {
                        stillFind = false;
                    }
                }
            } while (!IsEmptyStck(ReverseStack) && stillFind && !IsOneElmt(Left(ScopePencarian)));
            if (IsOneElmt(Left(ScopePencarian)))// bahannya terurut
            {
                Push(&Tray,Akar(ScopePencarian));
                hasil++;
            }
        } while (!IsEmptyStck(ReverseStack));
        if (hasil==0)
        {
            printf("Tidak ada makanan yang berhasil dibuat!\n");
        }
        else
        {
            printf("Ada %d makanan yang berhasil dibuat!\n",hasil);
        }
    }
}

int main(){
    CreateEmptyStck(&Hand);
    // Push(&Hand,'0');
    // Push(&Hand,'1');
    // Push(&Hand,'3');
    // Push(&Hand,'7');
    // Push(&Hand,'0');
    // Push(&Hand,'1');
    // Push(&Hand,'3');
    // Push(&Hand,'3');
    // Push(&Hand,'7');
    printf("aaaa\n");
    Put();
    return 0;
}

BinTree SubTree(BinTree P, Infotype target)
{
    if (Akar(P)==target)
    {
        return P;
    }
    else
    {
        if (SearchTree(Left(P),target))
        {
            SubTree(Left(P),target);
        }
        else
        {
            SubTree(Right(P),target);
        }
    }
}
