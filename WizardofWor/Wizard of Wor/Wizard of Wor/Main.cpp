#include<windows.h>
#include"icb_gui.h"
#include"ic_image.h"
#include<random>


int FRM1, BTN;
HANDLE hTimerQueue = NULL;
HANDLE hTimer = NULL;

ICBYTES m, loading, rules, congr;//loading rules ve tebrik resimleri
ICBYTES map, gameoverscreen, loadingscreen, enemyright1, enemyup1, enemydown1, enemyleft1, enemyright11, enemyup11, enemydown11, enemyleft11, enemyright111, enemyup111, enemydown111, enemyleft111, enemyright2, enemyup2, enemydown2, enemyleft2, enemyright22, enemyup22, enemydown22, enemyleft22, enemyright222, enemyup222, enemydown222, enemyleft222, playerleft, playerright, playerup, playerdown, deadanim1, deadanim2;//player ve enemy bmplerinin variablelarý
int keypressed, lastKeyp;//basýlan tuþ ve basýlan son tuþ
int px = 307, py = 207;//player x y
int nextStep;//oyuncunun bir sonraki adýmýnýn bulunduðu pikselin rengi
const int SHOOT_COOLDOWN = 500;//shoot fonksiyonunun tekrar aktif olmasý için bekleme süresi
std::random_device rd;
std::uniform_int_distribution<int> randir(1, 4);
int nextp1, nextp2, nextp3, nextp4;//isdead fonksiyonunun bir sonraki piksele bakan deðeri
int count2 = 0, count1 = 0; //count 1 spawn olan enemy sayýsý count 2 ölen enemy sayýsý
int phealth = 3;//player ýn toplam caný
bool pisdead = false;//player öldü mü booleaný
int gameon = 1; // oyunun devam edip etmediðini belli eden variable

void ICGUI_Create()
{
    ICG_MWSize(800, 500);
    ICG_MWTitle("Wizard Of Wor");
    ICG_MWColor(0, 0, 0);
}

void enemyDeadAnim(int x, int y) { // enemy ölüm animasyonu
    PasteNon0(deadanim1, x, y, m);
    Sleep(150);
    DisplayImage(FRM1, m);
    PasteNon0(deadanim2, x, y, m);
    Sleep(150);
    DisplayImage(FRM1, m);

}

bool isAlive(int x, int y) { //enemy nin yaþayýp yaþamadýðýný kontrol eden fonksiyon
    for (int i = 0; i < 36; i++) {

        nextp1 = m.U(x + i, y - 6);
        nextp2 = m.U(x + 41, y + i);
        nextp3 = m.U(x + i, y + 41);
        nextp4 = m.U(x - 6, y + i);

        if (nextp1 == 0x00ff00 || nextp2 == 0x00ff00 || nextp3 == 0x00ff00 || nextp4 == 0x00ff00) return false;
    }
    return true;
}

bool canMove(int x, int y, int b) { //1 sola 2 saða 3 yukarý 4 aþaðý

    if (b == 1) {
        if ((py <= y && py + 35 >= y) || (y <= py && y + 35 >= py)) {
            if (x == px + 35 || x == px + 36 || x == px + 37 || x == px + 38) pisdead = true;
        }
        for (int i = 0; i < 36; i++) {
            nextStep = m.U(x - 3, y + i);
            if (nextStep != 0) {
                return false;
            }
        }
        return true;
    }
    if (b == 2) {
        if ((py <= y && py + 35 >= y) || (y <= py && y + 35 >= py)) {
            if (x + 35 == px || x + 36 == px || x + 37 == px || x + 38 == px) pisdead = true;
        }
        for (int i = 0; i < 36; i++) {
            nextStep = m.U(x + 38, y + i);

            if (nextStep != 0) {
                return false;
            }
        }
        return true;
    }
    if (b == 3) {
        if ((px <= x && px + 35 >= x) || (x <= px && x + 35 >= px)) {
            if (y == py + 35 || y == py + 36 || y == py + 37 || y == py + 38) pisdead = true;
        }
        for (int i = 0; i < 36; i++) {
            nextStep = m.U(x + i, y - 3);

            if (nextStep != 0) {
                return false;
            }
        }
        return true;
    }
    else {
        if ((px <= x && px + 35 >= x) || (x <= px && x + 35 >= px)) {
            if (y + 35 == py || y + 36 == py || y + 37 == py || y + 38 == py) pisdead = true;
        }
        for (int i = 0; i < 36; i++) {
            nextStep = m.U(x + i, y + 38);

            if (nextStep != 0) {
                return false;
            }
        }
        return true;
    }
}

