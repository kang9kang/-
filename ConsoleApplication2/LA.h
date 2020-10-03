#ifndef LEXICAL_ANALYZER_LA_H
#define LEXICAL_ANALYZER_LA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

//����������
static string rsv_words1[] = { "int","double","char","void" ,"float","short","long"};
static string rsv_words2[] = { "if", "else", "for", "while", "do", "return", "break", "continue", "main", "scanf", "printf", "getchar" };

class LA
{
private:
    ifstream fin;
    ostringstream sin;
    string txt; //��Ŷ���Ĵ����
    string word; //��Ź��ɵ��ʵ��ַ���
    int fg; //�ֱ���
    int line; //��¼����
    int num; //�������
    char ch; //���ÿ�ζ�����ַ�
public:
    void show() { cout << txt << endl; };
    LA(const char* s);
    void scan();
};

#endif //LEXICAL_ANALYZER_LA_H