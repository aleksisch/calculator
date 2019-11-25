#ifndef OPERATIONS_H
#define OPERATIONS_H

struct Operators
{
    int num;
    int type;
    char name[STR_LENGTH];
};

        const static Operators operation[] =   {
                                                    {SUB, OPERATION, "-", },
                                                    {ADD, OPERATION, "+"},
                                                    {DIV, OPERATION, "/"},
                                                    {MUL, OPERATION, "*"},
                                                    {SIN, FUNC, "sin"},
                                                    {COS, FUNC, "cos"},
                                                    {LN, FUNC, "ln"},
                                                    {TAN, FUNC, "tan"},
                                                    {POW, OPERATION, "^"},
                                                    {VAR, VARIABLE, "x"},
                                                    {SINH, FUNC, "sinh"},
                                                    {COSH, FUNC, "cosh"},
                                                    {TANH, FUNC, "tanh"},
                                                };


/*template <typename type_t>
class Operations
{
    public:
        const static Operators operation[] =   {
                                                    {SUB, "-"},
                                                    {ADD, "+"},
                                                    {DIV, "/"},
                                                    {MUL, "*"},
                                                    {SIN, "sin"},
                                                    {COS, "cos"},
                                                    {LN, "ln"},
                                                    {TAN, "tan"},
                                                    {POW, "^"},
                                                    {VAR, ""},
                                                    {SINH, "sinh"},
                                                    {COSH, "cosh"},
                                                    {TANH, "tanh"},
                                                }
};*/

#endif // OPERATIONS_H
