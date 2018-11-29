#include "display.h"
#include <stdlib.h>

/* Kelompok Tampilan */
/* Kamus Tampilan*/
    /* Cursor */
    int start_y, start_x;
    int player_y, player_x;

    char user_input[10];

void initMainMenu(){
    int ch;

    printf("\n######                            ######                          #    # #     #  #####  \n");
    printf("#     # # #    # ###### #####     #     #   ##    ####  #    #    #   #  #  #  # #     # \n");
    printf("#     # # ##   # #      #    #    #     #  #  #  #      #    #    #  #   #  #  #       # \n");
    printf("#     # # # #  # #####  #    #    #     # #    #  ####  ######    ###    #  #  #  #####  \n");
    printf("#     # # #  # # #      #####     #     # ######      # #    #    #  #   #  #  #       # \n");
    printf("#     # # #   ## #      #   #     #     # #    # #    # #    #    #   #  #  #  # #     # \n");
    printf("######  # #    # ###### #    #    ######  #    #  ####  #    #    #    #  ## ##   #####  \n");
    printf("\n\n");

    printf("Please input your name\n");
    printf("Name: ");
    scanf("%s",GameData.Nama);
    system("clear");
}

void initCredit(){
    int ch;

    printf("\n######                            ######                          #    # #     #  #####  \n");
    printf("#     # # #    # ###### #####     #     #   ##    ####  #    #    #   #  #  #  # #     # \n");
    printf("#     # # ##   # #      #    #    #     #  #  #  #      #    #    #  #   #  #  #       # \n");
    printf("#     # # # #  # #####  #    #    #     # #    #  ####  ######    ###    #  #  #  #####  \n");
    printf("#     # # #  # # #      #####     #     # ######      # #    #    #  #   #  #  #       # \n");
    printf("#     # # #   ## #      #   #     #     # #    # #    # #    #    #   #  #  #  # #     # \n");
    printf("######  # #    # ###### #    #    ######  #    #  ####  #    #    #    #  ## ##   #####  \n");
    printf("\n\n");

    printf("Created by\n");
    printf("13517014 - Yoel Susanto (IF 2017)\n");
    printf("13517119 - Stefanus Ardi Mulia (IF 2017)\n");
    printf("13517146 - Hansen (IF 2017)\n");
    printf("13517053 - Jesslyn Nathania (IF 2017)\n");
    printf("13517125 - Christzen Leonardy (IF 2017)\n");

    printf("\nPress any button to continue\n");

    getchar();
}

void initLayout(){
    updateLayout();
}

void CursePrintTreeRec (BinTree P, int level, int h) {
    int i;

	if (!IsTreeEmpty(P)) {
		if (level == 0)
			printf("%s\n", JenisBahan[Akar(P)]);
		else {
            for (i = 1; i <= (level-1)*h; i++)
                printf(" ");
            if (IsTreeOneElmt(P))
                printf("`---%s\n", JenisMakanan[Akar(P)]);
            else
                printf("`---%s\n", JenisBahan[Akar(P)]);
        }

		if (!IsTreeEmpty(Left(P))){
			CursePrintTreeRec(Left(P), level+1, h);
		}
		if (!IsTreeEmpty(Right(P))){
			CursePrintTreeRec(Right(P), level+1, h);
		}
	}
}

void CursePrintTree(BinTree P){
	// Kamus Lokal
	int y;

	// Algoritma
    system("clear");
	CursePrintTreeRec(P, 0, 4);

	// mvwprintw(tree_disp, 0, 0, "#Recipe Tree");
	printf("\nPress Enter to close recipe\n");
    getchar(); 
}

void CursePrintQC(TypeQueueCustomer QC){
	int i;
	int y, x;

	x = 1;
	y = 1;

	if (!IsEmptyQC(QC))
		for(i = Head(QC); i <= Tail(QC); i++){
			// printf("%d %d %d %d %u\n", QC.Customer[i].Id, QC.Customer[i].NoMeja, QC.Customer[i].Kesabaran, QC.Customer[i].JmlOrang, QC.Customer[i].Star);
			if (QC.Customer[i].Star)
				printf("%d (%d) (Star) (%d)\n", QC.Customer[i].Id, QC.Customer[i].Kesabaran, QC.Customer[i].JmlOrang);
			else
				printf("%d (%d) (%d)\n", QC.Customer[i].Id, QC.Customer[i].Kesabaran, QC.Customer[i].JmlOrang);
		}
	else
		printf("There's no one here");
}

