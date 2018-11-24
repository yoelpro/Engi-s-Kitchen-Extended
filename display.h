/*  File : display.h
    berisi fungsi dan prosedur yang dibutuhkan program untuk display
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "data.h"

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

void CurseTulisMatriks (Matriks M, int y, int x);

void updateLayout();
/* Meng-update isi game sesuai kondisi game */

void GetCommand();
/* Menerima command dari user */
/* Sebenarnya BacaCommand() untuk curses, cuman blom dicoba begini bs atau ngak */

void CursorCommand();

void endLayout();
/* Menghentikan tampilan */

#endif