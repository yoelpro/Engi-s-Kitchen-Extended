/*  File : display.h
    berisi fungsi dan prosedur yang dibutuhkan program untuk display
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "data.h"
#include <curses.h>

/* Perintah curses yang bisa digunakan:
	void move(int y,x) : (x,y) adalah koordinat di tampilan
	void printw(...) : penggunaan seperti printf
	WINDOW newwin(int height,width,y,x) : height dan width adalah ukuran window baru, (x,y) adalah koordinat di mana window baru akan dibuat
	void box(WINDOW &disp, int topbottom_border, leftright_border) : disp adalah window yang sudah diinisialisasi, topbottom_border dan leftright_border adalah
			kode ascii karakter yang ingin ditampilkan
	void refresh() : mengupdate display curses (dalam curses, update tidak terjadi setiap ada perubahan)

	tambah prefix 'w' untuk menggunakan fungsi relatif terhadap window, parameter fungsi pertama menjadi WINDOW
	Contoh: wmove(disp,y,x)

	tambah prefix 'mv' untuk menggunakan fungsi dengan tambahan parameter posisi dilakukannya aksi
	Contoh: mvprintw(y,x,...)
*/

/* Kelompok tampilan */

void initLayout();
/* Mulai menampilkan tampilan */

void setLayout();
/* Mengatur setting layout game */

void printLayout();
/* Mencetak layout sesuai setting yang ada */

void CurseTulisMatriks (Matriks M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

void CursePrintStack(WINDOW *win, Stack *Current, char opt);
/* I.S. win dan Current terdefinisi */
/* F.S. Nilai Current ditulis ke dalam win per baris, masing-masing elemen dipisah sebuah newline */
/* Proses: Menyalin semua elemen Current ke dalam ReverseStack, kemudian menulis nilai setiap elemen ReverseStack ke dalam win dengan
		loop hingga isi ReverseStack kosong */
/* Contoh: menulis Current dengan isi 0 1 3 7 8 10
+---------------+
|Hand			|
|0				|
|1				|
|3				|
|7				|
|8				|
+etc...---------+
*/
/* BUG: UNTUK ISI STACK YANG MELEBIHI UKURAN WINDOW TIDAK AKAN TAMPIL DI WINDOW */

void updateLayout();
/* Meng-update isi game sesuai kondisi game:
	1. Money
	2. Life
	3. Waktu
	4. Waiting Customer (pending)
	5. Map
	6. Food Stack
	7. Order (pending)
	8. Hand Stack
	9. Command 
*/

void GetCommand();
/* Menerima command dari user */
/* BUG: KARAKTER PERTAMA DARI INPUT TIDAK DITAMPILKAN, BACKSPACE DIANGGAP KARAKTER, SEHINGGA TIDAK BISA MENGUBAH INPUT */

void CursorOnCommand();
/* Memindahkan cursor input di window command */

void endLayout();
/* Menghentikan tampilan dan curses */

void CurseADVCommand();
/*Pita dimajukan satu karakter. 
  I.S. : Karakter pada jendela = 
          CCommand, CCommand != MARK
  F.S. : CCommand adalah karakter berikutnya dari CCommand yang lama, 
          CCommand mungkin = MARK.
  Jika CCommand = MARK maka EOP akan menyala (true) */

void CurseBacaCommand();
/* I.S. : CCommand sembarang 
   F.S. : EndKata = true, dan CCommand = MARK; 
          atau EndKata = false, Command adalah kata yang sudah diakuisisi,
          CCommand karakter pertama sesudah karakter terakhir kata */

void CurseSalinCommand();
/* Mengakuisisi command dari console, menyimpan dalam CCommand
   I.S. : CCommand adalah karakter pertama dari kata
   F.S. : CCommand berisi kata yang sudah diakuisisi; 
          CCommand = \n */

#endif