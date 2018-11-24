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
/* Contoh: menulis Current dengan isi 0 1 3 7
+---------------+
|Hand			|
|0				|
|1				|
|3				|
|7				|
|				|
+---------------+
*/
/* BUG: UNTUK ISI STACK YANG MELEBIHI UKURAN WINDOW TIDAK AKAN TAMPIL DI WINDOW */

void updateLayout();
/* Meng-update isi game sesuai kondisi game */

void GetCommand();
/* Menerima command dari user */
/* Sebenarnya BacaCommand() untuk curses, cuman blom dicoba begini bs atau ngak */

void CursorOnCommand();

void endLayout();
/* Menghentikan tampilan */

#endif