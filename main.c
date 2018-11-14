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

/* Deklarasi variable global */
int main()
{
	int i;
	InitGame();
	BacaCommand();
	while (!(EqualKata(Command.TabKata,Command.Length,"EXIT")))
	{
		/* Game Main Loop */
		// printf("%d\n",Command.Length);
		for (i=1; i<=Command.Length; i++)
		{
			printf("%c",Command.TabKata[i]);
		}
		printf("\n");
		BacaCommand();
	}
}