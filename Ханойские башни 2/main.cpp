#include <iostream>
#include <windows.h>
#include "ctime"
#include "conio.h"
#include <string>
#include <cmath>

void start();
void startMenu(int switcher);
void rules();
void typePlay(int switcher);
void enterSize();
void playClassic();
void playBicolor();
void playMagnet();
void drawClassic(int up);
void drawBicolor(int up);
void drawMagnet(int up);
int checkWin();
void Win();
void moveToverClassic(int amount, int point1, int point2, int temp);
void doMoveClassic(int point1, int point2);


const int NotUsed = system( "color E8" );
short watchOrPlay = 1; //1-play, 2-watch
short tPlay = 1; //1-классическая, 2-двухцветная, 3-магнитная
short allSize = 3;//кол-во дисков
short step = 0;//номер хода
bool flag1 = 0;
bool flag2 = 0;
bool flag3 = 0;

std::string Classic[10] = {"        |        ", "        0        ", "       OOO       ", "      OOOOO      ", "     OOOOOOO     ",
                    "    OOOOOOOOO    ", "   OOOOOOOOOOO   ", "  OOOOOOOOOOOOO  ", " OOOOOOOOOOOOOOO ", "OOOOOOOOOOOOOOOOO"};
std::string Bicolor[10] = {"        |        ", "        *        ", "       ***       ", "      *****      ", "     *******     ",
                    "    *********    ", "   ***********   ", "  *************  ", " *************** ", "*****************"};

struct Hanoi_type {
    Hanoi_type() {}
    Hanoi_type(int s)
    : size1(s)
    , data1(new int[s])
    , size2(0), size3(0)
    , data2(new int[s]), data3(new int[s])
    {
        for (int i=0; i<=s; ++i) data1[i] = i+1;
        for (int i=0; i<=s; ++i) data2[i] = 0;
        for (int i=0; i<=s; ++i) data3[i] = 0;
    }

    Hanoi_type(int a, int b)
    : size1(a)
    , data1(new int[a])
    , size2(a), size3(0)
    , data2(new int[a]), data3(new int[a])
    {
        for (int i=0; i<=a; ++i) data1[i] = i+1;
        for (int i=0; i<=a; ++i) data2[i] = -(i+1);
        for (int i=0; i<=a; ++i) data3[i] = 0;
    }

    ~Hanoi_type() {
        delete [] data1;
        delete [] data2;
        delete [] data3;
    }

    OnetoTwo() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=allSize; ++i)
            if (data1[i]!=0) {
                n_i = i;
                n_s = data1[i];
                data1[i]=0;
                break;
            }
        data2[n_i] = n_s;
    }
    OnetoThree() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=allSize; ++i)
            if (data1[i]!=0) {
                n_i = i;
                n_s = data1[i];
                data1[i]=0;
                break;
            }
        data3[n_i] = n_s;
    }
    TwotoThree() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=allSize; ++i)
            if (data2[i]!=0) {
                n_i = i;
                n_s = data2[i];
                data2[i]=0;
                break;
            }
        data3[n_i] = n_s;
    }
    TwotoOne() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=allSize; ++i)
            if (data2[i]!=0) {
                n_i = i;
                n_s = data2[i];
                data2[i]=0;
                break;
            }
        data1[n_i] = n_s;
    }
    ThreetoOne() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=allSize; ++i)
            if (data3[i]!=0) {
                n_i = i;
                n_s = data3[i];
                data3[i]=0;
                break;
            }
        data1[n_i] = n_s;
    }
    ThreetoTwo() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=allSize; ++i)
            if (data3[i]!=0) {
                n_i = i;
                n_s = data3[i];
                data3[i]=0;
                break;
            }
        data2[n_i] = n_s;
    }


    int s;
    int size1;
    int size2;
    int size3;
    int * data1;
    int * data2;
    int * data3;
};

Hanoi_type Hanoi(3);
Hanoi_type Hanoi2(3, 3);

