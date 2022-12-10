#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <string.h>
#pragma comment(lib,"winmm.lib")

using namespace std;

typedef struct {
    int frnt;
    int rear;
} Queue;

void logo(int pos);

void start();
void select();
void go_sel();

string sel1 = "●";
string sel2 = "○";

void bad_word();
void bw();

void speller(Queue* q);
void spe();

string sentence;

void loading(int get);
void go_load();

void res();
void result(Queue* q);

string ret;
int retry = 0;

void speller_check(Queue* q);
int wrong_list(Queue *q, string sliced_Str);

void gotoxy(int x, int y); // 좌표 이동

/* Stack Function And Piled String Array */

#define MX 1000

void push(Queue* q, string wrg_wo, string wrg_li);
string pop(Queue* q, string type);
int is_full(Queue* q);
int is_emp(Queue* q);

string wrong_wo[MX];
string wrong_li[MX];

#define WRONG_MAX_SIZE 2

string correct_word_list[] =
{
    "워낙(워낙에)", "제멋대로"
};

string wrong_word_list[] =
{
    "워낙에도", "지멋대로"
};

string wrong_word_report[] =
{
    "'본디부터' 혹은 '두드러지게 아주.'를 의미하는 단어는 '워낙' 혹은 '워낙에'로 쓰시기 바랍니다.",
    "'자기 마음대로'를 뜻하는 단어는 '제멋대로'로 쓰시기 바랍니다."
};

string chk_sentence;

int wrong_no;

string correct_sentence;

void initQueue(Queue* q);

int main()
{
    Queue *q = new Queue;
    Sleep(1000);
    PlaySound(TEXT("bgm.wav"),NULL,SND_ASYNC);
    do {
        initQueue(q);
        correct_sentence = "";
        chk_sentence = "";
        q->rear = -1;
        system("cls");
        select();
        if(sel1 == "●") bad_word();
        else speller(q);
        result(q);
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
    cout << endl << "      입력하실 문장을 입력해 주세요." << endl << endl << "      (문장 부호 없이 작성)";
    cout << endl << endl;
    cout << endl << "       ▷ ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(2);
    // 부적절한 단어를 발췌해 검색
}

void speller(Queue* q)
{
    system("cls");
    logo(3);
    cout << endl << endl << endl;
    cout << endl << "      입력하실 문장을 입력해 주세요." << endl << endl << "      (문장 부호 없이 작성)";
    cout << endl << endl;
    cout << endl << "       ▷ ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(3);
    speller_check(q);
}

void speller_check(Queue* q)
{
    string tmp = sentence;
    int prev = 0;
    int cur;
    cur = tmp.find(' ');
    while(cur != string::npos)
    {
        int chk = 0;
        string substring = tmp.substr(prev, cur - prev);

        chk = wrong_list(q, substring);

        if(chk)
        {
            chk_sentence = chk_sentence + " [(" + to_string(q->rear + 1) + ")" + substring + "]";
            correct_sentence = correct_sentence + " " + correct_word_list[wrong_no];
        }
        else
        {
            chk_sentence = chk_sentence + " " + substring;
            correct_sentence = correct_sentence + " " + substring;
        }

        prev = cur + 1;
        cur = tmp.find(' ', prev);
    }
    int chk = 0;
    string substring = tmp.substr(prev, cur - prev);
    chk = wrong_list(q, substring);
    if(chk)
    {
        chk_sentence = chk_sentence + " [(" + to_string(q->rear + 1) + ")" + substring + "]";
        correct_sentence = correct_sentence + " " + correct_word_list[wrong_no];
    }
    else
    {
        chk_sentence = chk_sentence + " " + substring;
        correct_sentence = correct_sentence + " " + substring;
    }
}

int wrong_list(Queue *q, string sliced_Str) // chk_sentence.c_str()
{
    int found = 0;
    int i = WRONG_MAX_SIZE;

    int fir = 0, lst = i - 1;

    while(fir <= lst)
    {
        int mid = (fir + lst) / 2;
        if(strcmp(sliced_Str.c_str(), wrong_word_list[mid].c_str()) == 1) fir = mid + 1;
        else if(strcmp(sliced_Str.c_str(), wrong_word_list[mid].c_str()) == -1) lst = mid - 1;
        else
        {
            wrong_no = mid;
            found = 1;
            push(q, sliced_Str, wrong_word_report[mid]);
            break;
        }
    }
    return found;
}

void initQueue(Queue* q)
{
    q -> frnt = -1;
    q -> rear = -1;
}

void push(Queue* q, string wrg_wo, string wrg_li)
{
    if(!is_full(q))
    {
        q->rear++;
        wrong_wo[q->rear] = wrg_wo;
        wrong_li[q->rear] = wrg_li;
    }
}

string pop(Queue* q, string type[])
{
    return type[q->frnt];
}

int is_full(Queue* q)
{
    return q->rear == MX - 1 ? 1 : 0;
}

int is_emp(Queue* q)
{
    return q->rear == q->frnt ? 1 : 0;
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

void result(Queue* q)
{
    system("cls");
    logo(4);
    cout << endl << endl << endl << endl;
    if(q->rear == -1)
    {
        cout << "  문제되거나 오타가 있는 내용이 없습니다." << endl << endl;
        cout << "  작성하신 문장: " << sentence << endl;
    }
    else
    {
        int i = 1;
        cout << "  :: 맞춤법 오류를 " << q->rear + 1 << "개 발견하였습니다 ::" << endl << endl;
        cout << "  작성하신 문장: " << chk_sentence << endl;
        while(!is_emp(q))
        {
            q->frnt++;
            cout << endl << "  " << "(" << i++ << ") " << pop(q, wrong_wo) << ": " << pop(q, wrong_li) << endl;
        }
        cout << endl << endl << "  바른 문장: " << correct_sentence;
    }
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
