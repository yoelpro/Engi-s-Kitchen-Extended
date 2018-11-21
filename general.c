#include "general.h"
#include "data.h"
#include "time.h"

void InitGame()
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