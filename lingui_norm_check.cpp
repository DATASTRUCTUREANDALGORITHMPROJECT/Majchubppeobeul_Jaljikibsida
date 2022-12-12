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

void bad_word(Queue *q);
void bad_word2(Queue* q);
void bw();
int bad_list(Queue *q, string sliced_Str);

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

#define WRONG_MAX_SIZE 5

string correct_word_list[] =
{
    "됐다", "되었다", "워낙(워낙에)", "왠지", "제멋대로"
};

string wrong_word_list[] =
{
    "됬다", "돼었다", "워낙에도", "웬지", "지멋대로"
}; // 반드시 사전순으로 정렬된 데이터를 넣어야 한다.

string wrong_word_report[] =
{
    "'돼'와 '되'를 자주 혼동하여 쓰이는 경우가 있습니다.\n '돼'는 '되어'의 준말이므로, '되어'로 표현했을 때 어색하지 않으면 '돼'로,\n 어색하면 '되'로 표기합니다.", // 됬다
    "'돼'와 '되'를 자주 혼동하여 쓰이는 경우가 있습니다.\n '돼'는 '되어'의 준말이므로, '되어'로 표현했을 때 어색하지 않으면 '돼'로,\n 어색하면 '되'로 표기합니다.", // 돼었다
    "'본디부터' 혹은 '두드러지게 아주.'를 의미하는 단어는 '워낙' 혹은 '워낙에'로 쓰시기 바랍니다.", // 워낙에도
    "'왜인지'가 줄어든 말은 '왠지'로, 잘못된 표현이니 '왠지'로 쓰시기 바랍니다.", // 웬지
    "'자기 마음대로'를 뜻하는 단어는 '제멋대로'로 쓰시기 바랍니다.", // 지멋대로
};

string chk_sentence;

int wrong_no;

string correct_sentence;

void initQueue(Queue* q);

int wrong_list(Queue *q, string sliced_Str);

string bad_wo[MX];
string bad_li[MX];

#define BAD_MAX_SIZE 4

int pos_s;

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
    "패륜+드립의 합성어인 패드립이며 '너희 엄마'라는 뜻입니다. \n 상대방의 부모님을 비하하는 표현은 게임에서는 물론이고 어디에서도 사용하면 안 되겠죠?",
    "다리 병신, 손가락 병신 등의 용례에서 보듯이 장애인을 일컫는 말에서 기원되었습니다. \n 본래 장애인을 모욕하는 말이었기에 장애인에 대한 혐오 표현이 될 수 있습니다. \n 당연하게도, 실제로 장애가 있는 사람은 특히 이 말을 불쾌하게 생각할 수 있으므로 사용을 자제해야 합니다.",
    "원래 '네 어머니와 씹을 할 놈'을 줄인 말이며, 모계사회였던 오랑캐 여진족을 비하하는 의미입니다. \n 즉, '여진족처럼 천륜을 모르는 놈'이라는 뜻입니다. \n (네 어머니와 성관계를 가지는 놈들 -> 니미씨팔놈 -> 씨팔놈 -> 씨팔, 시발, 시발) \n 특정한 대상을 비하하며, 좋은 의미가 아닌 부적절한 단어를 사용하지 않는 것이 좋습니다.",
    "사물이 몹시 마음에 안 들거나 보기에 싫다는 의미로, 더불어 남성의 성기같다를 속되게 말하는 단어입니다. \n 좋은 의미도 아닐 뿐더러 특정 대상을 속되게 말하는 표현을 사용하지 않는게 좋겠죠?",
};

string good_sentence;

int bad_no;

int main()
{
    Queue *q = new Queue;
    Sleep(1000);
    PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC);
    do {
        initQueue(q);
        good_sentence = "";
        correct_sentence = "";
        chk_sentence = "";
        q->rear = -1;
        system("cls");
        select();
        if(sel1 == "●") bad_word(q);
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
    pos_s = 4;
    cout << "○ 속어 검사 ○";
}

void spe()
{
    pos_s = 3;
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

void bad_word(Queue *q)
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
    bad_word2(q);
}

void bad_word2(Queue* q)
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
        if(i==10)
        {
            Sleep(1000);
            break;
        }
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
        if(pos_s == 3) cout << "  :: 맞춤법 오류를 " << q->rear + 1 << "개 발견하였습니다 ::" << endl << endl;
        else cout << "  :: 부적절한 표현을 " << q->rear + 1 << "개 발견하였습니다 ::" << endl << endl;
        cout << "  작성하신 문장: " << chk_sentence << endl;
        while(!is_emp(q))
        {
            q->frnt++;
            cout << endl << "  " << "(" << i++ << ") " << pop(q, wrong_wo) << ": " << pop(q, wrong_li) << endl;
        }
        if(pos_s == 3) cout << endl << endl << "  바른 문장: " << correct_sentence;
        else cout << endl << endl << "  바른 문장: " << good_sentence;
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