void Shoot(int sx, int sy, int pe, int a) {//sx =shooter x , sy =shooter y, pe = player or enemy , a = direction

    static DWORD lastShotTime = 0; // Track the time of the last shot

    //Check if enough time has passed since the last shot
    if (GetTickCount() - lastShotTime < SHOOT_COOLDOWN) {
        // Cooldown time has not elapsed, cannot shoot yet
        return;
    }

    int bulx = sx + 17, buly = sy + 17;//mermi x y
    if (a == 37) {
        bulx = sx;
        while (m.U(bulx - 1, buly) == 0 && m.U(bulx - 2, buly) == 0 && m.U(bulx - 3, buly) == 0) {
            FillRect(m, bulx, buly, 10, 2, 0x000000);
            bulx -= 3;
            FillRect(m, bulx, buly, 10, 2, 0x00ff00);
            Sleep(1);
            DisplayImage(FRM1, m);
        }
        FillRect(m, bulx, buly, 10, 2, 0x000000);
    }
    if (a == 39) {
        bulx = sx + 25;
        while (m.U(bulx + 11, buly) == 0 && m.U(bulx + 12, buly) == 0 && m.U(bulx + 13, buly) == 0) {
            FillRect(m, bulx, buly, 10, 2, 0x000000);
            bulx += 3;
            FillRect(m, bulx, buly, 10, 2, 0x00ff00);
            Sleep(1);
            DisplayImage(FRM1, m);
        }
        FillRect(m, bulx, buly, 10, 2, 0x000000);

    }
    if (a == 38) {
        buly = sy;
        while (m.U(bulx, buly - 1) == 0 && m.U(bulx, buly - 2) == 0 && m.U(bulx, buly - 3) == 0) {
            FillRect(m, bulx, buly, 2, 10, 0x000000);
            buly -= 3;
            FillRect(m, bulx, buly, 2, 10, 0x00ff00);
            Sleep(1);
            DisplayImage(FRM1, m);
        }
        FillRect(m, bulx, buly, 2, 10, 0x000000);
    }
    if (a == 40) {
        buly = sy + 25;
        while (m.U(bulx, buly + 11) == 0 && m.U(bulx, buly + 12) == 0 && m.U(bulx, buly + 13) == 0) {
            FillRect(m, bulx, buly, 2, 10, 0x000000);
            buly += 3;
            FillRect(m, bulx, buly, 2, 10, 0x00ff00);
            Sleep(1);
            DisplayImage(FRM1, m);
        }
        FillRect(m, bulx, buly, 2, 10, 0x000000);
    }
    lastShotTime = GetTickCount();
}

