#include "../include/MainHeader.h"

int ExecuteOperation(int first, int second, int operands)
{
    switch (operands)
    {
        case (ADD):
            return first + second;
        case (SUB):
            return first - second;
        case (MUL):
            return first * second;
        case (DIV):
            return first / second;

        case (LN):
            return log(second);
        case (SIN):
            return sin(second);
        case (COS):
            return cos(second);
        case (TAN):
            return tan(second);

        default:
            return 0;
    }
}

int StrCmdToNum(char* command, bool* is_func)
{
    //start operator

    *is_func = false;

    if (strcmp(command, "+") == 0)
        return ADD;

    else if (strcmp(command, "-") == 0)
        return SUB;

    else if (strcmp(command, "*") == 0)
        return MUL;

    else if (strcmp(command, "/") == 0)
        return DIV;

    //start function

    *is_func = true;

    if (strcmp(command, "ln") == 0)
        return LN;

    else if (strcmp(command, "sin") == 0)
        return SIN;

    else if (strcmp(command, "cos") == 0)
        return COS;

    else if (strcmp(command, "tan") == 0)
        return TAN;

    else return UNKNOWN_OPERATION;
}

const char* NodeDataToStr(TreeNode* current)
{
    if (current->left_child != nullptr &&
        current->right_child != nullptr)
    switch ( current->number)
    {
        case ADD:
            return "+";
        case SUB:
            return "-";
        case MUL:
            return "*";
        case DIV:
            return "/";
        case LN:
            return "ln";
        case SIN:
            return "sin";
        case COS:
            return "cos";
        case TAN:
            return "tan";
        default:
            return "unknown cmd";
    }

    std::string res = std::to_string(current->number);
    return res.c_str();
}
