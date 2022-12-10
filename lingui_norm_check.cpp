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

string sel1 = "●";
string sel2 = "○";

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
        if(sel1 == "●") bad_word();
        else speller();
        result();
    } while(retry);

    return 0;
}

void logo(int pos) // 기본 틀
{
    cout << "  ━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "  ◑ 어문 규범 검사기 ◐" << endl;
    cout << "  ━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << endl;
    for(int i=0; i<31; i++)
        if(i==15)
        {
            switch(pos) // 무슨 상태인지에 따라 달라짐
            {
                case 1: start(); break;
                case 2: bw(); break;
                case 3: spe(); break;
                case 4: res(); break;
            }
        }
        else cout << "─";
}

void start()
{
    cout << "○ 검사 방식 선택 ○";
}

void bw()
{
    cout << "○ 속어 검사 ○";
}

void spe()
{
    cout << "○ 맞춤법 검사 ○";
}

void res()
{
    cout << "○ 검사 결과 ○";
}

void select()
{
    logo(1);
    cout << endl << endl << endl;
    cout << endl << "   왼쪽과 오른쪽 방향키를 눌러 선택해 주세요." << endl << endl;
    cout << "       " << sel1 << "[속어 검사]";
    cout << "       ";
    cout << sel2 << "[맞춤법 검사]";
    cout << endl << endl;
    cout << endl << endl;
    for(int i=0; i<48; i++) cout << "─";
    cout << endl << endl;
    cout << "     ※ 완료되었으면 Space bar를 눌러 주세요!";
    go_sel();
}

void go_sel()
{
    while(1)
    {
        if(GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            sel1 = "●";
            sel2 = "○";
            gotoxy(7, 10);
            cout << "●";
            gotoxy(26, 10);
            cout << "○";
        }
        if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            sel1 = "○";
            sel2 = "●";
            gotoxy(7, 10);
            cout << "○";
            gotoxy(26, 10);
            cout << "●";
        }
        if(GetAsyncKeyState(VK_SPACE) & 0x8000) return;
    }
}

void bad_word()
{
    system("cls");
    logo(2);
    cout << endl << endl << endl;
    cout << endl << "      입력하실 문장을 입력해 주세요.";
    cout << endl << endl;
    cout << endl << "       ▷ ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(2);
    // 부적절한 단어를 발췌해 검색
}

void speller()
{
    system("cls");
    logo(3);
    cout << endl << endl << endl;
    cout << endl << "      입력하실 문장을 입력해 주세요.";
    cout << endl << endl;
    cout << endl << "       ▷ ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(3);
    // 문법상 맞지 않은 부분을 찾아 검색
}

void loading(int get)
{
    system("cls");
    logo(get);
    cout << endl << endl << endl << endl;
    cout << "     검사 중입니다, 잠시만 기다려 주세요... " << endl << endl << "                ";
    for(int j=0; j<10; j++) cout << "□";
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
        cout << "■";
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
    if(!report_cnt) cout << "  문제되거나 오타가 있는 내용이 없습니다.";
    cout << endl << endl;
    cout << "  다시 사용하시겠습니까?(예 아니면 아니요로만 대답하시기 바랍니다)" << endl << endl;
    cout << " ▷ ";
    getline(cin, ret);
    if(ret == "예") retry = 1;
    else
    {
        system("cls");
        cout << "프로그램을 종료합니다.";
        retry = 0;
    }
    cout << endl;
    for(int i=0; i<43; i++) cout << "─";
}

void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
