#include "general.h"
#include "load_file.h"
#include "data.h"
#include "time.h"
#include "display.h"
#include <curses.h>

void InitGame()
{
    MakeEmptyTabOrder(&TabOrders);
	CreateEmptyQC(&QWaitingC);
	CreateEmptyQC(&QSeatedC);
	CreateEmptyStck(&Tray);
	Absis(GameData.PosisiPlayer)=4;
	Ordinat(GameData.PosisiPlayer)=4;

    load_resep(&Resep);
    CurrentRoom(GameData) = 4; //Dapur
    GameData.PosisiPlayer = MakePoint(4,4); //Sepakati dapur 4,4 harus kosong dan tidak menjebak
    CreateGraph(&Door);
    Waktu(GameData) = MakeJAM(0,0,0);
    Money(GameData) = 0;
    Life(GameData) = 5;

    /* Reading dari file (belum diimplementasi) */
    load_arr_ruangan(&Door, Room,4);
}

void UpdateWaitingCustomer(int * X)
{
    if (!IsEmptyQC(QWaitingC))
    {
        CleanQC(&QWaitingC,X);
    }
}

void UpdateSeatedCustomer(int * X)
{
    if (!IsEmptyQC(QSeatedC))
    {
        CleanQC(&QSeatedC,X);
    }
}

void AddCustomer()
{
    /* Random from 0 to 19 */
    unsigned int chanceInsert = rand() % 20;
    unsigned int chanceStarred =  rand() % 20;
    if (chanceInsert>=15 && !IsFullQC(QWaitingC))
    {
        if (chanceStarred>=15)
        {
            AddCustomerWC(&QWaitingC,GameData.JmlCustomer+1,12,(rand()%4)+1,true);
        }
        else
        {
            AddCustomerWC(&QWaitingC,GameData.JmlCustomer+1,20,(rand()%4)+1,false);
        }
        /* Jika berhasil insert, jml customer tambah 1 */
        GameData.JmlCustomer++;
    }
}

void UpdateGameState()
{
    UpdateWaitingCustomer(&GameData.Life);
    UpdateSeatedCustomer(&GameData.Life);
    Waktu(GameData) = NextDetik(Waktu(GameData));
    AddCustomer();
}

void Put()
{
    Stack ReverseStack;
    BinTree ScopePencarian = Resep;
    int X;

    if(IsEmptyStck(Hand))
    {
        printf("Hand kosong!\n");     
    }
    else if (IsFullStck(Tray))
    {
        printf("Tray penuh!\n");      
    }
    else //kalau hand gk kosong
    {
        /*Membuat salinan Hand*/
        CreateEmptyStck(&ReverseStack);
        do
        {
            Pop(&Hand,&X);
            Push(&ReverseStack,X);
        }
        while (!IsEmptyStck(Hand));

        // Mulai iterasi per item
        int target;
        int hasil = 0;
        boolean stillFind = true;
        do
        {
            ScopePencarian = Resep;
            do
            {
                Pop(&ReverseStack,&target); //change target
                if (target == 0) //piring
                {
                    ScopePencarian = Resep;
                    stillFind = true;
                }
                else
                {
                    if (Akar(Left(ScopePencarian)) == target) //kalau ketemu
                    {
                        ScopePencarian = Left(ScopePencarian);
                    }
                    else if (Akar(Right(ScopePencarian))==target)
                    {
                        ScopePencarian = Right(ScopePencarian);
                    }
                    else
                    {
                        stillFind = false;
                    }
                }
            } while (!IsEmptyStck(ReverseStack) && stillFind && !IsTreeOneElmt(Left(ScopePencarian)));
            if (IsTreeOneElmt(Left(ScopePencarian)))// bahannya terurut
            {
                Push(&Tray,Akar(Left(ScopePencarian)));
                hasil++;
            }
        } while (!IsEmptyStck(ReverseStack));
        if (hasil==0)
        {
            printf("Tidak ada makanan yang berhasil dibuat!");
        }
        else
        {
            printf("Ada %d makanan yang berhasil dibuat!",hasil);
        }
    }
}

