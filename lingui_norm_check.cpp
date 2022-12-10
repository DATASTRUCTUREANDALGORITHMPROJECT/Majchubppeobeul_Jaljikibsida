#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <string.h>

using namespace std;

void logo(int pos);

void start();
void select();
void go_sel();

string sel1 = "��";
string sel2 = "��";

void bad_word();
void bw();

void speller();
void spe();

string sentence;

void loading(int get);
void go_load();

void res();
void result();

int report_cnt = 0;
string ret;
int retry = 0;

void gotoxy(int x, int y);

int main()
{

    do {
        system("cls");
        select();
        if(sel1 == "��") bad_word();
        else speller();
        result();
    } while(retry);

    return 0;
}

void logo(int pos) // �⺻ Ʋ
{
    cout << "  ����������������������������������������" << endl;
    cout << "  �� � �Թ� �˻�� ��" << endl;
    cout << "  ����������������������������������������" << endl;
    cout << endl;
    for(int i=0; i<31; i++)
        if(i==15)
        {
            switch(pos) // ���� ���������� ���� �޶���
            {
                case 1: start(); break;
                case 2: bw(); break;
                case 3: spe(); break;
                case 4: res(); break;
            }
        }
        else cout << "��";
}

void start()
{
    cout << "�� �˻� ��� ���� ��";
}

void bw()
{
    cout << "�� �Ӿ� �˻� ��";
}

void spe()
{
    cout << "�� ����� �˻� ��";
}

void res()
{
    cout << "�� �˻� ��� ��";
}

void select()
{
    logo(1);
    cout << endl << endl << endl;
    cout << endl << "   ���ʰ� ������ ����Ű�� ���� ������ �ּ���." << endl << endl;
    cout << "       " << sel1 << "[�Ӿ� �˻�]";
    cout << "       ";
    cout << sel2 << "[����� �˻�]";
    cout << endl << endl;
    cout << endl << endl;
    for(int i=0; i<48; i++) cout << "��";
    cout << endl << endl;
    cout << "     �� �Ϸ�Ǿ����� Space bar�� ���� �ּ���!";
    go_sel();
}

void go_sel()
{
    while(1)
    {
        if(GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            sel1 = "��";
            sel2 = "��";
            gotoxy(7, 10);
            cout << "��";
            gotoxy(26, 10);
            cout << "��";
        }
        if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            sel1 = "��";
            sel2 = "��";
            gotoxy(7, 10);
            cout << "��";
            gotoxy(26, 10);
            cout << "��";
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000) return;
    }
}

void bad_word()
{
    system("cls");
    logo(2);
    cout << endl << endl << endl;
    cout << endl << "      �Է��Ͻ� ������ �Է��� �ּ���.";
    cout << endl << endl;
    cout << endl << "       �� ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(2);
    // �������� �ܾ ������ �˻�
}

void speller()
{
    system("cls");
    logo(3);
    cout << endl << endl << endl;
    cout << endl << "      �Է��Ͻ� ������ �Է��� �ּ���.";
    cout << endl << endl;
    cout << endl << "       �� ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(3);
    // ������ ���� ���� �κ��� ã�� �˻�
}

void loading(int get)
{
    system("cls");
    logo(get);
    cout << endl << endl << endl << endl;
    cout << "     �˻� ���Դϴ�, ��ø� ��ٷ� �ּ���... " << endl << endl << "                ";
    for(int j=0; j<10; j++) cout << "��";
    cout << " 0%";
    Sleep(100);
    go_load();
}

void go_load()
{
    int i=0;
    while(1)
    {
        gotoxy(16 + i++, 10);
        cout << "��";
        gotoxy(26, 10);
        printf(" %d%%", i*10);
        Sleep(100 + 10*i);
        if(i==10) break;
    }
}

void result()
{
    system("cls");
    logo(4);
    cout << endl << endl << endl << endl;
    if(!report_cnt) cout << "  �����ǰų� ��Ÿ�� �ִ� ������ �����ϴ�.";
    cout << endl << endl;
    cout << "  �ٽ� ����Ͻðڽ��ϱ�?(�� �ƴϸ� �ƴϿ�θ� ����Ͻñ� �ٶ��ϴ�)" << endl << endl;
    cout << " �� ";
    getline(cin, ret);
    if(ret == "��") retry = 1;
    else
    {
        system("cls");
        cout << "���α׷��� �����մϴ�.";
        retry = 0;
    }
    cout << endl;
    for(int i=0; i<43; i++) cout << "��";
}

void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
