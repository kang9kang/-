#include <iostream>
#include "LA.h"

using namespace std;

LA::LA(const char* s) :fin(s), line(1), num(0), fg(0), ch('\0')
{
    sin << fin.rdbuf();
    txt = sin.str();
    fin.close();
    fin.clear();
}

void LA::scan()
{
    int p = 0;

    //��ȡ��һ���ǿ��ַ�
    do {
        ch = txt[p++];
        if (ch == 10)
            line++;
    } while (ch == ' ' || ch == 10);
    cout << "line " << line << " :" << endl;

    while (ch != '\0') {
        while (ch == ' ' || ch == 10) {
            if (ch == 10) {
                line++;
                cout << "line " << line << " :" << endl;
            }
            ch = txt[p++];
        }

        //����'_'��ͷ�ı���
        if (ch == '_') {
            word += ch;
            ch = txt[p++];
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_') {
                fg = 2;
                word += ch;
                ch = txt[p++];
                while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_') {
                    word += ch;
                    ch = txt[p++];
                }
            }
            else {
                fg = -1;
                word += ch;
                ch = txt[p++];
                while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_') {
                    word += ch;
                    ch = txt[p++];
                }
            }
            switch (fg) {
            case -1: cout << "error: " << '<' << word << '>' << endl; break;
            case 2: cout << '<' << fg << ',' << word << '>' << endl; break;
            default: break;
            }
            word.clear();
            fg = 0;
        }

        //�������ֺ���ĸ��ͷ�ı���
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            fg = 1;
            word += ch;
            ch = txt[p++];
            while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_') {
                word += ch;
                ch = txt[p++];
            }
            for (int i = 0; i < 16; i++) {
                if (i == 15 && word != rsv_words[i]&&ch!='(')
                    fg++;
                if ( (word == rsv_words[i])||ch=='(') {
                    cout << '<' << fg << ',' << word << '>' << endl;
                    word.clear();
                    break;
                }
            }

            if (fg == 2)
                cout << '<' << fg << ',' << word << '>' << endl;
            word.clear();
            fg = 0;
        }

        //��������
        if (ch >= '0' && ch <= '9') {
            fg = 3;
            num = 10 * num + (ch - '0');
            ch = txt[p++];
            while (ch >= '0' && ch <= '9') {
                num = 10 * num + (ch - '0');
                ch = txt[p++];
            }
            cout << '<' << fg << ',' << num << '>' << endl;
            num = 0;
            fg = 0;
        }

        //�������
        switch (ch) {
            //���������
        case '+': 
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else if (txt[p] == '+') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '-': 
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else if (txt[p] == '-') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '*': 
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '/': 
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '%':
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '=':
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '<':
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '>':
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case '!':
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case'&':
            fg = 4;
            if (txt[p] == '&') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }
        case'|':
            fg = 4;
            if (txt[p] == '|') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << '<' << fg << ',' << word << '>' << endl;
                word.clear();
                break;
            }
            else {
                cout << '<' << fg << ',' << ch << '>' << endl;
                ch = txt[p++];
                break;
            }

            //����ָ���
        case ',': fg = 5; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case ';': fg = 5; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case ':': fg = 5; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;

            //������
        case '(': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case ')': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case '[': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case ']': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case '{': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case '}': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case '"': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        case '\'': fg = 6; cout << '<' << fg << ',' << ch << '>' << endl; ch = txt[p++]; break;
        }
    }


}