/* Fungsi pendukung put dan take */
int hexToInt(char target)
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (target >= '0' && target <= '9') {
        return (int)(target-'0');
    }
    else if (target >= 'a' && target <= 'f') {
        return (int)(target - 'a') + 10;
    }
    else {
        return -1;
    }
}

/*fungsi isMeja*/
boolean isMejaBahan(Point kotak)
/* Menerima point koordinat kotak yang ingin dicek apakah meja bahan*/
{
    char x = (Room[GameData.CurrentRoom].Map.Mem[Ordinat(kotak)][Absis(kotak)]);
    return (hexToInt(x)!=-1);
}

void Take ()
{
    int dataMeja;

    /*kondisi hand penuh*/
    if (IsFullStck(Hand))
    {
        printf("Hand penuh!");      
    }
    else
    {
        if(isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)+1))) //meja di atas
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer)+1][Absis(GameData.PosisiPlayer)]));
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer)+1,Ordinat(GameData.PosisiPlayer)))) //meja di kanan
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer)][Absis(GameData.PosisiPlayer)+1]));
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)-1))) //meja di bawah
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer)-1][Absis(GameData.PosisiPlayer)]));
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer)-1,Ordinat(GameData.PosisiPlayer)))) //meja di kiri
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer)][Absis(GameData.PosisiPlayer)-1]));
            /*Memasukkan bahan ke Tray*/
            printf("%d",dataMeja);
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand!\n");
        }
        else
        {
            printf("Meja tidak ditemukan!\n");
        }
    }
}

/* Jesnat */

void FreeMeja(Meja* table)
/*I.S. Meja berisi customer
F.S. Meja kosong dari customer. Id=-1, Terisi=0, order=-1, NIsiCustomer false*/
{
    table->Id =-1;
    table->Terisi=0; /* jumlah kursi yang terisi */
    table->order=-1;
    for (int i=1; i<=4;i++)
    {
        table->NIsiCustomer[i]=false;
    }
}

int searchMejaII(Point Posisi, Meja meja,int X) //X==1 for place. X==2 for give and order
/*Lanjutan dari searchMejaII
I.S. Meja mempunyai arah atas bawah kiri kanan yang mungkin berisi kursi atau tidak
F.S. Sesuai fungsi nilai X, fungsi akan mencari Point Posisi yang sama terhadap empat arah meja tersebut*/
{
    Point Pup, Pdown, Pleft, Pright, Pnow; //P terhadap meja dan player
    if (EQPoint(Posisi,meja.Posisi))
    {
        return meja.NoMeja;
    }
    else
    {
    Pnow = meja.Posisi;
    Pup = MakePoint(Absis(Pnow),Ordinat(Pnow)+1);
    Pdown = MakePoint(Absis(Pnow),Ordinat(Pnow)-1);
    Pleft = MakePoint(Absis(Pnow)-1,Ordinat(Pnow));
    Pright = MakePoint(Absis(Pnow)+1,Ordinat(Pnow));
    if (X==1)
    {
        if (((EQPoint(Posisi,Pup)) && (meja.N[1])) || ((EQPoint(Posisi,Pright)) && (meja.N[2])) || ((EQPoint(Posisi,Pdown)) && (meja.N[3]))  || ((EQPoint(Posisi,Pleft)) && (meja.N[4])))
        {
            return meja.NoMeja;
        }
    }
    else if (X==2)
    {
        if (((EQPoint(Posisi,Pup)) && (meja.NIsiCustomer[1])) || ((EQPoint(Posisi,Pright)) && (meja.NIsiCustomer[2])) || ((EQPoint(Posisi,Pdown)) && (meja.NIsiCustomer[3]))  || ((EQPoint(Posisi,Pleft)) && (meja.NIsiCustomer[4])))
        {
            return meja.NoMeja;
        }
    }
    return Nol;
    }
}