void CursePrintTabOrder(TabOrder T){
	// Algoritma
  	for (int i=1; i<=Neff(T); i++){
        printf("%s, %d\n", JenisMakanan[ElmtArr(T, i).NoMenu], ElmtArr(T,i).NoMeja);
  	}
    if (Neff(T) == 0)
        printf("You don't have any order, you can sleep\n");

  	// Kasus jika elemen T melebihi batas window order_disp
  	// if (y == maxy-1){
  	// 	printf("etc...\n");
  	// }
}

void CurseTulisMatriks (Matriks M)
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
    int x,y,k;

    /* ALGORITMA */
    x = 1;
    y = 1;
    
    printf("+------------MAP ROOM------------+\n");
    for(i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++){
        for(j=GetFirstIdxKol(M);j<=GetLastIdxKol(M);j++){
            if (j == GetFirstIdxKol(M))
                printf("|");
            if (j == Absis(GameData.PosisiPlayer) && i == Ordinat(GameData.PosisiPlayer)){
                printf(" P  ");
                // for (k = 1; k <= 4; k++){
                //     if (k != CurrentRoom(GameData)){
                //         if (j == Absis(InfoG(SearchEdge(Door,CurrentRoom(GameData),k))) && i == Ordinat(InfoG(SearchEdge(Door,CurrentRoom(GameData),k))))
                //             printf(" # ");
                //     }
                // }
            }
            else
                printf(" %c  ", ElmtMat(M,i,j));
            if (j == GetLastIdxKol(M))
                printf("|");
        }
        printf("\n\n");
    }
    printf("+--------------------------------+");
    printf("\n");
}

void CursePrintStack(Stack *Current, char opt)
{
    Stack ReverseStack;
    int Z;
    int y,x;

    if(!IsEmptyStck(*Current)){
        /*Membuat salinan *Current*/
            CreateEmptyStck(&ReverseStack);
            do
            {
                Pop(&*Current,&Z);
                Push(&ReverseStack,Z);
            }
            while (!IsEmptyStck(*Current));

        /* Mencetak dan memasukkan kembali salinan *Current */
            Pop(&ReverseStack, &Z);
            Push(&*Current, Z);
                switch(opt){
                    case 'h': printf("%s", JenisBahan[Z]);
                        break;
                    case 't': printf("%s", JenisMakanan[Z]);
                }
            while (!IsEmptyStck(ReverseStack))
            {
                Pop(&ReverseStack, &Z);
                Push(&*Current, Z);
	                switch(opt){
	                	case 'h': printf(", %s", JenisBahan[Z]);
	                		break;
	                	case 't': printf(", %s", JenisMakanan[Z]);
	                }
                // printf("%c ", Z);
            }
            printf("\n");
    }
    else{
    	printf("It's Empty, bro\n");
    }
}

void updateLayout(){
    /* Print data */
        // system("cls"); //windows

        printf("+----------------------------------------------------------------+\n");
        printf("   %s", GameData.Nama); // Display
        printf("        | ");

        printf("Money: %ld", Money(GameData)); // Display
        printf("        | ");

        printf("Life: %d", Life(GameData)); // Display
        printf("        | ");

        printf("Waktu: "); 
        TulisJAM(Waktu(GameData)); // Display
        printf("\n");
        printf("+----------------------------------------------------------------+\n");
        printf("player pos x: %d  y: %d \n", Absis(GameData.PosisiPlayer), Ordinat(GameData.PosisiPlayer));

        printf("+--------------------------+\n");
        printf("|     Waiting Customer     |\n");
        printf("+--------------------------+\n");
        CursePrintQC(QWaitingC);
        printf("\n");

        printf("+--------------------------+\n");
        printf("|     Seating Customer     |\n");
        printf("+--------------------------+\n");
        CursePrintQC(QSeatedC);
        printf("\n");
        
        if (CurrentRoom(GameData) == 1)
            CurseTulisMatriks(Room[1].Map);
        else if (CurrentRoom(GameData) == 2)
            CurseTulisMatriks(Room[2].Map);
        else if (CurrentRoom(GameData) == 3)
            CurseTulisMatriks(Room[3].Map);
        else if (CurrentRoom(GameData) == 4)
            CurseTulisMatriks(Room[4].Map);    
    
        printf("\n");
        printf("+--------------------+\n");
        printf("|     Food Stack     |\n");
        printf("+--------------------+\n");
        CursePrintStack(&Tray, 't'); // Displaying the food

        printf("\n");
        printf("+---------------+\n");
        printf("|     Order     |\n");
        printf("+---------------+\n");
        CursePrintTabOrder(TabOrders);

        printf("\n");
        printf("+--------------+\n");
        printf("|     Hand     |\n");
        printf("+--------------+\n");
        CursePrintStack(&Hand, 'h'); // Displaying what's on the hand

        printf("\n");
        printf("Type EXIT to stop\n");

        printf("+------------------\n");
        printf("| Command: ");
        // printf("+-----------");
}

