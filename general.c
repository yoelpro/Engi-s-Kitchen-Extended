#include "general.h"
#include "data.h"

void InitGame()
/* Procedure untuk menginisialisasi game data untuk new game */
{
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
    
}

void UpdateSeatedCustomer()
{

}

void AddCustomer()
{

}

void UpdateGameState()
{
    UpdateWaitingCustomer();
    UpdateSeatedCustomer();
    Waktu(GameData)++;
    AddCustomer();
}