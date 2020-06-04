#include <iostream>
#include <windows.h>
#include "ctime"
#include "conio.h"
#include <string>
#include <cmath>

void start();//��������
void startMenu(int switcher);//����� ��������(������, ��������)
void rules();//�������
void typePlay(int switcher);//����� ���� ����
void enterSize();//���� ���������� ������
void play();//�������� ������� ��� ����
int getLast(int i);//���������� ����� ���������� ����� �� ������ i
void draw(int up);//������ ������� ����
void drawData(int data);//������ �����
int checkWin();//��������� ��������� �� ������
void Win();//������!
void moveTover(int amount, int point1, int point2, int temp);//������� ����� (� �������� ��� ������������ ����)
void doMove(int point1, int point2);//������� �����
void moveToverBicolor(int amount, int point1, int point2, int temp);//�������� ��� ���������� ����
void BildBicolor(int amount, int point1, int point2, int temp);//������ ������ ����� �� ���� �������
void DestroyBicolor(int amount, int point1, int point2, int temp);//��������� ������ ����� �� ��� ����������
void MTM_1(int n, int i, int s, int d);//���������� moveToverMagnit
void MTM_2(int n, int s, int d, int i);//����� ��� ��������� ��������� �����
bool checkColor(int i);//��������� ������ ����� ���� (��� ���������� �����)
bool checkMove(int i, int k);//���������, ���������� �� ���

const int NotUsed = system( "color E8" );//���� ���� � ����
short watchOrPlay = 1; //��� �� ����� ������? 1-������, 2-��������
short tPlay = 1; //����� ��� ����? 1-������������, 2-�����������, 3-���������
short allSize = 3;//���-�� ������
short step = 0;//����� ����
bool flag1 = 0;//���� ������ ����, ������ ���� (1,2 ��� 3) � �������
bool flag2 = 0;
bool flag3 = 0;

//��� ��������� ������
std::string Classic[10] = {"        |        ", "        O        ", "       OOO       ", "      OOOOO      ", "     OOOOOOO     ",
                    "    OOOOOOOOO    ", "   OOOOOOOOOOO   ", "  OOOOOOOOOOOOO  ", " OOOOOOOOOOOOOOO ", "OOOOOOOOOOOOOOOOO"};
std::string Bicolor[10] = {"        |        ", "        V        ", "       VVV       ", "      VVVVV      ", "     VVVVVVV     ",
                    "    VVVVVVVVV    ", "   VVVVVVVVVVV   ", "  VVVVVVVVVVVVV  ", " VVVVVVVVVVVVVVV ", "VVVVVVVVVVVVVVVVV"};
std::string Plus[10] = {"        |        ", "       |+|       ", "      |+++|      ", "     |+++++|     ", "    |+++++++|    ",
                    "   |+++++++++|   ", "  |+++++++++++|  ", " |+++++++++++++| ", "|+++++++++++++++|", "|+++++++++++++++++|"};
std::string Minus[10] = {"        |        ", "       |-|       ", "      |---|      ", "     |-----|     ", "    |-------|    ",
                    "   |---------|   ", "  |-----------|  ", " |-------------| ", "|---------------|", "|-----------------|"};

//�������� ��������� - � ��� ��, ��� ���������� � �������
struct Hanoi_type {
    Hanoi_type(int s)//�����������
    : size1(s)//������ ������� �������
    , data1(new int[2*s+1])//������ �����
    , size2(s), size3(s)
    , data2(new int[2*s+1]), data3(new int[2*s+1])//������ � ������ ������
    {
        for (int i=0; i<=2*size1; ++i) data1[i] = 0;//���������� �������� ������ (��� ��������� �������)
        for (int i=0; i<=2*size1; ++i) data2[i] = 0;
        for (int i=0; i<=2*size1; ++i) data3[i] = 0;
    }

    Classic()//������ ����� ��� ������������ ����
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//��� ������ ����� �����, ��� �� ������
    }
    Bicolor()//��� �����������
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//�� ������ ������ ����� �������������,
        for (int i=2*allSize; i>=allSize; --i) data2[i] = -(i+1-allSize);//�� ������ - �������������
    }
    Magnit()//��� ���������
    {
        for (int i=2*allSize; i>=allSize; --i) data1[i] = i+1-allSize;//��� ������� ���� ������ - ��������� ������������
    }

    ~Hanoi_type() { //����������
        delete [] data1;
        delete [] data2;
        delete [] data3;
    }

    OnetoTwo() { //���������� ������� ���� � 1 ������ �� 2 (�� ����� ������� ������� �� ����� �������)
        int n_s = 0;//������ �����
        for (int i=0; i<=2*allSize; ++i) //������� ������� ����
            if (data1[i]!=0) {
                n_s = data1[i]; //���������� ������
                data1[i]=0; //������� � 1 ������
                break;
            }
        for (int i=2*allSize-1; i>=0; --i) //������� ������ � ����� �� ������� �����
            if (data2[i]==0)
                {data2[i] = n_s; break;} //��������� ��� ����

    }
    OnetoThree() { //����� � ����� - ����������
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


    int s; //�������, ��� ������� � ������ � ������� ����� �� ������������
    int size1;//�� ������������ ��������� ����
    int size2;//�� ����� �������, �� ����� ���������
    int size3;
    int * data1;//������-�������
    int * data2;
    int * data3;
};