void GetCommand(){
    CurseBacaCommand();
    updateLayout();
}

/* Kelompok MesinKata MesinKar */

void CurseADVCommand()
{
  /* Algoritma */
//   CCommand = scanf("%c", CC);
//   EOP = (CCommand == ENTER);
}

void CurseBacaCommand()
/* Procedure yang digunakan */
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
  STARTCommand();
  switch (CCommand)
  {
    case ENTER:
    {
      EndCommand = true;
      break;
    }
    default :
    {
      EndCommand = false;
      // printf("salin\n");
      CurseSalinCommand();
    }
  }
}

void CurseSalinCommand()
/* Mengakuisisi command dari console, menyimpan dalam CCommand
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CCommand berisi kata yang sudah diakuisisi; 
          CC = \n */
{
  int i;
  //Algoritma
  i=1;
  do
  {
    // printf("%c\n",CC);
    if (i<=NMax)
    {
      Command.TabKata[i] = CCommand;
      i++;
    }
    CurseADVCommand();
  } while (CCommand!=ENTER);
  i--;
  Command.Length = i;
}


// #include <curses.h>
// #include "display.h"

// /* Kelompok Tampilan */
// /* Kamus Tampilan*/
//     /* Pointer display */
//     WINDOW *name_disp, *money_disp, *life_disp, *time_disp, *waitcust_disp, *order_disp, *room1_disp, *room2_disp, *room3_disp, *room4_disp, 
//     	*food_disp, *hand_disp, *command_disp, *tree_disp, *prompt_disp;

//     /* Ukuran display */
//     int disp_height, disp_width;
//     int name_height, name_width, money_height, money_width, life_height, life_width, time_height, time_width;
//     int waitcust_height, waitcust_width, order_height, order_width, food_height, food_width, hand_height, hand_width;
//     int room1_height, room1_width, room2_height, room2_width, room3_height, room3_width, room4_height, room4_width;
//     int command_height, command_width;
//     int prompt_height, prompt_width;
//     int tree_height, tree_width;

//     /* Cursor */
//     int start_y, start_x;
//     int player_y, player_x;

//     char user_input[10];

// void initLayout(){
//     /* CURSES START */
//     initscr();
//     // cbreak();
//     // raw();
//     // noecho();    }

//     setLayout();
//     refresh();
//     printLayout();
//     updateLayout();
// }

// void setLayout(){
//     /* Set Ukuran Display */
//         name_height = 3;
//         name_width = 25;
//         money_height = name_height;
//         money_width = 25;
//         life_height = name_height;
//         life_width = 25;
//         time_height = name_height;
//         time_width = 25;
//         waitcust_height = 11;
//         waitcust_width = name_width;
//         order_height = 11;
//         order_width = name_width;

//         room1_height = 17; // CUSTOM, ORI = waitcust_height + order_height
//         room1_width = 33; // CUSTOM, ORI = 50
//         room2_height = 17; // CUSTOM, ORI = waitcust_height + order_height
//         room2_width = 33; // CUSTOM, ORI = 50
//         room3_height = 17; // CUSTOM, ORI = waitcust_height + order_height
//         room3_width = 33; // CUSTOM, ORI = 50
//         room4_height = 17; // CUSTOM, ORI = waitcust_height + order_height
//         room4_width = 33; // CUSTOM, ORI = 50

