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

void gotoxy(int x, int y); // 좌표 이동

void logo(int pos);

void start();
void select();
void go_sel();

string sel1 = "";
string sel2 = "";

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

string bad_wo[MX];
string bad_li[MX];

#define BAD_MAX_SIZE 4

string good_word_list[] = //泥댁
{
    "", "", "", ""
};

string bad_word_list[] = //⑥
{
    "誘", "蹂", "諛", "醫媛"
}; // 諛 ъ쇰 ��щ 곗댄곕� ｌ댁 .

string bad_word_report[] = //諛瑜댁  댁
{
    "瑜+由쎌 ⑹깆댁 ⑤由쎌대ŉ ' 留'쇰 살. /n 諛⑹ 遺紐⑤ 鍮  寃 臾쇰�닿� 대 ъ⑺硫 寃二?",
    "ㅻ━ 蹂, 媛 蹂 깆 ⑸ 蹂대� μ몄 쇱뺀 留 湲곗듬. /n 蹂몃 μ몄 紐⑥ 留댁湲곗 μ몄  ㅽ   듬. /n 뱀고寃, ㅼ濡 μ媛  щ 뱁  留 遺苡寃 媛  쇰濡 ъ⑹ �댁 ⑸.",
    " ' 대㉧ 뱀  ' 以 留대ŉ, 紐④ы ㅻ罹 ъ議깆 鍮 誘몄. /n 利, 'ъ議깆 泥瑜 紐⑤Ⅴ '대쇰 살. /n ( 대㉧ 깃怨瑜 媛吏  -> 誘몄⑦ -> ⑦ -> ⑦, 諛, 諛) /n 뱀  鍮硫, 醫 誘멸  遺�� ⑥대� ъ⑺吏 寃 醫듬.",
    "щЪ 紐뱀 留  ㅺ굅 蹂닿린 ルㅻ 誘몃, 遺 ⑥깆 깃린媛ㅻ� 寃 留 ⑥댁. /n 醫 誘몃  肉 뱀  寃 留  ъ⑺吏 寃 醫寃二?",
};

int bad_no;

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
    "榮", "돼었다", "워낙에도", "웬지", "지멋대로"
}; // 반드시 사전순으로 정렬된 데이터를 넣어야 한다.

string wrong_word_report[] =
{
    "'돼'와 '되'를 자주 혼동하여 쓰이는 경우가 있습니다.\n '돼'는 '되어'의 준말이므로, '되어'로 표현했을 때 어색하지 않으면 '돼'로,\n 어색하면 '되'로 표기합니다.", // 榮
    "'돼'와 '되'를 자주 혼동하여 쓰이는 경우가 있습니다.\n '돼'는 '되어'의 준말이므로, '되어'로 표현했을 때 어색하지 않으면 '돼'로,\n 어색하면 '되'로 표기합니다.", // 돼었다
    "'본디부터' 혹은 '두드러지게 아주.'를 의미하는 단어는 '워낙' 혹은 '워낙에'로 쓰시기 바랍니다.", // 워낙에도
    "'왜인지'가 줄어든 말은 '왠지'로, 잘못된 표현이니 '왠지'로 쓰시기 바랍니다.", // 웬지
    "'자기 마음대로'를 뜻하는 단어는 '제멋대로'로 쓰시기 바랍니다.", // 지멋대로
};

string chk_sentence;

int wrong_no;

string correct_sentence;

void initQueue(Queue* q);

int main()
{
    Queue *q = new Queue;
    Sleep(1000);
    PlaySound(TEXT("bgm.wav"), NULL, SND_ASYNC);
    do {
        initQueue(q);
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

void logo(int pos) // 湲곕낯 
{
    cout << "  " << endl;
    cout << "   대Ц 洹踰 寃ш린 " << endl;
    cout << "  " << endl;
    cout << endl;
    for(int i=0; i<31; i++)
        if(i==15)
        {
            switch(pos) // 臾댁 몄 곕 щ쇱
            {
                case 1: start(); break;
                case 2: bw(); break;
                case 3: spe(); break;
                case 4: res(); break;
            }
        }
        else cout << "";
}

void start()
{
    cout << " 寃 諛⑹  ";
}

void bw()
{
    cout << "  寃 ";
}

void spe()
{
    cout << " 留異ㅻ 寃 ";
}

void res()
{
    cout << " 寃 寃곌낵 ";
}

void select()
{
    logo(1);
    cout << endl << endl << endl;
    cout << endl << "   쇱そ怨 ㅻⅨ履 諛⑺νㅻ�   二쇱몄." << endl << endl;
    cout << "       " << sel1 << "[ 寃]";
    cout << "       ";
    cout << sel2 << "[留異ㅻ 寃]";
    cout << endl << endl;
    cout << endl << endl;
    for(int i=0; i<48; i++) cout << "";
    cout << endl << endl;
    cout << "      猷쇰㈃ Space bar瑜  二쇱몄!";
    go_sel();
}

void go_sel()
{
    while(1)
    {
        if(GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            sel1 = "";
            sel2 = "";
            gotoxy(7, 10);
            cout << "";
            gotoxy(26, 10);
            cout << "";
        }
        if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            sel1 = "";
            sel2 = "";
            gotoxy(7, 10);
            cout << "";
            gotoxy(26, 10);
            cout << "";
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
    cout << endl << "        ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(2);
    // 遺�� ⑥대� 諛痍 寃
}

void bad_word2(Queue* q) //鍮댄蹂
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
    cout << endl << "        ";
    getline(cin, sentence);
    cout << endl << endl;
    loading(3);
    // 臾몃 留吏  遺遺 李얠 寃
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
    cout << "     寃 以, 留 湲곕ㅻ 二쇱몄... " << endl << endl << "                ";
    for(int j=0; j<10; j++) cout << "";
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
        cout << "";
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
    cout << "  ㅼ ъ⑺寃듬源?( 硫 濡留 듯湲 諛)" << endl << endl;
    cout << "  ";
    getline(cin, ret);
    if(ret == "") retry = 1;
    else
    {
        system("cls");
        cout << "濡洹몃⑥ 醫猷⑸.";
        retry = 0;
    }
    cout << endl;
    for(int i=0; i<43; i++) cout << "";
}

void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}