#pragma once

#include "DiffFunc.h"


template <typename type_t>
struct Operators
{
    int num;
    int type;
    char name[STR_LENGTH];
    TreeNode<type_t>* (TreeNode<type_t>::*func)(void);
};

template <typename type_t>
const Operators<type_t> Operation[] = {
                                        {SUB, OPERATION, "-", &TreeNode<type_t>::DiffSub},
                                        {ADD, OPERATION, "+", &TreeNode<type_t>::DiffAdd},
                                        {DIV, OPERATION, "/", &TreeNode<type_t>::DiffDiv},
                                        {MUL, OPERATION, "*", &TreeNode<type_t>::DiffMul},
                                        {SIN, FUNC, "sin",    &TreeNode<type_t>::DiffSin},
                                        {COS, FUNC, "cos",    &TreeNode<type_t>::DiffCos},
                                        {LN, FUNC, "ln",      &TreeNode<type_t>::DiffLn},
                                        {TAN, FUNC, "tan",    &TreeNode<type_t>::DiffTan},
                                        {POW, OPERATION, "^", &TreeNode<type_t>::DiffPow},
                                        {VAR, VARIABLE, "x"},
                                        {SINH, FUNC, "sh",    &TreeNode<type_t>::DiffSinh},
                                        {COSH, FUNC, "ch",    &TreeNode<type_t>::DiffCosh},
                                        {TANH, FUNC, "th",    &TreeNode<type_t>::DiffTanh},
                                     };
