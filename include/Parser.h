#pragma once

#include "MainHeader.h"

void SkipToBrace(const char*& ptr_on_text);

template <typename type_t>
class Parser
{
    public:
        Parser()  {}
        ~Parser() {}

        static TreeNode<type_t>* CreateTree(const char* file = input_graph_file);

    private:

        static TreeNode<type_t>* GetG(const char*& str);

        static TreeNode<type_t>* GetE(const char*& str);

        static TreeNode<type_t>* GetT(const char*& str);

        static TreeNode<type_t>* GetP(const char*& str);

        static TreeNode<type_t>* GetLeaf(const char*& str);

        static type_t GetN(const char*& str);
};

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::CreateTree(const char* filename)
{
    size_t size = 0;

    const char* text = ReadFile(filename, &size, "r");

    BeginLatexFile(log_filename);

    TreeNode<type_t>* result = GetG(text);

    fprintf(CalcTree<type_t>::log_file, "I \\quad read: \\quad ");

    result->LogToLatex(CalcTree<type_t>::log_file);

    return result;
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetG(const char*& str)
{
    TreeNode<type_t>* res = GetE(str);

    SkipToBrace(str);

    if (*str == 10) //end of file in linux
        return res;

    else
    {
        printf("Error occured! Not all file was readed");
        return nullptr;
    }
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetE(const char*& str)
{
    TreeNode<type_t>* res = new TreeNode<type_t>();

    res->Addleft(GetT(str));

    SkipToBrace(str);

    if (*str == '+' || *str == '-')
    {
        str += StrCmdToNum(str, &(res->number), &(res->type_node));

        SkipToBrace(str);

        res->Addright(GetE(str));
    }

    else
    {
        TreeNode<type_t>* tmp = res;
        res = res->left_child;
        free(tmp);
    }

    return res;
}


template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetT(const char*& str)
{
    TreeNode<type_t>* res = new TreeNode<type_t>();

    SkipToBrace(str);

    res->Addleft(GetP(str));

    SkipToBrace(str);

    if (*str == '*' || *str == '/' || *str == '^')
    {

        str += StrCmdToNum(str, &(res->number), &(res->type_node));

        res->Addright(GetT(str));
    }

    else
    {
        TreeNode<type_t>* tmp = res;
        res = res->left_child;
        free(tmp);
    }

    return res;
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetP(const char*& str)
{
    TreeNode<type_t>* res = nullptr;

    SkipToBrace(str);

    if (*str == '(')
    {
        SkipToBrace(str);
        res = GetE(++str);
        if (*str != ')')
            printf("Error occured, no ')'");

        else
        {
            SkipToBrace(str);
            str++;
        }

        return res;
    }

    res = new TreeNode<type_t>();

    SkipToBrace(str);

    int cmd_len = StrCmdToNum(str, &(res->number), &(res->type_node));

    if (cmd_len != 0 && res->type_node != VARIABLE)
    {
        str += cmd_len;
        res->Addright(GetP(str));
        res->Addleft();
    }

    else
    {
        free(res);
        res = GetLeaf(str);
    }

    return res;
}

template <typename type_t>
TreeNode<type_t>* Parser<type_t>::GetLeaf(const char*& str)
{
    SkipToBrace(str);

    if ((*str >= 'a' && *str <= 'z') ||
        (*str >= 'A' && *str <= 'Z'))
        return new TreeNode<type_t>(*(str++), VARIABLE);

    else
        return new TreeNode<type_t>(GetN(str), VALUE);

}

template <typename type_t>
type_t Parser<type_t>::GetN(const char*& str)
{
    SkipToBrace(str);

    type_t res = 0;

    char cur_char = (*str) - '0';

    int read_comma = 0;

    while ((cur_char >= 0 && cur_char <= 9) || cur_char == ',' - '0' || cur_char == '.' - '0')
    {

        if (cur_char == '.' - '0' || cur_char == ',' - '0') read_comma = 1;

        else if (read_comma != 0)
            res += cur_char / std::pow(10, read_comma++);

        else
        {
            res *= 10;
            res += cur_char;
        }

        cur_char = (*(++str)) - '0';
        SkipToBrace(str);
    }

    return res;
}

void SkipToBrace(const char*& ptr_on_text)
{
    while (*ptr_on_text == '\t' ||
           *ptr_on_text == ' ' )
            ptr_on_text++;
}