Hanoi_type Hanoi(11);//������ ���������� ����� ���� ����� ������������� �������

void start()
{
    setlocale(0, "rus");//��������� (����� ������������ ������� �����)
    system("mode con cols=80 lines=20");//������� �������� ���� ������� 80 20
    system("title ��������� �����");//������� �������� ���� �������
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//��������� ������
    CONSOLE_CURSOR_INFO cursor = { 100, false };//����� �� 1 �� 100 ������ ������� � ���������; false\true - ���������
    SetConsoleCursorInfo(hCons, &cursor);//���������� �������� ���������� �������
    system("cls");//������� �������
    std::cout<<"\n\n\n\n\n\n\n\n"
 "                                  ���������\n\n"
 "                                    �����";
    Sleep(3000);//��������
}

void startMenu(int switcher)
{
    system("cls");//������� ������
    switch (switcher)//��������� ���� ������ �� ������
    {
    case 1:
        std::cout << "\n\n\n\n\n\n                                   < ������! >\n\n\n                                 �������� �������\n\n\n                                     �������";
        break;
    case 2:
        std::cout << "\n\n\n\n\n\n                                     ������!\n\n\n                               < �������� ������� >\n\n\n                                     �������";
        break;
    case 3:
        std::cout << "\n\n\n\n\n\n                                     ������!\n\n\n                                 �������� �������\n\n\n                                   < ������� >";
        break;
    }
    int choice = _getch(); //��������� ������
    if (choice == 224 || choice == 0)//����� �������
        choice = _getch();
    if (choice == 72)//�����
        if (switcher != 1)
            startMenu(switcher - 1);
        else
            startMenu(3);
    if (choice == 80)//����
        if (switcher != 3)
            startMenu(switcher + 1);
        else
            startMenu(1);
    if (choice == 13 || choice == 32) //������
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
    std::cout << " ���������: ESCAPE\n";
    std::cout << " ����� ����� �������";
    int controller = _getch();
    if (controller == 27)//���� Escape
        startMenu(1);
}

void typePlay(int switcher)
{
    system("cls");
    switch (switcher)
    {
    case 1:
        std::cout << "\n\n\n\n\n\n                                 < ������������ >\n\n\n                                   �����������\n\n\n                                    ���������";
        break;
    case 2:
        std::cout << "\n\n\n\n\n\n                                   ������������\n\n\n                                 < ����������� >\n\n\n                                    ���������";
        break;
    case 3:
        std::cout << "\n\n\n\n\n\n                                   ������������\n\n\n                                   �����������\n\n\n                                  < ��������� >";
        break;
    }
    int choice = _getch(); //��������� ������
    if (choice == 27)
        startMenu(1);
    if (choice == 224 || choice == 0)//����� �������
        choice = _getch();
    if (choice == 72)//�����
        if (switcher != 1)
            typePlay(switcher - 1);
        else
            typePlay(3);
    if (choice == 80)//����
        if (switcher != 3)
            typePlay(switcher + 1);
        else
            typePlay(1);
    if (choice == 13 || choice == 32) //������
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
    std::cout << "\n\n                      ���������� ������?" <<std::endl;
    std::cout << "\n                    -> ";
    std::cin >> ::allSize;

    ::Hanoi_type Hanoi(allSize);//������������� ��� ����� (�� �������, ��� ��� �����)

    if (tPlay == 1) ::Hanoi.Classic();//���� ��� ���� ������������, �� � ��������� ����������� � �.�.
    if (tPlay == 2) ::Hanoi.Bicolor();
    if (tPlay == 3) ::Hanoi.Magnit();
    draw(0);//������ ����, ��������������� ����� ��������� �����
}