//         food_height = waitcust_height;
//         food_width = 25;
//         hand_height = order_height;
//         hand_width = food_width;
//         command_height = 3;
//         command_width = order_width + 50 + hand_width;

//         prompt_height = 10;
//         prompt_width = 15;

//         tree_height = 28;
//         tree_width = 50;

//         disp_height = 10;
//         disp_width = 40;

//         start_y = 0;
//         start_x = 0;
// }

// void printLayout(){
//     /* Print Layout */
//         start_y = 0;
//         start_x = 0;

//         name_disp = newwin(name_height, name_width, start_y, start_x);
//         box(name_disp,0,0);
//         wrefresh(name_disp);

//         start_x += name_width;
//         money_disp = newwin(money_height, money_width, start_y, start_x);
//         box(money_disp,0,0);
//         wrefresh(money_disp);

//         start_x += money_width;
//         life_disp = newwin(life_height, life_width, start_y, start_x);
//         box(life_disp,0,0);
//         wrefresh(life_disp);

//         start_x += life_width;
//         time_disp = newwin(time_height, time_width, start_y, start_x);
//         box(time_disp,0,0);
//         wrefresh(time_disp);

//         start_x += time_width;
//         prompt_disp = newwin(prompt_height,prompt_width,start_y,start_x);
//         box(prompt_disp,0,0);
//         wrefresh(prompt_disp);

//         start_x = 0;
//         start_y += name_height;
//         waitcust_disp = newwin(waitcust_height, waitcust_width, start_y, start_x);
//         box(waitcust_disp,0,0);
//         wrefresh(waitcust_disp);

//         start_x += waitcust_width;
//         room1_disp = newwin(room1_height, room1_width, start_y+1, start_x+2);
//         box(room1_disp,0,0);
//         wrefresh(room1_disp);

//         room2_disp = newwin(room2_height, room2_width, start_y, start_x+11);
//         box(room2_disp,0,0);
//         wrefresh(room2_disp);

//         room3_disp = newwin(room3_height, room3_width, start_y+4, start_x+15);
//         box(room3_disp,0,0);
//         wrefresh(room3_disp);

//         room4_disp = newwin(room4_height, room4_width, start_y+5, start_x+5);
//         box(room4_disp,0,0);
//         wrefresh(room4_disp);

//         start_x += 50; // ORI room1_width
//         food_disp = newwin(food_height, food_width, start_y, start_x);
//         box(food_disp,0,0);
//         wrefresh(food_disp);

//         start_x = 0;
//         start_y += waitcust_height;
//         order_disp = newwin(order_height, order_width, start_y, start_x);
//         box(order_disp,0,0);
//         wrefresh(order_disp);

//         start_x += order_width + 50; // ORI 50 is room1_width
//         hand_disp = newwin(hand_height, hand_width, start_y, start_x);
//         box(hand_disp,0,0);
//         wrefresh(hand_disp);

//         start_x = 0;
//         start_y += order_height;
//         command_disp = newwin(command_height, command_width, start_y, start_x);
//         box(command_disp,0,0);
//         wrefresh(command_disp);
// }

// void CursePrintTreeRec (BinTree P, int level, int h, int *y, int x) {
// 	if (!IsTreeEmpty(P)) {
// 		int i;

// 		if (x == 1)
// 			mvwprintw(tree_disp,*y,x,"%s", JenisBahan[Akar(P)]);
// 		else if (IsTreeOneElmt(P))
// 			mvwprintw(tree_disp,*y,x-h,"`---%s", JenisMakanan[Akar(P)]);
// 		else
// 			mvwprintw(tree_disp,*y,x-h,"`---%s", JenisBahan[Akar(P)]);

// 		if (!IsTreeEmpty(Left(P))){
// 			(*y)++;
// 			CursePrintTreeRec(Left(P), level+1, h, y, x+h);
// 		}
// 		if (!IsTreeEmpty(Right(P))){
// 			(*y)++;
// 			CursePrintTreeRec(Right(P), level+1, h, y, x+h);
// 		}
// 	}
// }

// void CursePrintTree(BinTree P){
// 	// Kamus Lokal
// 	int y;