int searchMeja(Point P1, Meja meja, int X)
/*I.S. Player memiliki 4 arah, yaitu atas bawah kiri kanan yang kemungkinan memiliki object di arah tersebut atau tidak
F.S. Mengembalikan NoMeja apabila posisi player dalam 4 arah tersebut sama dengan posisi bersangkutan dari meja. searchMeja akan menyambung ke searchMejaII*/
{
    Point P1up, P1down, P1right, P1left; //P terhadap meja dan player
    P1up = MakePoint(Absis(P1),Ordinat(P1)+1);
    P1down = MakePoint(Absis(P1),Ordinat(P1)-1);
    P1right = MakePoint(Absis(P1)+1,Ordinat(P1));
    P1left = MakePoint(Absis(P1)-1,Ordinat(P1));
    // printf("absis %f ordinat %f\n", Absis(P1left), Ordinat(P1left));
    // printf("absis meja %f ordinat %f\n", Absis(meja.Posisi), Ordinat(meja.Posisi));
    if ((searchMejaII(P1up,meja,X)!=Nol) || (searchMejaII(P1right,meja,X)!=Nol) || (searchMejaII(P1down,meja,X)!=Nol) || (searchMejaII(P1left,meja,X)!=Nol)){
        return meja.NoMeja;
    }
    else
    {
        return Nol;
    }
}

int searchTabOrders(int tableno)
/*I.S. TabOrders ialah variabel global yang berisi pesanan yang ada pada saat itu
F.S. mengembalikan urutan array keberapa dalam TabOrders yang bersangkutan dengan nomor meja di parameter*/
{
    int i=1;
    while ((TabOrders.TI[i].NoMeja!=tableno) && (i<Neff(TabOrders)))
    {
        i++;
    }
    if (TabOrders.TI[i].NoMeja==tableno)
    {
        return i;
    }else
    {
        return Nol;
    }
}

void orderFood()
/*I.S. Meja bisa saja kosong. Meja kemungkinan berisi customer yang telah memesan sebelumnya. Player berada di manapun*/
/*F.S. List Order bertambah apabila memenuhi syarat. Failed apabila player berada tidak berdampingan dari kursi meja atau meja secara langsung dan order telah dilakukan seblumnya*/
{
    time_t t;
    srand((unsigned) time(&t));
    int tableno=0;
    int i =1;
    boolean cek = false;
    int menu;
    Ruangan RNow=Room[GameData.CurrentRoom];
    Point P1 = GameData.PosisiPlayer;
    if (!IsFullTabOrder(TabOrders))
    {
        while ((i<=MAX_MEJA) && (!cek))
        {
            if ((DMeja[i].order<=8 && DMeja[i].order>=0) || DMeja[i].Terisi<=0)
            {
                i++;
            }
            else
            {
                // printf("absis %f ordinat %f\n", Absis(DMeja[i].Posisi), Ordinat(DMeja[i].Posisi));
                tableno = searchMeja(P1,DMeja[i],2);
                if (tableno!=Nol)
                {
                    cek = true;
                }
                else
                {
                    i++;
                }
            }
        }
        if (!cek)
        {
            printf("failed\n");
        }
        else
        {
            Order Temp;
            menu = (rand() % 9); //Jumlah makanan ada 0..8
            DMeja[tableno].order = menu;
            // DMeja[tableno].Pelanggan.Kesabaran = ((rand()%6)+25);/*tambah kesabaran*/
            Temp.NoMeja = tableno;
            Temp.NoMenu = menu;
            AddAsLastElTabOrder(&TabOrders,Temp);
            printf("Order berhasil ! Menu : %d dan nomor meja : %d\n", Temp.NoMenu, Temp.NoMeja);
        }
        Room[GameData.CurrentRoom] = RNow;

    }
    else
    {
        printf("Order sudah penuh, orderan tidak berhasil diambil!");
    }
}