void start()
{
    setlocale(0, "rus");//кодировка
    system("mode con cols=80 lines=20");//задание размеров окна консоли
    system("title Ханойские башни");//задание описания окна консоли
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
    CONSOLE_CURSOR_INFO cursor = { 100, false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
    SetConsoleCursorInfo(hCons, &cursor);//применение заданных параметров курсора
    system("cls");
    std::cout<<"\n\n\n\n\n\n\n\n"
 "                                  ХАНОЙСКИЕ\n\n"
 "                                    бАШНИ";
    Sleep(3000);
}

void startMenu(int switcher)
{
    system("cls");
    switch (switcher)
    {
    case 1:
        std::cout << "\n\n\n\n\n\n                                   < ИГРАТЬ! >\n\n\n                                 СМОТРЕТЬ РЕШЕНИЕ\n\n\n                                     ПРАВИЛА";
        break;
    case 2:
        std::cout << "\n\n\n\n\n\n                                     ИГРАТЬ!\n\n\n                               < СМОТРЕТЬ РЕШЕНИЕ >\n\n\n                                     ПРАВИЛА";
        break;
    case 3:
        std::cout << "\n\n\n\n\n\n                                     ИГРАТЬ!\n\n\n                                 СМОТРЕТЬ РЕШЕНИЕ\n\n\n                                   < ПРАВИЛА >";
        break;
    }
    int choice = _getch(); //считанный символ
    if (choice == 224 || choice == 0)//любая стрелка
        choice = _getch();
    if (choice == 72)//вверх
        if (switcher != 1)
            startMenu(switcher - 1);
        else
            startMenu(3);
    if (choice == 80)//вниз
        if (switcher != 3)
            startMenu(switcher + 1);
        else
            startMenu(1);
    if (choice == 13 || choice == 32) //пробел
    {
        if (switcher == 1)
            typePlay(1);
        if (switcher == 2)
        {
            watchOrPlay = 2;
            typePlay(1);
        }
        if (switcher == 3)
            rules();
    }
}

void rules()
{
    system("cls");
    std::cout << " ВЕРНУТЬСЯ: ESCAPE\n";
    std::cout << " Здесь будут правила";
    int controller = _getch();
    if (controller == 27)//если Escape
        startMenu(1);
}

void typePlay(int switcher)
{
    system("cls");
    switch (switcher)
    {
    case 1:
        std::cout << "\n\n\n\n\n\n                                 < КЛАССИЧЕСКАЯ >\n\n\n                                   ДВУХЦВЕТНАЯ\n\n\n                                    МАГНИТНАЯ";
        break;
    case 2:
        std::cout << "\n\n\n\n\n\n                                   КЛАССИЧЕСКАЯ\n\n\n                                 < ДВУХЦВЕТНАЯ >\n\n\n                                    МАГНИТНАЯ";
        break;
    case 3:
        std::cout << "\n\n\n\n\n\n                                   КЛАССИЧЕСКАЯ\n\n\n                                   ДВУХЦВЕТНАЯ\n\n\n                                  < МАГНИТНАЯ >";
        break;
    }
    int choice = _getch(); //считанный символ
    if (choice == 224 || choice == 0)//любая стрелка
        choice = _getch();
    if (choice == 72)//вверх
        if (switcher != 1)
            typePlay(switcher - 1);
        else
            typePlay(3);
    if (choice == 80)//вниз
        if (switcher != 3)
            typePlay(switcher + 1);
        else
            typePlay(1);
    if (choice == 13 || choice == 32) //пробел
    {
        if (switcher == 1)
            enterSize();
        if (switcher == 2)
        {
            ::tPlay = 2;
            enterSize();
        }
        if (switcher == 3)
        {
            ::tPlay = 3;
            enterSize();
        }
    }
}

void enterSize()
{
    system("cls");
    std::cout << "Количество дисков?" <<std::endl;
    std::cin >> ::allSize;
    Hanoi_type Hanoi(allSize);
    Hanoi_type Hanoi2(allSize, allSize);

    if (tPlay == 1) drawClassic(0);
    if (tPlay == 2) drawBicolor(0);
    if (tPlay == 3) drawMagnet(0);
}

void playClassic()
{
    ::step++;

    int one = 0; int two = 0; int three = 0;
    for (int j=0; j<allSize; ++j) //для проверки хода
        if (Hanoi.data1[j]!=0) {
            one = Hanoi.data1[j];
            break;
        }
    for (int j=0; j<allSize; ++j)
        if (Hanoi.data2[j]!=0) {
            two = Hanoi.data2[j];
            break;
        }
    for (int j=0; j<allSize; ++j)
        if (Hanoi.data3[j]!=0) {
            three = Hanoi.data3[j];
            break;
        }

    int choice = _getch();
    if (choice == 49) {
        if (!flag1 && !flag2 && !flag3) {
            ::flag1 = 1;
            drawClassic(1);
            choice = _getch();
        }
        else {
            if (flag1) {
                ::flag1 = 0;
                drawClassic(0);
                choice = _getch();
            }

            if (flag2 && one<two && one!=0 || two==0) {system("color E4"); std::cerr << "\nТак нельзя!!!"; playClassic();}
            if (flag2 && (one>two || one==0) && two!=0) {
                ::flag2 = 0;
                Hanoi.TwotoOne();
                drawClassic(0);
                choice = _getch();
            }

            if (flag3 && one<three && one!=0 || three==0) {system("color E4"); std::cerr << "\nТак нельзя!!!"; playClassic();}
            if (flag3 && (one>three || one==0) && three!=0) {
                ::flag3 = 0;
                Hanoi.ThreetoOne();
                drawClassic(0);
                choice = _getch();
            }
        }
    }
    if (choice == 50) {
        if (!flag2 && !flag1 && !flag3) {
            ::flag2 = 1;
            drawClassic(2);
            choice = _getch();
        }
        else {
            if (flag2) {
                ::flag2 = 0;
                drawClassic(0);
                choice = _getch();
            }
            if (flag1 && two<one && two!=0 || one==0) {system("color E4"); std::cerr << "\nТак нельзя!!!"; playClassic();}
            if (flag1 && (two>one || two==0) && one!=0) {
                ::flag1 = 0;
                Hanoi.OnetoTwo();
                drawClassic(0);
                choice = _getch();
            }

            if (flag3 && two<three && two!=0 || three==0) {system("color E4"); std::cerr << "\nТак нельзя!!!"; playClassic();}
            if (flag3 && (two>three || two==0) && three!=0) {
                ::flag3 = 0;
                Hanoi.ThreetoTwo();
                drawClassic(0);
                choice = _getch();
            }
        }
    }
    if (choice == 51) {
        if (!flag3 && !flag1 && !flag2) {
            ::flag3 = 1;
            drawClassic(3);
            choice = _getch();
        }
        else {
            if (flag3) {
                ::flag3 = 0;
                drawClassic(0);
                choice = _getch();
            }
            if (flag1 && three<one && three!=0 || one==0) {system("color E4"); std::cerr << "\nТак нельзя!!!"; playClassic();}
            if (flag1 && (three>one || three==0) && one!=0) {
                ::flag1 = 0;
                Hanoi.OnetoThree();
                drawClassic(0);
                choice = _getch();
            }

            if (flag2 && three<two && three!=0 || two==0) {system("color E4"); std::cerr << "\nТак нельзя!!!"; playClassic();}
            if (flag2 && (three>two || three==0) && two!=0) {
                ::flag2 = 0;
                Hanoi.TwotoThree();
                drawClassic(0);
                choice = _getch();
            }
        }
    }
    choice = _getch();

}
void playBicolor()
{

}
void playMagnet()
{

}

void drawClassic(int up)
{
    system("cls");
    system( "color E8" );
    std::cout << "Выбор башни - \"1\", \"2\", \"3\"" << std::endl;
    std::cout << "Количество ходов: " << step/2 << std::endl;
    std::cout << "\n\n\n\n\n\n";

    int up_now = 0;

        if (up==1) {
            for (int j=0; j<allSize; ++j)
                if (Hanoi.data1[j]!=0)
                {
                    std::cout << "    ";//4
                    std::cout << Classic[Hanoi.data1[j]];
                    up_now = Hanoi.data1[j];
                    break;
                }
        }
        if (up==2) {
            for (int j=0; j<allSize; ++j)
                if (Hanoi.data2[j]!=0)
                {
                    std::cout << "                              ";//27+3
                    std::cout << Classic[Hanoi.data2[j]];
                    up_now = Hanoi.data2[j];
                    break;
                }
        }
        if (up==3) {
            for (int j=0; j<allSize; ++j)
                if (Hanoi.data3[j]!=0)
                {
                    std::cout << "                                                        ";//27+27+2
                    std::cout << Classic[Hanoi.data3[j]];
                    up_now = Hanoi.data3[j];
                    break;
                }
        }

    std::cout << "\n\n\n";
    for (int i=0; i<allSize; ++i)
    {
        std::cout << "    ";//4
        if (up_now == Hanoi.data1[i])
            std::cout << Classic[0];
        if (up_now != Hanoi.data1[i])
            std::cout << Classic[Hanoi.data1[i]];
        std::cout << "         ";
        if (up_now == Hanoi.data2[i])
            std::cout << Classic[0];
        if (up_now != Hanoi.data2[i])
            std::cout << Classic[Hanoi.data2[i]];
        std::cout << "         ";
        if (up_now == Hanoi.data3[i])
            std::cout << Classic[0];
        if (up_now != Hanoi.data3[i])
        std::cout << Classic[Hanoi.data3[i]];

        std::cout << "\n";

    }

    std::cout << " _________________________ _________________________ _________________________"
                 "\n            1                         2                         3";

    if (checkWin()) Win();

    if (watchOrPlay == 1) playClassic();
    else if (step==0) moveToverClassic(allSize, 1, 2, 3);

}

void drawBicolor(int up)
{
    system("cls");
    system( "color E8" );
    std::cout << "Выбор башни - \"1\", \"2\", \"3\"" << std::endl;
    std::cout << "Количество ходов: " << step/2 << std::endl;
    std::cout << "\n\n\n\n\n\n";

    int up_now = 0;

        if (up==1) {
            for (int j=-allSize+1; j<allSize; ++j)
                if (Hanoi2.data1[j]!=0)
                {
                    std::cout << "    ";//4
                    if ((Hanoi2.data1[j]>0 && Hanoi2.data1[j]%2==1) || (Hanoi2.data1[j]<0 && Hanoi2.data1[j]%2==0))
                        std::cout << Classic[abs(Hanoi2.data1[j])];
                    else
                        std::cout << Bicolor[abs(Hanoi2.data1[j])];
                    up_now = Hanoi2.data1[j];
                    break;
                }
        }
        if (up==2) {
            for (int j=-allSize+1; j<allSize; ++j)
                if (Hanoi2.data2[j]!=0)
                {
                    std::cout << "                              ";//27+3

                    if ((Hanoi2.data2[j]>0 && Hanoi2.data2[j]%2==1) || (Hanoi2.data2[j]<0 && Hanoi2.data2[j]%2==0))
                        std::cout << Classic[abs(Hanoi2.data2[j])];
                    else
                        std::cout << Bicolor[abs(Hanoi2.data2[j])];
                    up_now = Hanoi2.data2[j];
                    break;
                }
        }
        if (up==3) {
            for (int j=-allSize+1; j<allSize; ++j)
                if (Hanoi2.data3[j]!=0)
                {
                    std::cout << "                                                        ";//27+27+2
                    if ((Hanoi2.data3[j]>0 && Hanoi2.data3[j]%2==1) || (Hanoi2.data3[j]<0 && Hanoi2.data3[j]%2==0))
                        std::cout << Classic[abs(Hanoi2.data3[j])];
                    else
                        std::cout << Bicolor[abs(Hanoi2.data3[j])];
                    up_now = Hanoi2.data3[j];
                    break;
                }
        }


    std::cout << "\n\n\n";
    for (int i=-allSize+1; i<allSize; ++i)
    {
        std::cout << "    ";//4
        if (up_now == Hanoi2.data1[i])
            std::cout << Classic[0];
        if (up_now != Hanoi2.data1[i])
            if ((Hanoi2.data1[i]>0 && Hanoi2.data1[i]%2==1) || (Hanoi2.data1[i]<0 && Hanoi2.data1[i]%2==0))
                std::cout << Classic[abs(Hanoi2.data1[i])];
            else
                std::cout << Bicolor[abs(Hanoi2.data1[i])];

        std::cout << "         ";
        if (up_now == Hanoi2.data2[i])
            std::cout << Classic[0];
        if (up_now != Hanoi2.data2[i])
            if ((Hanoi2.data2[i]>0 && Hanoi2.data2[i]%2==1) || (Hanoi2.data2[i]<0 && Hanoi2.data2[i]%2==0))
                std::cout << Classic[abs(Hanoi2.data2[i])];
            else
                std::cout << Bicolor[abs(Hanoi2.data2[i])];

        std::cout << "         ";
        if (up_now == Hanoi2.data3[i])
            std::cout << Classic[0];
        if (up_now != Hanoi2.data3[i])
            if ((Hanoi2.data3[i]>0 && Hanoi2.data3[i]%2==1) || (Hanoi2.data3[i]<0 && Hanoi2.data3[i]%2==0))
                std::cout << Classic[abs(Hanoi2.data3[i])];
            else
                std::cout << Bicolor[abs(Hanoi2.data3[i])];

        std::cout << "\n";

    }


    std::cout << " _________________________ _________________________ _________________________"
                 "\n            1                         2                         3";

    //if (checkWin()) Win();

}

void drawMagnet(int up)
{

}

int checkWin()
{
    int flag_win1 = 1;
    int flag_win2 = 1;
    for (int i=0; i<allSize; ++i)
        if (Hanoi.data2[i]==0) flag_win1=0;
    for (int i=0; i<allSize; ++i)
        if (Hanoi.data3[i]==0) flag_win2=0;
    if (flag_win1 || flag_win2) return 1;
    else return 0;
}

void Win()
{
    Sleep(2000);
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n"
 "                                    ПОБЕДА!!!\n\n\n\n\n\n\n\n\n";
}

void doMoveClassic(int point1, int point2)
{
    Sleep(1500);
    step = step+2;
    system("cls");
    drawClassic(point1);
    Sleep(1500);
    if (point1==1 && point2==2) {Hanoi.OnetoTwo(); drawClassic(0);}
    if (point1==1 && point2==3) {Hanoi.OnetoThree(); drawClassic(0);}
    if (point1==2 && point2==3) {Hanoi.TwotoThree(); drawClassic(0);}
    if (point1==2 && point2==1) {Hanoi.TwotoOne(); drawClassic(0);}
    if (point1==3 && point2==1) {Hanoi.ThreetoOne(); drawClassic(0);}
    if (point1==3 && point2==2) {Hanoi.ThreetoTwo(); drawClassic(0);}
}

void moveToverClassic(int amount, int point1, int point2, int temp)
{
    if (amount==0) return;
    moveToverClassic(amount-1, point1, temp, point2);
    doMoveClassic(point1, point2);
    moveToverClassic(amount-1, temp, point2, point1);
}

int main(int argc, char *argv[])
{
    start();
    startMenu(1);

    return 0;
}

