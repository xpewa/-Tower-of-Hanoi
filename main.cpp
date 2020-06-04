#include <iostream>
#include <windows.h>
#include "ctime"
#include "conio.h"
#include <string>
#include <cmath>

void start();//заставка
void startMenu(int switcher);//выбор действи€(играть, смотреть)
void rules();//правила
void typePlay(int switcher);//выбор типа игры
void enterSize();//ввод количества дисков
void play();//основна€ функци€ дл€ игры
int getLast(int i);//возвращает номер последнего диска на столбе i
void draw(int up);//рисует игровое поле
void drawData(int data);//рисует диски
int checkWin();//провер€ет наступила ли победа
void Win();//победа!
void moveTover(int amount, int point1, int point2, int temp);//двигает башни (в основном дл€ классической игры)
void doMove(int point1, int point2);//двигает диски
void moveToverBicolor(int amount, int point1, int point2, int temp);//алгоритм дл€ двуцветной игры
void BildBicolor(int amount, int point1, int point2, int temp);//строит единую башню из двух цветных
void DestroyBicolor(int amount, int point1, int point2, int temp);//разбивает единую башню на две однотонных
void MTM_1(int n, int i, int s, int d);//сокращенно moveToverMagnit
void MTM_2(int n, int s, int d, int i);//нужны дл€ алгоритма магнитной башни
bool checkColor(int i);//провер€ет какого цвета диск (дл€ двуцветной башни)
bool checkMove(int i, int k);//провер€ет, правильный ли ход

const int NotUsed = system( "color E8" );//цвет фона и букв
short watchOrPlay = 1; //„то мы будем делать? 1-играть, 2-смотреть
short tPlay = 1; // акой тип игры? 1-классическа€, 2-двухцветна€, 3-магнитна€
short allSize = 3;//кол-во дисков
short step = 0;//номер хода
bool flag1 = 0;//если подн€т флаг, значит диск (1,2 или 3) в воздухе
bool flag2 = 0;
bool flag3 = 0;

//дл€ рисовани€ дисков
std::string Classic[10] = {"        |        ", "        O        ", "       OOO       ", "      OOOOO      ", "     OOOOOOO     ",
                    "    OOOOOOOOO    ", "   OOOOOOOOOOO   ", "  OOOOOOOOOOOOO  ", " OOOOOOOOOOOOOOO ", "OOOOOOOOOOOOOOOOO"};
std::string Bicolor[10] = {"        |        ", "        V        ", "       VVV       ", "      VVVVV      ", "     VVVVVVV     ",
                    "    VVVVVVVVV    ", "   VVVVVVVVVVV   ", "  VVVVVVVVVVVVV  ", " VVVVVVVVVVVVVVV ", "VVVVVVVVVVVVVVVVV"};
std::string Plus[10] = {"        |        ", "       |+|       ", "      |+++|      ", "     |+++++|     ", "    |+++++++|    ",
                    "   |+++++++++|   ", "  |+++++++++++|  ", " |+++++++++++++| ", "|+++++++++++++++|", "|+++++++++++++++++|"};
std::string Minus[10] = {"        |        ", "       |-|       ", "      |---|      ", "     |-----|     ", "    |-------|    ",
                    "   |---------|   ", "  |-----------|  ", " |-------------| ", "|---------------|", "|-----------------|"};

//основна€ структура - в ней всЄ, что происходит с дисками
struct Hanoi_type {
    Hanoi_type(int s)//конструктор
    : size1(s)//резмер первого массива
    , data1(new int[2*s+1])//первый столб
    , size2(s), size3(s)
    , data2(new int[2*s+1]), data3(new int[2*s+1])//второй и третий столбы
    {
        for (int i=0; i<=2*size1; ++i) data1[i] = 0;//заполнение массивов нул€ми (дл€ рисовани€ палочек)
        for (int i=0; i<=2*size1; ++i) data2[i] = 0;
        for (int i=0; i<=2*size1; ++i) data3[i] = 0;
    }

    Classic()//создаЄм диски дл€ классической игры
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//чем больше номер диска, тем он больше
    }
    Bicolor()//дл€ двухцветной
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//на первом столбе диски положительные,
        for (int i=2*allSize; i>=allSize; --i) data2[i] = -(i+1-allSize);//на втором - отрицательные
    }
    Magnit()//дл€ магнитной
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//это верхн€€ чать дисков - остальное дорисовываем
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
                data1[i]=0; //удал€ем с 1 стодба
                break;
            }
        for (int i=2*allSize-1; i>=0; --i) //находим первое с конца не зан€тое место
            if (data2[i]==0)
                {data2[i] = n_s; break;} //вставл€ем наш диск

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


    int s; //размеры, про которые € забыла и поэтому никак не использовала
    int size1;//но переделывать программу лень
    int size2;//их можно удалить, но пусть останутс€
    int size3;
    int * data1;//столбы-массивы
    int * data2;
    int * data3;
};

Hanoi_type Hanoi(11);//создаЄм переменную ханои типа ханои максимального размера

