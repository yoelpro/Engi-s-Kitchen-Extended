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

	system("clear");
	initLayout();
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