// 	// Algoritma
// 	tree_disp = newwin(tree_height, tree_width, 2, 24);
//     box(tree_disp,0,0);
//     y = 1;
// 	CursePrintTreeRec(P, 0, 4, &y, 1);

// 	// mvwprintw(tree_disp, 0, 0, "#Recipe Tree");
// 	wattron(tree_disp, A_UNDERLINE);
// 	mvwprintw(tree_disp, tree_height-2, 1, "Press Enter to close recipe");
// 	wattroff(tree_disp, A_UNDERLINE);
// 	wrefresh(tree_disp);
// 	noecho();
// 	while (wgetch(tree_disp) != ENTER){}
// 	delwin(tree_disp);
// 	wrefresh(tree_disp);
// 	printLayout();
// 	updateLayout();
// 	echo();
// }

// void CursePrintQC(TypeQueueCustomer QC){
// 	int i;
// 	int y, x;

// 	x = 1;
// 	y = 1;

// 	if (!IsEmptyQC(QC))
// 		for(i = Head(QC); i <= Tail(QC); i++){
// 			// printf("%d %d %d %d %u\n", QC.Customer[i].Id, QC.Customer[i].NoMeja, QC.Customer[i].Kesabaran, QC.Customer[i].JmlOrang, QC.Customer[i].Star);
// 			if (QC.Customer[i].Star)
// 				mvwprintw(waitcust_disp, y + i, x, "%d (%d) (Star)", QC.Customer[i].Id, QC.Customer[i].Kesabaran);
// 			else
// 				mvwprintw(waitcust_disp, y + i, x, "%d (%d)", QC.Customer[i].Id, QC.Customer[i].Kesabaran);
// 		}
// 	else
// 		mvwprintw(waitcust_disp, y, x, "There's no one here");
// }

// void CursePrintTabOrder(TabOrder T){
// 	// Kamus Lokal
// 	int x,y;
// 	int maxx, maxy;

// 	// Algoritma
// 	x = 1;
// 	y = 2;
// 	getmaxyx(order_disp, maxy, maxx);

//   	for (int i=1; i<=Neff(T); i++){
//   		// Tidak akan lanjut mencetak elemen jika window order_disp sudah penuh
//   		if (y < maxy-1){ 
//     		mvwprintw(order_disp, y, x, "%s, %d", JenisMakanan[ElmtArr(T, i).NoMenu], ElmtArr(T,i).NoMeja);
//     		y++;
//   		}
//   	}

//   	// Kasus jika elemen T melebihi batas window order_disp
//   	if (y == maxy-1){
//   		wattron(order_disp, A_UNDERLINE);
//   		mvwprintw(order_disp, y, x, "etc...");
//   		wattroff(order_disp, A_UNDERLINE);
//   	}
// }

// void CurseTulisMatriks (WINDOW *win, Matriks M)
// /* I.S. M terdefinisi */
// /* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
//    dipisahkan sebuah spasi */
// /* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
// /* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
// 1 2 3
// 4 5 6
// 8 9 10
// */
// {
//     /* KAMUS LOKAL */
//     matriksIndeks i, j;
//     int x,y;

//     /* ALGORITMA */
//     x = 1;
//     y = 1;

//     wmove(win, y,x);
    
//     for(i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++){

//         for(j=GetFirstIdxKol(M);j<GetLastIdxKol(M);j++){
//             wprintw(win, " %c  ", ElmtMat(M,i,j));
//         }

//         if(i==GetLastIdxBrs(M)){
//             wprintw(win, " %c ", ElmtMat(M,i,GetLastIdxKol(M)));
//         }
//         else{
//             wprintw(win, " %c ", ElmtMat(M,i,GetLastIdxKol(M)));
//         }
//         y+=2;
//         wmove(win, y,x);
//     }
// }

// void CursePrintStack(WINDOW *win, Stack *Current, char opt)
// {
//     Stack ReverseStack;
//     int Z;
//     int y,x;
//     int maxy,maxx;

//     if(!IsEmptyStck(*Current)){
//         /*Membuat salinan *Current*/
//             CreateEmptyStck(&ReverseStack);
//             do
//             {
//                 Pop(&*Current,&Z);
//                 Push(&ReverseStack,Z);
//             }
//             while (!IsEmptyStck(*Current));

