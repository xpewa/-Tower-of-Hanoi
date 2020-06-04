#include <iostream>
#include <windows.h>
#include "ctime"
#include "conio.h"
#include <string>
#include <cmath>

void console_gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void start();//заставка
void startMenu(int switcher);//выбор действия(играть, смотреть)
void rules();//правила
void typePlay(int switcher);//выбор типа игры
void enterSize();//ввод количества дисков
void play();//основная функция для игры
int getLast(int i);//возвращает номер последнего диска на столбе i
void draw(int up);//рисует игровое поле
void drawData(int data);//рисует диски
void drawData_color(int data, int color);
int checkWin();//проверяет наступила ли победа
void Win();//победа!
void moveTover(int amount, int point1, int point2, int temp);//двигает башни (в основном для классической игры)
void doMove(int point1, int point2);//двигает диски
void moveToverBicolor(int amount, int point1, int point2, int temp);//алгоритм для двуцветной игры
void BildBicolor(int amount, int point1, int point2, int temp);//строит единую башню из двух цветных
void DestroyBicolor(int amount, int point1, int point2, int temp);//разбивает единую башню на две однотонных
void MTM_1(int n, int i, int s, int d);//сокращенно moveToverMagnit
void MTM_2(int n, int s, int d, int i);//нужны для алгоритма магнитной башни
bool checkColor(int i);//проверяет какого цвета диск (для двуцветной башни)
bool checkMove(int i, int k);//проверяет, правильный ли ход

const int NotUsed = system( "color E8" );//цвет фона и букв
short watchOrPlay = 1; //Что мы будем делать? 1-играть, 2-смотреть
short tPlay = 1; //Какой тип игры? 1-классическая, 2-двухцветная, 3-магнитная
short allSize = 3;//кол-во дисков
short step = 0;//номер хода
bool flag1 = 0;//если поднят флаг, значит диск (1,2 или 3) в воздухе
bool flag2 = 0;
bool flag3 = 0;

//для рисования дисков
std::string Classic[1] = {"        |        "};

//основная структура - в ней всё, что происходит с дисками
struct Hanoi_type {
    Hanoi_type(int s)//конструктор
    : size1(s)//резмер первого массива
    , data1(new int[2*s+1])//первый столб
    , size2(s), size3(s)
    , data2(new int[2*s+1]), data3(new int[2*s+1])//второй и третий столбы
    {
        for (int i=0; i<=2*size1; ++i) data1[i] = 0;//заполнение массивов нулями (для рисования палочек)
        for (int i=0; i<=2*size1; ++i) data2[i] = 0;
        for (int i=0; i<=2*size1; ++i) data3[i] = 0;
    }

    Classic()//создаём диски для классической игры
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//чем больше номер диска, тем он больше
    }
    Bicolor()//для двухцветной
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//на первом столбе диски положительные,
        for (int i=2*allSize; i>=allSize; --i) data2[i] = -(i+1-allSize);//на втором - отрицательные
    }
    Magnit()//для магнитной
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//это верхняя чать дисков - остальное дорисовываем
    }

    ~Hanoi_type() { //деструктор
        delete [] data1;
        delete [] data2;
        delete [] data3;
    }

    OnetoTwo() { //перемещает верхний диск с 1 столба на 2 (из конца первого массива на конец второго)
        int n_s = 0;//размер диска
        for (int i=0; i<=2*allSize; ++i) //находим верхний диск
            if (data1[i]!=0) {
                n_s = data1[i]; //запоминаем размер
                data1[i]=0; //удаляем с 1 стодба
                break;
            }
        for (int i=2*allSize-1; i>=0; --i) //находим первое с конца не занятое место
            if (data2[i]==0)
                {data2[i] = n_s; break;} //вставляем наш диск

    }
    OnetoThree() { //здесь и далее - аналогично
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=2*allSize; ++i)
            if (data1[i]!=0) {
                n_i = i;
                n_s = data1[i];
                data1[i]=0;
                break;
            }
        for (int i=2*allSize-1; i>=0; --i)
            if (data3[i]==0)
                {data3[i] = n_s; break;}
    }
    TwotoThree() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=2*allSize; ++i)
            if (data2[i]!=0) {
                n_i = i;
                n_s = data2[i];
                data2[i]=0;
                break;
            }
        for (int i=2*allSize-1; i>=0; --i)
            if (data3[i]==0)
                {data3[i] = n_s; break;}
    }
    TwotoOne() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=2*allSize; ++i)
            if (data2[i]!=0) {
                n_i = i;
                n_s = data2[i];
                data2[i]=0;
                break;
            }
        for (int i=2*allSize-1; i>=0; --i)
            if (data1[i]==0)
                {data1[i] = n_s; break;}
    }
    ThreetoOne() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=2*allSize; ++i)
            if (data3[i]!=0) {
                n_i = i;
                n_s = data3[i];
                data3[i]=0;
                break;
            }
        for (int i=2*allSize-1; i>=0; --i)
            if (data1[i]==0)
                {data1[i] = n_s; break;}
    }
    ThreetoTwo() {
        int n_i = 0;
        int n_s = 0;
        for (int i=0; i<=2*allSize; ++i)
            if (data3[i]!=0) {
                n_i = i;
                n_s = data3[i];
                data3[i]=0;
                break;
            }
        for (int i=2*allSize-1; i>=0; --i)
            if (data2[i]==0)
                {data2[i] = n_s; break;}
    }


    int s; //размеры, про которые я забыла и поэтому никак не использовала
    int size1;//но переделывать программу лень
    int size2;//их можно удалить, но пусть останутся
    int size3;
    int * data1;//столбы-массивы
    int * data2;
    int * data3;
};

