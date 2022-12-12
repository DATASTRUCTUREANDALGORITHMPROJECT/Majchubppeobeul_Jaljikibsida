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

string sel1 = "��";
string sel2 = "��";

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

void gotoxy(int x, int y); // ��ǥ �̵�

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
    "�ƴ�", "�Ǿ���", "����(������)", "����", "���ڴ��"
};

string wrong_word_list[] =
{
    "���", "�ž���", "��������", "����", "���ڴ��"
}; // �ݵ�� ���������� ���ĵ� �����͸� �־�� �Ѵ�.

string wrong_word_report[] =
{
    "'��'�� '��'�� ���� ȥ���Ͽ� ���̴� ��찡 �ֽ��ϴ�.\n '��'�� '�Ǿ�'�� �ظ��̹Ƿ�, '�Ǿ�'�� ǥ������ �� ������� ������ '��'��,\n ����ϸ� '��'�� ǥ���մϴ�.", // ���
    "'��'�� '��'�� ���� ȥ���Ͽ� ���̴� ��찡 �ֽ��ϴ�.\n '��'�� '�Ǿ�'�� �ظ��̹Ƿ�, '�Ǿ�'�� ǥ������ �� ������� ������ '��'��,\n ����ϸ� '��'�� ǥ���մϴ�.", // �ž���
    "'�������' Ȥ�� '�ε巯���� ����.'�� �ǹ��ϴ� �ܾ�� '����' Ȥ�� '������'�� ���ñ� �ٶ��ϴ�.", // ��������
    "'������'�� �پ�� ���� '����'��, �߸��� ǥ���̴� '����'�� ���ñ� �ٶ��ϴ�.", // ����
    "'�ڱ� �������'�� ���ϴ� �ܾ�� '���ڴ��'�� ���ñ� �ٶ��ϴ�.", // ���ڴ��
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

string good_word_list[] = //��ü��
{
    "", "", "", ""
};

string bad_word_list[] = //�ܾ�
{
    "�Ͼֹ�", "����", "�ù�", "������"
}; // �ݵ�� ���������� ���ĵ� �����͸� �־�� �Ѵ�.

string bad_word_report[] = //�ٸ��� ���� ����
{
    "�з�+�帳�� �ռ����� �е帳�̸� '���� ����'��� ���Դϴ�. \n ������ �θ���� �����ϴ� ǥ���� ���ӿ����� �����̰� ��𿡼��� ����ϸ� �� �ǰ���?",
    "�ٸ� ����, �հ��� ���� ���� ��ʿ��� ������ ������� ���´� ������ ����Ǿ����ϴ�. \n ���� ������� ����ϴ� ���̾��⿡ ����ο� ���� ���� ǥ���� �� �� �ֽ��ϴ�. \n �翬�ϰԵ�, ������ ��ְ� �ִ� ����� Ư�� �� ���� �����ϰ� ������ �� �����Ƿ� ����� �����ؾ� �մϴ�.",
    "���� '�� ��ӴϿ� ���� �� ��'�� ���� ���̸�, ����ȸ���� ����ĳ �������� �����ϴ� �ǹ��Դϴ�. \n ��, '������ó�� õ���� �𸣴� ��'�̶�� ���Դϴ�. \n (�� ��ӴϿ� �����踦 ������ ��� -> �Ϲ̾��ȳ� -> ���ȳ� -> ����, �ù�, �ù�) \n Ư���� ����� �����ϸ�, ���� �ǹ̰� �ƴ� �������� �ܾ ������� �ʴ� ���� �����ϴ�.",
    "�繰�� ���� ������ �� ��ų� ���⿡ �ȴٴ� �ǹ̷�, ���Ҿ� ������ ���ⰰ�ٸ� �ӵǰ� ���ϴ� �ܾ��Դϴ�. \n ���� �ǹ̵� �ƴ� �Ӵ��� Ư�� ����� �ӵǰ� ���ϴ� ǥ���� ������� �ʴ°� ������?",
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
        if(sel1 == "��") bad_word(q);
        else speller(q);
        result(q);
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
    pos_s = 4;
    cout << "�� �Ӿ� �˻� ��";
}

void spe()
{
    pos_s = 3;
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

void bad_word(Queue *q)
{
    system("cls");
    logo(2);
    cout << endl << endl << endl;
    cout << endl << "      �Է��Ͻ� ������ �Է��� �ּ���." << endl << endl << "      (���� ��ȣ ���� �ۼ�)";
    cout << endl << endl;
    cout << endl << "       �� ";
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
    cout << endl << "      �Է��Ͻ� ������ �Է��� �ּ���." << endl << endl << "      (���� ��ȣ ���� �ۼ�)";
    cout << endl << endl;
    cout << endl << "       �� ";
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
        cout << "  �����ǰų� ��Ÿ�� �ִ� ������ �����ϴ�." << endl << endl;
        cout << "  �ۼ��Ͻ� ����: " << sentence << endl;
    }
    else
    {
        int i = 1;
        if(pos_s == 3) cout << "  :: ����� ������ " << q->rear + 1 << "�� �߰��Ͽ����ϴ� ::" << endl << endl;
        else cout << "  :: �������� ǥ���� " << q->rear + 1 << "�� �߰��Ͽ����ϴ� ::" << endl << endl;
        cout << "  �ۼ��Ͻ� ����: " << chk_sentence << endl;
        while(!is_emp(q))
        {
            q->frnt++;
            cout << endl << "  " << "(" << i++ << ") " << pop(q, wrong_wo) << ": " << pop(q, wrong_li) << endl;
        }
        if(pos_s == 3) cout << endl << endl << "  �ٸ� ����: " << correct_sentence;
        else cout << endl << endl << "  �ٸ� ����: " << good_sentence;
    }
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
