#include <curses.h>

/* Kamus */
	/* Pointer display */
	WINDOW *name_disp, *money_disp, *life_disp, *time_disp, *waitcust_disp, *order_disp, *map_disp, *food_disp, *hand_disp, *command_disp;

	/* Ukuran display */
	int disp_height, disp_width;
	int name_height, name_width, money_height, money_width, life_height, life_width, time_height, time_width;
	int waitcust_height, waitcust_width, order_height, order_width, map_height, map_width, food_height, food_width, hand_height, hand_width;
	int command_height, command_width;

	/* Cursor */
	int start_y, start_x;
	int player_y, player_x;

	char user_input[10];

/* Fungsi dan Prosedur */
	void setLayout();
	void printLayout();
	void updateLayout();

int main(){
	/* CURSES START */
	initscr();

	setLayout();

	refresh();

	printLayout();

	updateLayout();

	mvprintw(25,0,"Press F1 to give command");
	mvprintw(26,0,"Use keypad to move 'X' around");

	player_x = 1;
	player_y = 1;

	mvwprintw(map_disp,player_y,player_x,"X");
	wrefresh(map_disp);

	keypad(stdscr, TRUE); // For reading F1 key
	int ch;
	while((ch = getch()) != KEY_F(1))
	{	
		mvwprintw(map_disp,player_y,player_x," ");
		switch(ch)
		{	case KEY_LEFT:
				if (player_x > 1)
					player_x--;
				break;
			case KEY_RIGHT:
				if (player_x < map_width - 2)
					player_x++;
				break;
			case KEY_UP:
				if (player_y > 1)
					player_y--;
				break;
			case KEY_DOWN:
				if (player_y < map_height - 2)
					player_y++;
				break;	
		}
		mvwprintw(map_disp,player_y,player_x,"X");
		wrefresh(map_disp);
	}

	mvwgetstr(command_disp, 1, 10, user_input);
	updateLayout();

	mvprintw(27,0,"Press any key to exit");
	getch();
	endwin();
	/* Terminate curses */
}

void setLayout(){
	/* Set Ukuran Display */
		name_height = 3;
		name_width = 25;
		money_height = name_height;
		money_width = 25;
		life_height = name_height;
		life_width = 25;
		time_height = name_height;
		time_width = 25;
		waitcust_height = 8;
		waitcust_width = name_width;
		order_height = 8;
		order_width = name_width;
		map_height = waitcust_height + order_height;
		map_width = 50;
		food_height = waitcust_height;
		food_width = 25;
		hand_height = order_height;
		hand_width = food_width;
		command_height = 3;
		command_width = order_width + map_width + hand_width;

		disp_height = 10;
		disp_width = 40;

		start_y = 0;
		start_x = 0;
}

void printLayout(){
	/* Print Layout */
		start_y = 0;
		start_x = 0;

		name_disp = newwin(name_height, name_width, start_y, start_x);
		box(name_disp,0,0);
		wrefresh(name_disp);

		start_x += name_width;
		money_disp = newwin(money_height, money_width, start_y, start_x);
		box(money_disp,0,0);
		wrefresh(money_disp);

		start_x += money_width;
		life_disp = newwin(life_height, life_width, start_y, start_x);
		box(life_disp,0,0);
		wrefresh(life_disp);

		start_x += life_width;
		time_disp = newwin(time_height, time_width, start_y, start_x);
		box(time_disp,0,0);
		wrefresh(time_disp);

		start_x = 0;
		start_y += name_height;
		waitcust_disp = newwin(waitcust_height, waitcust_width, start_y, start_x);
		box(waitcust_disp,0,0);
		wrefresh(waitcust_disp);

		start_x += waitcust_width;
		map_disp = newwin(map_height, map_width, start_y, start_x);
		box(map_disp,0,0);
		wrefresh(map_disp);

		start_x += map_width;
		food_disp = newwin(food_height, food_width, start_y, start_x);
		box(food_disp,0,0);
		wrefresh(food_disp);

		start_x = 0;
		start_y += waitcust_height;
		order_disp = newwin(order_height, order_width, start_y, start_x);
		box(order_disp,0,0);
		wrefresh(order_disp);

		start_x += order_width + map_width;
		hand_disp = newwin(hand_height, hand_width, start_y, start_x);
		box(hand_disp,0,0);
		wrefresh(hand_disp);

		start_x = 0;
		start_y += order_height;
		command_disp = newwin(command_height, command_width, start_y, start_x);
		box(command_disp,0,0);
		wrefresh(command_disp);
}

void updateLayout(){
	/* Print data */
		wmove(name_disp, 1, 1);
		wprintw(name_disp, "<Name>");
		wrefresh(name_disp);

		wmove(money_disp, 1, 1);
		wprintw(money_disp, "Money: ");
		wrefresh(money_disp);

		wmove(life_disp, 1, 1);
		wprintw(life_disp, "Life: ");
		wrefresh(life_disp);

		wmove(time_disp, 1, 1);
		wprintw(time_disp, "Time: ");
		wrefresh(time_disp);

		wmove(waitcust_disp, 1, 1);
		wprintw(waitcust_disp, "Waiting Customer");
		wrefresh(waitcust_disp);

		wmove(map_disp, 1, 1);
		wprintw(map_disp, "");
		wrefresh(map_disp);

		wmove(food_disp, 1, 1);
		wprintw(food_disp, "Food Stack");
		wrefresh(food_disp);

		wmove(order_disp, 1, 1);
		wprintw(order_disp, "Order");
		wrefresh(order_disp);

		wmove(hand_disp, 1, 1);
		wprintw(hand_disp, "Hand");
		wrefresh(hand_disp);

		start_x = 0;
		start_y = name_height + waitcust_height + order_height;
		command_disp = newwin(command_height, command_width, start_y, start_x);
		box(command_disp,0,0);

		wmove(command_disp, 1, 1);
		wprintw(command_disp, "Command: ");
		wrefresh(command_disp);
}