Hanoi_type Hanoi(11);//создаём переменную ханои типа ханои максимального размера

void start()
{
    setlocale(0, "rus");//кодировка (чтобы отображались русские буквы)
    system("mode con cols=80 lines=20");//задание размеров окна консоли 80 20
    system("title Ханойские башни");//задание описания окна консоли
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
    CONSOLE_CURSOR_INFO cursor = { 100, false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
    SetConsoleCursorInfo(hCons, &cursor);//применение заданных параметров курсора
    system("cls");//очистка консоли
    std::cout<<"\n\n\n\n\n\n\n\n"
 "                                  ХАНОЙСКИЕ\n\n"
 "                                    бАШНИ";
    Sleep(3000);//задержка
    startMenu(1);
}

void startMenu(int switcher)
{
    ::step = 0;
    system("cls");//очистка экрана
    switch (switcher)//возможные типы текста на экране
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
    std::cout << " Пользование программой:\n"
                 " Вернуться в главное меню: escape\n"
                 " Выбор башен: клавиши 1, 2 и 3\n"
                 " Поддерживается количество дисков до 9\n"
                 " Правила игры:\n"
                 " Классическая: Даны три стержня, на один из которых нанизаны кольца, причём кольца отличаются размером и лежат меньшее на большем."
                 " Задача состоит в том, чтобы перенести пирамиду из колец за наименьшее число ходов на другой стержень."
                 " За один раз разрешается переносить только одно кольцо, причём нельзя класть большее кольцо на меньшее.\n"
                 " Двухцветная: различия с классической в том, что изначально на двух стержнях нанизаны кольца разных цветов."
                 " Необходимо поменять местами некоторые диски так, чтобы получились две одноцветные пирамиды, причем пирамиды должны совпасть по цвету с начальным верхним диском.\n"
                 " Магнитная: правила как в классической игре. За исключением того, что при каждом ходе диски переварачиваются,"
                 " и нельзя ставить двух на друга стороны диска с одноимёнными зарядами.";
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
    if (choice == 27)
        startMenu(1);
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
    std::cout << "\n\n                      Количество дисков?" <<std::endl;
    std::cout << "\n                    -> ";
    std::cin >> ::allSize;

    ::Hanoi_type Hanoi(allSize);//переназначаем тип ханои (не уверена, что так можно)

    if (tPlay == 1) ::Hanoi.Classic();//если тип игры классический, то и заполняем классически и т.п.
    if (tPlay == 2) ::Hanoi.Bicolor();
    if (tPlay == 3) ::Hanoi.Magnit();
    draw(0);//рисуем поле, соответствующее нашей структере ханои
}

bool checkMove(int i, int k) //i - куда ходим, k - откуда
{
    int one = Hanoi.data1[getLast(1)]; int two = Hanoi.data2[getLast(2)]; int three = Hanoi.data3[getLast(3)];//верхние диски
//учитываем, что нельзя класть больший диск на меньший (только если меньший = 0),
//нельзя походить ничем и для магнитной игры - полярность
    if (i==1 && k==2 && (abs(one)>=abs(two) || abs(one)==0) && abs(two)!=0 && ((tPlay == 3 && ((one>=0 && two>=0) || (one<=0 && two<=0))) || tPlay !=3))
        return true;
    if (i==1 && k==3 && (abs(one)>=abs(three) || abs(one)==0) && abs(three)!=0 && ((tPlay == 3 && ((one>=0 && three>=0) || (one<=0 && three<=0))) || tPlay !=3))
        return true;
    if (i==2 && k==1 && (abs(two)>=abs(one) || abs(two)==0) && abs(one)!=0 && ((tPlay == 3 && ((one>=0 && two>=0) || (one<=0 && two<=0))) || tPlay !=3))
        return true;
    if (i==2 && k==3 && (abs(two)>=abs(three) || abs(two)==0) && abs(three)!=0 && ((tPlay == 3 && ((three>=0 && two>=0) || (three<=0 && two<=0))) || tPlay !=3))
        return true;
    if (i==3 && k==1 && (abs(three)>=abs(one) || abs(three)==0) && abs(one)!=0 && ((tPlay == 3 && ((one>=0 && three>=0) || (one<=0 && three<=0))) || tPlay !=3))
        return true;
    if (i==3 && k==2 && (abs(three)>=abs(two) || abs(three)==0) && abs(two)!=0 && ((tPlay == 3 && ((three>=0 && two>=0) || (three<=0 && two<=0))) || tPlay !=3))
        return true;
    return 0;
}

void play()//вызывается, если играем
{

    int choice = _getch();
    if (choice == 27)//если esc
        startMenu(1);

    if (choice == 49) {//если выбрали башню 1
        if (!flag1 && !flag2 && !flag3) {//если диска в воздухе нет
            ::flag1 = 1;//поднимаем диск с 1 башни
            if (tPlay == 3) Hanoi.data1[getLast(1)] = -Hanoi.data1[getLast(1)];//если игра магнитная - меняем полярность
            draw(1);//рисуем поднятый диск
            choice = _getch();
        }
        else {
            if (flag1) {//если до этого был поднят диск на 1 башне
                ::flag1 = 0;//опускаем обратно
                if (tPlay == 3) Hanoi.data1[getLast(1)] = -Hanoi.data1[getLast(1)];//возвращаем полярность
                draw(0);//рисуем опущенный диск
                choice = _getch();
            }
            //если до этого был поднят диск на 2 башне и он не модет быть опущен на 1 - ругаемся
            if (flag2 && !checkMove(1, 2)) {system("color E4"); std::cerr << "\nТак нельзя!!!"; play();}
            //если может - опускаем
            if (flag2 && checkMove(1, 2)) {
                ::flag2 = 0;
                ::step++;//считаем шаги
                Hanoi.TwotoOne();
                draw(0);
                choice = _getch();
            }
            //далее всё аналогично
            if (flag3 && !checkMove(1, 3)) {system("color E4"); std::cerr << "\nТак нельзя!!!"; play();}
            if (flag3 && checkMove(1, 3)) {
                ::flag3 = 0;
                ::step++;//считаем шаги
                Hanoi.ThreetoOne();
                draw(0);
                choice = _getch();
            }
        }
    }
    if (choice == 50) { //если нажали 2
        if (!flag2 && !flag1 && !flag3) {
            ::flag2 = 1;
            if (tPlay == 3) Hanoi.data2[getLast(2)] = -Hanoi.data2[getLast(2)];
            draw(2);
            choice = _getch();
        }
        else {
            if (flag2) {
                ::flag2 = 0;
                if (tPlay == 3) Hanoi.data2[getLast(2)] = -Hanoi.data2[getLast(2)];
                draw(0);
                choice = _getch();
            }
            if (flag1 && !checkMove(2, 1)) {system("color E4"); std::cerr << "\nТак нельзя!!!"; play();}
            if (flag1 && checkMove(2, 1)) {
                ::flag1 = 0;
                ::step++;//считаем шаги
                Hanoi.OnetoTwo();
                draw(0);
                choice = _getch();
            }

            if (flag3 && !checkMove(2, 3)) {system("color E4"); std::cerr << "\nТак нельзя!!!"; play();}
            if (flag3 && checkMove(2, 3)) {
                ::flag3 = 0;
                ::step++;//считаем шаги
                Hanoi.ThreetoTwo();
                draw(0);
                choice = _getch();
            }
        }
    }
    if (choice == 51) { //если нажали 3
        if (!flag3 && !flag1 && !flag2) {
            ::flag3 = 1;
            if (tPlay == 3) Hanoi.data3[getLast(3)] = -Hanoi.data3[getLast(3)];
            draw(3);
            choice = _getch();
        }
        else {
            if (flag3) {
                ::flag3 = 0;
                if (tPlay == 3) Hanoi.data3[getLast(3)] = -Hanoi.data3[getLast(3)];
                draw(0);
                choice = _getch();
            }
            if (flag1 && !checkMove(3, 1)) {system("color E4"); std::cerr << "\nТак нельзя!!!"; play();}
            if (flag1 && checkMove(3, 1)) {
                ::flag1 = 0;
                ::step++;//считаем шаги
                Hanoi.OnetoThree();
                draw(0);
                choice = _getch();
            }

            if (flag2 && !checkMove(3, 2)) {system("color E4"); std::cerr << "\nТак нельзя!!!"; play();}
            if (flag2 && checkMove(3, 2)) {
                ::flag2 = 0;
                ::step++;//считаем шаги
                Hanoi.TwotoThree();
                draw(0);
                choice = _getch();
            }
        }
    }
    choice = _getch();

}

int getLast(int i)//i -номер столба
{
    if (i == 1)
        for (int j=0; j<2*allSize; ++j)
            if (Hanoi.data1[j]!=0)
                return j;
    if (i == 2)
        for (int j=0; j<2*allSize; ++j)
            if (Hanoi.data2[j]!=0)
                return j;
    if (i == 3)
        for (int j=0; j<2*allSize; ++j)
            if (Hanoi.data3[j]!=0)
                return j;
}


void draw(int up)//если up=0 - ни диск не поднят, если 1 - поднят с 1 башни и т.п.
{
    if (step==0) system("cls");
    else console_gotoxy(0,0);
    if (tPlay != 1 && allSize>6) system("mode con cols=80 lines=27");//увеличиваем поле, если не влазит
    system( "color E8" );
    std::cout << " Количество ходов: " << step << "                                Выбор башни - \"1\", \"2\", \"3\"" << std::endl;
    std::cout << "\n\n";

    int up_now = 0;//то, что поднято сейчас (нужно для правильной отрисовки)
    //рисуем поднятые диски
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
        if (up==1) {
            std::cout << "    ";//4
            drawData(Hanoi.data1[getLast(1)]);
            up_now = Hanoi.data1[getLast(1)];
        }
        else std::cout << "                              ";
        if (up==2) {
            //std::cout << "                              ";//30
            drawData(Hanoi.data2[getLast(2)]);
            up_now = Hanoi.data2[getLast(2)];
        }
        else std::cout << "                          ";
        if (up==3) {
            //std::cout << "                                                        ";//27+27+2
            drawData(Hanoi.data3[getLast(3)]);
            up_now = Hanoi.data3[getLast(3)];
        }
        else std::cout << "                      ";
        if (tPlay == 3) {
            if (up==1) {std::cout << "\n    "; drawData(-Hanoi.data1[getLast(1)]);}
            if (up!=1) std::cout << "\n                              ";
            if (up==2) {drawData(-Hanoi.data2[getLast(2)]);}
            if (up!=2) std::cout << "                          ";
            if (up==3) drawData(-Hanoi.data3[getLast(3)]);
            if (up!=3) std::cout << "                      ";
        }

    std::cout << "\n\n\n";
    //рисуем дополнительные палочки только для двухцветной игры (больше они не нужны)
    int i;
    if (tPlay == 2) i = 0;
    else i = allSize;
    //рисуем не поднятые диски
    for (i; i<2*allSize; ++i)
    {
        std::cout << "    ";//4
        if (up_now == Hanoi.data1[i])//если диск поднят - рисуем на его месте палочку
            std::cout << Classic[0];
        else
            drawData(Hanoi.data1[i]);//иначе рисуем его самого

        std::cout << "         ";
        if (up_now == Hanoi.data2[i])
            std::cout << Classic[0];
        else
            drawData(Hanoi.data2[i]);

        std::cout << "         ";
        if (up_now == Hanoi.data3[i])
            std::cout << Classic[0];
        else
            drawData(Hanoi.data3[i]);

        //для магнитной дорисовываем вторую(нижнюю) часть диска

            if (tPlay == 3) {
                std::cout << "\n    ";//4
                if (up_now == Hanoi.data1[i])
                    std::cout << Classic[0];
                else
                    drawData(-Hanoi.data1[i]);

                std::cout << "         ";
                if (up_now == Hanoi.data2[i])
                    std::cout << Classic[0];
                else
                    drawData(-Hanoi.data2[i]);

                std::cout << "         ";
                if (up_now == Hanoi.data3[i])
                    std::cout << Classic[0];
                else
                    drawData(-Hanoi.data3[i]);

            }
    std::cout << "\n";
    }

    SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8));
    std::cout << " _________________________ _________________________ _________________________"
                 "\n            1                         2                         3";

    if (checkWin()) Win();//если победили то победили

    if (watchOrPlay == 1) play();//если играем то играем
    //если смотрим, то вызываем алгоритмы
    else if (step == 0 && tPlay == 1) moveTover(allSize, 1, 2, 3);
    else if (step == 0 && tPlay == 2) moveToverBicolor(allSize, 2, 3, 1);
    else if (step == 0 && tPlay == 3) MTM_2(allSize, 1, 3, 2);

}