void SpawnEnemy1() {// enemy çaðýran fonksiyon
    count1++;
    int count1kalan = count1 % 4;
    int enemyx = 53, enemyy = 7, dir;//x y direction
    if (count1kalan % 4 == 1) {
        enemyx = 53;
        enemyy = 7;
    }
    if (count1kalan % 4 == 2) {
        enemyx = 543;
        enemyy = 7;
    }
    if (count1kalan % 4 == 3) {
        enemyx = 605;
        enemyy = 110;
    }
    if (count1kalan % 4 == 0) {
        enemyx = 7;
        enemyy = 110;
    }
    dir = 2;
   // bool alive = true;

    if (count2 == 14) { //14 tane 1 level ve 2 level enemy kesince çaðýrýlýcak olan son boss
        enemyx = 307;
        enemyy = 57;
        while (isAlive(enemyx, enemyy)) {
            if (gameon == 0) {
                enemyleft222 = 0;
                enemyleft111 = 0;
                enemyright111 = 0;
                enemyright222 = 0;
                enemyup222 = 0;
                enemyup111 = 0;
                enemydown222 = 0;
                enemydown111 = 0;

            }
           // alive = isAlive(enemyx, enemyy);

            if (canMove(enemyx, enemyy, dir)) {
                if (dir == 1)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyx -= 3;
                    if ((enemyx / 20) % 2 == 0) PasteNon0(enemyleft111, enemyx, enemyy, m);
                    else PasteNon0(enemyleft222, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(1);
                }
                if (dir == 2)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyx += 3;
                    if ((enemyx / 20) % 2 == 0) PasteNon0(enemyright111, enemyx, enemyy, m);
                    else PasteNon0(enemyright222, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(1);
                }
                if (dir == 3)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyy -= 3;
                    if ((enemyy / 20) % 2 == 0) PasteNon0(enemyup111, enemyx, enemyy, m);
                    else PasteNon0(enemyup222, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(1);
                }
                if (dir == 4)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyy += 3;
                    if ((enemyy / 20) % 2 == 0) PasteNon0(enemydown111, enemyx, enemyy, m);
                    else PasteNon0(enemydown222, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(1);
                }

            }
            else dir = randir(rd);

        }
        enemyDeadAnim(enemyx, enemyy);
        enemyDeadAnim(enemyx, enemyy);
        FillRect(m, enemyx, enemyy, 35, 35, 0x000000);

        count2++;
        m = 0;
        PasteNon0(congr, 1, 1, m);
        DisplayImage(FRM1, m);

    }

    if (count1 > 8 && count1 < 15) { // 2 level enemy çaðýrma 

        while (isAlive(enemyx, enemyy)) {
            if (gameon == 0) {
                enemyleft22 = 0;
                enemyleft11 = 0;
                enemyright11 = 0;
                enemyright22 = 0;
                enemyup22 = 0;
                enemyup11 = 0;
                enemydown22 = 0;
                enemydown11 = 0;
            }
           // alive = isAlive(enemyx, enemyy);
            if (canMove(enemyx, enemyy, dir)) {
                if (dir == 1)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyx -= 4;
                    if ((enemyx / 15) % 2 == 0) PasteNon0(enemyleft11, enemyx, enemyy, m);
                    else PasteNon0(enemyleft22, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }
                if (dir == 2)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyx += 4;
                    if ((enemyx / 15) % 2 == 0) PasteNon0(enemyright11, enemyx, enemyy, m);
                    else PasteNon0(enemyright22, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }
                if (dir == 3)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyy -= 4;
                    if ((enemyy / 15) % 2 == 0) PasteNon0(enemyup11, enemyx, enemyy, m);
                    else PasteNon0(enemyup22, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }
                if (dir == 4)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyy += 4;
                    if ((enemyy / 15) % 2 == 0) PasteNon0(enemydown11, enemyx, enemyy, m);
                    else PasteNon0(enemydown22, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }

            }
            else dir = randir(rd);

        }
        enemyDeadAnim(enemyx, enemyy);
        enemyDeadAnim(enemyx, enemyy);
        FillRect(m, enemyx, enemyy, 35, 35, 0x000000);

        count2++;

        DisplayImage(FRM1, m);
        Sleep(20);

        SpawnEnemy1();

    }

    if (count1 < 9) { // 1 level enemy çaðýrma
        while (isAlive(enemyx, enemyy)) {
            if (gameon == 0) {
                enemyleft2 = 0;
                enemyleft1 = 0;
                enemyright1 = 0;
                enemyright2 = 0;
                enemyup2 = 0;
                enemyup1 = 0;
                enemydown2 = 0;
                enemydown1 = 0;
            }
            //alive = isAlive(enemyx, enemyy);
            if (canMove(enemyx, enemyy, dir)) {
                if (dir == 1)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyx -= 2;
                    if ((enemyx / 10) % 2 == 0) PasteNon0(enemyleft1, enemyx, enemyy, m);
                    else PasteNon0(enemyleft2, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }
                if (dir == 2)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyx += 2;
                    if ((enemyx / 10) % 2 == 0) PasteNon0(enemyright1, enemyx, enemyy, m);
                    else PasteNon0(enemyright2, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }
                if (dir == 3)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyy -= 2;
                    if ((enemyy / 10) % 2 == 0) PasteNon0(enemyup1, enemyx, enemyy, m);
                    else PasteNon0(enemyup2, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }
                if (dir == 4)
                {
                    FillRect(m, enemyx, enemyy, 35, 35, 0x000000);
                    enemyy += 2;
                    if ((enemyy / 10) % 2 == 0) PasteNon0(enemydown1, enemyx, enemyy, m);
                    else PasteNon0(enemydown2, enemyx, enemyy, m);
                    DisplayImage(FRM1, m);
                    Sleep(20);
                }

            }
            else dir = randir(rd);

        }
        enemyDeadAnim(enemyx, enemyy);
        enemyDeadAnim(enemyx, enemyy);
        FillRect(m, enemyx, enemyy, 35, 35, 0x000000);

        count2++;

        DisplayImage(FRM1, m);
        Sleep(20);

        SpawnEnemy1();
    }

}

