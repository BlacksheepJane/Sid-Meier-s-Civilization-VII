#include"Letterform.h"

void Letterform::SetColor(const char* color = "white") {
    if (!strcmp("white", color)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    if (!strcmp("red", color)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    if (!strcmp("green", color)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    if (!strcmp("blue", color)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    if (!strcmp("yellow", color)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    if (!strcmp("pink", color)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
    if (!strcmp("cyan", color)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    if (!strcmp("none", color))SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
}


void Letterform::SetFont(int size = 16, const char* name = "����") {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = size;  //���������С��Ĭ�ϴ�СΪ16
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL; //�����ϸ FW_BOLD
    wcscpy_s(cfi.FaceName, L"name");  //�������壬Ĭ������Ϊ���壬�����ǿ���̨���е�
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    //��õ�ǰ����
    //HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_FONT_INFO consoleCurrentFont;
    //GetCurrentConsoleFont(handle, FALSE, &consoleCurrentFont);
}


void Letterform::ReSetFont() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.dwFontSize.Y = 16;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"����");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}