void start()
{
    setlocale(0, "rus");//кодировка (чтобы отображались русские буквы)
    system("mode con cols=80 lines=20");//задание размеров окна консоли 80 20
    system("title ’анойские башни");//задание описани€ окна консоли
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//получение хендла
    CONSOLE_CURSOR_INFO cursor = { 100, false };//число от 1 до 100 размер курсора в процентах; false\true - видимость
    SetConsoleCursorInfo(hCons, &cursor);//применение заданных параметров курсора
    system("cls");//очистка консоли
    std::cout<<"\n\n\n\n\n\n\n\n"
 "                                  ’јЌќ…— »≈\n\n"
 "                                    бјЎЌ»";
    Sleep(3000);//задержка
}

void startMenu(int switcher)
{
    system("cls");//очистка экрана
    switch (switcher)//возможные типы текста на экране
    {
    case 1:
        std::cout << "\n\n\n\n\n\n                                   < »√–ј“№! >\n\n\n                                 —ћќ“–≈“№ –≈Ў≈Ќ»≈\n\n\n                                     ѕ–ј¬»Ћј";
        break;
    case 2:
        std::cout << "\n\n\n\n\n\n                                     »√–ј“№!\n\n\n                               < —ћќ“–≈“№ –≈Ў≈Ќ»≈ >\n\n\n                                     ѕ–ј¬»Ћј";
        break;
    case 3:
        std::cout << "\n\n\n\n\n\n                                     »√–ј“№!\n\n\n                                 —ћќ“–≈“№ –≈Ў≈Ќ»≈\n\n\n                                   < ѕ–ј¬»Ћј >";
        break;
    }
    int choice = _getch(); //считанный символ
    if (choice == 224 || choice == 0)//люба€ стрелка
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
    std::cout << " ¬≈–Ќ”“№—я: ESCAPE\n";
    std::cout << " «десь будут правила";
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
        std::cout << "\n\n\n\n\n\n                                 <  Ћј——»„≈— јя >\n\n\n                                   ƒ¬”’÷¬≈“Ќјя\n\n\n                                    ћј√Ќ»“Ќјя";
        break;
    case 2:
        std::cout << "\n\n\n\n\n\n                                    Ћј——»„≈— јя\n\n\n                                 < ƒ¬”’÷¬≈“Ќјя >\n\n\n                                    ћј√Ќ»“Ќјя";
        break;
    case 3:
        std::cout << "\n\n\n\n\n\n                                    Ћј——»„≈— јя\n\n\n                                   ƒ¬”’÷¬≈“Ќјя\n\n\n                                  < ћј√Ќ»“Ќјя >";
        break;
    }
    int choice = _getch(); //считанный символ
    if (choice == 27)
        startMenu(1);
    if (choice == 224 || choice == 0)//люба€ стрелка
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
    std::cout << "\n\n                       оличество дисков?" <<std::endl;
    std::cout << "\n                    -> ";
    std::cin >> ::allSize;

    ::Hanoi_type Hanoi(allSize);//переназначаем тип ханои (не уверена, что так можно)

    if (tPlay == 1) ::Hanoi.Classic();//если тип игры классический, то и заполн€ем классически и т.п.
    if (tPlay == 2) ::Hanoi.Bicolor();
    if (tPlay == 3) ::Hanoi.Magnit();
    draw(0);//рисуем поле, соответствующее нашей структере ханои
}

