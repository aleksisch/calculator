#ifndef PARSER_H
#define PARSER_H

#include "ReadFile.h"

class Parser
{
    public:
        Parser() {}
        ~Parser() {}

        static int CountFile(const char* file = "input.txt");

        static int CountString(const char* str = "");

    private:

        static int GetG(const char*& str);

        static int GetE(const char*& str);

        static int GetT(const char*& str);

        static int GetP(const char*& str);

        static int GetN(const char*& str);
};

int Parser::CountFile(const char* file)
{
    size_t size = 0;

    char* text = ReadFile(file, &size, "r");

    int res = CountString(text);

    return res;
}

int Parser::CountString(const char* str)
{
    return GetG(str);
}

int Parser::GetG(const char*& str)
{
    int res = GetE(str);

    return res;
    if (*str == 10) //end of line in linux
        return res;
    else
    {
        printf("Error occured! Not all file was readed");
        return -1;
    }
}

int Parser::GetE(const char*& str)
{
    int res = GetT(str);

    while (*str == '+' || *str == '-')
    {
        char last_symb = *str;
        str++;

        if (last_symb == '+')
            res += GetT(str);

        else if (last_symb == '-')
            res -= GetT(str);
    }

    printf("%d %c", res, *str);
    return res;
}

int Parser::GetT(const char*& str)
{
    int res = GetP(str);

    while (*str == '*' || *str == '/')
    {
        char last_symb = *str;
        str++;

        if (last_symb == '*')
            res *= GetP(str);

        else if (last_symb == '/')
            res /= GetP(str);
    }

    printf("T %d %c\n", res, *str);
    return res;
}

int Parser::GetN(const char*& str)
{
    int res = 0;

    char cur_char = (*str) - '0';

    while (cur_char >= 0 && cur_char <= 9 )
    {
        res *= 10;
        res += cur_char;
        cur_char = (*(++str)) - '0';
    }

    printf("N %d %c\n", res, *str);

    return res;
}

int Parser::GetP(const char*& str)
{
    int res = 0;
    if (*str == '(')
    {
        res = GetE(++str);
        if (*str != ')')
            printf("Error occured, no ')'");
        else str++;
    }

    else
        res = GetN(str);

    return res;
}

#endif // PARSER_H
