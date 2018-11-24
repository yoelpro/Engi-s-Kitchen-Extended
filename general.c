#include "general.h"
#include "load_file.h"
#include "data.h"
#include "time.h"
#include <curses.h>

void InitGame()
{
    load_resep(&Resep);
    CurrentRoom(GameData) = 4; //Dapur
    GameData.PosisiPlayer = MakePoint(4,4); //Sepakati dapur 4,4 harus kosong dan tidak menjebak
    CreateEmptyStck(&GameData.Hand);
    CreateEmptyStck(&GameData.Tray);
    Waktu(GameData) = 0;
    Money(GameData) = 0;
    Life(GameData) = 5;

    /* Reading dari file (belum diimplementasi) */
    load_arr_ruangan(Room,1);
}

void UpdateWaitingCustomer()
{
    if (!IsEmptyQC(QWaitingC))
    {
        CleanQC(&QWaitingC);
    }
}

void UpdateSeatedCustomer()
{
    if (!IsEmptyQC(QSeatedC))
    {
        CleanQC(&QSeatedC);
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
    UpdateWaitingCustomer();
    UpdateSeatedCustomer();
    Waktu(GameData)++;
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
            printf("%c ",X);
            printf("\n");
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
                Push(&Tray,Akar(ScopePencarian));
                hasil++;
            }
        } while (!IsEmptyStck(ReverseStack));
        if (hasil==0)
        {
            printf("Tidak ada makanan yang berhasil dibuat!\n");
        }
        else
        {
            printf("Ada %d makanan yang berhasil dibuat!\n",hasil);
        }
    }
}

/* Fungsi pendukung put dan take */
int hexToInt(char target)
{
    if (target >= '0' && target <= '9')
        return target - '0';
    if (target >= 'a' && target <= 'f')
        return target - 'a' + 10;
    return -1;
}

/*fungsi isMeja*/
boolean isMejaBahan(Point kotak)
/* Menerima point koordinat kotak yang ingin dicek apakah meja bahan*/
{
    char x = (Room[GameData.CurrentRoom].Map.Mem[Absis(kotak)][Ordinat(kotak)]);
    return (x != 'T' && x != ' ');
}

void Take ()
{
    Stack Hand;
    int dataMeja;

    /*kondisi hand penuh*/
    if (IsFullStck(Hand))
    {
        printf("Hand penuh!\n");
    }
    else
    {
        if(isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)+1))) //meja di atas
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)][Ordinat(GameData.PosisiPlayer)+1]));
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer)+1,Ordinat(GameData.PosisiPlayer)))) //meja di kanan
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)+1][Ordinat(GameData.PosisiPlayer)]));
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer),Ordinat(GameData.PosisiPlayer)-1))) //meja di bawah
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)][Ordinat(GameData.PosisiPlayer)+1]));
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
        }
        else if (isMejaBahan(MakePoint(Absis(GameData.PosisiPlayer)-1,Ordinat(GameData.PosisiPlayer)))) //meja di kiri
        {
            dataMeja = hexToInt((Room[GameData.CurrentRoom].Map.Mem[Absis(GameData.PosisiPlayer)+1][Ordinat(GameData.PosisiPlayer)]));
            /*Memasukkan bahan ke Tray*/
            Push(&Hand,dataMeja);
            printf("Bahan berhasil ditambahkan ke hand.\n");
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
        while ((i<=RNow.JmlMeja) && (!cek))
        {
            if ((RNow.DMeja[i].order<=8 && RNow.DMeja[i].order>=0) || RNow.DMeja[i].Terisi<=0)
            {
                i++;
            }
            else
            {
                // printf("absis %f ordinat %f\n", Absis(RNow.DMeja[i].Posisi), Ordinat(RNow.DMeja[i].Posisi));
                tableno = searchMeja(P1,RNow.DMeja[i],2);
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
            RNow.DMeja[tableno].order = menu;
            // Rnow.Dmeja[tableno].Pelanggan.Kesabaran = ((rand()%6)+25);/*tambah kesabaran*/
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
            while ((i<=RNow.JmlMeja) && (!cek))
            {
                if ((RNow.DMeja[i].Terisi>0) || (X.JmlOrang>RNow.DMeja[i].JmlKursi))
                {
                    i++;
                }
                else
                {
                    tableno = searchMeja(P1,RNow.DMeja[i],1);
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
        RNow.DMeja[tableno].Terisi= Temp.JmlOrang;
        RNow.DMeja[tableno].Id = Temp.Id;
        while (i<=Temp.JmlOrang)
        {
            if (RNow.DMeja[tableno].N[j])
            {
                RNow.DMeja[tableno].NIsiCustomer[j]=true;
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
        while ((i<=RNow.JmlMeja) && (!cek))
        {
            if ((RNow.DMeja[i].Terisi<=0) || (RNow.DMeja[i].order>8) || (RNow.DMeja[i].order<0))
            {
                i++;
            }
            else
            {
                tableno = searchMeja(P1,RNow.DMeja[i],2);
                if (tableno!=Nol && RNow.DMeja[i].order==InfoTop(Tray))
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
        DelCustomerQC (&QSeatedC, RNow.DMeja[tableno].Id);
        FreeMeja(&RNow.DMeja[tableno]);
    }
    Room[GameData.CurrentRoom] = RNow;
}

/* Kelompok Tampilan */
/* Kamus Tampilan*/
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

void initLayout(){
    /* CURSES START */
    initscr();
    setLayout();
    refresh();
    printLayout();
    updateLayout();

    mvwgetstr(command_disp, 1, 10, user_input);
    updateLayout();
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
        wprintw(money_disp, "%ld", Money(GameData));
        wrefresh(money_disp);

        wmove(life_disp, 1, 1);
        wprintw(life_disp, "%ld", Life(GameData));
        wrefresh(life_disp);

        wmove(time_disp, 1, 1);
        wprintw(time_disp, "%ld", Waktu(GameData));
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

void endLayout(){
    endwin();
    /* Terminate curses */
}