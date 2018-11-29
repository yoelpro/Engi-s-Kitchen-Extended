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

/* Deklarasi variable global */
int main()
{
	initMainMenu();
	InitGame();

	/* Added 15 random Orders to TabOrders */
		Order Orders;
		// Orders.NoMenu = 1;  Orders.NoMeja = 2;  AddAsLastElTabOrder(&TabOrders, Orders);
		// Orders.NoMenu = 3;  Orders.NoMeja = 4;  AddAsLastElTabOrder(&TabOrders, Orders);  
		// Orders.NoMenu = 5;  Orders.NoMeja = 6;  AddAsLastElTabOrder(&TabOrders, Orders);

	CreateEmptyStck(&Hand);
    // Push(&Hand,0);
    // Push(&Hand,2);
    // Push(&Hand,3);

    CreateEmptyStck(&Tray);
    // Push(&Tray,0);
    // Push(&Tray,2);
    // Push(&Tray,3);
    // Push(&Tray,7);

	// AddCustomerWC(&QWaitingC, 1, 2, 3, FALSE);
	// AddCustomerWC(&QWaitingC, 2, 3, 1, FALSE);
	// AddCustomerWC(&QWaitingC, 3, 1, 2, true);
	system("clear");
	initLayout();
	// updateLayout();
	
	// GetCommand();
	// BacaCommand();

	// if (EqualKata(Command,"NEW"))
	// {
	// 	// mvprintw(25,1,"aka");
	// }
	BacaCommand();
	while (!(EqualKata(Command,"EXIT")) && GameData.Life > 0)
	{
		system("clear");
		/* Game Main Loop */
		if (EqualKata(Command, "RECIPE"))
		{
			CursePrintTree(Resep);
		}
		else if (EqualKata(Command, "GU"))
		{
			GU();
			UpdateGameState(&GameData.Life);
		}
		else if (EqualKata(Command, "GD"))
		{
			GD();
			UpdateGameState();
		}
		else if (EqualKata(Command, "GL"))
		{
			GL();
			UpdateGameState();
		}
		else if (EqualKata(Command, "GR"))
		{
			GR();
			UpdateGameState();
		}
		else if (EqualKata(Command, "ORDER"))
		{
			orderFood();
			UpdateGameState();
		}
		else if (EqualKata(Command, "PUT"))
		{
			Put();
			UpdateGameState();
		}
		else if (EqualKata(Command, "TAKE"))
		{
			Take();
			UpdateGameState();
		}
		else if (EqualKata(Command, "CH"))
		{
			CreateEmptyStck(&Hand);
			UpdateGameState();
		}
		else if (EqualKata(Command, "CT"))
		{
			CreateEmptyStck(&Tray);
			UpdateGameState();
		}
		else if (EqualKata(Command, "PLACE"))
		{
			placeCustomer();
			UpdateGameState();
		}
		else if (EqualKata(Command, "GIVE"))
		{
			giveFood();
			UpdateGameState();
		}
		else if (EqualKata(Command, "RECIPE"))
		{
			orderFood();
		}
		else if (EqualKata(Command, "SAVE"))
		{
			orderFood();
		}
		else if (EqualKata(Command, "LOAD"))
		{
			orderFood();
		}
		else if (EqualKata(Command, "EXIT"))
		{
			printf("Goodbye!\n");
		}
		if (GameData.Life > 0)
		{
			updateLayout();
			BacaCommand();
		}
	}

	initCredit();

}