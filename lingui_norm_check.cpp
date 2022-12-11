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

string bad_wo[MX];
string bad_li[MX];

#define BAD_MAX_SIZE 4

string good_word_list[] = //대체어
{
    "", "", "", ""
};

string bad_word_list[] = //단어
{
    "니애미", "병신", "시발", "좆같다"
}; // 반드시 사전순으로 정렬된 데이터를 넣어야 한다.

string bad_word_report[] = //바르지 않은 이유
{
    "페륜+드립의 합성어인 패드립이며 '너희 엄마'라는 뜻입니다. /n 상대방의 부모님을 비하하는 표현은 게임에서는 물론이고 어디에서도 사용하면 안되겠죠?",
    "다리 병신, 손가락 병신 등의 용례에서 보듯이 장애인을 일컫는 말에서 기원되었습니다. /n 본래 장애인을 모욕하는 말이었기에 장애인에 대한 혐오표현이 될 수 있습니다. /n 당연하게도, 실제로 장애가 있는 사람은 특히 이 말을 불쾌하게 생각할 수 있으므로 사용을 자제해야 합니다.",
    "원래 '네 어머니와 씹을 할 놈'을 줄인 말이며, 모계사회였던 오랑캐 여진족을 비하하는 의미입니다. /n 즉, '여진족처럼 천륜을 모르는 놈'이라는 뜻입니다. /n (네 어머니와 성관계를 가지는 놈들 -> 니미씨팔놈 -> 씨팔놈 -> 씨팔, 시발, 시발) /n 특정한 대상을 비하하며, 좋은 의미가 아닌 부적절한 단어를 사용하지 않는것이 좋습니다.",
    "사물이 몹시 마음에 안 들거나 보기에 싫다는 의미로, 더불어 남성의 성기같다를 속되게 말하는 단어입니다. /n 좋은 의미도 아닐 뿐더러 특정 대상을 속되게 말하는 표현을 사용하지 않는게 좋겠죠?",
};

int bad_no;

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

void bad_word2(Queue* q) //비속어판별
{
    string tmp = sentence;
    int prev = 0;
    int cur;
    cur = tmp.find(' ');
    while(cur != string::npos)
    {
        int chk = 0;
        string substring = tmp.substr(prev, cur - prev);

        chk = bad_list(q, substring);

        if(chk)
        {
            chk_sentence = chk_sentence + " [(" + to_string(q->rear + 1) + ")" + substring + "]";
            good_sentence = good_sentence + " " + good_word_list[bad_no];
        }
        else
        {
            chk_sentence = chk_sentence + " " + substring;
            good_sentence = good_sentence + " " + substring;
        }

        prev = cur + 1;
        cur = tmp.find(' ', prev);
    }
    int chk = 0;
    string substring = tmp.substr(prev, cur - prev);
    chk = bad_list(q, substring);
    if(chk)
    {
        chk_sentence = chk_sentence + " [(" + to_string(q->rear + 1) + ")" + substring + "]";
        good_sentence = good_sentence + " " + good_word_list[bad_no];
    }
    else
    {
        chk_sentence = chk_sentence + " " + substring;
        good_sentence = good_sentence + " " + substring;
    }
}

int bad_list(Queue *q, string sliced_Str) // chk_sentence.c_str()
{
    int found = 0;
    int i = BAD_MAX_SIZE;

    int fir = 0, lst = i - 1;

    while(fir <= lst)
    {
        int mid = (fir + lst) / 2;
        if(strcmp(sliced_Str.c_str(), bad_word_list[mid].c_str()) == 1) fir = mid + 1;
        else if(strcmp(sliced_Str.c_str(), bad_word_list[mid].c_str()) == -1) lst = mid - 1;
        else
        {
            bad_no = mid;
            found = 1;
            push(q, sliced_Str, bad_word_report[mid]);
            break;
        }
    }
    return found;
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