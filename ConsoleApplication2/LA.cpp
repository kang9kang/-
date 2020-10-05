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
    cout << '[' << endl;

    //读取第一个非空字符
    do {
        ch = txt[p++];
        if (ch == 10)
            line++;
    } while (ch == ' ' || ch == 10);
   // cout << "line " << line << " :" << endl;

    while (ch != '\0') {
        while (ch == ' ' || ch == 10) {
            if (ch == 10) {
                line++;
               // cout << "line " << line << " :" << endl;
            }
            ch = txt[p++];
        }

        //处理'_'开头的变量
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
            case 2: cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
            default: break;
            }
            word.clear();
            fg = 0;
        }

        //处理保留字和字母开头的变量
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            fg = 1;
            word += ch;
            ch = txt[p++];
            while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_') {
                word += ch;
                ch = txt[p++];
            }
            for (int i = 0; i < 12; i++) {
                if (/*i == 7 &&*/ word != rsv_words1[i]&&ch!='('&& (word != rsv_words2[i]))
                    fg=2;
                if ( (word == rsv_words1[i])/*||ch=='('|| (word == rsv_words2[i])*/) {
                    cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                    word.clear();
                    break;
                }
                if ((word == rsv_words2[i])/*||ch=='('|| (word == rsv_words2[i])*/) {
                    fg = 7;
                    cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                    word.clear();
                    break;
                }
                if (/*(word == rsv_words1[i])*//*||*/ch=='('/*|| (word == rsv_words2[i])*/) {
                    fg = 8;
                    cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                    word.clear();
                    break;
                    if (/*i == 7 &&*/ word != rsv_words1[i] && ch != '(' && (word != rsv_words2[i]))
                        fg = 2;
                }
            }

            if (fg == 2 && ch != '[') {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                fg = 0;
            }
            if (fg == 2 && ch == '[') {
                fg = 9;
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                fg = 0;
            }
        }

        //处理整数
        if (ch >= '0' && ch <= '9') {
            fg = 3;
            num = 10 * num + (ch - '0');
            ch = txt[p++];
            while (ch >= '0' && ch <= '9') {
                num = 10 * num + (ch - '0');
                ch = txt[p++];
            }
            cout << "{\"type\":\"" << fg << "\",\"value\":" << num << "}," << endl;
            num = 0;
            fg = 0;
        }

        //处理符号
        switch (ch) {
            //处理运算符
        case '+': 
            fg = 4;
            if (txt[p] == '=') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else if (txt[p] == '+') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else if (txt[p] == '-') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else if (txt[p] == '/') {
                while (ch != '\0' && ch != '\n')
                ch = txt[p++];
                break;
            }
            else if (txt[p] == '*') {
                ch = txt[p++];
                do{
                    ch = txt[p++];
                } while (ch != '*');
                ch = txt[p++];
                ch = txt[p++];
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            if (txt[p] == '<') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            if (txt[p] == '>') {
                word += ch;
                ch = txt[p++];
                word += ch;
                ch = txt[p++];
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
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
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << word << "\"}," << endl;
                word.clear();
                break;
            }
            else {
                cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl;
                ch = txt[p++];
                break;
            }

            //处理分隔符
        case ',': fg = 5; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case ';': fg = 5; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case ':': fg = 5; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;

            //处理界符
        case '(': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case ')': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case '[': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case ']': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case '{': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case '}': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case '"': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        case '\'': fg = 6; cout << "{\"type\":\"" << fg << "\",\"value\":\"" << ch << "\"}," << endl; ch = txt[p++]; break;
        }
    }
    cout << ']' << endl;

}

