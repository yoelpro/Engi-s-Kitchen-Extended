#include "data.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "ADT/array.c"
// #include "ADT/boolean.h"
// #include "ADT/stackt.c"
// #include "ADT/queue.c"
// #include "ADT/point.c"


#define Nol 0

/*
  INPUT RNow

  SimulationData GameData;

  TabOrder TabOrders;
  MakeEmptyTabOrder (&TOrder);

  TypeQueueCustomer QWaitingC;	// Waiting customer
  TypeQueueCustomer QSeatedC;

  Stack Tray

*/





Point Pup, Pdown, Pleft, Pright, Pnow, P1, P1up, P1down, P1right, P1left; //P terhadap meja dan player
void FreeMeja(Meja * table){
  table->Id =0;
	table->Terisi=0; /* jumlah kursi yang terisi */
  table->order=-1;
  for (int i=1; i<=4;i++){
    table->NIsiCustomer[i]=false;
  }
}

int searchMejaII(Point Posisi, Meja meja,int X) //X==1 for place. X==2 for give and order
{
  if (EQPoint(Posisi,meja.Posisi))
  {
    return meja.NoMeja;
  }else
  {
    Pnow = meja.Posisi;
    Pup = MakePoint(Absis(Pnow),Ordinat(Pnow)+1);
    Pdown = MakePoint(Absis(Pnow),Ordinat(Pnow)-1);
    Pleft = MakePoint(Absis(Pnow)-1,Ordinat(Pnow));
    Pright = MakePoint(Absis(Pnow)+1,Ordinat(Pnow));

    if (X==1){
      if (((EQPoint(Posisi,Pup)) && (meja.N[1])) || ((EQPoint(Posisi,Pright)) && (meja.N[2])) || ((EQPoint(Posisi,Pdown)) && (meja.N[3]))  || ((EQPoint(Posisi,Pleft)) && (meja.N[4])))
      {
        return meja.NoMeja;
      }
    }else if (X==2){
      if (((EQPoint(Posisi,Pup)) && (meja.NIsiCustomer[1])) || ((EQPoint(Posisi,Pright)) && (meja.NIsiCustomer[2])) || ((EQPoint(Posisi,Pdown)) && (meja.NIsiCustomer[3]))  || ((EQPoint(Posisi,Pleft)) && (meja.NIsiCustomer[4])))
      {
        return meja.NoMeja;
      }
    }

    return Nol;
  }
}

int searchMeja(Point P1, Meja meja, int X)
{
  P1up = MakePoint(Absis(P1),Ordinat(P1)+1);
  P1down = MakePoint(Absis(P1),Ordinat(P1)-1);
  P1right = MakePoint(Absis(P1)+1,Ordinat(P1));
  P1left = MakePoint(Absis(P1)-1,Ordinat(P1));
  // printf("absis %f ordinat %f\n", Absis(P1left), Ordinat(P1left));
  // printf("absis meja %f ordinat %f\n", Absis(meja.Posisi), Ordinat(meja.Posisi));
  if ((searchMejaII(P1up,meja,X)!=Nol) || (searchMejaII(P1right,meja,X)!=Nol) || (searchMejaII(P1down,meja,X)!=Nol) || (searchMejaII(P1left,meja,X)!=Nol)){
    return meja.NoMeja;
  }else{
    return Nol;
  }
}

int searchTabOrders(int tableno)
{
  int i=1;
  while ((TabOrders.TI[i].NoMeja!=tableno) && (i<Neff(TabOrders))){
    i++;
  }
  if (TabOrders.TI[i].NoMeja==tableno){
    return i;
  }else{
    return Nol;
  }
}


void orderFood()
{
  time_t t;
  srand((unsigned) time(&t));

  int tableno=0;
  int i =1;
  boolean cek = false;
  int menu;

  Ruangan RNow=RSkrg;
  // printf("jml meja %d\n",RSkrg.JmlMeja);
  Point P1 = GameData.PosisiPlayer;

  while ((i<=RNow.JmlMeja) && (!cek))
  {
    if ((RNow.DMeja[i].order<=8 && RNow.DMeja[i].order>=0) || RNow.DMeja[i].Terisi<=0){
      i++;
    }else{
      // printf("absis %f ordinat %f\n", Absis(RNow.DMeja[i].Posisi), Ordinat(RNow.DMeja[i].Posisi));
      tableno = searchMeja(P1,RNow.DMeja[i],2);
      if (tableno!=Nol)
      {
        cek = true;
      }else
      {
        i++;
      }
    }
  }

  if (!cek){
    printf("failed\n");
  }else{
    Order Temp;

    menu = (rand() % 9); //Jumlah makanan ada 0..8
    RNow.DMeja[tableno].order = menu;
    // Rnow.Dmeja[tableno].Pelanggan.Kesabaran = ((rand()%6)+25);/*tambah kesabaran*/
    Temp.NoMeja = tableno;
    Temp.NoMenu = menu;
    AddAsLastElTabOrder(&TabOrders,Temp);
  }

}