//         /* Mencetak dan memasukkan kembali salinan *Current */
//             x = 1;
//             y = 2;
//             getmaxyx(win,maxy,maxx);

//             do{
//                 Pop(&ReverseStack, &Z);
//                 Push(&*Current, Z);
//                 if (y < maxy-1){
// 	                switch(opt){
// 	                	case 'h': mvwprintw(win, y, x, "%s", JenisBahan[Z]);
// 	                		break;
// 	                	case 't': mvwprintw(win, y, x, "%s", JenisMakanan[Z]);
// 	                }
//                 	y++;
//             	}
//                 // printf("%c ", Z);
//             }while (!IsEmptyStck(ReverseStack));

//             if (y == maxy-1){
//             	wattron(win, A_UNDERLINE);
//             	mvwprintw(win, y, x, "etc...");
//             	wattroff(win, A_UNDERLINE);
//             }
//     }
//     else{
//     	mvwprintw(win, 3, 1, "It's Empty, bro");
//     }
// }

// void updateLayout(){
//     /* Print data */
//         wmove(name_disp, 1, 1);
//         wprintw(name_disp, "<Name>"); // Display
//         wrefresh(name_disp);

//         wmove(money_disp, 1, 1);
//         wprintw(money_disp, "Money: %ld", Money(GameData)); // Display
//         wrefresh(money_disp);

//         wmove(life_disp, 1, 1);
//         wprintw(life_disp, "Life: %ld", Life(GameData)); // Display
//         wrefresh(life_disp);

//         wmove(time_disp, 1, 1);
//         wprintw(time_disp, "Waktu: %ld", Waktu(GameData)); // Display
//         wrefresh(time_disp);

//         wmove(waitcust_disp, 1, 1);
//         wattron(waitcust_disp, A_BOLD);
//         wprintw(waitcust_disp, "Waiting Customer");
//         wattroff(waitcust_disp, A_BOLD);
//         CursePrintQC(QWaitingC);
//         wrefresh(waitcust_disp);

//         // int i,j;
//         // i = 0;
//         // j = 0;

//         switch(CurrentRoom(GameData)){
//         	case 1:
// 		        room1_disp = newwin(room1_height, room1_width, name_height+1, waitcust_width+2);
// 		        box(room1_disp,0,0);

// 		        wmove(room1_disp, 1, 1);
// 		        CurseTulisMatriks(room1_disp, Room[1].Map); // Displaying the map
// 		        mvwprintw(room1_disp, Ordinat(GameData.PosisiPlayer)*2-1, (Absis(GameData.PosisiPlayer)-1)*4+2, "P"); // Display Player
// 		        wattron(room1_disp, A_UNDERLINE);

// 			        // if (Ordinat(InfoG(SearchEdge(Door, 1, 2))) == 1){
// 			        // 	i = 0;
// 			        // 	j = -1;
// 			        // }
// 			        // else if (Ordinat(InfoG(SearchEdge(Door, 1, 2))) == 8){
// 			        // 	i = 0;
// 			        // 	j = 1;
// 			        // }
// 			        // else if (Absis(InfoG(SearchEdge(Door, 1, 2))) == 1){
// 			        // 	i = -1;
// 			        // 	j = 0;
// 			        // }
// 			        // else if (Absis(InfoG(SearchEdge(Door, 1, 2))) == 8){
// 			        // 	i = 1;
// 			        // 	j = 0;
// 			        // }

// 			    mvwprintw(room1_disp, Ordinat(InfoG(SearchEdge(Door, 1, 2)))*2-1, (Absis(InfoG(SearchEdge(Door, 1, 2)))-1)*4+2, "#"); // Display Door