// Thread called by the timer
VOID CALLBACK PlayerMove(PVOID lpParam, BOOLEAN TimerOrWaitFired) //player hareket fonksiyonu
{

    if (keypressed == 37) {
        lastKeyp = keypressed;


        if (canMove(px, py, 1)) {
            FillRect(m, px, py, 35, 35, 0x000000);
            keypressed = NULL;
            px -= 3;
            PasteNon0(playerleft, px, py, m);
            DisplayImage(FRM1, m);
        }
    }
    if (keypressed == 39) {
        lastKeyp = keypressed;


        if (canMove(px, py, 2)) {
            FillRect(m, px, py, 35, 35, 0x000000);
            keypressed = NULL;
            px += 3;
            PasteNon0(playerright, px, py, m);
            DisplayImage(FRM1, m);
        }
    }
    if (keypressed == 38) {
        lastKeyp = keypressed;


        if (canMove(px, py, 3)) {
            FillRect(m, px, py, 35, 35, 0x000000);
            keypressed = NULL;
            py -= 3;
            PasteNon0(playerup, px, py, m);
            DisplayImage(FRM1, m);
        }
    }//up
    if (keypressed == 40) {
        lastKeyp = keypressed;

        if (canMove(px, py, 4)) {
            FillRect(m, px, py, 35, 35, 0x000000);
            keypressed = NULL;
            py += 3;
            PasteNon0(playerdown, px, py, m);
            DisplayImage(FRM1, m);
        }

    }//down+
    if (keypressed == 32) {

        keypressed = NULL;
        Shoot(px, py, 1, lastKeyp);
    }


    DisplayImage(FRM1, m);
    Sleep(10);
    if (pisdead) {// playerýn ölüp ölmediðini kontrol etme
        FillRect(m, px, py, 35, 35, 0x00000);
        px = 307;
        py = 207;
        phealth -= 1;
        PasteNon0(playerleft, px, py, m);
        DisplayImage(FRM1, m);
        pisdead = false;
        if (phealth == 2) FillRect(m, 257, 357, 35, 35, 0x00000);
        if (phealth == 1) FillRect(m, 307, 357, 35, 35, 0x00000);
        if (phealth == 0) FillRect(m, 357, 357, 35, 35, 0x00000);

    }
    if (phealth < 0) {

        gameon = 0;
        DeleteTimerQueueEx(hTimerQueue, NULL);
        m = 0;
        PasteNon0(gameoverscreen, 1, 1, m);
        DisplayImage(FRM1, m);

    }
}

