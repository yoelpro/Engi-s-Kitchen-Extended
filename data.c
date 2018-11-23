#include "data.h"

/* Definition of global variable */

const char * JenisBahan[MAX_BAHAN] =
{
	"Piring",		//0
	"Sendok",		//1
	"Garpu",		//2
	"EsKrim",		//3
	"Nasi",			//4
	"Roti",			//5
	"Spaghetti",	//6
	"Pisang",		//7
	"Stroberi",		//8
	"Telur",		//9
	"AyamGoreng",	//10
	"Patty",		//11
	"Sosis",		//12
	"Bolognese",	//13
	"Carbonara",	//14
	"Keju"			//15
};

const char * JenisMakanan[MAX_MAKANAN] =
{
	"BananaSplit",			//0
	"Sundae",				//1
	"NasiTelurDadar",		//2
	"NasiAyamGoreng",		//3
	"Burger",				//4
	"HotDog",				//5
	"Keju",					//6
	"SpaghettiCarbonara",	//7
	"SpaghettiBolognese"	//8
};

SimulationData GameData;
Stack Hand;
Stack Tray;
TypeQueueCustomer QWaitingC;	// Waiting customer
TypeQueueCustomer QSeatedC;
TabOrder TabOrders;
Ruangan Room [4+1];
BinTree Resep;