// 		        mvwprintw(room1_disp, Ordinat(InfoG(SearchEdge(Door, 1, 3)))*2-1, (Absis(InfoG(SearchEdge(Door, 1, 3)))-1)*4+2, "#"); // Display Door
// 		        wattroff(room1_disp, A_UNDERLINE);
// 		        // mvwprintw(room1_disp, Ordinat(InfoG(SearchEdge(Door, 1, 2)))*2, (Absis(InfoG(SearchEdge(Door, 1, 2)))-1)*4+1, "vvv");
// 		        // mvwprintw(room1_disp, Ordinat(InfoG(SearchEdge(Door, 1, 4)))*2, (Absis(InfoG(SearchEdge(Door, 1, 4)))-1)*4+4, ">");
// 		        // mvwprintw(room1_disp, Ordinat(InfoG(SearchEdge(Door, 1, 4)))*2-1, (Absis(InfoG(SearchEdge(Door, 1, 4)))-1)*4+4, ">");
// 		        // mvwprintw(room1_disp, Ordinat(InfoG(SearchEdge(Door, 1, 4)))*2+1, (Absis(InfoG(SearchEdge(Door, 1, 4)))-1)*4+4, ">");
// 		        wrefresh(room1_disp);
// 		        break;
// 		    case 2:
// 		        room1_disp = newwin(room2_height, room2_width, name_height, waitcust_width+11);
// 		        box(room2_disp,0,0);

// 		        wmove(room2_disp, 1, 1);
// 		        CurseTulisMatriks(room2_disp, Room[2].Map); // Displaying the map
// 		        mvwprintw(room2_disp, Ordinat(GameData.PosisiPlayer)*2-1, (Absis(GameData.PosisiPlayer)-1)*4+2, "P"); // Display Player
// 		        wattron(room2_disp, A_UNDERLINE);
// 		        mvwprintw(room2_disp, Ordinat(InfoG(SearchEdge(Door, 2, 3)))*2-1, (Absis(InfoG(SearchEdge(Door, 2, 3)))-1)*4+2, "#"); // Display Door
// 		        mvwprintw(room2_disp, Ordinat(InfoG(SearchEdge(Door, 2, 1)))*2-1, (Absis(InfoG(SearchEdge(Door, 2, 1)))-1)*4+2, "#"); // Display Door
// 		        wattroff(room2_disp, A_UNDERLINE);
// 		        // mvwprintw(room2_disp, Ordinat(InfoG(SearchEdge(Door, 2, 3)))*2-1, (Absis(InfoG(SearchEdge(Door, 2, 3)))-1)*4+2, "vvv");
// 		        // mvwprintw(room2_disp, Ordinat(InfoG(SearchEdge(Door, 2, 1)))*2-2, (Absis(InfoG(SearchEdge(Door, 2, 1)))-1)*4+2, "<");
// 		        // mvwprintw(room2_disp, Ordinat(InfoG(SearchEdge(Door, 2, 1)))*2-1, (Absis(InfoG(SearchEdge(Door, 2, 1)))-1)*4+2, "<");
// 		        // mvwprintw(room2_disp, Ordinat(InfoG(SearchEdge(Door, 2, 1)))*2-0, (Absis(InfoG(SearchEdge(Door, 2, 1)))-1)*4+2, "<");
// 		        wrefresh(room2_disp);
// 		        break;
// 		    case 3:
// 		        room3_disp = newwin(room3_height, room3_width, name_height+4, waitcust_width+15);
// 		        box(room3_disp,0,0);

// 		        wmove(room3_disp, 1, 1);
// 		        CurseTulisMatriks(room3_disp, Room[3].Map); // Displaying the map
// 		        mvwprintw(room3_disp, Ordinat(GameData.PosisiPlayer)*2-1, (Absis(GameData.PosisiPlayer)-1)*4+2, "P"); // Display Player
// 		        wattron(room3_disp, A_UNDERLINE);
// 		        mvwprintw(room3_disp, Ordinat(InfoG(SearchEdge(Door, 3, 4)))*2-1, (Absis(InfoG(SearchEdge(Door, 3, 4)))-1)*4+2, "#"); // Display Door
// 		        mvwprintw(room3_disp, Ordinat(InfoG(SearchEdge(Door, 3, 2)))*2-1, (Absis(InfoG(SearchEdge(Door, 3, 2)))-1)*4+2, "#"); // Display Door
// 		        wattroff(room3_disp, A_UNDERLINE);
// 		        wrefresh(room3_disp);
// 		        break;
// 		    case 4:
// 		        room4_disp = newwin(room4_height, room4_width, name_height+5, waitcust_width+5);
// 		        box(room4_disp,0,0);