void WhenKeyPressed(int k)
{
    keypressed = k;

}

void Play()
{
    DWORD dw;
    ReadImage("Enemyright1.bmp", enemyright1);
    ReadImage("Enemyright11.bmp", enemyright11);
    ReadImage("Enemyright111.bmp", enemyright111);
    ReadImage("Enemyleft1.bmp", enemyleft1);
    ReadImage("Enemyleft11.bmp", enemyleft11);
    ReadImage("Enemyleft111.bmp", enemyleft111);
    ReadImage("Enemyup1.bmp", enemyup1);
    ReadImage("Enemyup11.bmp", enemyup11);
    ReadImage("Enemyup111.bmp", enemyup111);
    ReadImage("Enemydown1.bmp", enemydown1);
    ReadImage("Enemydown11.bmp", enemydown11);
    ReadImage("Enemydown111.bmp", enemydown111);
    ReadImage("Enemyright2.bmp", enemyright2);
    ReadImage("Enemyright22.bmp", enemyright22);
    ReadImage("Enemyright222.bmp", enemyright222);
    ReadImage("Enemyleft2.bmp", enemyleft2);
    ReadImage("Enemyleft22.bmp", enemyleft22);
    ReadImage("Enemyleft222.bmp", enemyleft222);
    ReadImage("Enemyup2.bmp", enemyup2);
    ReadImage("Enemyup22.bmp", enemyup22);
    ReadImage("Enemyup222.bmp", enemyup222);
    ReadImage("Enemydown2.bmp", enemydown2);
    ReadImage("Enemydown22.bmp", enemydown22);
    ReadImage("Enemydown222.bmp", enemydown222);
    ReadImage("playerright.bmp", playerright);
    ReadImage("playerleft.bmp", playerleft);
    ReadImage("playerup.bmp", playerup);
    ReadImage("playerdown.bmp", playerdown);
    ReadImage("deadanim1.bmp", deadanim1);
    ReadImage("deadanim2.bmp", deadanim2);
    ReadImage("rules.bmp", rules);
    ReadImage("congr.bmp", congr);
    CreateImage(m, 660, 420, ICB_UINT);
    m = 0;
    ReadImage("map.bmp", map);

    PasteNon0(rules, 1, 1, m);

    DisplayImage(FRM1, m);
    Sleep(3000);
    m = 0;
    PasteNon0(map, 1, 1, m);
    PasteNon0(playerleft, px, py, m);
    PasteNon0(playerleft, 307, 357, m);
    PasteNon0(playerleft, 257, 357, m);
    PasteNon0(playerleft, 357, 357, m);

    hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        return;
    }
    //starts 1000 ms later calls thread every 30 ms

    CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)PlayerMove, NULL, 1000, 30, 0);
    for (int i = 0; i < 4; i++) {

        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SpawnEnemy1, NULL, 0, &dw);

        Sleep(400);
    }


    SetFocus(ICG_GetMainWindow());

}

void ICGUI_main()
{
    CreateImage(loading, 660, 420, ICB_UINT);
    ReadImage("loading.bmp", loadingscreen);
    ReadImage("gameover.bmp", gameoverscreen);
    ICG_SetOnKeyPressed(WhenKeyPressed);
    FRM1 = ICG_FrameMedium(5, 5, 660, 420);
    BTN = ICG_Button(675, 5, 100, 50, "START", Play);
    PasteNon0(loadingscreen, 1, 1, loading);
    DisplayImage(FRM1, loading);

}