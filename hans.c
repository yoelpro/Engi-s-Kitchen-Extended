#include <stdio.h>
#include "ADT/boolean.h"
#include "ADT/listrekursif.c"
#include "ADT/mesinkar.c"
#include "ADT/pohon.c"
#include "ADT/stackt.c"
#include "data.c"

/*Membaca Resep*/
List BacaResep(BinTree recipe){
    /*I.S. Order tidak kosong*/
    /*F.S. Order dibaca, mengembalikan List JenisBahan yang dibutuhkan*/
}

/*Membuat prosedur Take*/
void Take (){
    /*I.S. Tray terdefinisi, pohon resep terdifinisi, Tray mungkin penuh*/
    /*F.S. Bahan yang dicari ditambahkan ke tray*/
    Stack *Hand;
    BinTree JenisBahan;
    stackInfoType X;
    /*Kondisi tray penuh*/
    if (IsFullStck(*Hand)){
        printf("Tray penuh.\n");
    } else {
        /*Mencari bahan ke pohon Resep*/
        SearchTree(JenisBahan,X);
        /*Memasukkan bahan ke Tray*/
        Push(Hand,X);
        printf("Bahan ditambahkan.\n");
    }
}

/*Membuat prosedur Put*/
void Put (){
    /*I.S. Hand memiliki bahan penyusun makanan, nama makanan yang di
        order dipastikan ada*/
    /*F.S. Makanan dalam order dicari dan dipindahkan ke FoodStack*/
    Stack *Hand;
    Stack *FoodStack;
    Stack *TempHand; /*Menyimpan sementara bahan" yang dikumpulkan*/
    Stack *Temp;
    BinTree JenisBahan;
    BinTree JenisMakanan;
    stackInfoType X;
    /*Diasumsikan order berupa list bahan*/
    List Order;
    char Food; /*Food adalah nama makanan dari fungsi order*/

    /*Membuat salinan Hand*/
    CreateEmptyStck(TempHand);
    CreateEmptyStck(Temp);
    do{
        Pop(Hand,&X);
        Push(Temp,X);
    }
    while (!IsEmptyStck(*Hand));
    
    do{
        Pop(Temp,&X);
        Push(TempHand,X);
    }
    while (!IsEmptyStck(*Temp));

    /*BacaResep fungsi yang belum diimplementasi*/
    BacaResep(JenisMakanan);

    do{
        SearchTree(JenisBahan,X);
        Pop(TempHand,&X);
    }
    while (!IsListEmpty(Order));

    if (IsListEmpty(Order)){
        do{
            SearchTree(JenisBahan,X);
            Pop(Hand,&X);
        }
        while (!IsListEmpty(Order));
        Push(FoodStack,Food);
    } else {
        /*Do Nothing*/
    }
}

int main () {

    return 0;
}