// 		        wmove(room4_disp, 1, 1);
// 		        CurseTulisMatriks(room4_disp, Room[4].Map); // Displaying the map
// 		        mvwprintw(room4_disp, Ordinat(GameData.PosisiPlayer)*2-1, (Absis(GameData.PosisiPlayer)-1)*4+2, "P"); // Display Player
// 		        wattron(room4_disp, A_UNDERLINE);
// 		        mvwprintw(room4_disp, Ordinat(InfoG(SearchEdge(Door, 4, 3)))*2-1, (Absis(InfoG(SearchEdge(Door, 4, 3)))-1)*4+2, "#"); // Display Door
// 		        mvwprintw(room4_disp, Ordinat(InfoG(SearchEdge(Door, 4, 1)))*2-1, (Absis(InfoG(SearchEdge(Door, 4, 1)))-1)*4+2, "#"); // Display Door
// 		        wattroff(room4_disp, A_UNDERLINE);
// 		        wrefresh(room4_disp);
// 		        break;
		    
// 	    }
        

//         wmove(food_disp, 1, 1);
//         wattron(food_disp, A_BOLD);
//         wprintw(food_disp, "Food Stack");
//         wattroff(food_disp, A_BOLD);
//         CursePrintStack(food_disp, &Tray, 't'); // Displaying the food
//         wrefresh(food_disp);

//         wmove(order_disp, 1, 1);
//         wattron(order_disp, A_BOLD);
//         wprintw(order_disp, "Order");
//         wattroff(order_disp, A_BOLD);
//         CursePrintTabOrder(TabOrders);
//         wrefresh(order_disp);

//         wmove(hand_disp, 1, 1);
//         wattron(hand_disp, A_BOLD);
//         wprintw(hand_disp, "Hand");
//         wattroff(hand_disp, A_BOLD);
//         CursePrintStack(hand_disp, &Hand, 'h'); // Displaying what's on the hand
//         wrefresh(hand_disp);

//         start_x = 0;
//         start_y = name_height + waitcust_height + order_height;
//         command_disp = newwin(command_height, command_width, start_y, start_x);
//         box(command_disp,0,0);

//         mvprintw(start_y + 3,0,"Type EXIT to stop");
//         refresh();

//         wmove(command_disp, 1, 1);
//         wattron(command_disp, A_BOLD);
//         wprintw(command_disp, "Command: ");
//         wattroff(command_disp, A_BOLD);
//         wrefresh(command_disp);
// }

// void GetCommand(){
//     CursorOnCommand();
//     CurseBacaCommand();
//     updateLayout();
// }

// void CursorOnCommand(){
//     // wmove(command_disp, 1, 10); // memindah cursor ke posisi (10,1) relatif terhadap command_disp
//     wmove(command_disp, 1, 10);
//     wrefresh(command_disp);
// }

// void endLayout(){
//     endwin();
//     /* Terminate curses */
// }

// /* Kelompok MesinKata MesinKar */

// void CurseADVCommand()
// {
//   /* Algoritma */
//   CCommand = wgetch(command_disp);
//   EOP = (CCommand == ENTER);
// }

// void CurseBacaCommand()
// /* Procedure yang digunakan */
// /* I.S. : CC sembarang 
//    F.S. : EndKata = true, dan CC = MARK; 
//           atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
//           CC karakter pertama sesudah karakter terakhir kata */
// {
//   STARTCommand();
//   switch (CCommand)
//   {
//     case ENTER:
//     {
//       EndCommand = true;
//       break;
//     }
//     default :
//     {
//       EndCommand = false;
//       // printf("salin\n");
//       CurseSalinCommand();
//     }
//   }
// }

// void CurseSalinCommand()
// /* Mengakuisisi command dari console, menyimpan dalam CCommand
//    I.S. : CC adalah karakter pertama dari kata
//    F.S. : CCommand berisi kata yang sudah diakuisisi; 
//           CC = \n */
// {
//   int i;
//   //Algoritma
//   i=1;
//   do
//   {
//     // printf("%c\n",CC);
//     if (i<=NMax)
//     {
//       Command.TabKata[i] = CCommand;
//       i++;
//     }
//     CurseADVCommand();
//   } while (CCommand!=ENTER);
//   i--;
//   Command.Length = i;
// }