void placeCustomer()
/*I.S. Player berada di manapun. Tabel QWaitingC mungkin kosong
F.S. apabila memenuhi, Tabel QSeatedC bertambah satu elemennya dan QWaitingC berkurang satu elemennya. Kesabaran customer bertambah secara random. Failed jika player berada jauh. Customer di meja bersangkutan belum melakukan order*/
{
    time_t t;
    srand((unsigned) time(&t));
    int tableno=0;
    int i =1;
    boolean cek = false;
    struct TypeCustomer X;
    Point P1 = GameData.PosisiPlayer;
    Ruangan RNow = Room[GameData.CurrentRoom];
    if (!IsEmptyQC(QWaitingC))
    {
        while ((!cek) && (Head(QWaitingC)<=Tail(QWaitingC)))
        {
            X=InfoHeadC(QWaitingC);
            while ((i<=MAX_MEJA) && (!cek))
            {
                if ((DMeja[i].Terisi>0) || (X.JmlOrang>DMeja[i].JmlKursi))
                {
                    i++;
                }
                else
                {
                    tableno = searchMeja(P1,DMeja[i],1);
                    if (tableno!=Nol)
                    {
                        cek = true;
                    }
                    else
                    {
                        i++;
                    }
                }
            }
            if (!cek)
            {
                Head(QWaitingC)++;
            }
        }
    }
    else
    {
        printf("Tidak ada customer yang menunggu!\n");
    }
    if (!cek)
    {
        Head(QWaitingC)=1;
        printf("Failed\n");
    }
    else
    {
        int j=1;
        i=1;
        struct TypeCustomer Temp = InfoHeadC(QWaitingC);
        DelCustomerQC (&QWaitingC, Temp.Id);
        Head(QWaitingC)=1;
        DMeja[tableno].Terisi= Temp.JmlOrang;
        DMeja[tableno].Id = Temp.Id;
        while (i<=Temp.JmlOrang)
        {
            if (DMeja[tableno].N[j])
            {
                DMeja[tableno].NIsiCustomer[j]=true;
                i++;
            }
            else
            {
                j++;
            }
        }
        Temp.NoMeja=tableno;
        Temp.Kesabaran = ((rand()%6)+25);/*tambah kesabaran*/
        AddCustomerWC (&QSeatedC, Temp.Id, Temp.Kesabaran, Temp.JmlOrang, false);
    }
    Room[GameData.CurrentRoom] = RNow;
}

void giveFood()
/*I.S.player dapat berada di manapun. Tray mungkin kosong.
F.S. Apabila memenuhi, meja yang telah menerima makanan akan mengosongkan meja dan QSeatedC berkurang satu elemennya*/
{
    time_t t;
    int max =5;
    srand((unsigned) time(&t));
    int tableno=0,i=1;
    boolean cek = false;
    Ruangan RNow=Room[GameData.CurrentRoom];
    Point P1 = GameData.PosisiPlayer;
    if (!IsEmptyStck(Tray) && Top(Tray)!=max)
    {
        while ((i<=MAX_MEJA) && (!cek))
        {
            if ((DMeja[i].Terisi<=0) || (DMeja[i].order>8) || (DMeja[i].order<0))
            {
                i++;
            }
            else
            {
                tableno = searchMeja(P1,DMeja[i],2);
                if (tableno!=Nol && DMeja[i].order==InfoTop(Tray))
                {
                    cek = true;
                }
                else
                {
                    i++;
                }
            }
        }
    }
    if(!cek)
    {
        printf("failed");
    }
    else
    {
        int Temp;
        Pop(&Tray, &Temp);
    }
    if (cek){
        int noarray = searchTabOrders(tableno);
        Order Hapus;
        DelEliTabOrder(&TabOrders,noarray,&Hapus);
        DelCustomerQC (&QSeatedC, DMeja[tableno].Id);
        FreeMeja(&DMeja[tableno]);
    }
    Room[GameData.CurrentRoom] = RNow;
}

