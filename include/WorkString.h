#ifndef WORK_STRING_HEADER
#define WORK_STRING_HEADER

#include "../include/MainHeader.h"

template <typename type_t>
type_t ExecuteOperation(type_t first, type_t second, type_t operands)
{
    switch (MyRound(operands))
    {
        case ADD:
            return first + second;
        case SUB:
            return first - second;
        case MUL:
            return first * second;
        case DIV:
            return first / second;

        case LN:
            return log(second);
        case SIN:
            return sin(second);
        case COS:
            return cos(second);
        case TAN:
            return tan(second);
        case POW:
            return pow(first, second);
        case SINH:
            return sinh(second);
        case COSH:
            return cosh(second);
        case TANH:
            return tanh(second);

        default:
            return 0;
    }
}

template <typename type_t>
int StrCmdToNum(const char* command, type_t* number, int* type_cmd)
{
    for (int op = 0; op < NUM_OPER; op++)

        if (strstr(command, operation[op].name) == command)
        {
            *type_cmd = operation[op].type;

            *number = operation[op].num;

            return strlen(operation[op].name);
        }

    if ((*command >= 'a' && *command <= 'z') || (*command >= 'A' && *command <= 'Z'))
    {
        *type_cmd = VARIABLE;
        *number = *command;
        return 1;       ///return current variable length (max 1)
    }

    return 0;
}

template <typename type_t>
const char* NodeDataToStr(TreeNode<type_t>* current)
{

    if (current->right_child != nullptr)    ///keep func arg in right child
    {
        for (int op = 0; op < NUM_OPER; op++)
            if (MyRound(current->number) == operation[op].num)
                return operation[op].name;
        return "Unknown cmd";
    }

    else if (current->type_node ==  VARIABLE)
    {
        char* var_name = new char[2]{};
        var_name[0] = (char) MyRound(current->number);
        return var_name;
    }

    else
    {
        std::string res = std::to_string(current->number);
        return res.c_str();
    }
}

void PrintError(int err_code, const char* function_name)
{
    printf("Error occured in function %s code %d", function_name, err_code);
}

FILE* BeginLatexFile(const char* output)
{
    FILE* file = fopen (output, "w");
    fprintf(file,    "\\documentclass{article}\n\
                        \\usepackage{hyperref}\n\
                        \\begin{document}\n $$");
    return file;
}

void CloseLatexFile(FILE*& file)
{
    if (file == nullptr) return;

    fprintf(file, "$$\n\\end{document}");

    fclose(file);

    char s[STR_LENGTH] = "";

    sprintf(s, "pdflatex %s > /dev/null ", log_filename);

    system(s);

    file = nullptr;
}

char* ReadFile (const char* str, size_t *size, const char* chmod)
{
    FILE *fp = NULL;

    if ((fp = fopen(str, chmod)) == NULL)
    {
        printf("Cannot find text\n");
        system("pause");
        exit(0);
    }

    fseek (fp, 0L, SEEK_END);

    *size = ftell(fp);

    char *text = (char *) calloc(*size + 1, sizeof(char));

    fseek (fp, 0L, SEEK_SET);

    fread (text, sizeof(char), *size, fp);

    text[*size] = '\0';

    fclose (fp);

    return text;
}

#endif