void placeCustomer(){
  time_t t;
  srand((unsigned) time(&t));

  int tableno=0;
  int i =1;
  boolean cek = false;
  struct TypeCustomer X;

  Point P1 = GameData.PosisiPlayer;
  Ruangan RNow = RSkrg;

  if (!IsEmptyQC(QWaitingC))
  {
    while ((!cek) && (Head(QWaitingC)<=Tail(QWaitingC)))
    {
      X=InfoHeadC(QWaitingC);
      while ((i<=RNow.JmlMeja) && (!cek))
      {
        if ((RNow.DMeja[i].Terisi>0) || (X.JmlOrang>RNow.DMeja[i].JmlKursi)){
          i++;
        }else{
          tableno = searchMeja(P1,RNow.DMeja[i],1);
          if (tableno!=Nol)
          {
            cek = true;
          }else
          {
            i++;
          }
        }
      }
      if (!cek){
        Head(QWaitingC)++;
      }
    }
  }


  if (!cek){
    Head(QWaitingC)=1;
    printf("Failed\n");
  }else{
    int j=1;
    i=1;
    struct TypeCustomer Temp = InfoHeadC(QWaitingC);
    DelCustomerQC (&QWaitingC, Temp.Id);
    Head(QWaitingC)=1;

    RNow.DMeja[tableno].Terisi= Temp.JmlOrang;
    RNow.DMeja[tableno].Id = Temp.Id;
    while (i<=Temp.JmlOrang){
      if (RNow.DMeja[tableno].N[j]){
        RNow.DMeja[tableno].NIsiCustomer[j]=true;
        i++;
      }else{
        j++;
      }
    }

    Temp.NoMeja=tableno;
    Temp.Kesabaran = ((rand()%6)+25);/*tambah kesabaran*/
    AddCustomerWC (&QSeatedC, Temp.Id, Temp.Kesabaran, Temp.JmlOrang, false);
  }
}

void giveFood()
{
  time_t t;
  int max =5;
  srand((unsigned) time(&t));

  int tableno=0,i =1,j=1;
  boolean cek = false;

  Ruangan RNow=RSkrg;
  Point P1 = GameData.PosisiPlayer;

  if (!IsEmptyStck(Tray) && Top(Tray)!=max)
  {
    while ((i<=RNow.JmlMeja) && (!cek))
    {
      if ((RNow.DMeja[i].Terisi<=0) || (RNow.DMeja[i].order>8) || (RNow.DMeja[i].order<0)){
        i++;
      }else{
        tableno = searchMeja(P1,RNow.DMeja[i],2);
        if (tableno!=Nol && RNow.DMeja[i].order==InfoTop(Tray))
        {
          cek = true;
        }else
        {
          i++;
        }
      }
    }
  }

  if(!cek){
    printf("failed");
  }else{
    int Temp;
    Pop(&Tray, &Temp);
  }
  if (cek){
    int noarray = searchTabOrders(tableno);
    Order Hapus;
    DelEliTabOrder(&TabOrders,noarray,&Hapus);

    DelCustomerQC (&QSeatedC, RNow.DMeja[tableno].Id);

    FreeMeja(&RNow.DMeja[tableno]);
  }

}

int testmain(){
  RSkrg.JmlMeja=2;
  RSkrg.Tipe=0;

  for (int i=1;i<=2;i++){
    FreeMeja(&RSkrg.DMeja[i]);
    RSkrg.DMeja[i].NoMeja=i+2;
  }
  Absis(RSkrg.DMeja[1].Posisi)=2;
  Ordinat(RSkrg.DMeja[1].Posisi)=4;
  RSkrg.DMeja[1].JmlKursi=2;
  RSkrg.DMeja[1].N[1]=true;
  RSkrg.DMeja[1].N[2]=true;
  RSkrg.DMeja[1].N[3]=false;
  RSkrg.DMeja[1].N[4]=false;


  Absis(RSkrg.DMeja[2].Posisi)=2;
  Ordinat(RSkrg.DMeja[2].Posisi)=10;
  RSkrg.DMeja[2].JmlKursi=4;
  RSkrg.DMeja[2].N[1]=true;
  RSkrg.DMeja[2].N[2]=true;
  RSkrg.DMeja[2].N[3]=true;
  RSkrg.DMeja[2].N[4]=true;

  RSkrg.DMeja[2].Terisi =2;
  RSkrg.DMeja[2].NIsiCustomer[1]=true;
  RSkrg.DMeja[2].NIsiCustomer[2]=true;


  MakeEmptyTabOrder(&TabOrders);
  CreateEmptyQC(&QWaitingC);
  CreateEmptyQC(&QSeatedC);
  CreateEmptyStck(&Tray);
  Absis(GameData.PosisiPlayer)=4;
  Ordinat(GameData.PosisiPlayer)=10;
  printf("absis %f ordinat %f", GameData.PosisiPlayer.X, Ordinat(GameData.PosisiPlayer));


  int cmd;
  printf("input 1/2/3: ");
  scanf("%d", &cmd);

  if (cmd==1){
    orderFood();
  }else if(cmd==2){
    placeCustomer();
  }else if(cmd==3){
    giveFood();
  }
  return 0;

}