bool checkMove(int i, int k) //i - куда ходим, k - откуда
{
    int one = Hanoi.data1[getLast(1)]; int two = Hanoi.data2[getLast(2)]; int three = Hanoi.data3[getLast(3)];//верхние диски
//учитываем, что нельз€ класть больший диск на меньший (только если меньший = 0),
//нельз€ походить ничем и дл€ магнитной игры - пол€рность
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

void play()//вызываетс€, если играем
{
    ::step++;//считаем шаги

    int choice = _getch();
    if (choice == 27)//если esc
        startMenu(1);

    if (choice == 49) {//если выбрали башню 1
        if (!flag1 && !flag2 && !flag3) {//если диска в воздухе нет
            ::flag1 = 1;//поднимаем диск с 1 башни
            if (tPlay == 3) Hanoi.data1[getLast(1)] = -Hanoi.data1[getLast(1)];//если игра магнитна€ - мен€ем пол€рность
            draw(1);//рисуем подн€тый диск
            choice = _getch();
        }
        else {
            if (flag1) {//если до этого был подн€т диск на 1 башне
                ::flag1 = 0;//опускаем обратно
                if (tPlay == 3) Hanoi.data1[getLast(1)] = -Hanoi.data1[getLast(1)];//возвращаем пол€рность
                draw(0);//рисуем опущенный диск
                choice = _getch();
            }
            //если до этого был подн€т диск на 2 башне и он не модет быть опущен на 1 - ругаемс€
            if (flag2 && !checkMove(1, 2)) {system("color E4"); std::cerr << "\n“ак нельз€!!!"; play();}
            //если может - опускаем
            if (flag2 && checkMove(1, 2)) {
                ::flag2 = 0;
                Hanoi.TwotoOne();
                draw(0);
                choice = _getch();
            }
            //далее всЄ аналогично
            if (flag3 && !checkMove(1, 3)) {system("color E4"); std::cerr << "\n“ак нельз€!!!"; play();}
            if (flag3 && checkMove(1, 3)) {
                ::flag3 = 0;
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
            if (flag1 && !checkMove(2, 1)) {system("color E4"); std::cerr << "\n“ак нельз€!!!"; play();}
            if (flag1 && checkMove(2, 1)) {
                ::flag1 = 0;
                Hanoi.OnetoTwo();
                draw(0);
                choice = _getch();
            }

            if (flag3 && !checkMove(2, 3)) {system("color E4"); std::cerr << "\n“ак нельз€!!!"; play();}
            if (flag3 && checkMove(2, 3)) {
                ::flag3 = 0;
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
            if (flag1 && !checkMove(3, 1)) {system("color E4"); std::cerr << "\n“ак нельз€!!!"; play();}
            if (flag1 && checkMove(3, 1)) {
                ::flag1 = 0;
                Hanoi.OnetoThree();
                draw(0);
                choice = _getch();
            }

            if (flag2 && !checkMove(3, 2)) {system("color E4"); std::cerr << "\n“ак нельз€!!!"; play();}
            if (flag2 && checkMove(3, 2)) {
                ::flag2 = 0;
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


void draw(int up)//если up=0 - ни диск не подн€т, если 1 - подн€т с 1 башни и т.п.
{
    system("cls");
    if (tPlay != 1 && allSize>6) system("mode con cols=80 lines=27");//увеличиваем поле, если не влазит
    system( "color E8" );
    std::cout << "  оличество ходов: " << step/2 << "                                ¬ыбор башни - \"1\", \"2\", \"3\"" << std::endl;
    std::cout << "\n\n";

    int up_now = 0;//то, что подн€то сейчас (нужно дл€ правильной отрисовки)
    //рисуем подн€тые диски
        if (up==1) {
            std::cout << "    ";//4
            drawData(Hanoi.data1[getLast(1)]);
            if (tPlay == 3) {
                std::cout << "\n    ";
                drawData(-Hanoi.data1[getLast(1)]);
            }
            up_now = Hanoi.data1[getLast(1)];
        }
        if (up==2) {
            std::cout << "                              ";//27+3
            drawData(Hanoi.data2[getLast(2)]);
            if (tPlay == 3) {
                std::cout << "\n                              ";
                drawData(-Hanoi.data2[getLast(2)]);
            }
            up_now = Hanoi.data2[getLast(2)];
        }
        if (up==3) {
            std::cout << "                                                        ";//27+27+2
            drawData(Hanoi.data3[getLast(3)]);
            if (tPlay == 3) {
                std::cout << "\n                                                        ";
                drawData(-Hanoi.data3[getLast(3)]);
            }
            up_now = Hanoi.data3[getLast(3)];
        }

    std::cout << "\n\n\n";
    //рисуем дополнительные палочки только дл€ двухцветной игры (больше они не нужны)
    int i;
    if (tPlay == 2) i = 0;
    else i = allSize;
    //рисуем не подн€тые диски
    for (i; i<2*allSize; ++i)
    {
        std::cout << "    ";//4
        if (up_now == Hanoi.data1[i])//если диск подн€т - рисуем на его месте палочку
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

        //дл€ магнитной дорисовываем вторую(нижнюю) часть диска

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


    std::cout << " _________________________ _________________________ _________________________"
                 "\n            1                         2                         3";

    if (checkWin()) Win();//если победили то победили

    if (watchOrPlay == 1) play();//если играем то играем
    //если смотрим, то вызываем алгоритмы
    else if (step == 0 && tPlay == 1) DestroyBicolor(allSize, 1, 2, 3);
    else if (step == 0 && tPlay == 2) moveToverBicolor(allSize, 2, 3, 1);
    else if (step == 0 && tPlay == 3) MTM_2(allSize, 1, 3, 2);

}

void drawData(int data)//просто рисует разные виды дисков. Data - их размер
{
    if (tPlay == 1) std::cout << Classic[data];
    if (tPlay == 2)
    {
        if (checkColor(data))
            std::cout << Classic[abs(data)];
        else
            std::cout << Bicolor[abs(data)];
    }
    if (tPlay == 3) {
        if (data>0) std::cout << Plus[data];
        else std::cout << Minus[abs(data)];
    }
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

int checkWin()//дл€ классичекой и магнитной игры смотрим количество дисков на стержн€х, дл€ двухцветной - их цвета и количество
{
    int flag_win2 = 1;
    int flag_win3 = 1;
    int flag_b_win1 = 1; //дл€ Bicolor
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
 "                                    ѕќЅ≈ƒј!!!\n\n\n\n\n\n\n\n\n";
}

void doMove(int point1, int point2)
{
    Sleep(1000);
    step = step+2;
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
    startMenu(1);

    return 0;
}