/* Fungsi untuk GU , GD, GL, GR */
boolean IsDoor(int noRuang, Point P)
{
    adrSuccNode Pt = GetDoor(noRuang, P);
    if (Pt != NULL) {
        return true;
    }
    else {
        return false;    
    }    
}

adrSuccNode GetDoor(int noRuang, Point P) {
    adrNode Pn = SearchNode(Door, noRuang); 
    if (Pn != NULL) {
        adrSuccNode Pt = Trail(Pn);
        if (Pt != NULL) {
            while (NextG(Pt) != NULL && !EQPoint(InfoG(Pt), P)) {
                Pt = NextG(Pt);
            }

            if (EQPoint(InfoG(Pt), P)) {
                return Pt;
            }
            else {
                return NULL;
            }
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
}

void GU()
{
    if ((Ordinat(GameData.PosisiPlayer)==1 && IsDoor(GameData.CurrentRoom,GameData.PosisiPlayer)))
    {
        int sebelum = GameData.CurrentRoom;
        GameData.CurrentRoom  = Id(Succ(GetDoor(GameData.CurrentRoom,GameData.PosisiPlayer)));
        GameData.PosisiPlayer = InfoG(SearchEdge(Door,GameData.CurrentRoom,sebelum));
    }
    else if (Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer)-1][Absis(GameData.PosisiPlayer)]==' ')
    {
        Ordinat(GameData.PosisiPlayer)--;
    }
    else
    {
        printf("Tidak dapat menuju ke atas!\n");
    }
}

void GD()
{
    if ((Ordinat(GameData.PosisiPlayer)==8 && IsDoor(GameData.CurrentRoom,GameData.PosisiPlayer)))
    {
        int sebelum = GameData.CurrentRoom;
        GameData.CurrentRoom  = Id(Succ(GetDoor(GameData.CurrentRoom,GameData.PosisiPlayer)));
        GameData.PosisiPlayer = InfoG(SearchEdge(Door,GameData.CurrentRoom,sebelum));
    }
    else if (Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer)+1][Absis(GameData.PosisiPlayer)]==' ')
    {
        // printf("aaaaaa%caaaa",Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer )][Ordinat(GameData.PosisiPlayer )+1]);
        Ordinat(GameData.PosisiPlayer)++;
    }
    else
    {
        printf("Tidak dapat menuju ke bawah!\n");
    }
}

void GL()
{
    if ((Absis(GameData.PosisiPlayer)==1 && IsDoor(GameData.CurrentRoom,GameData.PosisiPlayer)))
    {
        int sebelum = GameData.CurrentRoom;
        GameData.CurrentRoom  = Id(Succ(GetDoor(GameData.CurrentRoom,GameData.PosisiPlayer)));
        GameData.PosisiPlayer = InfoG(SearchEdge(Door,GameData.CurrentRoom,sebelum));
    }
    else if (Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer)][Absis(GameData.PosisiPlayer)-1]==' ')
    {
        Absis(GameData.PosisiPlayer)--;
    }
    else
    {
        printf("Tidak dapat menuju ke kiri!\n");
    }
}

void GR()
{
    if ((Absis(GameData.PosisiPlayer)==8 && IsDoor(GameData.CurrentRoom,GameData.PosisiPlayer)))
    {
        int sebelum = GameData.CurrentRoom;
        GameData.CurrentRoom  = Id(Succ(GetDoor(GameData.CurrentRoom,GameData.PosisiPlayer)));
        GameData.PosisiPlayer = InfoG(SearchEdge(Door,GameData.CurrentRoom,sebelum));
    }
    else if (Room[GameData.CurrentRoom].Map.Mem[Ordinat(GameData.PosisiPlayer )][Absis(GameData.PosisiPlayer )+1]==' ')
    {
        Absis(GameData.PosisiPlayer)++;
    }
    else
    {
        printf("Tidak dapat menuju ke kanan!\n");
    }
}