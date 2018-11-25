#include "data.h"
#include "ADT/array.h"
#include "ADT/boolean.h"
#include "ADT/jam.h"
#include "ADT/listrekursif.h"
#include "ADT/matriks.h"
#include "ADT/mesinkar.h"
#include "ADT/mesinkata.h"
#include "ADT/pohon.h"
#include "ADT/point.h"
#include "ADT/stackt.h"
#include "general.h"
#include "display.h"
#include <curses.h>

/* Deklarasi variable global */
int main()
{
	InitGame();

	// PrintTree(Resep,2);
	// Room[GameData.CurrentRoom].JmlMeja=2;
	// Room[GameData.CurrentRoom].Tipe=0;

	// for (int i=1;i<=2;i++)
	// {
	// 	FreeMeja(&Room[GameData.CurrentRoom].DMeja[i]);
	// 	Room[GameData.CurrentRoom].DMeja[i].NoMeja=i+2;
	// }
	// Absis(Room[GameData.CurrentRoom].DMeja[1].Posisi)=2;
	// Ordinat(Room[GameData.CurrentRoom].DMeja[1].Posisi)=4;
	// Room[GameData.CurrentRoom].DMeja[1].JmlKursi=2;
	// Room[GameData.CurrentRoom].DMeja[1].N[1]=true;
	// Room[GameData.CurrentRoom].DMeja[1].N[2]=true;
	// Room[GameData.CurrentRoom].DMeja[1].N[3]=false;
	// Room[GameData.CurrentRoom].DMeja[1].N[4]=false;


	// Absis(Room[GameData.CurrentRoom].DMeja[2].Posisi)=2;
	// Ordinat(Room[GameData.CurrentRoom].DMeja[2].Posisi)=10;
	// Room[GameData.CurrentRoom].DMeja[2].JmlKursi=4;
	// Room[GameData.CurrentRoom].DMeja[2].N[1]=true;
	// Room[GameData.CurrentRoom].DMeja[2].N[2]=true;
	// Room[GameData.CurrentRoom].DMeja[2].N[3]=true;
	// Room[GameData.CurrentRoom].DMeja[2].N[4]=true;

	// Room[GameData.CurrentRoom].DMeja[2].Terisi =2;
	// Room[GameData.CurrentRoom].DMeja[2].NIsiCustomer[1]=true;
	// Room[GameData.CurrentRoom].DMeja[2].NIsiCustomer[2]=true;


	MakeEmptyTabOrder(&TabOrders);
	CreateEmptyQC(&QWaitingC);
	CreateEmptyQC(&QSeatedC);
	CreateEmptyStck(&Tray);
	Absis(GameData.PosisiPlayer)=4;
	Ordinat(GameData.PosisiPlayer)=4;

	/* Added 15 random Orders to TabOrders */
		Order Orders;
		Orders.NoMenu = 1;  Orders.NoMeja = 2;  AddAsLastElTabOrder(&TabOrders, Orders);
		Orders.NoMenu = 3;  Orders.NoMeja = 4;  AddAsLastElTabOrder(&TabOrders, Orders);  
		Orders.NoMenu = 5;  Orders.NoMeja = 6;  AddAsLastElTabOrder(&TabOrders, Orders);

	CreateEmptyStck(&Hand);
    Push(&Hand,0);
    Push(&Hand,2);
    Push(&Hand,3);

    CreateEmptyStck(&Tray);
    Push(&Tray,0);
    Push(&Tray,2);
    Push(&Tray,3);
    Push(&Tray,7);

	AddCustomerWC(&QWaitingC, 1, 2, 3, FALSE);
	AddCustomerWC(&QWaitingC, 2, 3, 1, FALSE);
	AddCustomerWC(&QWaitingC, 3, 1, 2, true);

	initLayout();

	// printf("absis %d ordinat %d\n", GameData.PosisiPlayer.X, Ordinat(GameData.PosisiPlayer));
	// // Room[GameData.CurrentRoom].Map.NBrsEff=8;
	// // Room[GameData.CurrentRoom].Map.NKolEff=8;
	// TulisMatriks(Room[1].Map);
	// printf("\n");

	// printf("input 1/2/3: ");
	
	updateLayout();
	
	GetCommand();
	// BacaCommand();

	// if (EqualKata(Command,"1"))
	// {
	// 	orderFood();
	// }
	// else if(EqualKata(Command,"2"))
	// {
	// 	placeCustomer();
	// }
	// else if(EqualKata(Command,"3"))
	// {
	// 	giveFood();
	// }

	// BacaCommand();
	if (EqualKata(Command,"NEW"))
	{
		// mvprintw(25,1,"aka");
	}
	while (!(EqualKata(Command,"EXIT")))
	{
		/* Game Main Loop */
		if (EqualKata(Command, "RECIPE"))
			CursePrintTree(Resep);

		// BacaCommand();
		GetCommand();
	}
	endLayout();
}