void drawData(int data)//просто рисует разные виды дисков. Data - их размер
{
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    if (tPlay == 1) drawData_color(data, 13);
    if (tPlay == 2)
    {
        if (checkColor(data))
            drawData_color(data, 11);
        else
            drawData_color(data, 13);
    }
    if (tPlay == 3) {
        if (data>0) drawData_color(data, 1);
        else drawData_color(data, 4);
    }
}

void drawData_color(int data, int color)
{
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    if (data==0) std::cout << Classic[data];
    if (abs(data)==1) {std::cout << "       ";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "___"; else{if (data>0) std::cout << "|+|";
     if (data<0) std::cout << "|-|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"       ";}
    if (abs(data)==2) {std::cout << "      ";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "_____"; else{if (data>0) std::cout << "|+++|";
     if (data<0) std::cout << "|---|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"      ";}
    if (abs(data)==3) {std::cout << "     ";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "_______"; else{if (data>0) std::cout << "|+++++|";
     if (data<0) std::cout << "|-----|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"     ";}
    if (abs(data)==4) {std::cout << "    ";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "_________"; else{if (data>0) std::cout << "|+++++++|";
     if (data<0) std::cout << "|-------|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"    ";}
    if (abs(data)==5) {std::cout << "   ";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "___________"; else{if (data>0) std::cout << "|+++++++++|";
     if (data<0) std::cout << "|---------|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"   ";}
    if (abs(data)==6) {std::cout << "  ";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "_____________"; else{if (data>0) std::cout << "|+++++++++++|";
     if (data<0) std::cout << "|-----------|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"  ";}
    if (abs(data)==7) {std::cout << " ";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "_______________"; else{if (data>0) std::cout << "|+++++++++++++|";
     if (data<0) std::cout << "|-------------|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<" ";}
    if (abs(data)==8) {std::cout << "";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "|_______________|"; else{if (data>0) std::cout << "|+++++++++++++++|";
     if (data<0) std::cout << "|---------------|";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"";}
    if (abs(data)==9) {std::cout << "";SetConsoleTextAttribute(hCons, (WORD) ((color << 4) | 14)); if (tPlay==1 || tPlay==2) std::cout << "_________________"; else{if (data>0) std::cout << "+++++++++++++++++";
     if (data<0) std::cout << "-----------------";} SetConsoleTextAttribute(hCons, (WORD) ((14 << 4) | 8)); std::cout <<"";}
}

bool checkColor(int i) //1-Classic, 0-Bicolor
{
    if (i>0) {
        if ((i%2)==1)
            return true;
        else
            return false;
    }
    if (i<=0) {
        if ((abs(i)%2)==1)
            return false;
        else
            return true;
    }
}

int checkWin()//для классичекой и магнитной игры смотрим количество дисков на стержнях, для двухцветной - их цвета и количество
{
    int flag_win2 = 1;
    int flag_win3 = 1;
    int flag_b_win1 = 1; //для Bicolor
    int flag_b_win2 = 1;
    for (int i=allSize; i<2*allSize; ++i)
        if (Hanoi.data2[i]==0) flag_win2=0;
    for (int i=allSize; i<2*allSize; ++i)
        if (Hanoi.data3[i]==0) flag_win3=0;

    for (int i=allSize; i<2*allSize; ++i)
        if (!checkColor(Hanoi.data1[i]) || Hanoi.data1[i]==0) flag_b_win1=0;
    for (int i=allSize; i<2*allSize; ++i)
        if (checkColor(Hanoi.data2[i]) || Hanoi.data1[i]==0) flag_b_win2=0;

    if ((flag_win2 || flag_win3) && (tPlay == 1 || tPlay == 3)) return 1;
    if (flag_b_win1 && flag_b_win2 && tPlay==2) return 1;
    return 0;
}

void Win()
{
    Sleep(2000);
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n"
 "                                    ПОБЕДА!!!\n\n\n\n\n\n\n\n\n";
}

void doMove(int point1, int point2)
{
    Sleep(1000);
    step++;
    system("cls");
    if (tPlay == 3 && point1 == 1) Hanoi.data1[getLast(1)] = -Hanoi.data1[getLast(1)];
    if (tPlay == 3 && point1 == 2) Hanoi.data2[getLast(2)] = -Hanoi.data2[getLast(2)];
    if (tPlay == 3 && point1 == 3) Hanoi.data3[getLast(3)] = -Hanoi.data3[getLast(3)];
    draw(point1);
    Sleep(1000);
    if (point1==1 && point2==2) {Hanoi.OnetoTwo();  draw(0);}
    if (point1==1 && point2==3) {Hanoi.OnetoThree(); draw(0);}
    if (point1==2 && point2==3) {Hanoi.TwotoThree(); draw(0);}
    if (point1==2 && point2==1) {Hanoi.TwotoOne(); draw(0);}
    if (point1==3 && point2==1) {Hanoi.ThreetoOne(); draw(0);}
    if (point1==3 && point2==2) {Hanoi.ThreetoTwo(); draw(0);}
}

void moveTover(int amount, int point1, int point2, int temp)
{
    if (amount <= 0) return;
    moveTover(amount-1, point1, temp, point2);
    doMove(point1, point2);
    if (tPlay == 2) doMove(point1, point2);
    moveTover(amount-1, temp, point2, point1);
}

void moveToverBicolor(int amount, int point1, int point2, int temp) //не работает :((((((
{
    if (amount%2 == 0)
        BildBicolor(amount, 1, 2, 3);
    else
        BildBicolor(amount-1, 1, 2, 3);
    if (amount%2 == 0)
        DestroyBicolor(amount, 3, 1, 2);
    else
        DestroyBicolor(amount-1, 3, 1, 2);
}

void BildBicolor(int amount, int point1, int point2, int temp)
{
    if (amount <= 0) return;
    BildBicolor(amount-1, temp, point2, point1);
    doMove(point2, temp);
    moveTover(amount-1, point1, point2, temp);
    doMove(point1, temp);
    moveTover(amount-1, point2, temp, point1);
}

void DestroyBicolor(int amount, int point1, int point2, int temp)
{
    moveTover(amount-1, point1, point2, temp);
    doMove(point1, temp);
    if (amount <= 0) return;
    moveTover(amount-1, point2, temp, point1);
    doMove(point1, point2);
    DestroyBicolor(amount-1, temp, point2, point1);
}

void MTM_1(int n, int i, int s, int d)
{
    if (n<=0) return;
    MTM_1(n-1, i, s, d);
    MTM_2(n-1, s, d, i);
    doMove(i, s);
    MTM_1(n-1, d, s, i);

}

void MTM_2(int n, int s, int d, int i)
{
    if (n<=0) return;
    MTM_2(n-1, s, i, d);
    doMove(s, d);
    MTM_1(n-1, i, s, d);
    MTM_2(n-1, s, d, i);
}


int main()
{
    start();

    return 0;
}

