#include "general.h"
#include "data.h"
#include "time.h"

void InitGame()
{
    // Read resep
    char x[120] = "(0(1(3(7(0()())())(8(1()())()))(4(9(2()())())(a(3()())())))(2(5(b(4()())())(c(5()())()))(6(d(f(8()())())())(e(7()())))))";
    int textPointer = 0;
    BuildTreeText(&Resep, x, &textPointer);

    CurrentRoom(GameData) = 4; //Dapur
    GameData.PosisiPlayer = MakePoint(4,4); //Sepakati dapur 4,4 harus kosong dan tidak menjebak
    CreateEmptyStck(&GameData.Hand);
    CreateEmptyStck(&GameData.Tray);
    Waktu(GameData) = 0;
    Money(GameData) = 0;
    Life(GameData) = 5;

    /* Reading dari file (belum diimplementasi) */
    
}

void UpdateWaitingCustomer()
{
    if (!IsEmptyQC(QWaitingC))
    {
        CleanQC(&QWaitingC);
    }
}

void UpdateSeatedCustomer()
{
    if (!IsEmptyQC(QSeatedC))
    {
        CleanQC(&QSeatedC);
    }
}

void AddCustomer()
{
    /* Random from 0 to 19 */
    unsigned int chanceInsert = rand() % 20;
    unsigned int chanceStarred =  rand() % 20;
    if (chanceInsert>=15 && !IsFullQC(QWaitingC))
    {
        if (chanceStarred>=15)
        {
            AddCustomerWC(&QWaitingC,GameData.JmlCustomer+1,12,(rand()%4)+1,true);
        }
        else
        {
            AddCustomerWC(&QWaitingC,GameData.JmlCustomer+1,20,(rand()%4)+1,false);
        }
        /* Jika berhasil insert, jml customer tambah 1 */
        GameData.JmlCustomer++;
    }
}

void UpdateGameState()
{
    UpdateWaitingCustomer();
    UpdateSeatedCustomer();
    Waktu(GameData)++;
    AddCustomer();
}

void Put()
{
    Stack ReverseStack;
    BinTree ScopePencarian = Resep;
    char X;

    if(IsEmptyStck(Hand))
    {
        printf("Hand kosong!\n");
    }
    else if (IsFullStck(Tray))
    {
        printf("Tray penuh!\n");
    }
    else //kalau hand gk kosong
    {
        /*Membuat salinan Hand*/
        CreateEmptyStck(&ReverseStack);
        do
        {
            Pop(&Hand,&X);
            Push(&ReverseStack,X);
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
            ScopePencarian = Resep;
            do
            {
                Pop(&ReverseStack,&target); //change target
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

/*fungsi isMeja*/
boolean isMejaBahan(Point kotak)
{
    char x = (Room[GameData.CurrentRoom].Map.Mem[Absis(kotak)][Ordinat(kotak)]);
    return (x != 'T' && x != 'B');
}

void Take ()
{
    Stack Hand;
    char dataMeja;

    /*kondisi hand penuh*/
    if (IsFullStck(Hand))
    {
        printf("Hand penuh!\n");
    }
    else
    {
        if(isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)+1))) //meja di atas
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)][Ordinat(GameData.PosisiPlayer)+1]);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer)+1,Ordinat(GameData.PosisiPlayer)))) //meja di kanan
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)+1][Ordinat(GameData.PosisiPlayer)]);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)-1))) //meja di bawah
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)][Ordinat(GameData.PosisiPlayer)+1]);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer)-1,Ordinat(GameData.PosisiPlayer)))) //meja di kiri
        {
            dataMeja = (Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)+1][Ordinat(GameData.PosisiPlayer)]);
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
        }
        else
        {
            printf("Meja tidak ditemukan!\n");
        }
    }
}

/* Jesnat */

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