bool checkMove(int i, int k) //i - ���� �����, k - ������
{
    int one = Hanoi.data1[getLast(1)]; int two = Hanoi.data2[getLast(2)]; int three = Hanoi.data3[getLast(3)];//������� �����
//���������, ��� ������ ������ ������� ���� �� ������� (������ ���� ������� = 0),
//������ �������� ����� � ��� ��������� ���� - ����������
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

void play()//����������, ���� ������
{
    ::step++;//������� ����

    int choice = _getch();
    if (choice == 27)//���� esc
        startMenu(1);

    if (choice == 49) {//���� ������� ����� 1
        if (!flag1 && !flag2 && !flag3) {//���� ����� � ������� ���
            ::flag1 = 1;//��������� ���� � 1 �����
            if (tPlay == 3) Hanoi.data1[getLast(1)] = -Hanoi.data1[getLast(1)];//���� ���� ��������� - ������ ����������
            draw(1);//������ �������� ����
            choice = _getch();
        }
        else {
            if (flag1) {//���� �� ����� ��� ������ ���� �� 1 �����
                ::flag1 = 0;//�������� �������
                if (tPlay == 3) Hanoi.data1[getLast(1)] = -Hanoi.data1[getLast(1)];//���������� ����������
                draw(0);//������ ��������� ����
                choice = _getch();
            }
            //���� �� ����� ��� ������ ���� �� 2 ����� � �� �� ����� ���� ������ �� 1 - ��������
            if (flag2 && !checkMove(1, 2)) {system("color E4"); std::cerr << "\n��� ������!!!"; play();}
            //���� ����� - ��������
            if (flag2 && checkMove(1, 2)) {
                ::flag2 = 0;
                Hanoi.TwotoOne();
                draw(0);
                choice = _getch();
            }
            //����� �� ����������
            if (flag3 && !checkMove(1, 3)) {system("color E4"); std::cerr << "\n��� ������!!!"; play();}
            if (flag3 && checkMove(1, 3)) {
                ::flag3 = 0;
                Hanoi.ThreetoOne();
                draw(0);
                choice = _getch();
            }
        }
    }
    if (choice == 50) { //���� ������ 2
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
            if (flag1 && !checkMove(2, 1)) {system("color E4"); std::cerr << "\n��� ������!!!"; play();}
            if (flag1 && checkMove(2, 1)) {
                ::flag1 = 0;
                Hanoi.OnetoTwo();
                draw(0);
                choice = _getch();
            }

            if (flag3 && !checkMove(2, 3)) {system("color E4"); std::cerr << "\n��� ������!!!"; play();}
            if (flag3 && checkMove(2, 3)) {
                ::flag3 = 0;
                Hanoi.ThreetoTwo();
                draw(0);
                choice = _getch();
            }
        }
    }
    if (choice == 51) { //���� ������ 3
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
            if (flag1 && !checkMove(3, 1)) {system("color E4"); std::cerr << "\n��� ������!!!"; play();}
            if (flag1 && checkMove(3, 1)) {
                ::flag1 = 0;
                Hanoi.OnetoThree();
                draw(0);
                choice = _getch();
            }

            if (flag2 && !checkMove(3, 2)) {system("color E4"); std::cerr << "\n��� ������!!!"; play();}
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

int getLast(int i)//i -����� ������
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


void draw(int up)//���� up=0 - �� ���� �� ������, ���� 1 - ������ � 1 ����� � �.�.
{
    system("cls");
    if (tPlay != 1 && allSize>6) system("mode con cols=80 lines=27");//����������� ����, ���� �� ������
    system( "color E8" );
    std::cout << " ���������� �����: " << step/2 << "                                ����� ����� - \"1\", \"2\", \"3\"" << std::endl;
    std::cout << "\n\n";

    int up_now = 0;//��, ��� ������� ������ (����� ��� ���������� ���������)
    //������ �������� �����
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
    //������ �������������� ������� ������ ��� ����������� ���� (������ ��� �� �����)
    int i;
    if (tPlay == 2) i = 0;
    else i = allSize;
    //������ �� �������� �����
    for (i; i<2*allSize; ++i)
    {
        std::cout << "    ";//4
        if (up_now == Hanoi.data1[i])//���� ���� ������ - ������ �� ��� ����� �������
            std::cout << Classic[0];
        else
            drawData(Hanoi.data1[i]);//����� ������ ��� ������

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

        //��� ��������� ������������ ������(������) ����� �����

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

    if (checkWin()) Win();//���� �������� �� ��������

    if (watchOrPlay == 1) play();//���� ������ �� ������
    //���� �������, �� �������� ���������
    else if (step == 0 && tPlay == 1) DestroyBicolor(allSize, 1, 2, 3);
    else if (step == 0 && tPlay == 2) moveToverBicolor(allSize, 2, 3, 1);
    else if (step == 0 && tPlay == 3) MTM_2(allSize, 1, 3, 2);

}

void drawData(int data)//������ ������ ������ ���� ������. Data - �� ������
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

int checkWin()//��� ����������� � ��������� ���� ������� ���������� ������ �� ��������, ��� ����������� - �� ����� � ����������
{
    int flag_win2 = 1;
    int flag_win3 = 1;
    int flag_b_win1 = 1; //��� Bicolor
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
 "                                    ������!!!\n\n\n\n\n\n\n\n\n";
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

void moveToverBicolor(int amount, int point1, int point2, int temp) //�� �������� :((((((
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

